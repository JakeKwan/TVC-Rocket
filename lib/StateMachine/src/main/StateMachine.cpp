#include "StateMachine.h"

/**
 * @brief Construct a new State Machine:: State Machine object
 *
 */
StateMachine::StateMachine()
{
    Log.notice("Initialising StateMachine");
    currentState = State::TESTING;
    lastRunUs = micros();
}

/**
 * @brief
 *
 */
void StateMachine::setup()
{
    // Calibrate etc.

    navigation.initialise();
    control.initialise(&navigation.attitude.pitch, &navigation.attitude.yaw);
    
    if (!logger.begin("datalog.bin"))
    {
        buzzer.play(errorTune);
        Log.errorln(F("---Logger failed to init---"));
    }

    Log.noticeln(F("Setup completed"));
    buzzer.play(startupTune);
    delay(1000);
}

/**
 * @brief Main loop
 *
 */
void StateMachine::run()
{
    const uint32_t currentUs = micros();
    
    // Run logger when not running navigation / contro
    if (currentUs - lastRunUs >= loopPeriod)
    {
        Log.info("dt:%u", static_cast<unsigned long>(currentUs - lastRunUs));
        nowUs = currentUs;
        lastRunUs = currentUs;

        const Event event = processInput();
        processEvent(event);

        if (currentState == State::TEST_PID)
        {
            log();
        }

        Log.info(F(";" AL_CR));
        return;
    }
    
    logger.service();

}

/**
 * @brief Transition between states using events in transition table. If NONE event, then transition to itself and run main task. If no match found, set to a default state.
 *
 * @param event
 */
void StateMachine::processEvent(Event event)
{
    prevState = currentState;
    auto transition = stateTransition.find({currentState, event});

    if (transition == stateTransition.end())
    {
        Log.errorln("\nE:No matching state found for %s via %s. Transitioning to %s." AL_CR,
                    printState[currentState].c_str(), printEvent[event].c_str(), printState[defaultState].c_str());
        currentState = defaultState; // DEFAULT STATE: CHANGE TO DESCENT FOR DEPLOYMENT
    }
    else
    {
        currentState = transition->second;
    }

    Log.trace("prevState:%S,", printState[prevState].c_str());
    Log.info("event:%S,", printEvent[event].c_str());
    Log.info("state:%S,", printState[currentState].c_str());

    onStateEntry();
}

/**
 * @brief Gets event from environment inputs, e.g. checks if above height or experience g forces.
 * @return Event
 */
Event StateMachine::processInput()
{
    if (buttonA.isPressed())
    {
        return Event::BUTTON_A;
    }

    if (buttonB.isPressed())
    {
        return Event::BUTTON_B;
    }

    switch (currentState) // For more specific requirements, e.g. check different sensor readings per stage
    {
    default:
        break;
    case State::PAD_IDLE:
        break;
    case State::PAD_ARMED:
        break;
    }

    return Event::NONE;
}

void StateMachine::onStateEntry()
/**
 * @brief Main functions to be run each loop.
 * TODO: add scheduler, handle entry function better?
 */
{
    switch (currentState)
    {
    default:
        break;

    case State::TESTING:
        Testing::onEntry(prevState);

        // Reset timer
        // lastRunUs = micros();
        // Log.notice("Testing -> %s", printState[currentState].c_str());
        break;

    case State::TEST_IMU:
        TestIMU::onEntry(prevState);
        break;

    case State::TEST_PID:
        TestPID::onEntry(prevState);
        break;

    case State::PAD_IDLE:
        PadIdle::onEntry(prevState);
        break;

    case State::PAD_ARMED:
        PadArmed::onEntry(prevState);
        break;
    }
}

void StateMachine::log()
{

    const auto controlData = control.telemetry();

    LoggedData record{};
    record.timeUs = nowUs;
    record.roll = navigation.attitude.roll;
    record.pitch = navigation.attitude.pitch;
    record.yaw = navigation.attitude.yaw;
    record.accelX = navigation.accel.x;
    record.accelY = navigation.accel.y;
    record.accelZ = navigation.accel.z;
    record.gyroX = navigation.gyro.x;
    record.gyroY = navigation.gyro.y;
    record.gyroZ = navigation.gyro.z;
    record.xPIDError = controlData.xError;
    record.zPIDError = controlData.zError;
    record.xPIDOutput = controlData.xOutput;
    record.zPIDOutput = controlData.zOutput;
    record.altitude = navigation.bmp.altitude;

    logger.push(record);
}
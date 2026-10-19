#include "StateCommon.h"

Navigation navigation;
Control control;
DataLogger logger;

Buzzer buzzer = Buzzer(BUZZER_PIN);
Tune startupTune = Tune({NOTE_C4, NOTE_E4, NOTE_G4, NOTE_C5}, {4, 4, 4, 4});
Tune oneBeep = Tune({NOTE_C4}, {4});
Tune errorTune = Tune({NOTE_GS4, NOTE_D4}, {4, 4});

/**
 * @brief State transtion table. Currently TEST_SITL goes directly to PAD_IDLE. Button A exits testing; Button B cycles tests. 
 * 
 */
std::map<std::pair<State, Event>, State> stateTransition =
    {
        {{State::TESTING, Event::NONE}, State::TESTING},
        {{State::TESTING, Event::BUTTON_A}, State::PAD_IDLE},
        {{State::TESTING, Event::BUTTON_B}, State::TEST_IMU},
        {{State::TEST_IMU, Event::NONE}, State::TEST_IMU},
        {{State::TEST_IMU, Event::BUTTON_A}, State::TESTING},
        {{State::TEST_IMU, Event::BUTTON_B}, State::TEST_SERVO},
        {{State::TEST_SERVO, Event::NONE}, State::TEST_SERVO},
        {{State::TEST_SERVO, Event::BUTTON_A}, State::TESTING},
        {{State::TEST_SERVO, Event::BUTTON_B}, State::TEST_PID},
        {{State::TEST_PID, Event::NONE}, State::TEST_PID}, 
        {{State::TEST_PID, Event::BUTTON_A}, State::TESTING},
        {{State::TEST_PID, Event::BUTTON_B}, State::TEST_IMU},
        {{State::PAD_IDLE, Event::NONE}, State::PAD_IDLE},
        {{State::PAD_IDLE, Event::BUTTON_A}, State::TESTING},
        {{State::PAD_IDLE, Event::BUTTON_B}, State::PAD_ARMED},
        {{State::PAD_ARMED, Event::NONE}, State::PAD_ARMED}, 
        {{State::PAD_ARMED, Event::BUTTON_B}, State::PAD_IDLE}, 
        {{State::PAD_ARMED, Event::COMMAND}, State::FLIGHT_POWERED},
        {{State::FLIGHT_POWERED, Event::NONE}, State::FLIGHT_POWERED},
        {{State::FLIGHT_POWERED, Event::COMMAND}, State::DESCENT},
        {{State::FLIGHT_POWERED, Event::IMU}, State::FLIGHT_UNPOWERED},
        {{State::FLIGHT_UNPOWERED, Event::NONE}, State::FLIGHT_UNPOWERED},
        {{State::FLIGHT_UNPOWERED, Event::COMMAND}, State::DESCENT},
        {{State::FLIGHT_UNPOWERED, Event::IMU}, State::DESCENT},
        {{State::DESCENT, Event::NONE}, State::DESCENT},
        {{State::DESCENT, Event::IMU}, State::LANDED},
        {{State::LANDED, Event::NONE}, State::LANDED},
    };

std::map<State, String> printState =
    {
        {State::TESTING, "TESTING"},
        {State::TEST_IMU, "TEST_IMU"},
        {State::TEST_PID, "TEST_PID"}, 
        {State::TEST_SERVO, "TEST_SERVO"},
        {State::PAD_IDLE, "PAD_IDLE"},
        {State::PAD_ARMED, "PAD_ARMED"}, 
        {State::FLIGHT_POWERED, "FLIGHT_POWERED"},
        {State::FLIGHT_UNPOWERED, "FLIGHT_UNPOWERED"},
        {State::DESCENT, "DESCENT"}, 
        {State::LANDED, "LANDED"}
    };

std::map<Event, String> printEvent =
    {
        {Event::NONE, "NONE"},
        {Event::BUTTON_A, "BUTTON_A"},
        {Event::BUTTON_B, "BUTTON_B"},
        {Event::COMMAND, "COMMAND"},
        {Event::IMU, "IMU"}};
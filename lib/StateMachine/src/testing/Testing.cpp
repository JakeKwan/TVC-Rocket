#include "Testing.h"

Testing::Testing()
{
    ;
}
void Testing::onEntry(State prevState)
{
    switch (prevState)
    {
    default:
        buzzer.play(oneBeep);
        Log.trace("default");
        break;
    case State::TESTING:
        Log.trace("testing");
        break;
    case State::TEST_PID:
        logger.stop();
    }
    // For now, sitl just goes to pad_idle
    // Log.notice(F("1: Servos; 2: IMU; 3: PID; 4: SITL; "));
    // while (Serial.available() == 0) {} // gets user input
    // return static_cast<State>(Serial.parseInt());
}

void Testing::run()
{
    // Nothing to run
}
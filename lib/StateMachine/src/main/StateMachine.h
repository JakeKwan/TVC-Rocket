/**
 * https://www.youtube.com/watch?v=NTEHRjiAY2I&t=1045s
 * https://www.youtube.com/watch?v=PKPX3-T1Y1I&list=PLO89phzZmnHg4gxvDRyOxUy2wcDKCIlqv&index=5&pp=iAQB
 *
 */

#ifndef STATEMACHINE_H
#define STATEMACHINE_H

#include <Arduino.h>
#include <map>
#include <utility>
#include <string>

#include "StateCommon.h"
#include "testing/Testing.h"
#include "testing/TestIMU.h"
#include "testing/TestPID.h"
#include "testing/TestServo.h"
#include "PadIdle.h"
#include "PadArmed.h"

#include "DataLogger\DataLogger.h"
#include "Button.h"

class StateMachine
{
public:
    StateMachine();

    void setup();
    void run();
    void processEvent(Event event);
    Event processInput();
    void onStateEntry();
    void log();

private:
    State currentState;
    State prevState; 

    // Change for flight?
    State defaultState = State::TESTING;

    uint32_t lastRunUs = 0;
    uint32_t nowUs = 0;
    const uint32_t loopPeriod = 1e6 / MAIN_LOOP_FREQUENCY;


    Button buttonA = Button(BUTTON_A_PIN);
    Button buttonB = Button(BUTTON_B_PIN);
    // state data?
};

#endif // STATEMACHINE_H
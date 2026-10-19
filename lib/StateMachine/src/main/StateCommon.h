#ifndef STATECOMMON_H
#define STATECOMMON_H

#include <Arduino.h>
#include <map>
#include <utility>
#include <string>

#include "Config.h"
#include "Navigation\Navigation.h"
#include "Control\Control.h"
#include "Buzzer\Buzzer.h"

#include "DataLogger\DataLogger.h"

enum class State
{
    TESTING,
    TEST_SERVO, 
    TEST_IMU, 
    TEST_PID,
    PAD_IDLE,
    PAD_ARMED,
    FLIGHT_POWERED,
    FLIGHT_UNPOWERED,
    DESCENT,
    LANDED,
};

enum class TestStates {
    SERVO, 
    IMU, 
    PID
}; 

enum class Event
{
    NONE,
    BUTTON_A,
    BUTTON_B,
    COMMAND,
    IMU,
};
extern Navigation navigation;
extern Control control; 

extern DataLogger logger;

extern std::map<std::pair<State, Event>, State> stateTransition;
extern std::map<State, String> printState;
extern std::map<Event, String> printEvent;

extern Buzzer buzzer; 
extern Tune startupTune; 
extern Tune oneBeep; 
extern Tune errorTune; 

#endif // STATECOMMON_H
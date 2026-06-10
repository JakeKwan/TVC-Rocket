#include <Arduino.h>
#include "RocketConfig.h"
#include "Button.h"
#include "Rocket.h"

class StateMachine {
    public: 
        StateMachine(); 
        void setup(); 
        void stateSetup(); 
        void stateLoop(); 
        void flightStageSetup(); 
        void flightStageLoop(); 
        void eventHandler(); 

        void printSwitchMessage(); 
        
        enum State { // for debugging currently 
            Switcher, 
            State1, // Sensor test 
            State2, // Servo test
            State3, // PID 
            State4, // Staging test 
        };

        enum FlightStage {
            padIdle, 
            poweredFlight, 
            unpoweredFlight, 
            parachuteDescent, 
            landed, 
        };

        State activeState = Switcher; 
        FlightStage activeFlightStage = padIdle;

        Rocket myRocket; 
        Rocket* pMyRocket = &myRocket; 
        IMU* RocketIMU = &myRocket.myIMU; 
        Chrono* StateChrono = &myRocket.myIMU.IMUChrono; // double check this actually makes things better

    private: 
        bool hasCompletedStageSetup = false; 
        bool hasCompletedFlightStageSetup = false; 
        
        Button ModeButton = Button(MODE_BUTTON_PIN); 
        Button *pModeButton = &ModeButton;
        void buttonHandler(); 

};
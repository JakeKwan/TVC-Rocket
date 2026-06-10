#include "State.h"

StateMachine::StateMachine() {
}

void StateMachine::setup() {
    RocketIMU->calibrate(); 
    myRocket.myBuzzer.play(myRocket.myBuzzer.startupTune); 
}

void StateMachine::printSwitchMessage() {
    Serial.print(F("--- Switching to: ")), Serial.print(activeState), Serial.println(F(" ---"));
}

void StateMachine::buttonHandler() {
    if (ModeButton.buttonIsPressed()) {
        activeState = Switcher; 
        activeFlightStage = padIdle; 
        printSwitchMessage(); 
    }
}

void StateMachine::stateSetup() {
    if (!hasCompletedStageSetup) {
        myRocket.myIMU.resetOrientation(); 
        switch(activeState) {
            default: 
                break; 
            case State1: 
                break; 
            case State2: 
                break; 
            case State3: 
                break; 
        }
        hasCompletedStageSetup = true; 
    }
}

void StateMachine::stateLoop() {
    buttonHandler(); 
    stateSetup(); 
    switch(activeState) {
        default: 
            activeState = Switcher; 
            break; 
        case Switcher: 
            int inputState; 
            Serial.println(F("1: Sensors")); 
            Serial.println(F("2: Servo Test")); 
            Serial.println(F("3: PID")); 
            Serial.println(F("4: Staging")); 

            while (Serial.available() == 0) {} // gets user input 
            inputState = Serial.parseInt(); 
            activeState = static_cast<State>(inputState); 
            printSwitchMessage();
            hasCompletedStageSetup = false; 
            StateChrono->reset(); 
            break; 

        case State1: 
            pMyRocket->State1(); 
            break; 

        case State2: 
            pMyRocket->myGimbal.setAngles(0, 0); 
            delay(500); 
            pMyRocket->myGimbal.setAngles(180, 180); 
            delay(500); 
            pMyRocket->myGimbal.setAngles(90, 90); 
            activeState = Switcher; 
            break; 

        case State3: 
            pMyRocket->State2();  
            break; 

        case State4: 
            flightStageLoop(); // can move this out of this loop later for flight? 
            break;
    }
    StateChrono->timekeeper(); // this is important dont lose it
}

void StateMachine::flightStageSetup() { // setups for flight stages 
    if (!hasCompletedFlightStageSetup) {
        switch(activeFlightStage) {
            default: 
                break; 
            case padIdle:  
                myRocket.myIMU.calibrate(); 
                break; 
            case poweredFlight: 
                StateChrono->startFlight();
                break; 
            case unpoweredFlight: 
                break; 
            case parachuteDescent: 
                Serial.println(F("--- Deploying parachutes --- "));
                break; 
            case landed: 
                break; 
        }
        hasCompletedFlightStageSetup = true;
    }
}

void StateMachine::flightStageLoop() { // main flight loop 
    flightStageSetup(); 
    switch(activeFlightStage) {
        default: 
            break; 
        case padIdle: // todo: put testing modes here or in another stage?
            pMyRocket->navigate(); 
            pMyRocket->telemetry(); 
            break; 
        case poweredFlight: 
            pMyRocket->navigate();
            pMyRocket->control();
            pMyRocket->telemetry(); 
            break; 
        case unpoweredFlight: // currently not used  
            break; 
        case parachuteDescent: 
            pMyRocket->navigate(); 
            pMyRocket->telemetry(); 
            break; 
        case landed: 
            pMyRocket->telemetry(); 
            break;    
    }
    eventHandler(); 
}

void StateMachine::eventHandler() { // what to check at each stage, so that we can move to next stage
    switch (activeFlightStage) {
        default: 
            break; 
        case padIdle: 
            if (myRocket.isLiftingOff()) {
                activeFlightStage = poweredFlight; 
                hasCompletedFlightStageSetup = false; 
            }
            break; 
        case poweredFlight: 
            if (micros() - StateChrono->flightStart >= POWERED_FLIGHT_TIME*1e6) { // swap micros with chrono time ?
                activeFlightStage = parachuteDescent; 
                hasCompletedFlightStageSetup = false; 
            }
            break; 
        case unpoweredFlight: 
            break; 
        case parachuteDescent: // need to check that there has been no movement with moving window 
            break; 
        case landed: // not needed 
            break; 
    }

}

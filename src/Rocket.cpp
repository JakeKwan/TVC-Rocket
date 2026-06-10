#include "Rocket.h"

void Rocket::navigate() {
    myIMU.measureGyros(); 
    myIMU.measureAccel(); 
    myIMU.measureOrientation(); 
}

void Rocket::control() {
    float yAngle = yPID.getPIDOutput(pOrient->y) * RAD_TO_DEG + PID_OFFSET; 
    float zAngle = zPID.getPIDOutput(pOrient->z) * RAD_TO_DEG + PID_OFFSET; 
    myGimbal.setAngles(yAngle, zAngle); 
    Serial.print(yAngle); Serial.print(", "), Serial.print(zAngle); Serial.print(" | "); 
}

void Rocket::telemetry(bool printValues) {
    //TODO: write to sd card 
    mySDCard.logData(); 
    if (printValues) {
        Serial.print("Altitude: "), Serial.print(myBMP.getAltitude()), Serial.print(" | "); //idk why this is so slow 
    }
}

bool Rocket::isLiftingOff() { // to do : make this a moving window of average accel 
    if (myIMU.accel.x > LIFTOFF_THRESHOLD) {
        Serial.println("---Launch detected---");
        return true; 
    } else {
        return false; 
    }
}

void Rocket::State1() { // sensor test 
    navigate(); 
    pGyro->print(); 
    pAccel->print(); 
    pOrient->print(); 
}

void Rocket::State2() { // pid test 
    navigate(); pGyro->print(); 
    control(); 
}
#include "RocketConfig.h"
#include "PID.h"

/**
 * @brief Construct a new PID::PID object
 * 
 * @param kP Proportional gain. 
 * @param kI Integral gain. 
 * @param kD Derivative gain. 
 * @param saturation Output clamped to +ve and -ve of saturation. 
 * @param setpoint PID target.
 */
PID::PID(float kP, float kI, float kD, float saturation, float setpoint, unsigned long* pdt ) {
    this->kP = kP; 
    this->kI = kI; 
    this->kD = kD; 
    this->setpoint = setpoint; 
    this->saturation = saturation*DEG_TO_RAD; 
    this->pdt = pdt; 
}

float PID::getPIDOutput(float input) { 
    dt = *pdt * 1e-6;
    
    error = input - setpoint; 
    
    pError = error; 
    iError += error * dt; 
    dError = (error - previousError) / dt; 
    // Serial.print("error: "), Serial.print(error), Serial.print(", "), Serial.print(pError), Serial.print(", "), Serial.print(iError), Serial.print(", "), Serial.print(dError);
    
    output = kP * pError + kI * iError + kD * dError;

    Serial.print("Output: "), Serial.print(output), Serial.print(" | "); 
    
    previousError = error; 
    
    if (output > saturation) {
        output = saturation; 
    } else  if (output < -saturation) {
        output = -saturation; 
    }
    
    return output; 
}

#include "Arduino.h"


class PID {
    public: 
        PID(float kP, float kI, float kD, float saturation, float setpoint, unsigned long *pdt ); 
        float getPIDOutput(float input); 
        unsigned long* pdt; 

    private:

        float setpoint; 

        float dt; 
        
        float kP = 0.0f, kI = 0.0f, kD = 0.0f; 
        float saturation = 0.0f; 

        float error = 0.0f, previousError = 0.0f; 
        float pError = 0.0f, iError = 0.0f, dError = 0.0f; 

        float output; 
}; 
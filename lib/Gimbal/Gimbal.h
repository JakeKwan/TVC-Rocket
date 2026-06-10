#include <Arduino.h>
#include <PWMServo.h>
#include "RocketConfig.h"

class Gimbal { 
    public: 
        Gimbal(int xPin, int yPin) {
            xServo.attach(xPin); 
            yServo.attach(yPin); 
        };

        void setAngles(float y, float z) { // taking angle from 0 to 180 degrees // by convention x is roll axis. 
            xServo.write(y); 
            yServo.write(z); 
        }

    private:
        PWMServo xServo; 
        PWMServo yServo; 

};
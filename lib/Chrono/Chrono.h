#include <Arduino.h>
#include "RocketConfig.h"

class Chrono {
    private: 
        const unsigned long loopPeriod = 1e6 / LOOP_FREQUENCY; //micros
    public: 
        Chrono() {}
        unsigned long currentTime = 0.0; //micros
        unsigned long previousTime = 0.0; //micros
        unsigned long dt = 0.0; 
        unsigned long* pdt = &dt; //micros
        unsigned long flightStart = 0.0; 
        unsigned long flightTime = 0.0; 
        
        void startFlight() {
            flightStart = micros(); 
            Serial.print("Flight time started at: "), Serial.println(flightStart); 
        }

        void timekeeper() {
            *pdt = currentTime - previousTime; 
            previousTime = currentTime; 
            flightTime = currentTime - flightStart; 
            Serial.print("dt: "), Serial.println(*pdt); 
            
            while (micros() - currentTime < loopPeriod) {}
            currentTime = micros(); 
        }

        void reset() {
            currentTime = micros(); 
            previousTime = currentTime - loopPeriod; 
        }  
};
#include "RocketConfig.h"
#include "IMU.h"
#include "Gimbal.h"
#include "PID.h"
#include "BMP.h"
#include "SDCard.h"
#include "Buzzer.h"

class Rocket {
    public: 
        Rocket() {}; 
        void navigate(); 
        void control(); 
        void telemetry(bool printValues = false); 

        void State1();
        void State2();

        bool isLiftingOff();          

        IMU myIMU; 
        BMP myBMP; 
        Gimbal myGimbal = Gimbal(Y_SERVO_PIN, Z_SERVO_PIN); 
        PID yPID = PID(yKP, yKI, yKD, SATURATION, SETPOINT, myIMU.IMUChrono.pdt);  
        PID zPID = PID(zKP, zKI, zKD, SATURATION, SETPOINT, myIMU.IMUChrono.pdt);  
        
        unsigned long* pFlightTime = &myIMU.IMUChrono.currentTime; 
        Vector3D* pGyro = myIMU.pGyro; 
        Vector3D* pAccel = myIMU.pAccel;
        Vector3D* pOrient = myIMU.pOrient;

        SDCard mySDCard = SDCard(pFlightTime, pGyro, pAccel, pOrient); 
        Buzzer myBuzzer; 
    };
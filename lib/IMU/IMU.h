#include <Adafruit_MPU6050.h>
#include "RocketMaths.h"
#include "Chrono.h"

/* 
SCL: 19
SDA: 18
*/

class IMU {
    public: 
        IMU(); 
        Chrono IMUChrono; 
        void measureGyros(); 
        void measureAccel(); 
        void measureOrientation(); 
        void calibrate();
        void resetOrientation(); 

        Vector3D gyro; 
        Vector3D accel; 
        Vector3D orient; 

        Vector3D* pGyro = &gyro; 
        Vector3D* pAccel = &accel; 
        Vector3D* pOrient = &orient; 

    private: 
        Adafruit_MPU6050 mpu; 
        Adafruit_Sensor *mpuGyro; 
        Adafruit_Sensor *mpuAccel; 
        sensors_event_t gyroSensorEvent; 
        sensors_event_t accelSensorEvent; 

        Vector3D gyroOffset; 
        Vector3D accelOffset; 
};

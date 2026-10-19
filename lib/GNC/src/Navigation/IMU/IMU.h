#ifndef IMU_H
#define IMU_H

#include <Adafruit_MPU6050.h>
#include "Config.h"
#include "Maths.h"

class IMU
{
public:
    IMU();
    /**
     * @brief Get gyros in rads-1.
     *
     * @return Vec3D
     */
    inline Vec3D getGyros()
    {
        mpuGyro->getEvent(&gyroSensor_e);
        return Vec3D(
            gyroSensor_e.gyro.x + gyroOffset.x,
            gyroSensor_e.gyro.y + gyroOffset.y,
            gyroSensor_e.gyro.z + gyroOffset.z);
    }
    /**
     * @brief Get acceleration in ms^-2.
     *
     * @return Vec3D
     */
    inline Vec3D getAccel()
    {
        mpuAccel->getEvent(&accelSensor_e);
        return Vec3D(
                   accelSensor_e.acceleration.x + accelOffset.x,
                   accelSensor_e.acceleration.y + accelOffset.y,
                   accelSensor_e.acceleration.z + accelOffset.z) *
               -1; // idk why this is here 
    }

private:
    Adafruit_MPU6050 mpu;
    Adafruit_Sensor *mpuGyro;
    Adafruit_Sensor *mpuAccel;
    sensors_event_t gyroSensor_e;
    sensors_event_t accelSensor_e;

    const Vec3D gyroOffset = Vec3D(0.050000, 0.030117, 0.004097);
    const Vec3D accelOffset = Vec3D(-0.319883, 0.067320, -0.320777); // calibrated in my head !
};

#endif
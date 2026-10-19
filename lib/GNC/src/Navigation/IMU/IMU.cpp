#include "IMU.h"

IMU::IMU() {
    Wire.begin();
    if (!mpu.begin()) {
        Log.warningln(F("N: MPU failed to init."));
    }

    mpuGyro = mpu.getGyroSensor(); 
    mpuAccel = mpu.getAccelerometerSensor();

    Log.noticeln(F("MPU found!"));
    mpuGyro->printSensorDetails();
    mpuAccel->printSensorDetails();
}

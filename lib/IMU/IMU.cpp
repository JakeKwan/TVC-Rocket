#include "IMU.h"

IMU::IMU() {
    Wire.begin(); 
    Wire.setClock(400000); 
    if (!mpu.begin()) {
        Serial.println(F("Failed to load MPU6050")); 
    }
    
    mpuGyro = mpu.getGyroSensor(); 
    mpuAccel = mpu.getAccelerometerSensor(); 
    
    Serial.println(F("MPU6050 found!"));
    // mpuGyro->printSensorDetails(); 
    // mpuAccel->printSensorDetails(); 
}

void IMU::calibrate() {
    Serial.println(F("Calibrating..."));
    orient = Vector3D();
    gyroOffset = Vector3D();
    accelOffset = Vector3D();
    Vector3D gyroSum = Vector3D();
    Vector3D accelSum = Vector3D();

    const float count = 100.0f; 
    for (int n = 0; n <= count; n++) {
        measureGyros();
        measureAccel();
        gyroSum += gyro; 
        accelSum += accel; 
    }
    gyroOffset = (gyroSum * (-1.0f/count)); 
    accelOffset = (accelSum * (-1.0f/count)); 
    Serial.print(F("Gyro offset: ")), gyroOffset.print(); 
    Serial.print(F("Accel offset: ")), accelOffset.print(); Serial.println(""); 

}

void IMU::measureGyros() {
    mpuGyro->getEvent(&gyroSensorEvent); 
    gyro = Vector3D(
        gyroSensorEvent.gyro.x + gyroOffset.x, 
        gyroSensorEvent.gyro.y + gyroOffset.y, 
        gyroSensorEvent.gyro.z + gyroOffset.z
    );
}

void IMU::measureAccel() {
    mpuAccel->getEvent(&accelSensorEvent); 
    accel = Vector3D(
        accelSensorEvent.acceleration.x + accelOffset.x, 
        accelSensorEvent.acceleration.y + accelOffset.y, 
        accelSensorEvent.acceleration.z + accelOffset.z
    );
}
void IMU::measureOrientation() {
    orient += ((gyro * *IMUChrono.pdt) * 1e-6); 
}

void IMU::resetOrientation() {
    orient = Vector3D(); 
}

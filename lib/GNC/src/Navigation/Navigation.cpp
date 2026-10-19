#include "Navigation.h"

/**
 * @brief Construct a new Navigation:: Navigation object
 *
 */
Navigation::Navigation()
{

    // nowUs = micros();
    // lastRunUs = nowUs - (1e6 / NAV_LOOP_FREQUENCY); // stinky thing to stop big jumpy
}

Navigation::~Navigation()
{
    sensorFusion::terminate();
}

void Navigation::initialise() {
    sensorFusion::initialize();
}

/**
 * @brief Fuses accelerometer and gyroscope measurements with a kalman filter
 * TODO: swap the roll and yaw outputs? or make it configurable; tune filter covariances; altimeter?
 */
void Navigation::filter()
{
    // INPUT
    accel = imu.getAccel();
    gyro = imu.getGyros();

    filterInput.accel[0] = static_cast<real_T>(accel.x);
    filterInput.accel[1] = static_cast<real_T>(accel.y);
    filterInput.accel[2] = static_cast<real_T>(accel.z);

    filterInput.gyro[0] = static_cast<real_T>(gyro.x);
    filterInput.gyro[1] = static_cast<real_T>(gyro.y);
    filterInput.gyro[2] = static_cast<real_T>(gyro.z);

    FUSE.setExternalInputs(&filterInput);

    FUSE.step();
    
    // OUTPUT: change rpy here.
    filterOutput = FUSE.getExternalOutputs();

    attitude.roll = static_cast<float>(filterOutput.angles[0]);
    attitude.pitch = static_cast<float>(filterOutput.angles[1]);
    attitude.yaw = static_cast<float>(filterOutput.angles[2]);

    rotators.qw = static_cast<float>(filterOutput.rotators[0]);
    rotators.qx = static_cast<float>(filterOutput.rotators[1]);
    rotators.qy = static_cast<float>(filterOutput.rotators[2]);
    rotators.qz = static_cast<float>(filterOutput.rotators[3]);
}

/**
 * @brief Main navigation function to update ang values every loop.
 * TODO: maybe change the run frequency
 */
void Navigation::step()
{
    filter();
    bmp.update();
}
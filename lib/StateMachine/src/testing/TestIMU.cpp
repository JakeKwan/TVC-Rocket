#include "TestIMU.h"

TestIMU::TestIMU()
{
    ;
}

void TestIMU::run()
{
    navigation.step();
    const float &roll = navigation.attitude.roll * RAD_TO_DEG;
    const float &pitch = navigation.attitude.pitch * RAD_TO_DEG;
    const float &yaw = navigation.attitude.yaw * RAD_TO_DEG;
    Log.notice("RPY:%F %F %F;", roll, pitch, yaw);
    // const float &qw = navigation.rotators.qw;
    // const float &qx = navigation.rotators.qx;
    // const float &qy = navigation.rotators.qy;
    // const float &qz = navigation.rotators.qz;
    // Log.notice("q:%F %F %F %F;", qw, qx, qy, qz);

    // Vec3D accel = navigation.imu.getAccel();
    // Vec3D gyro = navigation.imu.getGyros();
    // Log.notice("accel:"), accel.print();
    // Log.notice("gyro:"), gyro.print();

    Log.notice("Alt:%F;", navigation.bmp.altitude);
}

void TestIMU::onEntry(State prevState)
{
    switch (prevState)
    {
    default:
        // navigation.reset();
        Log.notice("NAVIGATION RESET");
        break;
    case State::TEST_IMU:
        run();
        break;
    }
}
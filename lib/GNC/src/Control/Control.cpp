#include "Control.h"

Control::Control() {};

Control::~Control() {};

void Control::initialise(float *pXAng, float *pZAng)
{
    XPID.initialise(xKP, xKI, xKD, PID_FILTER, -X_SATURATION + X_SETPOINT, X_SATURATION + X_SETPOINT, X_SETPOINT, X_AXIS_SENSOR_OFFSET);
    ZPID.initialise(zKP, zKI, zKD, PID_FILTER, -Z_SATURATION + Z_SETPOINT, Z_SATURATION + Z_SETPOINT, Z_SETPOINT, Z_AXIS_SENSOR_OFFSET);

    XPID.setInput(pXAng); // IMU angle inputs
    ZPID.setInput(pZAng);

    GIMBAL.initialise(X_SERVO_PIN, Z_SERVO_PIN, &X_PID_OUT, &Z_PID_OUT);
    GIMBAL.test();
};

/**
 * @brief Step control
 * TOOD: map outputs to appropriate range
 */
void Control::step()
{
    XPID.step();
    ZPID.step();

    X_PID_OUT = XPID.output;
    Z_PID_OUT = ZPID.output;
    GIMBAL.update();
};

Control::ControlTelemetry Control::telemetry()
{
    return {XPID.error,
            ZPID.error,
            XPID.output,
            ZPID.output};
}
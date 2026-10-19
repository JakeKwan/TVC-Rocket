#include "Gimbal.h"

Gimbal::Gimbal() {};

/**
 * @brief Initialise gimbal 
 * 
 * @param xPin 
 * @param zPin 
 * @param pXAng 
 * @param pZAng 
 */
void Gimbal::initialise(uint8_t xPin, uint8_t zPin, float *pXAng, float *pZAng)
{
    this->pXAng = pXAng;
    this->pZAng = pZAng;
    XServo.attach(xPin);
    ZServo.attach(zPin);

}

/**
 * @brief Update gimbal angle
 *
 * @param x Degrees, [0, 180]
 * @param z
 * @return * void
 */
void Gimbal::update()
{
    //TODO: convert input from pid to servo (i.e. map inputs to correct range)
    const float x = *pXAng * RAD_TO_DEG ; 
    const float z = *pZAng * RAD_TO_DEG ; 
    XServo.write(x + 90.0f);
    ZServo.write(z + 90.0f);

    // remove
    Log.trace("xPID:%F;", x);
    Log.trace("zPID:%F;", z);
}

void Gimbal::center()
{
    XServo.write(90);
    ZServo.write(90);
}

void Gimbal::test() 
{
    float xLow = 90 - X_SATURATION * RAD_TO_DEG; 
    float xHigh = 90 + X_SATURATION * RAD_TO_DEG; 
    for (float angle = xLow; angle <= xHigh; angle += 1) 
    {
        XServo.write(angle); 
        delay(50);
    }
    XServo.write(90); 

    float zLow = 90 - Z_SATURATION * RAD_TO_DEG; 
    float zHigh = 90 + Z_SATURATION * RAD_TO_DEG; 
    for (float angle = zLow; angle <= zHigh; angle += 1) 
    {
        ZServo.write(angle); 
        delay(50); 
    }
    ZServo.write(90);
}

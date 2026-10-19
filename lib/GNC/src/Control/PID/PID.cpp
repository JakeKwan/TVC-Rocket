#include "PID.h"

PID::PID() {};

PID::~PID() {};

/**
 * @brief Set PID parameters.
 * TODO: add filtering? do we want to keep the constrain in here or change it elsewhere
 *
 * @param kP
 * @param kI
 * @param kD
 * @param f Filter coefficient from [0, 1)
 * @param floor
 * @param ceiling
 * @param setpoint
 */
void PID::initialise(float kP, float kI, float kD, float f,
                     float floor, float ceiling, float setpoint, float offset)
{
    this->kP = kP;
    this->kI = kI;
    this->kD = kD;
    this->filter = f;
    this->floor = floor;
    this->ceiling = ceiling;
    this->setpoint = setpoint;
    this->offset = offset; 

    nowUs = micros();
    lastRunUs = nowUs;
}

void PID::setInput(const float *pInput)
{
    this->pInput = pInput;
};

void PID::step()
{
    if (pInput == nullptr)
    {
        return;
    }

    lastRunUs = nowUs;
    nowUs = micros();
    dtS = (nowUs - lastRunUs) * (1e-6);

    error = *pInput - setpoint + offset;

    pError = error;
    iError += error * dtS;
    dError = dtS > 0 ? (error - prevError) / dtS : 0.0f;
    // Log.trace("dt:%F;",dtS);

    output = constrain(kP * pError + kI * iError + kD * dError, floor, ceiling);
    output = filter * prevOutput + (1 - filter) * output;

    prevOutput = output;
    // Log.trace("err:%F;",iError);
    prevError = error;
}
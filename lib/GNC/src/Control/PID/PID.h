#ifndef PID_H
#define PID_H

#include "Config.h"
#include "Maths.h"

class PID
{
public:
    PID();
    ~PID();
    void initialise(float kP, float kI, float kD, float f,
                    float floor, float ceiling, float setpoint, float offset);
    void setInput(const float *pInput);
    void step();

    float output;
    float error = 0.0f;

private:
    float offset;
    float prevOutput; // for filtering?
    const float *pInput = nullptr;
    float setpoint;

    float kP = 0.0f;
    float kI = 0.0f;
    float kD = 0.0f;
    float filter = 0.0f;
    float floor = 0.0f;
    float ceiling = 0.0f;

    float prevError = 0.0f;
    float pError = 0.0f;
    float iError = 0.0f;
    float dError = 0.0f;

    double dtS;
    double nowUs, lastRunUs;
};

#endif
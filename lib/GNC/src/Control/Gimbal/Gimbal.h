#include <PWMServo.h>
#include "Config.h"
#include "Control\PID\PID.h"

class Gimbal
{
public:
    Gimbal();
    void initialise(uint8_t xPin, uint8_t zPin, float *pXAng, float *pZAng);
    void update();
    void center(); 
    void test(); 

private:
    float *pXAng = nullptr;
    float *pZAng = nullptr;
    PWMServo XServo;
    PWMServo ZServo;
};

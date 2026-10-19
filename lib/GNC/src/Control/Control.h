#include "Config.h"
#include "Control\Gimbal\Gimbal.h"

class Control
{
public:
    Control();
    ~Control();
    void initialise(float *P_PID_XANG_IN, float *P_PID_ZANG_IN);
    void step();
    
    struct ControlTelemetry {
        float xError; 
        float zError; 
        float xOutput; 
        float zOutput;
    };
    
    ControlTelemetry telemetry();

private:
    Gimbal GIMBAL;
    PID XPID; 
    PID ZPID;

    float X_PID_OUT = 0; 
    float Z_PID_OUT = 0;
};
#include "IMU\IMU.h"
#include "Altimeter\Altimeter.h"
#include "SensorFusion\fusion\sensorFusion_ert_rtw\sensorFusion.h"

/**
 * @brief Navigation: where am i???!?!?!
 * TODO: calibration, reset imu for pad, altimeter, logging 
 */
class Navigation
{
public:
    Navigation();
    ~Navigation();

    void initialise();

    IMU imu;
    BMP bmp;

    Vec3D accel; 
    Vec3D gyro;

    struct Attitude {
        float roll = 0.0f;
        float pitch = 0.0f;
        float yaw = 0.0f;
    } attitude;

    struct Rotators {
        float qw = 1.0f;
        float qx = 0.0f;
        float qy = 0.0f;
        float qz = 0.0f;
    } rotators; 

    // void reset();
    void filter(); // updates ang using a kalman filter from accel Ang nd gyro Ang
    void step();
    
    private:
    sensorFusion FUSE;
    
    // Inport and outport structs 
    sensorFusion::ExtU_sensorFusion_T filterInput{};
    sensorFusion::ExtY_sensorFusion_T filterOutput{};

    // uint32_t lastRunUs, nowUs, dt;
};

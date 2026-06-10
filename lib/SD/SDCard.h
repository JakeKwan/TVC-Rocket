#include <SD.h> 
#include <SPI.h>
#include "RocketMaths.h"

/* 
SCK - 13
MISO - 12
MOSI - 11
CS - 10
*/

class SDCard {
    public: 
        SDCard(unsigned long* pFlightTime, Vector3D* pGyro, Vector3D* pAccel, Vector3D* pOrient);  

        void logData(); 
    
    private: 
        const int chipSelect = BUILTIN_SDCARD; 
        unsigned long* pFlightTime; Vector3D* pGyro; Vector3D* pAccel; Vector3D* pOrient;
};

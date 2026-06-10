#include <BMP.h>
#include "RocketConfig.h"

BMP::BMP() {
    if (!bmp.begin()) {
        Serial.println(F("Could not initialise BMP180."));
    }

}

float BMP::getAltitude() {
    return bmp.readAltitude(SEA_LEVEL_PRESSURE); 
}
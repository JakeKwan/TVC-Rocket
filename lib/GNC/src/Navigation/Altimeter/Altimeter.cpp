#include "Altimeter.h"

BMP::BMP() {
    if (!bmp.begin(BMP085_ULTRALOWPOWER)) {
        Log.warningln(F("BMP not initialised"));
    }
}

void BMP::update() {
    // temperature = bmp.readTemperature();
    altitude = bmp.readAltitude(SEA_LEVEL_PRESSURE); 
    // pressure = bmp.readPressure();
}
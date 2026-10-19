#ifndef ALTIMETER_H
#define ALTIMETER_H

#include <Adafruit_BMP085.h>
#include "Config.h"

class BMP
{
public:
    BMP();
    void update();
    float temperature;
    float pressure;
    float altitude;

private:
    Adafruit_BMP085 bmp;
};

#endif
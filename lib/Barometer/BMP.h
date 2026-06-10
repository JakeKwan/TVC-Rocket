#include <Adafruit_BMP085.h>

class BMP {
    public: 
        BMP(); 
        float getAltitude(); 
    private: 
        Adafruit_BMP085 bmp; 
    
};

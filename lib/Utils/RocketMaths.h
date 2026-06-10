#include <Arduino.h>
#include <Adafruit_Sensor.h>
#include <math.h>

#ifndef ROCKETMATHS_H
#define ROCKETMATHS_H

inline float clamp(float input, float min, float max) {
    if (input > max) {
        input = max; 
    } else if (input < min) {
        input = min; 
    }
    return input; 
}

struct Vector3D {
    float x, y, z;
    float *pX = &x, *pY = &y, *pZ = &z; 
    Vector3D(float x, float y, float z): x{x}, y{y}, z{z} {}
    Vector3D(): x(0), y(0), z(0) {}
    Vector3D(sensors_vec_t vec): x{vec.x}, y{vec.y}, z{vec.z} {};

    // Addition 
    Vector3D operator + (Vector3D vec) {
        Vector3D P; 
        P.x += vec.x; 
        P.y += vec.y; 
        P.z += vec.z; 
        return P;
    }

    // Scalar multiplication
    Vector3D operator * (float d) {
        Vector3D P; 
        P.x = x * d; 
        P.y = y * d; 
        P.z = z * d; 
        return P; 
    }
    
    // Integration
    Vector3D& operator += (Vector3D Vector) { 
        x += Vector.x; 
        y += Vector.y; 
        z += Vector.z; 
        return *this; 
    }
    void print() {
        Serial.print(this->x), Serial.print(F(", ")); 
        Serial.print(this->y), Serial.print(F(", "));
        Serial.print(this->z), Serial.print(F(" | ")); 
    }
};

#endif
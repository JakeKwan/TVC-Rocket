#include <Arduino.h>
#include <Adafruit_Sensor.h>
#include <math.h>

#ifndef MATHS_H
#define MATHS_H

struct Vec3D
{
    float x, y, z;
    Vec3D(float x, float y, float z) : x{x}, y{y}, z{z} {}
    Vec3D() : x(0), y(0), z(0) {}
    Vec3D(sensors_vec_t vec) : x{vec.x}, y{vec.y}, z{vec.z} {};

    // Addition
    Vec3D operator+(Vec3D vec)
    {
        Vec3D P;
        P.x += vec.x;
        P.y += vec.y;
        P.z += vec.z;
        return P;
    }

    // Scalar multiplication
    Vec3D operator*(float d)
    {
        Vec3D P;
        P.x = x * d;
        P.y = y * d;
        P.z = z * d;
        return P;
    }

    // Elementwise multiplication. idk what to use mate
    Vec3D operator<<(Vec3D vec)
    {
        Vec3D P;
        P.x *= vec.x;
        P.y *= vec.y;
        P.z *= vec.z;
        return P;
    };

    // Integration
    Vec3D &operator+=(Vec3D Vector)
    {
        x += Vector.x;
        y += Vector.y;
        z += Vector.z;
        return *this;
    }

    static Vec3D clamp(Vec3D vec, float low, float high)
    {
        return Vec3D(constrain(vec.x, low, high),
                     constrain(vec.y, low, high),
                     constrain(vec.z, low, high));
    }

    void print()
    {
        Log.notice("%F %F %F;", this->x, this->y, this->z);
    }
};

// struct Quat
// {
//     float w, x, y, z;
//     Quat(float w, float x, float y, float z) : w{w}, x{x}, y{y}, z{z} {}; 
//     Quat() : w(0), x(0), y(0), z(0) {}; 

// };
#endif
#ifndef DISABLE_FS_H_WARNING
#define DISABLE_FS_H_WARNING
#endif
#pragma once

#include <SdFat.h>
#include <RingBuf.h>
#include "Config.h"

struct LoggedData 
{
    uint32_t timeUs; 

    float accelX; 
    float accelY; 
    float accelZ; 

    float gyroX; 
    float gyroY; 
    float gyroZ; 

    float roll; 
    float pitch; 
    float yaw; 

    float xPIDError; 
    float zPIDError; 
    float xPIDOutput; 
    float zPIDOutput;

    float altitude; 
};
static_assert(sizeof(LoggedData) == 60);

class DataLogger
{
public:
    bool begin(const char *filename); 
    bool push(const LoggedData &record);
    void service(); 
    void stop();

    uint32_t droppedRecords() const; 

private:
    static constexpr size_t BufferBytes = 512 * 32; 

    SdFs sd; 
    FsFile file;
    RingBuf<FsFile, BufferBytes> buffer;

    uint32_t dropped = 0;

};

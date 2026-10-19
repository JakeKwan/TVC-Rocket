//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// File: sensorFusion_types.h
//
// Code generated for Simulink model 'sensorFusion'.
//
// Model version                  : 1.12
// Simulink Coder version         : 25.2 (R2025b) 28-Jul-2025
// C/C++ source code generated on : Wed Aug 26 10:35:09 2026
//
// Target selection: ert.tlc
// Embedded hardware selection: ARM Compatible->ARM Cortex
// Code generation objectives: Unspecified
// Validation result: Not run
//
#ifndef sensorFusion_types_h_
#define sensorFusion_types_h_
#include "rtwtypes.h"

// Custom Type definition for MATLAB Function: '<Root>/readIMU'
#ifndef struct_quaternion_sensorFusion_T
#define struct_quaternion_sensorFusion_T

struct quaternion_sensorFusion_T
{
    real_T a;
    real_T b;
    real_T c;
    real_T d;
};

#endif                                 // struct_quaternion_sensorFusion_T

#ifndef struct_fusion_internal_frames_NED_se_T
#define struct_fusion_internal_frames_NED_se_T

struct fusion_internal_frames_NED_se_T
{
    int32_T __dummy;
};

#endif                                // struct_fusion_internal_frames_NED_se_T

#ifndef struct_cell_wrap_3_sensorFusion_T
#define struct_cell_wrap_3_sensorFusion_T

struct cell_wrap_3_sensorFusion_T
{
    uint32_T f1[8];
};

#endif                                 // struct_cell_wrap_3_sensorFusion_T

#ifndef struct_imufilter_sensorFusion_T
#define struct_imufilter_sensorFusion_T

struct imufilter_sensorFusion_T
{
    int32_T isInitialized;
    boolean_T TunablePropsChanged;
    cell_wrap_3_sensorFusion_T inputVarSize[2];
    real_T AccelerometerNoise;
    real_T GyroscopeNoise;
    real_T GyroscopeDriftNoise;
    real_T LinearAccelerationNoise;
    real_T LinearAccelerationDecayFactor;
    real_T pQw[81];
    real_T pQv[9];
    quaternion_sensorFusion_T pOrientPost;
    boolean_T pFirstTime;
    fusion_internal_frames_NED_se_T pRefSys;
    real_T pSensorPeriod;
    real_T pKalmanPeriod;
    real_T pGyroOffset[3];
    real_T pLinAccelPost[3];
    real_T pInputPrototype[3];
};

#endif                                 // struct_imufilter_sensorFusion_T
#endif                                 // sensorFusion_types_h_

//
// File trailer for generated code.
//
// [EOF]
//

//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// File: sensorFusion.h
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
#ifndef sensorFusion_h_
#define sensorFusion_h_
#include <cmath>
#include "rtwtypes.h"
#include "SensorFusion\R2025b\simulink\include\rtw_continuous.h"
#include "SensorFusion\R2025b\simulink\include\rtw_solver.h"
#include "rt_nonfinite.h"
#include "sensorFusion_types.h"

extern "C"
{

#include "rtGetNaN.h"

}

// Class declaration for model sensorFusion
class sensorFusion final
{
    // public data and function members
  public:
    // Block signals (default storage)
    struct B_sensorFusion_T
    {
        real_T Ppost[81];
        real_T H[27];
        real_T K[27];
        real_T H_m[27];
        real_T h1[9];
        real_T h1_c[9];
        real_T c_x[9];
        real_T x[4];
        real_T deltaAng[3];
        real_T Reast[3];
        int8_T b_I[9];
        boolean_T x_k[9];
        real_T quaternions_b;
        real_T quaternions_c;
        real_T quaternions_d;
        real_T b_accelMeasNoiseVar;
        real_T c_b;
        real_T y_idx_0;
        real_T y_idx_1;
        real_T y_idx_2;
        real_T d_tmp;
        real_T f_idx_0;
        real_T q_a;
        real_T q_b;
        real_T q_c;
        real_T b_q_d;
        real_T n;
        real_T maxval;
        real_T a21;
        real_T y_c;
        real_T c;
        real_T pd;
        real_T d;
        real_T x_c;
        real_T deltaAng_idx_2;
        real_T deltaAng_idx_1;
        real_T deltaAng_idx_0;
        real_T H_b;
        real_T H_p;
        real_T H_c;
    };

    // Block states (default storage) for system '<Root>'
    struct DW_sensorFusion_T
    {
        imufilter_sensorFusion_T FUSE; // '<Root>/readIMU'
        boolean_T FUSE_not_empty;      // '<Root>/readIMU'
    };

    // External inputs (root inport signals with default storage)
    struct ExtU_sensorFusion_T
    {
        real_T accel[3];               // '<Root>/accel'
        real_T gyro[3];                // '<Root>/gyro'
    };

    // External outputs (root outports fed by signals with default storage)
    struct ExtY_sensorFusion_T
    {
        real_T angles[3];              // '<Root>/angles'
        real_T rotators[4];            // '<Root>/rotators'
    };

    // Real-time Model Data Structure
    struct RT_MODEL_sensorFusion_T
    {
        const char_T * volatile errorStatus;
        const char_T* getErrorStatus() const;
        void setErrorStatus(const char_T* const volatile aErrorStatus);
    };

    // Copy Constructor
    sensorFusion(sensorFusion const&) = delete;

    // Assignment Operator
    sensorFusion& operator= (sensorFusion const&) & = delete;

    // Move Constructor
    sensorFusion(sensorFusion &&) = delete;

    // Move Assignment Operator
    sensorFusion& operator= (sensorFusion &&) = delete;

    // Real-Time Model get method
    sensorFusion::RT_MODEL_sensorFusion_T * getRTM();

    // Root inports set method
    void setExternalInputs(const ExtU_sensorFusion_T *pExtU_sensorFusion_T)
    {
        sensorFusion_U = *pExtU_sensorFusion_T;
    }

    // Root outports get method
    const ExtY_sensorFusion_T &getExternalOutputs() const
    {
        return sensorFusion_Y;
    }

    // model initialize function
    static void initialize();

    // model step function
    void step();

    // model terminate function
    static void terminate();

    // Constructor
    sensorFusion();

    // Destructor
    ~sensorFusion();

    // private data and function members
  private:
    // External inputs
    ExtU_sensorFusion_T sensorFusion_U;

    // External outputs
    ExtY_sensorFusion_T sensorFusion_Y;

    // Block signals
    B_sensorFusion_T sensorFusion_B;

    // Block states
    DW_sensorFusion_T sensorFusion_DW;

    // private member function(s) for subsystem '<Root>'
    void sensorFusion_NED_ecompass(const real_T a[3], const real_T m[3], real_T
        R[9]);
    void sensorFus_quaternion_quaternion(const real_T varargin_1[3], real_T
        *obj_a, real_T *obj_b, real_T *obj_c, real_T *obj_d);
    void sensorFu_IMUFilterBase_stepImpl(imufilter_sensorFusion_T *obj, const
        real_T accelIn[3], const real_T gyroIn[3], real_T *orientOut_a, real_T
        *orientOut_b, real_T *orientOut_c, real_T *orientOut_d);

    // Real-Time Model
    RT_MODEL_sensorFusion_T sensorFusion_M;
};

//-
//  The generated code includes comments that allow you to trace directly
//  back to the appropriate location in the model.  The basic format
//  is <system>/block_name, where system is the system number (uniquely
//  assigned by Simulink) and block_name is the name of the block.
//
//  Use the MATLAB hilite_system command to trace the generated code back
//  to the model.  For example,
//
//  hilite_system('<S3>')    - opens system 3
//  hilite_system('<S3>/Kp') - opens and selects block Kp which resides in S3
//
//  Here is the system hierarchy for this model
//
//  '<Root>' : 'sensorFusion'
//  '<S1>'   : 'sensorFusion/readIMU'

#endif                                 // sensorFusion_h_

//
// File trailer for generated code.
//
// [EOF]
//

//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// File: sensorFusion.cpp
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
#include "sensorFusion.h"
#include "sensorFusion_types.h"
#include "rtwtypes.h"
#include <cmath>
#include "sensorFusion_private.h"
#include <cstring>
#include "cmath"
#include "rt_defines.h"

// Function for MATLAB Function: '<Root>/readIMU'
void sensorFusion::sensorFusion_NED_ecompass(const real_T a[3], const real_T m[3],
    real_T R[9])
{
    real_T R_0;
    int32_T i2;
    int32_T xpageoffset;
    boolean_T b_x[3];
    boolean_T exitg1;
    boolean_T nanPageIdx;
    sensorFusion_B.Reast[0] = a[1] * m[2] - m[1] * a[2];
    sensorFusion_B.Reast[1] = m[0] * a[2] - a[0] * m[2];
    sensorFusion_B.Reast[2] = a[0] * m[1] - m[0] * a[1];
    R[6] = a[0];
    R[3] = sensorFusion_B.Reast[0];
    R[7] = a[1];
    R[4] = sensorFusion_B.Reast[1];
    R[8] = a[2];
    R[5] = sensorFusion_B.Reast[2];
    R[0] = sensorFusion_B.Reast[1] * a[2] - a[1] * sensorFusion_B.Reast[2];
    R[1] = a[0] * sensorFusion_B.Reast[2] - sensorFusion_B.Reast[0] * a[2];
    R[2] = sensorFusion_B.Reast[0] * a[1] - a[0] * sensorFusion_B.Reast[1];
    for (i2 = 0; i2 < 9; i2++)
    {
        R_0 = R[i2];
        sensorFusion_B.c_x[i2] = R_0 * R_0;
    }

    for (i2 = 0; i2 < 3; i2++)
    {
        xpageoffset = i2 * 3;
        sensorFusion_B.Reast[i2] = std::sqrt((sensorFusion_B.c_x[xpageoffset + 1]
            + sensorFusion_B.c_x[xpageoffset]) + sensorFusion_B.c_x[xpageoffset
            + 2]);
    }

    std::memcpy(&sensorFusion_B.c_x[0], &R[0], 9U * sizeof(real_T));
    for (i2 = 0; i2 < 3; i2++)
    {
        R_0 = sensorFusion_B.Reast[i2];
        R[3 * i2] = sensorFusion_B.c_x[3 * i2] / R_0;
        xpageoffset = 3 * i2 + 1;
        R[xpageoffset] = sensorFusion_B.c_x[xpageoffset] / R_0;
        xpageoffset = 3 * i2 + 2;
        R[xpageoffset] = sensorFusion_B.c_x[xpageoffset] / R_0;
    }

    for (i2 = 0; i2 < 9; i2++)
    {
        sensorFusion_B.x_k[i2] = std::isnan(R[i2]);
    }

    b_x[0] = false;
    b_x[1] = false;
    b_x[2] = false;
    i2 = 1;
    for (xpageoffset = 0; xpageoffset < 3; xpageoffset++)
    {
        int32_T b_a;
        int32_T ix;
        b_a = i2 + 2;
        ix = i2;
        i2 += 3;
        exitg1 = false;
        while ((!exitg1) && (ix <= b_a))
        {
            if (sensorFusion_B.x_k[ix - 1])
            {
                b_x[xpageoffset] = true;
                exitg1 = true;
            }
            else
            {
                ix++;
            }
        }
    }

    nanPageIdx = false;
    i2 = 0;
    exitg1 = false;
    while ((!exitg1) && (i2 < 3))
    {
        if (b_x[i2])
        {
            nanPageIdx = true;
            exitg1 = true;
        }
        else
        {
            i2++;
        }
    }

    if (nanPageIdx)
    {
        std::memset(&R[0], 0, 9U * sizeof(real_T));
        R[0] = 1.0;
        R[4] = 1.0;
        R[8] = 1.0;
    }
}

// Function for MATLAB Function: '<Root>/readIMU'
void sensorFusion::sensorFus_quaternion_quaternion(const real_T varargin_1[3],
    real_T *obj_a, real_T *obj_b, real_T *obj_c, real_T *obj_d)
{
    real_T st;
    real_T st_tmp;
    real_T theta;
    *obj_a = 1.0;
    *obj_b = 0.0;
    *obj_c = 0.0;
    *obj_d = 0.0;
    theta = std::sqrt((varargin_1[0] * varargin_1[0] + varargin_1[1] *
                       varargin_1[1]) + varargin_1[2] * varargin_1[2]);
    st_tmp = theta / 2.0;
    st = std::sin(st_tmp);
    if (theta != 0.0)
    {
        *obj_a = std::cos(st_tmp);
        *obj_b = varargin_1[0] / theta * st;
        *obj_c = varargin_1[1] / theta * st;
        *obj_d = varargin_1[2] / theta * st;
    }
}

// Function for MATLAB Function: '<Root>/readIMU'
void sensorFusion::sensorFu_IMUFilterBase_stepImpl(imufilter_sensorFusion_T *obj,
    const real_T accelIn[3], const real_T gyroIn[3], real_T *orientOut_a, real_T
    *orientOut_b, real_T *orientOut_c, real_T *orientOut_d)
{
    int32_T K_tmp;
    int32_T b_k;
    int32_T iindx;
    int32_T r1;
    int32_T r2;
    int32_T r3;
    int32_T rtemp;
    static const real_T g[3]
    {
        1.0, 0.0, 0.0
    };

    static const int8_T h[9]
    {
        1, 0, 0, 0, 1, 0, 0, 0, 1
    };

    boolean_T exitg1;
    sensorFusion_B.c = obj->pOrientPost.a;
    sensorFusion_B.deltaAng_idx_0 = obj->pOrientPost.b;
    sensorFusion_B.deltaAng_idx_1 = obj->pOrientPost.c;
    sensorFusion_B.deltaAng_idx_2 = obj->pOrientPost.d;
    if (obj->pFirstTime)
    {
        sensorFusion_NED_ecompass(accelIn, g, sensorFusion_B.h1);
        sensorFusion_B.pd = (sensorFusion_B.h1[0] + sensorFusion_B.h1[4]) +
            sensorFusion_B.h1[8];
        sensorFusion_B.x[0] = (sensorFusion_B.pd * 2.0 + 1.0) -
            sensorFusion_B.pd;
        sensorFusion_B.x[1] = (2.0 * sensorFusion_B.h1[0] + 1.0) -
            sensorFusion_B.pd;
        sensorFusion_B.x[2] = (2.0 * sensorFusion_B.h1[4] + 1.0) -
            sensorFusion_B.pd;
        sensorFusion_B.x[3] = (2.0 * sensorFusion_B.h1[8] + 1.0) -
            sensorFusion_B.pd;
        if (!std::isnan(sensorFusion_B.x[0]))
        {
            r1 = 1;
        }
        else
        {
            r1 = 0;
            rtemp = 2;
            exitg1 = false;
            while ((!exitg1) && (rtemp < 5))
            {
                if (!std::isnan(sensorFusion_B.x[rtemp - 1]))
                {
                    r1 = rtemp;
                    exitg1 = true;
                }
                else
                {
                    rtemp++;
                }
            }
        }

        if (r1 == 0)
        {
            sensorFusion_B.pd = sensorFusion_B.x[0];
            iindx = 1;
        }
        else
        {
            sensorFusion_B.pd = sensorFusion_B.x[r1 - 1];
            iindx = r1;
            for (rtemp = r1 + 1; rtemp < 5; rtemp++)
            {
                sensorFusion_B.x_c = sensorFusion_B.x[rtemp - 1];
                if (sensorFusion_B.pd < sensorFusion_B.x_c)
                {
                    sensorFusion_B.pd = sensorFusion_B.x_c;
                    iindx = rtemp;
                }
            }
        }

        switch (iindx)
        {
          case 1:
            sensorFusion_B.pd = std::sqrt(sensorFusion_B.pd);
            sensorFusion_B.c = 0.5 * sensorFusion_B.pd;
            sensorFusion_B.pd = 0.5 / sensorFusion_B.pd;
            sensorFusion_B.deltaAng_idx_0 = (sensorFusion_B.h1[7] -
                sensorFusion_B.h1[5]) * sensorFusion_B.pd;
            sensorFusion_B.deltaAng_idx_1 = (sensorFusion_B.h1[2] -
                sensorFusion_B.h1[6]) * sensorFusion_B.pd;
            sensorFusion_B.deltaAng_idx_2 = (sensorFusion_B.h1[3] -
                sensorFusion_B.h1[1]) * sensorFusion_B.pd;
            break;

          case 2:
            sensorFusion_B.pd = std::sqrt(sensorFusion_B.pd);
            sensorFusion_B.deltaAng_idx_0 = 0.5 * sensorFusion_B.pd;
            sensorFusion_B.pd = 0.5 / sensorFusion_B.pd;
            sensorFusion_B.c = (sensorFusion_B.h1[7] - sensorFusion_B.h1[5]) *
                sensorFusion_B.pd;
            sensorFusion_B.deltaAng_idx_1 = (sensorFusion_B.h1[1] +
                sensorFusion_B.h1[3]) * sensorFusion_B.pd;
            sensorFusion_B.deltaAng_idx_2 = (sensorFusion_B.h1[2] +
                sensorFusion_B.h1[6]) * sensorFusion_B.pd;
            break;

          case 3:
            sensorFusion_B.pd = std::sqrt(sensorFusion_B.pd);
            sensorFusion_B.deltaAng_idx_1 = 0.5 * sensorFusion_B.pd;
            sensorFusion_B.pd = 0.5 / sensorFusion_B.pd;
            sensorFusion_B.c = (sensorFusion_B.h1[2] - sensorFusion_B.h1[6]) *
                sensorFusion_B.pd;
            sensorFusion_B.deltaAng_idx_0 = (sensorFusion_B.h1[1] +
                sensorFusion_B.h1[3]) * sensorFusion_B.pd;
            sensorFusion_B.deltaAng_idx_2 = (sensorFusion_B.h1[5] +
                sensorFusion_B.h1[7]) * sensorFusion_B.pd;
            break;

          default:
            sensorFusion_B.pd = std::sqrt(sensorFusion_B.pd);
            sensorFusion_B.deltaAng_idx_2 = 0.5 * sensorFusion_B.pd;
            sensorFusion_B.pd = 0.5 / sensorFusion_B.pd;
            sensorFusion_B.c = (sensorFusion_B.h1[3] - sensorFusion_B.h1[1]) *
                sensorFusion_B.pd;
            sensorFusion_B.deltaAng_idx_0 = (sensorFusion_B.h1[2] +
                sensorFusion_B.h1[6]) * sensorFusion_B.pd;
            sensorFusion_B.deltaAng_idx_1 = (sensorFusion_B.h1[5] +
                sensorFusion_B.h1[7]) * sensorFusion_B.pd;
            break;
        }

        if (sensorFusion_B.c < 0.0)
        {
            sensorFusion_B.c = -sensorFusion_B.c;
            sensorFusion_B.deltaAng_idx_0 = -sensorFusion_B.deltaAng_idx_0;
            sensorFusion_B.deltaAng_idx_1 = -sensorFusion_B.deltaAng_idx_1;
            sensorFusion_B.deltaAng_idx_2 = -sensorFusion_B.deltaAng_idx_2;
        }
    }

    sensorFusion_B.deltaAng[0] = (gyroIn[0] - obj->pGyroOffset[0]) *
        obj->pSensorPeriod;
    sensorFusion_B.deltaAng[1] = (gyroIn[1] - obj->pGyroOffset[1]) *
        obj->pSensorPeriod;
    sensorFusion_B.deltaAng[2] = (gyroIn[2] - obj->pGyroOffset[2]) *
        obj->pSensorPeriod;
    sensorFus_quaternion_quaternion(sensorFusion_B.deltaAng, &sensorFusion_B.pd,
        &sensorFusion_B.x_c, &sensorFusion_B.y_c, &sensorFusion_B.maxval);
    sensorFusion_B.n = ((sensorFusion_B.c * sensorFusion_B.maxval +
                         sensorFusion_B.deltaAng_idx_0 * sensorFusion_B.y_c) -
                        sensorFusion_B.deltaAng_idx_1 * sensorFusion_B.x_c) +
        sensorFusion_B.deltaAng_idx_2 * sensorFusion_B.pd;
    sensorFusion_B.q_c = ((sensorFusion_B.c * sensorFusion_B.y_c -
                           sensorFusion_B.deltaAng_idx_0 * sensorFusion_B.maxval)
                          + sensorFusion_B.deltaAng_idx_1 * sensorFusion_B.pd) +
        sensorFusion_B.deltaAng_idx_2 * sensorFusion_B.x_c;
    sensorFusion_B.q_b = ((sensorFusion_B.c * sensorFusion_B.x_c +
                           sensorFusion_B.deltaAng_idx_0 * sensorFusion_B.pd) +
                          sensorFusion_B.deltaAng_idx_1 * sensorFusion_B.maxval)
        - sensorFusion_B.deltaAng_idx_2 * sensorFusion_B.y_c;
    sensorFusion_B.q_a = ((sensorFusion_B.c * sensorFusion_B.pd -
                           sensorFusion_B.deltaAng_idx_0 * sensorFusion_B.x_c) -
                          sensorFusion_B.deltaAng_idx_1 * sensorFusion_B.y_c) -
        sensorFusion_B.deltaAng_idx_2 * sensorFusion_B.maxval;
    if (sensorFusion_B.q_a < 0.0)
    {
        sensorFusion_B.q_a = -sensorFusion_B.q_a;
        sensorFusion_B.q_b = -sensorFusion_B.q_b;
        sensorFusion_B.q_c = -sensorFusion_B.q_c;
        sensorFusion_B.n = -sensorFusion_B.n;
    }

    sensorFusion_B.pd = std::sqrt(((sensorFusion_B.q_a * sensorFusion_B.q_a +
        sensorFusion_B.q_b * sensorFusion_B.q_b) + sensorFusion_B.q_c *
        sensorFusion_B.q_c) + sensorFusion_B.n * sensorFusion_B.n);
    sensorFusion_B.c = sensorFusion_B.q_a / sensorFusion_B.pd;
    sensorFusion_B.maxval = sensorFusion_B.q_b / sensorFusion_B.pd;
    sensorFusion_B.a21 = sensorFusion_B.q_c / sensorFusion_B.pd;
    sensorFusion_B.b_q_d = sensorFusion_B.n / sensorFusion_B.pd;
    sensorFusion_B.deltaAng_idx_0 = (sensorFusion_B.maxval *
        sensorFusion_B.b_q_d * 2.0 - sensorFusion_B.c * sensorFusion_B.a21 * 2.0)
        * 9.81;
    sensorFusion_B.pd = obj->LinearAccelerationDecayFactor * obj->pLinAccelPost
        [0];
    sensorFusion_B.deltaAng_idx_1 = (sensorFusion_B.a21 * sensorFusion_B.b_q_d *
        2.0 + sensorFusion_B.c * sensorFusion_B.maxval * 2.0) * 9.81;
    sensorFusion_B.x_c = obj->LinearAccelerationDecayFactor * obj->
        pLinAccelPost[1];
    sensorFusion_B.deltaAng_idx_2 = ((sensorFusion_B.c * sensorFusion_B.c * 2.0
        - 1.0) + sensorFusion_B.b_q_d * sensorFusion_B.b_q_d * 2.0) * 9.81;
    sensorFusion_B.y_c = obj->LinearAccelerationDecayFactor * obj->
        pLinAccelPost[2];
    std::memset(&sensorFusion_B.h1[0], 0, 9U * sizeof(real_T));
    sensorFusion_B.h1[3] = sensorFusion_B.deltaAng_idx_2;
    sensorFusion_B.h1[6] = -sensorFusion_B.deltaAng_idx_1;
    sensorFusion_B.h1[7] = sensorFusion_B.deltaAng_idx_0;
    for (r1 = 0; r1 < 3; r1++)
    {
        sensorFusion_B.h1_c[3 * r1] = sensorFusion_B.h1[3 * r1];
        rtemp = 3 * r1 + 1;
        sensorFusion_B.h1_c[rtemp] = sensorFusion_B.h1[rtemp] -
            sensorFusion_B.h1[r1 + 3];
        rtemp = 3 * r1 + 2;
        sensorFusion_B.h1_c[rtemp] = sensorFusion_B.h1[rtemp] -
            sensorFusion_B.h1[r1 + 6];
    }

    for (r1 = 0; r1 < 9; r1++)
    {
        sensorFusion_B.maxval = sensorFusion_B.h1_c[r1];
        sensorFusion_B.H[r1] = sensorFusion_B.maxval;
        sensorFusion_B.H[r1 + 9] = -sensorFusion_B.maxval * obj->pKalmanPeriod;
        sensorFusion_B.H[r1 + 18] = h[r1];
    }

    for (r1 = 0; r1 < 9; r1++)
    {
        sensorFusion_B.K[r1] = sensorFusion_B.H[3 * r1];
        rtemp = 3 * r1 + 1;
        sensorFusion_B.K[r1 + 9] = sensorFusion_B.H[rtemp];
        iindx = 3 * r1 + 2;
        sensorFusion_B.K[r1 + 18] = sensorFusion_B.H[iindx];
        sensorFusion_B.H_b = 0.0;
        sensorFusion_B.H_p = 0.0;
        sensorFusion_B.H_c = 0.0;
        for (r2 = 0; r2 < 9; r2++)
        {
            sensorFusion_B.d = obj->pQw[9 * r1 + r2];
            sensorFusion_B.H_b += sensorFusion_B.H[3 * r2] * sensorFusion_B.d;
            sensorFusion_B.H_p += sensorFusion_B.H[3 * r2 + 1] *
                sensorFusion_B.d;
            sensorFusion_B.H_c += sensorFusion_B.H[3 * r2 + 2] *
                sensorFusion_B.d;
        }

        sensorFusion_B.H_m[iindx] = sensorFusion_B.H_c;
        sensorFusion_B.H_m[rtemp] = sensorFusion_B.H_p;
        sensorFusion_B.H_m[3 * r1] = sensorFusion_B.H_b;
    }

    for (r1 = 0; r1 < 3; r1++)
    {
        sensorFusion_B.d = 0.0;
        sensorFusion_B.maxval = 0.0;
        sensorFusion_B.a21 = 0.0;
        for (r2 = 0; r2 < 9; r2++)
        {
            sensorFusion_B.b_q_d = sensorFusion_B.K[9 * r1 + r2];
            sensorFusion_B.d += sensorFusion_B.H_m[3 * r2] *
                sensorFusion_B.b_q_d;
            sensorFusion_B.maxval += sensorFusion_B.H_m[3 * r2 + 1] *
                sensorFusion_B.b_q_d;
            sensorFusion_B.a21 += sensorFusion_B.H_m[3 * r2 + 2] *
                sensorFusion_B.b_q_d;
        }

        sensorFusion_B.h1_c[3 * r1 + 2] = sensorFusion_B.a21;
        sensorFusion_B.h1_c[3 * r1 + 1] = sensorFusion_B.maxval;
        sensorFusion_B.h1_c[3 * r1] = sensorFusion_B.d;
    }

    for (r1 = 0; r1 < 3; r1++)
    {
        sensorFusion_B.h1[3 * r1] = sensorFusion_B.h1_c[r1] + obj->pQv[r1];
        sensorFusion_B.h1[3 * r1 + 1] = sensorFusion_B.h1_c[r1 + 3] + obj->
            pQv[r1 + 3];
        sensorFusion_B.h1[3 * r1 + 2] = sensorFusion_B.h1_c[r1 + 6] + obj->
            pQv[r1 + 6];
    }

    for (r1 = 0; r1 < 9; r1++)
    {
        sensorFusion_B.H_m[r1] = 0.0;
        sensorFusion_B.H_m[r1 + 9] = 0.0;
        sensorFusion_B.H_m[r1 + 18] = 0.0;
    }

    for (r1 = 0; r1 < 3; r1++)
    {
        for (r2 = 0; r2 < 9; r2++)
        {
            sensorFusion_B.d = sensorFusion_B.K[9 * r1 + r2];
            for (rtemp = 0; rtemp < 9; rtemp++)
            {
                iindx = 9 * r1 + rtemp;
                sensorFusion_B.H_m[iindx] += obj->pQw[9 * r2 + rtemp] *
                    sensorFusion_B.d;
            }
        }
    }

    r1 = 0;
    r2 = 1;
    r3 = 2;
    sensorFusion_B.maxval = std::abs(sensorFusion_B.h1[0]);
    sensorFusion_B.a21 = std::abs(sensorFusion_B.h1[1]);
    if (sensorFusion_B.a21 > sensorFusion_B.maxval)
    {
        sensorFusion_B.maxval = sensorFusion_B.a21;
        r1 = 1;
        r2 = 0;
    }

    if (std::abs(sensorFusion_B.h1[2]) > sensorFusion_B.maxval)
    {
        r1 = 2;
        r2 = 1;
        r3 = 0;
    }

    sensorFusion_B.h1[r2] /= sensorFusion_B.h1[r1];
    sensorFusion_B.h1[r3] /= sensorFusion_B.h1[r1];
    sensorFusion_B.h1[r2 + 3] -= sensorFusion_B.h1[r1 + 3] *
        sensorFusion_B.h1[r2];
    sensorFusion_B.h1[r3 + 3] -= sensorFusion_B.h1[r1 + 3] *
        sensorFusion_B.h1[r3];
    sensorFusion_B.h1[r2 + 6] -= sensorFusion_B.h1[r1 + 6] *
        sensorFusion_B.h1[r2];
    sensorFusion_B.h1[r3 + 6] -= sensorFusion_B.h1[r1 + 6] *
        sensorFusion_B.h1[r3];
    if (std::abs(sensorFusion_B.h1[r3 + 3]) > std::abs(sensorFusion_B.h1[r2 + 3]))
    {
        rtemp = r2;
        r2 = r3;
        r3 = rtemp;
    }

    sensorFusion_B.h1[r3 + 3] /= sensorFusion_B.h1[r2 + 3];
    sensorFusion_B.h1[r3 + 6] -= sensorFusion_B.h1[r3 + 3] *
        sensorFusion_B.h1[r2 + 6];
    for (b_k = 0; b_k < 9; b_k++)
    {
        rtemp = 9 * r1 + b_k;
        sensorFusion_B.K[rtemp] = sensorFusion_B.H_m[b_k] / sensorFusion_B.h1[r1];
        iindx = 9 * r2 + b_k;
        sensorFusion_B.K[iindx] = sensorFusion_B.H_m[b_k + 9] -
            sensorFusion_B.h1[r1 + 3] * sensorFusion_B.K[rtemp];
        K_tmp = 9 * r3 + b_k;
        sensorFusion_B.K[K_tmp] = sensorFusion_B.H_m[b_k + 18] -
            sensorFusion_B.h1[r1 + 6] * sensorFusion_B.K[rtemp];
        sensorFusion_B.K[iindx] /= sensorFusion_B.h1[r2 + 3];
        sensorFusion_B.K[K_tmp] -= sensorFusion_B.h1[r2 + 6] *
            sensorFusion_B.K[iindx];
        sensorFusion_B.K[K_tmp] /= sensorFusion_B.h1[r3 + 6];
        sensorFusion_B.K[iindx] -= sensorFusion_B.h1[r3 + 3] *
            sensorFusion_B.K[K_tmp];
        sensorFusion_B.K[rtemp] -= sensorFusion_B.K[K_tmp] *
            sensorFusion_B.h1[r3];
        sensorFusion_B.K[rtemp] -= sensorFusion_B.K[iindx] *
            sensorFusion_B.h1[r2];
    }

    sensorFusion_B.deltaAng[0] = (accelIn[0] + sensorFusion_B.pd) -
        sensorFusion_B.deltaAng_idx_0;
    sensorFusion_B.deltaAng[1] = (accelIn[1] + sensorFusion_B.x_c) -
        sensorFusion_B.deltaAng_idx_1;
    sensorFusion_B.deltaAng[2] = (accelIn[2] + sensorFusion_B.y_c) -
        sensorFusion_B.deltaAng_idx_2;
    std::memset(&sensorFusion_B.h1[0], 0, 9U * sizeof(real_T));
    for (r1 = 0; r1 < 3; r1++)
    {
        sensorFusion_B.d = sensorFusion_B.deltaAng[r1];
        for (r2 = 0; r2 < 9; r2++)
        {
            sensorFusion_B.h1[r2] += sensorFusion_B.K[9 * r1 + r2] *
                sensorFusion_B.d;
        }
    }

    sensorFus_quaternion_quaternion(&sensorFusion_B.h1[0], &sensorFusion_B.c,
        &sensorFusion_B.deltaAng_idx_0, &sensorFusion_B.deltaAng_idx_1,
        &sensorFusion_B.deltaAng_idx_2);
    sensorFusion_B.b_q_d = ((sensorFusion_B.q_a * -sensorFusion_B.deltaAng_idx_2
        + sensorFusion_B.q_b * -sensorFusion_B.deltaAng_idx_1) -
                            sensorFusion_B.q_c * -sensorFusion_B.deltaAng_idx_0)
        + sensorFusion_B.n * sensorFusion_B.c;
    sensorFusion_B.a21 = ((sensorFusion_B.q_a * -sensorFusion_B.deltaAng_idx_1 -
                           sensorFusion_B.q_b * -sensorFusion_B.deltaAng_idx_2)
                          + sensorFusion_B.q_c * sensorFusion_B.c) +
        sensorFusion_B.n * -sensorFusion_B.deltaAng_idx_0;
    sensorFusion_B.maxval = ((sensorFusion_B.q_a *
        -sensorFusion_B.deltaAng_idx_0 + sensorFusion_B.q_b * sensorFusion_B.c)
        + sensorFusion_B.q_c * -sensorFusion_B.deltaAng_idx_2) -
        sensorFusion_B.n * -sensorFusion_B.deltaAng_idx_1;
    sensorFusion_B.c = ((sensorFusion_B.q_a * sensorFusion_B.c -
                         sensorFusion_B.q_b * -sensorFusion_B.deltaAng_idx_0) -
                        sensorFusion_B.q_c * -sensorFusion_B.deltaAng_idx_1) -
        sensorFusion_B.n * -sensorFusion_B.deltaAng_idx_2;
    if (sensorFusion_B.c < 0.0)
    {
        sensorFusion_B.c = -sensorFusion_B.c;
        sensorFusion_B.maxval = -sensorFusion_B.maxval;
        sensorFusion_B.a21 = -sensorFusion_B.a21;
        sensorFusion_B.b_q_d = -sensorFusion_B.b_q_d;
    }

    sensorFusion_B.n = std::sqrt(((sensorFusion_B.c * sensorFusion_B.c +
        sensorFusion_B.maxval * sensorFusion_B.maxval) + sensorFusion_B.a21 *
        sensorFusion_B.a21) + sensorFusion_B.b_q_d * sensorFusion_B.b_q_d);
    for (r1 = 0; r1 < 9; r1++)
    {
        sensorFusion_B.H_b = 0.0;
        sensorFusion_B.H_p = 0.0;
        sensorFusion_B.H_c = 0.0;
        for (r2 = 0; r2 < 9; r2++)
        {
            sensorFusion_B.d = obj->pQw[9 * r1 + r2];
            sensorFusion_B.H_b += sensorFusion_B.H[3 * r2] * sensorFusion_B.d;
            sensorFusion_B.H_p += sensorFusion_B.H[3 * r2 + 1] *
                sensorFusion_B.d;
            sensorFusion_B.H_c += sensorFusion_B.H[3 * r2 + 2] *
                sensorFusion_B.d;
        }

        sensorFusion_B.H_m[3 * r1 + 2] = sensorFusion_B.H_c;
        sensorFusion_B.H_m[3 * r1 + 1] = sensorFusion_B.H_p;
        sensorFusion_B.H_m[3 * r1] = sensorFusion_B.H_b;
    }

    for (r1 = 0; r1 < 9; r1++)
    {
        sensorFusion_B.q_c = sensorFusion_B.K[r1 + 9];
        sensorFusion_B.q_b = sensorFusion_B.K[r1];
        sensorFusion_B.q_a = sensorFusion_B.K[r1 + 18];
        for (r2 = 0; r2 < 9; r2++)
        {
            rtemp = 9 * r2 + r1;
            sensorFusion_B.Ppost[rtemp] = obj->pQw[rtemp] -
                ((sensorFusion_B.H_m[3 * r2 + 1] * sensorFusion_B.q_c +
                  sensorFusion_B.H_m[3 * r2] * sensorFusion_B.q_b) +
                 sensorFusion_B.H_m[3 * r2 + 2] * sensorFusion_B.q_a);
        }
    }

    std::memset(&obj->pQw[0], 0, 81U * sizeof(real_T));
    sensorFusion_B.q_c = obj->pKalmanPeriod * obj->pKalmanPeriod;
    sensorFusion_B.q_b = obj->GyroscopeDriftNoise + obj->GyroscopeNoise;
    obj->pQw[0] = (sensorFusion_B.Ppost[30] + sensorFusion_B.q_b) *
        sensorFusion_B.q_c + sensorFusion_B.Ppost[0];
    obj->pQw[30] = sensorFusion_B.Ppost[30] + obj->GyroscopeDriftNoise;
    obj->pQw[10] = (sensorFusion_B.Ppost[40] + sensorFusion_B.q_b) *
        sensorFusion_B.q_c + sensorFusion_B.Ppost[10];
    obj->pQw[40] = sensorFusion_B.Ppost[40] + obj->GyroscopeDriftNoise;
    obj->pQw[20] = (sensorFusion_B.Ppost[50] + sensorFusion_B.q_b) *
        sensorFusion_B.q_c + sensorFusion_B.Ppost[20];
    obj->pQw[50] = sensorFusion_B.Ppost[50] + obj->GyroscopeDriftNoise;
    sensorFusion_B.deltaAng_idx_0 = -obj->pKalmanPeriod * obj->pQw[30];
    sensorFusion_B.deltaAng_idx_1 = -obj->pKalmanPeriod * obj->pQw[40];
    sensorFusion_B.deltaAng_idx_2 = -obj->pKalmanPeriod * obj->pQw[50];
    sensorFusion_B.q_c = obj->LinearAccelerationDecayFactor *
        obj->LinearAccelerationDecayFactor;
    obj->pFirstTime = false;
    obj->pOrientPost.a = sensorFusion_B.c / sensorFusion_B.n;
    obj->pOrientPost.b = sensorFusion_B.maxval / sensorFusion_B.n;
    obj->pOrientPost.c = sensorFusion_B.a21 / sensorFusion_B.n;
    obj->pOrientPost.d = sensorFusion_B.b_q_d / sensorFusion_B.n;
    obj->pQw[3] = sensorFusion_B.deltaAng_idx_0;
    obj->pQw[27] = sensorFusion_B.deltaAng_idx_0;
    obj->pQw[60] = sensorFusion_B.q_c * sensorFusion_B.Ppost[60] +
        obj->LinearAccelerationNoise;
    obj->pGyroOffset[0] -= sensorFusion_B.h1[3];
    obj->pLinAccelPost[0] = sensorFusion_B.pd - sensorFusion_B.h1[6];
    obj->pQw[13] = sensorFusion_B.deltaAng_idx_1;
    obj->pQw[37] = sensorFusion_B.deltaAng_idx_1;
    obj->pQw[70] = sensorFusion_B.q_c * sensorFusion_B.Ppost[70] +
        obj->LinearAccelerationNoise;
    obj->pGyroOffset[1] -= sensorFusion_B.h1[4];
    obj->pLinAccelPost[1] = sensorFusion_B.x_c - sensorFusion_B.h1[7];
    obj->pQw[23] = sensorFusion_B.deltaAng_idx_2;
    obj->pQw[47] = sensorFusion_B.deltaAng_idx_2;
    obj->pQw[80] = sensorFusion_B.q_c * sensorFusion_B.Ppost[80] +
        obj->LinearAccelerationNoise;
    obj->pGyroOffset[2] -= sensorFusion_B.h1[5];
    obj->pLinAccelPost[2] = sensorFusion_B.y_c - sensorFusion_B.h1[8];
    *orientOut_a = obj->pOrientPost.a;
    *orientOut_b = obj->pOrientPost.b;
    *orientOut_c = obj->pOrientPost.c;
    *orientOut_d = obj->pOrientPost.d;
}

real_T rt_atan2d_snf(real_T u0, real_T u1)
{
    real_T y;
    if (std::isnan(u0) || std::isnan(u1))
    {
        y = (rtNaN);
    }
    else if (std::isinf(u0) && std::isinf(u1))
    {
        int32_T tmp;
        int32_T tmp_0;
        if (u0 > 0.0)
        {
            tmp = 1;
        }
        else
        {
            tmp = -1;
        }

        if (u1 > 0.0)
        {
            tmp_0 = 1;
        }
        else
        {
            tmp_0 = -1;
        }

        y = std::atan2(static_cast<real_T>(tmp), static_cast<real_T>(tmp_0));
    }
    else if (u1 == 0.0)
    {
        if (u0 > 0.0)
        {
            y = RT_PI / 2.0;
        }
        else if (u0 < 0.0)
        {
            y = -(RT_PI / 2.0);
        }
        else
        {
            y = 0.0;
        }
    }
    else
    {
        y = std::atan2(u0, u1);
    }

    return y;
}

// Model step function
void sensorFusion::step()
{
    int32_T i;
    static const real_T i_0[81]
    {
        6.0923483957341713E-6, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
        6.0923483957341713E-6, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
        6.0923483957341713E-6, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
        7.6154354946677142E-5, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
        7.6154354946677142E-5, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
        7.6154354946677142E-5, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
        0.0096236100000000012, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
        0.0096236100000000012, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
        0.0096236100000000012
    };

    // MATLAB Function: '<Root>/readIMU' incorporates:
    //   Inport: '<Root>/accel'
    //   Inport: '<Root>/gyro'

    if (!sensorFusion_DW.FUSE_not_empty)
    {
        sensorFusion_DW.FUSE.AccelerometerNoise = 0.0001924722;
        sensorFusion_DW.FUSE.GyroscopeNoise = 9.1385E-5;
        sensorFusion_DW.FUSE.GyroscopeDriftNoise = 3.0462E-13;
        sensorFusion_DW.FUSE.LinearAccelerationNoise = 0.0096236100000000012;
        sensorFusion_DW.FUSE.LinearAccelerationDecayFactor = 0.5;
        sensorFusion_DW.FUSE.isInitialized = 0;
        sensorFusion_DW.FUSE_not_empty = true;
    }

    if (sensorFusion_DW.FUSE.isInitialized != 1)
    {
        sensorFusion_DW.FUSE.isInitialized = 1;
        sensorFusion_DW.FUSE.pSensorPeriod = 0.02;
        sensorFusion_DW.FUSE.pKalmanPeriod = 0.02;
        sensorFusion_DW.FUSE.TunablePropsChanged = false;
        sensorFusion_DW.FUSE.pOrientPost.a = 1.0;
        sensorFusion_DW.FUSE.pOrientPost.b = 0.0;
        sensorFusion_DW.FUSE.pOrientPost.c = 0.0;
        sensorFusion_DW.FUSE.pOrientPost.d = 0.0;
        sensorFusion_DW.FUSE.pInputPrototype[0] = sensorFusion_U.accel[0];
        sensorFusion_DW.FUSE.pGyroOffset[0] = 0.0;
        sensorFusion_DW.FUSE.pInputPrototype[1] = sensorFusion_U.accel[1];
        sensorFusion_DW.FUSE.pGyroOffset[1] = 0.0;
        sensorFusion_DW.FUSE.pInputPrototype[2] = sensorFusion_U.accel[2];
        sensorFusion_DW.FUSE.pGyroOffset[2] = 0.0;
        sensorFusion_B.b_accelMeasNoiseVar =
            (sensorFusion_DW.FUSE.GyroscopeDriftNoise +
             sensorFusion_DW.FUSE.GyroscopeNoise) * 0.0004 +
            (sensorFusion_DW.FUSE.AccelerometerNoise +
             sensorFusion_DW.FUSE.LinearAccelerationNoise);
        for (i = 0; i < 9; i++)
        {
            sensorFusion_B.b_I[i] = 0;
        }

        sensorFusion_B.b_I[0] = 1;
        sensorFusion_B.b_I[4] = 1;
        sensorFusion_B.b_I[8] = 1;
        for (i = 0; i < 9; i++)
        {
            sensorFusion_DW.FUSE.pQv[i] = sensorFusion_B.b_accelMeasNoiseVar *
                static_cast<real_T>(sensorFusion_B.b_I[i]);
        }

        std::memcpy(&sensorFusion_DW.FUSE.pQw[0], &i_0[0], 81U * sizeof(real_T));
        sensorFusion_DW.FUSE.pLinAccelPost[0] = 0.0;
        sensorFusion_DW.FUSE.pLinAccelPost[1] = 0.0;
        sensorFusion_DW.FUSE.pLinAccelPost[2] = 0.0;
        sensorFusion_DW.FUSE.pFirstTime = true;
    }

    if (sensorFusion_DW.FUSE.TunablePropsChanged)
    {
        sensorFusion_DW.FUSE.TunablePropsChanged = false;
        sensorFusion_DW.FUSE.pSensorPeriod = 0.02;
        sensorFusion_DW.FUSE.pKalmanPeriod = 0.02;
        sensorFusion_B.b_accelMeasNoiseVar =
            (sensorFusion_DW.FUSE.GyroscopeDriftNoise +
             sensorFusion_DW.FUSE.GyroscopeNoise) * 0.0004 +
            (sensorFusion_DW.FUSE.AccelerometerNoise +
             sensorFusion_DW.FUSE.LinearAccelerationNoise);
        for (i = 0; i < 9; i++)
        {
            sensorFusion_B.b_I[i] = 0;
        }

        sensorFusion_B.b_I[0] = 1;
        sensorFusion_B.b_I[4] = 1;
        sensorFusion_B.b_I[8] = 1;
        for (i = 0; i < 9; i++)
        {
            sensorFusion_DW.FUSE.pQv[i] = sensorFusion_B.b_accelMeasNoiseVar *
                static_cast<real_T>(sensorFusion_B.b_I[i]);
        }
    }

    sensorFu_IMUFilterBase_stepImpl(&sensorFusion_DW.FUSE, sensorFusion_U.accel,
        sensorFusion_U.gyro, &sensorFusion_B.b_accelMeasNoiseVar,
        &sensorFusion_B.quaternions_b, &sensorFusion_B.quaternions_c,
        &sensorFusion_B.quaternions_d);
    sensorFusion_B.c_b = 1.0 / std::sqrt(((sensorFusion_B.b_accelMeasNoiseVar *
        sensorFusion_B.b_accelMeasNoiseVar + sensorFusion_B.quaternions_b *
        sensorFusion_B.quaternions_b) + sensorFusion_B.quaternions_c *
        sensorFusion_B.quaternions_c) + sensorFusion_B.quaternions_d *
        sensorFusion_B.quaternions_d);
    sensorFusion_B.y_idx_0 = sensorFusion_B.b_accelMeasNoiseVar *
        sensorFusion_B.c_b;
    sensorFusion_B.y_idx_1 = sensorFusion_B.quaternions_b * sensorFusion_B.c_b;
    sensorFusion_B.y_idx_2 = sensorFusion_B.quaternions_c * sensorFusion_B.c_b;
    sensorFusion_B.c_b *= sensorFusion_B.quaternions_d;
    sensorFusion_B.d_tmp = sensorFusion_B.y_idx_1 * sensorFusion_B.c_b * 2.0 -
        sensorFusion_B.y_idx_0 * sensorFusion_B.y_idx_2 * 2.0;
    if (sensorFusion_B.d_tmp > 1.0)
    {
        sensorFusion_B.d_tmp = 1.0;
    }

    sensorFusion_B.f_idx_0 = sensorFusion_B.d_tmp;
    if (sensorFusion_B.d_tmp < -1.0)
    {
        sensorFusion_B.f_idx_0 = -1.0;
    }

    if ((sensorFusion_B.f_idx_0 < 0.0) && (std::abs(sensorFusion_B.f_idx_0 + 1.0)
         < 2.2204460492503131E-15))
    {
        // Outport: '<Root>/angles'
        sensorFusion_Y.angles[0] = -2.0 * rt_atan2d_snf(sensorFusion_B.y_idx_1,
            sensorFusion_B.y_idx_0);
        sensorFusion_Y.angles[2] = 0.0;
        sensorFusion_Y.angles[1] = 1.5707963267948966;
    }
    else if ((sensorFusion_B.f_idx_0 > 0.0) && (std::abs(sensorFusion_B.f_idx_0
               - 1.0) < 2.2204460492503131E-15))
    {
        // Outport: '<Root>/angles'
        sensorFusion_Y.angles[0] = 2.0 * rt_atan2d_snf(sensorFusion_B.y_idx_1,
            sensorFusion_B.y_idx_0);
        sensorFusion_Y.angles[2] = 0.0;
        sensorFusion_Y.angles[1] = -1.5707963267948966;
    }
    else
    {
        sensorFusion_B.d_tmp = sensorFusion_B.y_idx_0 * sensorFusion_B.y_idx_0 *
            2.0 - 1.0;

        // Outport: '<Root>/angles'
        sensorFusion_Y.angles[0] = rt_atan2d_snf(sensorFusion_B.y_idx_0 *
            sensorFusion_B.c_b * 2.0 + sensorFusion_B.y_idx_1 *
            sensorFusion_B.y_idx_2 * 2.0, sensorFusion_B.y_idx_1 *
            sensorFusion_B.y_idx_1 * 2.0 + sensorFusion_B.d_tmp);
        sensorFusion_Y.angles[2] = rt_atan2d_snf(sensorFusion_B.y_idx_0 *
            sensorFusion_B.y_idx_1 * 2.0 + sensorFusion_B.y_idx_2 *
            sensorFusion_B.c_b * 2.0, sensorFusion_B.c_b * sensorFusion_B.c_b *
            2.0 + sensorFusion_B.d_tmp);
        sensorFusion_Y.angles[1] = -std::asin(sensorFusion_B.f_idx_0);
    }

    // Outport: '<Root>/rotators' incorporates:
    //   MATLAB Function: '<Root>/readIMU'

    sensorFusion_Y.rotators[0] = sensorFusion_B.b_accelMeasNoiseVar;
    sensorFusion_Y.rotators[1] = sensorFusion_B.quaternions_b;
    sensorFusion_Y.rotators[2] = sensorFusion_B.quaternions_c;
    sensorFusion_Y.rotators[3] = sensorFusion_B.quaternions_d;
}

// Model initialize function
void sensorFusion::initialize()
{
    // (no initialization code required)
}

// Model terminate function
void sensorFusion::terminate()
{
    // (no terminate code required)
}

const char_T* sensorFusion::RT_MODEL_sensorFusion_T::getErrorStatus() const
{
    return (errorStatus);
}

void sensorFusion::RT_MODEL_sensorFusion_T::setErrorStatus(const char_T* const
    volatile aErrorStatus)
{
    (errorStatus = aErrorStatus);
}

// Constructor
sensorFusion::sensorFusion() :
    sensorFusion_U(),
    sensorFusion_Y(),
    sensorFusion_B(),
    sensorFusion_DW(),
    sensorFusion_M()
{
    // Currently there is no constructor body generated.
}

// Destructor
// Currently there is no destructor body generated.
sensorFusion::~sensorFusion() = default;

// Real-Time Model get method
sensorFusion::RT_MODEL_sensorFusion_T * sensorFusion::getRTM()
{
    return (&sensorFusion_M);
}

//
// File trailer for generated code.
//
// [EOF]
//

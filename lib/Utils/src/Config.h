#pragma once

#include <Arduino.h>
#include <ArduinoLog.h>

#define GRAVITY_ACCEL 9.831

const uint8_t BUTTON_A_PIN = 1; 
const uint8_t BUTTON_B_PIN = 8; 
const uint8_t BUZZER_PIN = 28; 

const uint8_t X_SERVO_PIN = 36; // Choose a pwm pin
const uint8_t Z_SERVO_PIN = 37; 
const uint8_t CHUTE_SERVO_PIN = 33;

const uint8_t CE_PIN = 2;
const uint8_t CSN_PIN = 23;

const uint16_t MAIN_LOOP_FREQUENCY = 50; // Hz
const uint16_t NAV_LOOP_FREQUENCY = 50; 

const float xKP = 1.0f; 
const float xKI = 0.0f; 
const float xKD = 0.1f; 
const float X_SETPOINT = 0.0f * DEG_TO_RAD; // const setpoint for now
const float X_SATURATION = 25.0f * DEG_TO_RAD;
const bool X_REVERSED = false; 

// to correct for sensor being upside down etc. 
const float X_AXIS_SENSOR_OFFSET = 0.0f * DEG_TO_RAD; 

const float zKP = 1.0f; 
const float zKI = 0.0f; 
const float zKD = 0.1f; 
const float Z_SETPOINT = 0.0f * DEG_TO_RAD; // const setpoint for now
const float Z_SATURATION = 25.0f * DEG_TO_RAD;
const bool Z_REVERSED = true; 

// to correct for the sensor being upside down etc. this is applied to the angle inputted to the pid. equivalent to calibration offset but just big.
// calibration offset is handled in Navigation.h
const float Z_AXIS_SENSOR_OFFSET = -90.0f * DEG_TO_RAD; 

const float PID_FILTER = 0.0f;

const float SEA_LEVEL_PRESSURE = 102.87*1e3; // Pascals; https://barometricpressure.app/sydney
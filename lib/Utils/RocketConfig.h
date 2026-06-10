#include <Arduino.h>

#define LOOP_FREQUENCY 50.0 // Hz

#define MODE_BUTTON_PIN 2
#define BUZZER_PIN 3

#define Y_SERVO_PIN A0
#define Z_SERVO_PIN A1

#define yKP 2.0f
#define yKI 0.0f
#define yKD 0.2f

#define zKP 2.0f
#define zKI 0.0f
#define zKD 0.2f

#define SETPOINT 0.0f // degrees; 
#define SATURATION 90.0f // degrees
#define PID_OFFSET 90.0f // degrees; shifts outputs from [-90, 90] -> [0, 180]; 

#define LIFTOFF_THRESHOLD 6 //ms-2; calculated ... 
#define POWERED_FLIGHT_TIME 5 //s; simulated

#define SEA_LEVEL_PRESSURE 103400 // Pascals
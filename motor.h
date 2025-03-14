// motor.h

#ifndef MOTOR_H
#define MOTOR_H

#include "shared.h"

// Define GPIO pins
#define IN1 0 // GPIO 17
#define IN2 1 // GPIO 18
#define IN3 2 // GPIO 27
#define IN4 3 // GPIO 22

void stepMotor(int step);            // move the motor by step
void rotate(int steps, int delayMs); // rotate the motor
void body_motor(SharedVariable *v);  //  motor handler

#endif
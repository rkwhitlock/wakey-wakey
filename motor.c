/**
 * Sources:
 *
 * ChatGPT (OpenAI): Assisted in generating understanding of stepper motor control and functionality
 *
 */

// motor.c - Control a stepper motor with with ULN2003 Driver Board

#include "motor.h"
#include "shared.h"
#include <stdio.h>
#include <unistd.h>
#include <wiringPi.h>

// Step sequence (Half step)
int stepSequence[8][4] = {{1, 0, 0, 0}, {1, 1, 0, 0}, {0, 1, 0, 0}, {0, 1, 1, 0}, {0, 0, 1, 0}, {0, 0, 1, 1}, {0, 0, 0, 1}, {1, 0, 0, 1}};

void stepMotor(int step) // Write the corresponding step to the GPIO pins to move the motor
{
    digitalWrite(IN1, stepSequence[step][0]);
    digitalWrite(IN2, stepSequence[step][1]);
    digitalWrite(IN3, stepSequence[step][2]);
    digitalWrite(IN4, stepSequence[step][3]);
}

void rotate(int steps, int delayMs) // use stepMotor to rotate the motor
{
    for (int i = 0; i < steps; i++)
    {
        stepMotor(i % 8); // Rotate the motor by the number of steps
        delay(delayMs);
    }
}

void body_motor(SharedVariable *v) //  motor handler
{

    // Set GPIO pins to output
    pinMode(IN1, OUTPUT);
    pinMode(IN2, OUTPUT);
    pinMode(IN3, OUTPUT);
    pinMode(IN4, OUTPUT);

    // printf("Rotating clockwise...\n");
    while (1)
    {
        if (v->alarm)
        {
            rotate(512, 2); // 512 steps for a full rotation
        }
    }

    // printf("Done!\n");
}
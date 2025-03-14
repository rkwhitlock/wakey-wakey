/**
 * Sources:
 *
 * ChatGPT (OpenAI): Assisted in generating understanding of stepper motor control and functionality
 *
 */

// stepper_motor.c - Control a stepper motor with with ULN2003 Driver Board

#include <stdio.h>
#include <unistd.h>
#include <wiringPi.h>

// Define GPIO pins
#define IN1 0 // GPIO 17
#define IN2 1 // GPIO 18
#define IN3 2 // GPIO 27
#define IN4 3 // GPIO 22

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
    for (int i = 0; i < steps; i++) // Rotate the motor by the number of steps
    {
        stepMotor(i % 8);
        delay(delayMs);
    }
}

int main()
{
    if (wiringPiSetup() == -1)
    {
        printf("WiringPi setup failed!\n");
        return 1;
    }

    // Set GPIO pins to output
    pinMode(IN1, OUTPUT);
    pinMode(IN2, OUTPUT);
    pinMode(IN3, OUTPUT);
    pinMode(IN4, OUTPUT);

    printf("Rotating clockwise...\n");
    rotate(512, 2); // 512 steps for a full rotation

    printf("Rotating counterclockwise...\n"); // Rotate the motor counterclockwise
    for (int i = 512; i > 0; i--)
    {
        stepMotor(i % 8);
        delay(2);
    }

    printf("Done!\n");
    return 0;
}
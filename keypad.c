#include "keypad.h"
#include "shared.h"
#include <stdio.h>
#include <wiringPi.h>

int rowPins[ROWS] = {1, 4, 5, 6};
int colPins[COLS] = {26, 27, 28, 29};
char keys[ROWS][COLS] = {
    {'1', '2', '3', 'A'}, {'4', '5', '6', 'B'}, {'7', '8', '9', 'C'}, {'*', '0', '#', 'D'}};

// Function to initialize the keypad GPIOs
void setupKeypad()
{

    // Set row pins as OUTPUT and initialize LOW
    for (int i = 0; i < 4; i++)
    {
        pinMode(rowPins[i], OUTPUT);
        digitalWrite(rowPins[i], LOW); // Start with rows LOW
    }

    // Set column pins as INPUT with pull-down resistors
    for (int i = 0; i < 4; i++)
    {
        pinMode(colPins[i], INPUT);
        pullUpDnControl(colPins[i], PUD_DOWN); // Apply pull-down
    }
}

// Function to scan for key presses
char getKeyPress()
{
    for (int row = 0; row < 4; row++)
    {
        // Set all rows LOW before scanning
        for (int r = 0; r < 4; r++)
        {
            digitalWrite(rowPins[r], LOW);
        }

        digitalWrite(rowPins[row], HIGH); // Activate one row

        for (int col = 0; col < 4; col++)
        {
            if (digitalRead(colPins[col]) == HIGH)
            {               // Key detected
                delay(100); // Increased debounce delay for stability

                // Confirm keypress after debounce
                if (digitalRead(colPins[col]) == HIGH)
                {
                    printf("Detected key at ROW: %d, COL: %d\n", row, col);

                    // Wait for key release
                    while (digitalRead(colPins[col]) == HIGH)
                        ;

                    digitalWrite(rowPins[row], LOW); // Reset row LOW
                    return keys[row][col];           // Return correct key
                }
            }
        }
        digitalWrite(rowPins[row], LOW); // Reset row LOW before next scan
    }
    return 0; // No key pressed
}

void *body_keypad(SharedVariable *v)
{

    setupKeypad();

    while (!v->exit_flag)
    {
        char key = getKeyPress();
        if (key)
        {
            pthread_mutex_lock(&v->lock);

            if (key >= '1' && key <= '3') // Only allow numbers 1-3 for 3x3 grid
            {
                grid[cursor_y][cursor_x] = key - '0';
                printf("Keypad Pressed: %c at (%d, %d)\n", key, cursor_y, cursor_x);
            }
            else if (key == '*') // Clear cell
            {
                grid[cursor_y][cursor_x] = 0;
                printf("Cell Cleared at (%d, %d)\n", cursor_y, cursor_x);
            }

            pthread_mutex_unlock(&v->lock);
            delay(200); // Debounce delay
        }
    }

    pthread_exit(NULL);
}
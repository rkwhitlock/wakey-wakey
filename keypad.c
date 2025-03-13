#include "keypad.h"
#include "shared.h"
#include <stdio.h>
#include <wiringPi.h>

void setupKeypad()
{
    // Set row pin as output to send voltage to the row
    pinMode(ROW_PIN, OUTPUT);
    digitalWrite(ROW_PIN, LOW);

    // Set column pins as input
    // There is only one row so these are also just keypad numbers
    pinMode(PIN_ONE, INPUT);
    pullUpDnControl(PIN_ONE, PUD_DOWN);
    pinMode(PIN_TWO, INPUT);
    pullUpDnControl(PIN_TWO, PUD_DOWN);
    pinMode(PIN_THREE, INPUT);
    pullUpDnControl(PIN_THREE, PUD_DOWN);
}

int getKeyPress()
{
    // Activate the row
    digitalWrite(ROW_PIN, HIGH);

    int pins[3] = {PIN_ONE, PIN_TWO, PIN_THREE};

    for (int i = 0; i < 3; i++)
    {
        // Check if key is pressed
        if (digitalRead(pins[i]) == HIGH)
        {
            // Debounce delay
            delay(100);

            // Confirm button still pressed
            if (digitalRead(pins[i]) == HIGH)
            {

                // Wait for button releaase
                while (digitalRead(pins[i]) == HIGH)
                    ;

                // Deactivate row
                digitalWrite(ROW_PIN, LOW);

                // Return number pressed
                return (i + 1);
            }
        }
    }

    digitalWrite(ROW_PIN, LOW);

    // If no key pressed return 0
    return 0;
}

void *body_keypad(SharedVariable *v)
{

    setupKeypad();

    // While sudoku is not solved
    while (!v->sudoku_flag)
    {
        int key = getKeyPress();

        // If a key is pressed
        if (key)
        {
            pthread_mutex_lock(&v->lock);

            // Writes key to grid
            if (key >= 1 && key <= 3 && !v->locked[v->cursor_y][v->cursor_x])
            {
                v->grid[v->cursor_y][v->cursor_x] = key;
            }

            pthread_mutex_unlock(&v->lock);
        }

        delay(200);
    }

    pthread_exit(NULL);
}
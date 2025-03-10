#include "keypad.h"
#include "shared.h"
#include <stdio.h>
#include <wiringPi.h>

void setupKeypad()
{

    pinMode(ROW_PIN, OUTPUT);
    digitalWrite(ROW_PIN, LOW);

    pinMode(PIN_ONE, INPUT);
    pullUpDnControl(PIN_ONE, PUD_DOWN);
    pinMode(PIN_TWO, INPUT);
    pullUpDnControl(PIN_TWO, PUD_DOWN);
    pinMode(PIN_THREE, INPUT);
    pullUpDnControl(PIN_THREE, PUD_DOWN);
}

int getKeyPress()
{
    digitalWrite(ROW_PIN, HIGH);

    if (digitalRead(PIN_ONE) == HIGH)
    {
        delay(100);

        if (digitalRead(PIN_ONE) == HIGH)
        {

            while (digitalRead(PIN_ONE) == HIGH)
                ;

            digitalWrite(ROW_PIN, LOW);
            return 1;
        }
    }

    if (digitalRead(PIN_TWO) == HIGH)
    {
        delay(100);

        if (digitalRead(PIN_TWO) == HIGH)
        {
            while (digitalRead(PIN_TWO) == HIGH)
                ;

            digitalWrite(ROW_PIN, LOW);
            return 2;
        }
    }

    if (digitalRead(PIN_THREE) == HIGH)
    {
        delay(100);

        if (digitalRead(PIN_THREE) == HIGH)
        {
            while (digitalRead(PIN_THREE) == HIGH)
                ;

            digitalWrite(ROW_PIN, LOW);
            return 3;
        }
    }

    digitalWrite(ROW_PIN, LOW);

    return 0;
}

void *body_keypad(SharedVariable *v)
{

    setupKeypad();

    while (!v->sudoku_flag)
    {
        int key = getKeyPress();
        if (key)
        {
            pthread_mutex_lock(&v->lock);

            if (key >= 1 && key <= 3 && !v->locked[v->cursor_y][v->cursor_x])
            {
                v->grid[v->cursor_y][v->cursor_x] = key;
            }

            pthread_mutex_unlock(&v->lock);
            delay(200);
        }
    }

    pthread_exit(NULL);
}
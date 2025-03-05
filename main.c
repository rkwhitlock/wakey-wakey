#include "joystick.h"
#include "keypad.h"
#include "sudoku.h"
#include <pthread.h>
#include <stdio.h>
#include <wiringPi.h>

int grid[SIZE][SIZE] = {{1, 2, 3}, {3, 1, 2}, {2, 3, 1}};
int cursor_x = 0, cursor_y = 0;
pthread_mutex_t board_lock;

int main(int argc, char *argv[])
{
    SharedVariable v;
    v.exit_flag = 0;
    pthread_mutex_init(&v.lock, NULL);

    if (wiringPiSetup() == -1)
    {
        printf("Failed to setup wiringPi.\n");
        return 1;
    }

    pthread_t t_sudoku, t_joystick, t_keypad;

    pthread_create(&t_sudoku, NULL, body_sudoku, &v);
    pthread_create(&t_joystick, NULL, body_joystick, &v);
    pthread_create(&t_keypad, NULL, body_keypad, &v);

    printf("Press 'D' on the keypad to quit.\n");
    while (!v.exit_flag)
    {
        char key = getKeyPress();
        if (key == 'D')
        {
            v.exit_flag = 1;
            printf("Quit command received from keypad.\n");
            break;
        }
        delay(100);
    }

    pthread_join(t_sudoku, NULL);
    pthread_join(t_joystick, NULL);
    pthread_join(t_keypad, NULL);

    pthread_mutex_destroy(&v.lock);

    printf("Program finished.\n");

    return 0;
}

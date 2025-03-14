// main.c
#include "joystick.h"
#include "keypad.h"
#include "motor.h"
#include "pose.h"
#include "rtc.h"
#include "speaker.h"
#include "sudoku.h"
#include <pthread.h>
#include <stdio.h>
#include <wiringPi.h>

int cursor_x = 0, cursor_y = 0; // Cursor position
pthread_mutex_t board_lock;     // Mutex lock for the board

int main()
{

    if (wiringPiSetup() == -1)
    {
        printf("Failed to setup wiringPi.\n");
        return 1;
    }

    pthread_t t_sudoku, t_joystick, t_keypad, t_rtc, t_speaker, t_motor; //    Thread variables

    SharedVariable v;                  // Shared variable
    v.sudoku_flag = 0;                 // Initialize sudoku flag
    pthread_mutex_init(&v.lock, NULL); // Initialize mutex lock
    v.cursor_x = cursor_x;
    v.cursor_y = cursor_y;
    v.alarm = 0;

    // Initialize the shared variable grid
    pthread_create(&t_rtc, NULL, body_rtc, &v);
    pthread_create(&t_speaker, NULL, body_speaker, &v);
    pthread_create(&t_motor, NULL, body_motor, &v);

    // Wait for the alarm to go off
    while (!v.alarm)
    {
        delay(100);
    }

    int cnt = 0;

    // Check the user's pose
    while (!check_pose() && cnt < 10)
    {
        cnt++;
        printf("COUNT: %d", cnt);
    }

    v.alarm = 0;

    // Initialize the threads
    pthread_create(&t_sudoku, NULL, body_sudoku, &v);
    pthread_create(&t_joystick, NULL, body_joystick, &v);
    pthread_create(&t_keypad, NULL, body_keypad, &v);

    // Wait for the sudoku to be solved
    while (!v.sudoku_flag)
    {
        delay(100);
    }

    // Join the threads
    pthread_join(t_sudoku, NULL);
    pthread_join(t_joystick, NULL);
    pthread_join(t_keypad, NULL);
    pthread_join(t_rtc, NULL);
    pthread_join(t_speaker, NULL);
    pthread_join(t_motor, NULL);

    // Destroy the mutex lock
    pthread_mutex_destroy(&v.lock);

    clear();

    printf("Congratulations!! You solved it.\n");

    return 0;
}

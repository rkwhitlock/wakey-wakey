// sudoku.h
#ifndef SHARED_H
#define SHARED_H

#include <pthread.h>

#define SIZE 3

extern pthread_mutex_t board_lock;

typedef struct
{
    int exit_flag;
    pthread_mutex_t lock;
    int grid[SIZE][SIZE];
    int cursor_x, cursor_y;
} SharedVariable;

#endif
// sudoku.h
#ifndef SHARED_H
#define SHARED_H

#include <pthread.h>

#define SIZE 3 // Size of the sudoku board

extern pthread_mutex_t board_lock; // Mutex lock for the board

typedef struct
{
    int sudoku_flag;        // Flag to indicate if the sudoku is solved
    pthread_mutex_t lock;   // Mutex lock for the shared variable
    int grid[SIZE][SIZE];   // Sudoku board
    int cursor_x, cursor_y; // Cursor position
    int locked[SIZE][SIZE]; // Locked cells
    int alarm;              // Alarm flag
} SharedVariable;

#endif
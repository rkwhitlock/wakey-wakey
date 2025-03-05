// sudoku.h
#ifndef SHARED_H
#define SHARED_H

#include <pthread.h>

extern pthread_mutex_t board_lock;

typedef struct
{
    int exit_flag;
    pthread_mutex_t lock;
} SharedVariable;

#endif
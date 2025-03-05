// sudoku.h
#ifndef SUDOKU_H
#define SUDOKU_H

#include "shared.h"
#include <pthread.h>

#define SIZE 3

extern int grid[SIZE][SIZE];
extern int cursor_x, cursor_y;

void scramble();
void display_board();
void body_sudoku(SharedVariable *v);

#endif
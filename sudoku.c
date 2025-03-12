// sudoku.c
#include "sudoku.h"
#include "shared.h"
#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void scramble(SharedVariable *v)
{
    pthread_mutex_init(&v->lock, NULL);
    for (int i = 0; i < 6; i++)
    {
        int x = rand() % SIZE;
        int y = rand() % SIZE;
        v->grid[x][y] = 0;
        v->locked[x][y] = 0;
    }
    pthread_mutex_destroy(&v->lock);
}

int check_win(SharedVariable *v)
{
    int row_check[SIZE], col_check[SIZE], box_check[SIZE];

    for (int i = 0; i < SIZE; i++)
    {
        memset(row_check, 0, sizeof(row_check));
        memset(col_check, 0, sizeof(col_check));

        for (int j = 0; j < SIZE; j++)
        {
            // Check row
            if (v->grid[i][j] < 1 || v->grid[i][j] > SIZE)
                return 0; // Invalid number found
            if (row_check[v->grid[i][j] - 1] == 1)
                return 0; // Duplicate number in row
            row_check[v->grid[i][j] - 1] = 1;

            // Check column
            if (col_check[v->grid[j][i] - 1] == 1)
                return 0; // Duplicate number in column
            col_check[v->grid[j][i] - 1] = 1;
        }
    }

    return 1; // Sudoku is solved
}

void display_board(SharedVariable *v)
{
    clear();
    // Initialize ncurses
    initscr();
    start_color(); // Start color functionality
    use_default_colors();
    init_pair(1, COLOR_BLUE, -1);
    init_pair(2, COLOR_MAGENTA, -1);

    printw("Solve the Sudoku puzzle!! Press the joystick button to clear a cell.\n");
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            if (i == v->cursor_y && j == v->cursor_x)
            {
                attron(A_REVERSE);
            }
            if (v->locked[i][j])
            {
                attron(COLOR_PAIR(2));
            }
            else
            {
                attron(COLOR_PAIR(1));
            }
            if (v->grid[i][j] == 0)
            {
                printw(".");
            }
            else
            {
                printw("%d", v->grid[i][j]);
            }
            if (i == v->cursor_y && j == v->cursor_x)
            {
                attroff(A_REVERSE);
            }
            if (v->locked[i][j])
            {
                attroff(COLOR_PAIR(2));
            }
            else
            {
                attroff(COLOR_PAIR(1));
            }
            printw(" ");
        }
        printw("\n");
    }
    refresh();
}

void sudoku_init(SharedVariable *v)
{

    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            if (i > j)
            {
                v->grid[i][j] = SIZE - i + j + 1;
            }
            else
            {
                v->grid[i][j] = j - i + 1;
            }
            v->locked[i][j] = 1;
        }
    }
}

void body_sudoku(SharedVariable *v)
{
    initscr();
    noecho();
    curs_set(0);
    pthread_mutex_init(&v->lock, NULL);

    sudoku_init(v);
    scramble(v);
    display_board(v);

    while (!v->sudoku_flag)
    {
        pthread_mutex_lock(&v->lock);
        display_board(v);
        if (check_win(v))
        {
            v->sudoku_flag = 1;
        }
        pthread_mutex_unlock(&v->lock);
        napms(100); // Slow down display refresh
    }

    pthread_mutex_destroy(&v->lock);
    endwin();
}

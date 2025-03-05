// sudoku.c
#include "sudoku.h"
#include "shared.h"
#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>

void scramble()
{
    for (int i = 0; i < 6; i++)
    {
        int x = rand() % SIZE;
        int y = rand() % SIZE;
        grid[x][y] = 0;
    }
}

void display_board()
{
    clear();
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            if (i == cursor_y && j == cursor_x)
            {
                attron(A_REVERSE);
            }
            if (grid[i][j] == 0)
            {
                printw(".");
            }
            else
            {
                printw("%d", grid[i][j]);
            }
            if (i == cursor_y && j == cursor_x)
            {
                attroff(A_REVERSE);
            }
            printw(" ");
        }
        printw("\n");
    }
    refresh();
}

void body_sudoku(SharedVariable *v)
{
    initscr();
    noecho();
    curs_set(0);
    pthread_mutex_init(&v->lock, NULL);

    scramble();
    display_board();

    while (!v->exit_flag)
    {
        pthread_mutex_lock(&v->lock);
        display_board();
        pthread_mutex_unlock(&v->lock);
        napms(100); // Slow down display refresh
    }

    pthread_mutex_destroy(&v->lock);
    endwin();
}

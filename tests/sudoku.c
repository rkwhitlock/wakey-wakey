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
    }
    pthread_mutex_destroy(&v->lock);
}

void display_board(SharedVariable *v)
{
    pthread_mutex_init(&v->lock, NULL);
    clear();

    // Initialize ncurses
    initscr();
    start_color();                           // Start color functionality
    init_pair(1, COLOR_WHITE, COLOR_BLUE);   // Color pair for normal numbers
    init_pair(2, COLOR_BLACK, COLOR_YELLOW); // Color pair for highlighted number

    for (int i = 0; i < SIZE; i++)
    {

        const char *numbers[] = {ZERO, ONE, TWO, THREE};

        // Array to hold concatenated output for each row
        char result[1024] = ""; // Buffer to store the concatenated result
        char temp[1024];        // Temporary buffer for concatenation

        // We have 11 rows in each number's ASCII art, so loop over them
        for (int row = 0; row < 11; row++)
        {
            // Clear the temporary buffer for the current row
            temp[0] = '\0';

            // Loop over each number and append its current row to temp
            for (int j = 0; j < 3; j++)
            {
                // If this box matches the cursor position, use the highlighted color
                if (i == v->cursor_y && j == v->cursor_x)
                {
                    attron(COLOR_PAIR(2)); // Apply the highlight color pair (Yellow background)
                }
                else
                {
                    attron(
                        COLOR_PAIR(1)); // Apply the normal color pair (White text, Blue background)
                }

                if (i == v->cursor_y && j == v->cursor_x)
                {
                    attron(A_REVERSE);
                }
                // Extract the row for the current number (i) and concatenate it
                const char *line_start =
                    numbers[v->grid[i][j]] + row * 20; // Each row has 17 characters
                strncat(temp, line_start, 20);         // Append the current line to temp
                if (i == v->cursor_y && j == v->cursor_x)
                {
                    attroff(A_REVERSE);
                }

                // Turn off highlighting if this was the highlighted box
                if (i == v->cursor_y && j == v->cursor_x)
                {
                    attroff(COLOR_PAIR(2)); // Remove highlight color
                }
                else
                {
                    attroff(COLOR_PAIR(1)); // Remove normal color
                }
            }

            // After processing all numbers, append the current row to the result
            strcat(result, temp);
            strcat(result, "\n");
        }

        printw("%s", result);
        printw("\n");
    }
    refresh();
    pthread_mutex_destroy(&v->lock);
}

void body_sudoku(SharedVariable *v)
{
    initscr();
    noecho();
    curs_set(0);
    pthread_mutex_init(&v->lock, NULL);

    scramble(v);
    display_board(v);

    while (!v->exit_flag)
    {
        pthread_mutex_lock(&v->lock);
        display_board(v);
        pthread_mutex_unlock(&v->lock);
        napms(100); // Slow down display refresh
    }

    pthread_mutex_destroy(&v->lock);
    endwin();
}

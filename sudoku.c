// sudoku.c
#include "sudoku.h"
#include "shared.h"
#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void scramble(SharedVariable *v) // Scramble the sudoku board
{
    pthread_mutex_init(&v->lock, NULL); // Initialize the mutex lock to ensure thread safety
    for (int i = 0; i < 6; i++)
    {
        int x = rand() % SIZE; // Generate a random row index
        int y = rand() % SIZE; // Generate a random column index
        v->grid[x][y] = 0;     // Clear the cell
        v->locked[x][y] = 0;   // Mark it as editable
    }
    pthread_mutex_destroy(&v->lock); // Destroy mutex lock
}

int check_win(SharedVariable *v) // Check if the sudoku board is solved
{
    int row_check[SIZE], col_check[SIZE], box_check[SIZE];

    for (int i = 0; i < SIZE; i++)
    {
        memset(row_check, 0, sizeof(row_check)); // Reset row checker array
        memset(col_check, 0, sizeof(col_check)); // Reset column checker array

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

void display_board(SharedVariable *v) // Display the sudoku board
{
    clear();
    // Initialize ncurses
    initscr();
    start_color(); // Start color functionality
    use_default_colors();
    init_pair(1, COLOR_BLUE, -1); // Initialize color pair
    init_pair(2, COLOR_MAGENTA, -1);

    printw("Solve the Sudoku puzzle!! Press the joystick button to clear a cell.\n");
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            if (i == v->cursor_y && j == v->cursor_x)
            {
                attron(A_REVERSE); // Highlight the selected cell
            }
            if (v->locked[i][j])
            {
                attron(COLOR_PAIR(2)); // Use locked cell color
            }
            else
            {
                attron(COLOR_PAIR(1)); // Use unlocked cell color
            }

            // Print cell value or "." for empty cells
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
                attroff(A_REVERSE); // Remove highlight
            }
            if (v->locked[i][j])
            {
                attroff(COLOR_PAIR(2)); // Reset color
            }
            else
            {
                attroff(COLOR_PAIR(1)); // Reset color
            }
            printw(" "); // Print spacing between numbers
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
            // Generate a predefined pattern for Sudoku board
            if (i > j)
            {
                v->grid[i][j] = SIZE - i + j + 1;
            }
            else
            {
                v->grid[i][j] = j - i + 1;
            }
            v->locked[i][j] = 1; // Mark all cells as locked initially
        }
    }
}

void body_sudoku(SharedVariable *v)
{
    initscr();
    noecho();
    curs_set(0);
    pthread_mutex_init(&v->lock, NULL); // Initialize mutex lock for thread safety

    sudoku_init(v);   // Initialize the board
    scramble(v);      // Scramble the board by clearing some cells
    display_board(v); // Display the initial state of the board

    // Main game loop
    while (!v->sudoku_flag) // Continue until the Sudoku is solved
    {
        pthread_mutex_lock(&v->lock); // Lock mutex to prevent race conditions
        display_board(v);             // Refresh the board display

        if (check_win(v)) // Check if the board is solved
        {
            v->sudoku_flag = 1; // Mark game as completed
        }

        pthread_mutex_unlock(&v->lock); // Unlock mutex
        napms(100);                     // Delay execution to slow down display refresh
    }

    clear();                         // Clear the screen after solving the puzzle
    pthread_mutex_destroy(&v->lock); // Destroy mutex lock
    endwin();                        // End ncurses mode
}

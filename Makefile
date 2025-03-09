CC = gcc
CFLAGS = -Wall -Wextra -pthread
TARGET = sudoku
SRCS = main.c sudoku.c keypad.c joystick.c
OBJS = $(SRCS:.c=.o)
FLAGS = -lwiringPi -lncurses

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS) $(FLAGS)


clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all clean

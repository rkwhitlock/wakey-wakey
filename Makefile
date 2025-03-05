CC = gcc
CFLAGS = -Wall -Wextra -pthread -lncurses -lwiringPi
TARGET = sudoku
SRCS = main.c sudoku.c keypad.c joystick.c
OBJS = $(SRCS:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all clean

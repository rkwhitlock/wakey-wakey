CC = gcc
CFLAGS = -Wall -Wextra -pthread
TARGET = alarm
SRCS = main.c sudoku.c keypad.c joystick.c pose.c rtc.c lcd.c
OBJS = $(SRCS:.c=.o)
FLAGS = -lwiringPi -lncurses

all: $(TARGET) motor

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS) $(FLAGS)

motor: stepper_motor.c
	$(CC) $(CFLAGS) -o motor stepper_motor.c $(FLAGS)


clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all clean

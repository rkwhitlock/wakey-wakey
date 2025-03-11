CC = gcc
CFLAGS = -Wall -Wextra -pthread
TARGET = sudoku
SRCS = main.c sudoku.c keypad.c joystick.c pose.c
OBJS = $(SRCS:.c=.o)
FLAGS = -lwiringPi -lncurses

all: $(TARGET) capture motor rtc lcd

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS) $(FLAGS)

capture: capture.o
	g++ -o capture capture.cpp

motor: stepper_motor.c
	$(CC) $(CFLAGS) -o motor stepper_motor.c $(FLAGS)

rtc: rtc.c
	$(CC) $(CFLAGS) -o rtc rtc.c $(FLAGS)

lcd: lcd.c
	$(CC) $(CFLAGS) -o lcd lcd.c $(FLAGS)


clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all clean

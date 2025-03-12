CC = gcc
CFLAGS = -Wall -Wextra -pthread
TARGET = alarm
SRCS = main.c sudoku.c keypad.c joystick.c pose.c rtc.c lcd.c speaker.c motor.c
OBJS = $(SRCS:.c=.o)
FLAGS = -lwiringPi -lncurses

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS) $(FLAGS)


clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all clean

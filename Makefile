CC = gcc
CFLAGS = `pkg-config --cflags gtk+-3.0`
LIBS = `pkg-config --libs gtk+-3.0`
SRC = src/main.c

all:
	$(CC) $(SRC) -o sudoku $(CFLAGS) $(LIBS)

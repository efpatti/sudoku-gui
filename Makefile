CC = gcc
CFLAGS = `pkg-config --cflags gtk+-3.0`
LIBS = `pkg-config --libs gtk+-3.0`
SRC_DIR = src
SRC = $(SRC_DIR)/main.c $(SRC_DIR)/sudoku.c $(SRC_DIR)/generator.c
OUT = sudoku

all:
	$(CC) $(SRC) -o $(OUT) $(CFLAGS) $(LIBS)

run: all
	./$(OUT)

clean:
	rm -f $(OUT)

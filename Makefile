CC=gcc
CFLAGS=-Wall
INCL=-I /usr/include
LIBS=-l lua -l SDL2 -l SDL2_ttf -lm
OUT=StrangeEngine

SRC=src
BIN=bin

build:
	$(CC) $(CFLAGS) $(SRC)/* -o $(BIN)/$(OUT) $(INCL) $(LIBS)

clear:
	rm -rf $(BIN)
CC=gcc
CFLAGS=-Wall
INCL=-I /usr/include
LIBS=-l lua -l SDL2 -l SDL2_ttf -lm
OUT=StrangeEngine

SRC=src
BIN=bin

strange-engine: make-bin
	$(CC) $(CFLAGS) $(SRC)/* -o $(BIN)/$(OUT) $(INCL) $(LIBS)

debug: make-bin
	$(CC) -g $(CFLAGS) $(SRC)/* -o $(BIN)/$(OUT)-debug $(INCL) $(LIBS)

make-bin:
	mkdir -p $(BIN)

clear:
	rm -rf $(BIN)
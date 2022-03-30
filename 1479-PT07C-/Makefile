SRC=$(wildcard *.c)
OBJ=$(SRC:.c=.o)
BIN=a.exe

CFLAGS=-O2 -std=c99 -Wall -Wextra
LDFLAGS=-lm
LDFLAGS+=-static-libgcc

all: $(BIN)

$(BIN): $(OBJ)
	$(CC) -o $@ $^ $(LDFLAGS)

clean:
	rm -f $(OBJ) $(BIN)

.PHONY: clean all

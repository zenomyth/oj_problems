SRC=$(wildcard *.c)
OBJ=$(SRC:.c=.o)
BIN=a.exe

CFLAGS=-O2 -std=c99 -Wall -Wextra
# CFLAGS+=-mwindows
CFLAGS+=-DUNICODE
LDFLAGS=-lm
LDFLAGS+=-static-libgcc
# LDFLAGS+=-mwindows
LDFLAGS+=-Wl,--subsystem,windows
LDFLAGS+=-lcomctl32
LDFLAGS+=-lgdi32
# LDFLAGS+=-lwinmm

all: $(BIN)

$(BIN): $(OBJ)
	$(CC) -o $@ $^ $(LDFLAGS)

clean:
	rm -f $(OBJ) $(BIN)

.PHONY: clean all

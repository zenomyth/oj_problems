CC=gcc
CFLAGS=-c -Wall -o2
LDFLAGS=-lm
SOURCES=main.c
OBJECTS=$(SOURCES:.c=.o)
EXECUTABLE=a.out

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS) -o $@ $(LDFLAGS)

.c.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	@rm $(OBJECTS) $(EXECUTABLE)

.PHONY: clean


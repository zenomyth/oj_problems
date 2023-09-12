SRC=$(wildcard *.cpp)
OBJ=$(SRC:.cpp=.o)
BIN=a.exe

CXXFLAGS=-O2 -std=c++11 -Wall -Wextra
LDFLAGS+=-static-libstdc++

all: $(BIN)

$(BIN): $(OBJ)
	$(CXX) -o $@ $^ $(LDFLAGS)

clean:
	rm -f $(OBJ) $(BIN)

.PHONY: clean all

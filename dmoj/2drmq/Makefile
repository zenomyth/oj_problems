BIN := a.exe
SRC := $(wildcard *.cpp)
OBJ := $(SRC:.cpp=.o)

all: $(BIN)

$(BIN) : $(OBJ)
	$(CXX) -lstdc++ -o $@ $^

run: $(BIN)
	@./$(BIN) < input.txt

clean:
	@rm -rf $(BIN) $(OBJ)

.PHONY: clean all run

BIN := a.out
SRC := $(wildcard *.cpp)
OBJ := $(SRC:.cpp=.o)

%.o : %.cpp
	@$(CXX) -c $(CXXFLAGS) $< -o $@

all: $(BIN)

$(BIN) : $(OBJ)
	@$(CXX) -o $@ $^

run: $(BIN)
	@./$(BIN) < input.txt

clean:
	@rm -rf $(BIN) $(OBJ)

.PHONY: clean all run

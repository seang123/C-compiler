CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17

SRC = main.cpp Lexer.cpp Token.cpp
TEST_SRC = tests.cpp Lexer.cpp Token.cpp

TARGET = app
TEST_TARGET = tests

# Object files
OBJ = $(SRC:.cpp=.o)
TEST_OBJ = $(TEST_SRC:.cpp=.o)

#all: main.o Token.o Lexer.o
#	$(CXX) $(CXXFlags) -o a.exe main.o Token.o Lexer.o

# Build the main application
$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRC)


# Build the tests
# Build the tests
$(TEST_TARGET): $(TEST_OBJ)
	$(CXX) $(CXXFLAGS) -o $(TEST_TARGET) $(TEST_OBJ)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Run the tests
test: $(TEST_TARGET)
	./$(TEST_TARGET)

# Clean up the generated files
clean:
	rm -f $(TARGET) $(TEST_TARGET) $(OBJ) $(TEST_OBJ)

.PHONY: clean test

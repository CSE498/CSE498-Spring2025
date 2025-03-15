CXX = g++
CXXFLAGS = -std=c++2a -g -pthread -Wall -Wextra -I../src -I../../third-party/Catch/single_include/catch2/

# Directories
SRC_DIR = ../src
TEST_DIR = .

# Source and Test Files
SRC_FILES = $(wildcard $(SRC_DIR)/*.cpp)
TEST_FILES = $(wildcard $(TEST_DIR)/*.cpp)

# Object files
OBJS = $(SRC_FILES:.cpp=.o)
TEST_OBJS = $(TEST_FILES:.cpp=.o)

# Default target (run tests)
default: test

# Compile source files into object files
$(SRC_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Compile test files into object files
$(TEST_DIR)/%.o: $(TEST_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Build and run tests
test: $(OBJS) $(TEST_OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) $(TEST_OBJS) -o test.out
	./test.out

# Clean build files
clean:
	rm -f $(SRC_DIR)/*.o $(TEST_DIR)/*.o test.out

# Optional: Add a rule for cleaning specific files
clean-tests:
	rm -f $(TEST_DIR)/*.o test.out
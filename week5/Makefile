# Compiler and flags
CXX = g++
CXXFLAGS = -Wall -std=c++17

# Find all .cpp files in the current directory
SOURCES = $(wildcard *.cpp)

# Create corresponding executables for each .cpp file
EXECS = $(SOURCES:.cpp=)

# Default target: build all executables
all: $(EXECS)

# Rule to compile each .cpp file into an executable
%: %.cpp
	$(CXX) $(CXXFLAGS) -o $@ $<

# Clean target to remove all executables
clean:
	rm -f $(EXECS)
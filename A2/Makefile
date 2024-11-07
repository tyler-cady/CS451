# Compiler and flags
CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++23

# Targets
TARGETS = freecell parkinglot

# Default target
all: $(TARGETS)

# Rule to build geo executable
parkinglot: parkinglot.o
	$(CXX) $(CXXFLAGS) -o parkinglot parkinglot.o

# Rule to build pcp executable
freecell: freecell.o
	$(CXX) $(CXXFLAGS) -o freecell freecell.o

# Rule to build geo object file
parkinglot.o: parkinglot.cpp
	$(CXX) $(CXXFLAGS) -c parkinglot.cpp

# Rule to build pcp object file
freecell.o: freecell.cpp
	$(CXX) $(CXXFLAGS) -c freecell.cpp

# Clean up build artifacts
clean:
	rm -f $(TARGETS) *.o

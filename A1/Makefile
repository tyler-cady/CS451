# Compiler and flags
CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++11

# Targets
TARGETS = geo pcp

# Default target
all: $(TARGETS)

# Rule to build geo executable
geo: geo.o
	$(CXX) $(CXXFLAGS) -o geo geo.o

# Rule to build pcp executable
pcp: pcp.o
	$(CXX) $(CXXFLAGS) -o pcp pcp.o

# Rule to build geo object file
geo.o: geo.cpp
	$(CXX) $(CXXFLAGS) -c geo.cpp

# Rule to build pcp object file
pcp.o: pcp.cpp
	$(CXX) $(CXXFLAGS) -c pcp.cpp

# Clean up build artifacts
clean:
	rm -f $(TARGETS) *.o

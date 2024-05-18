# Variables
CXX = g++
CXXFLAGS = -std=c++17 -Wall -pthread

# Target executable
TARGET = mini1

# Source files
SRCS = mini1.cpp

# Object files
OBJS = $(SRCS:.cpp=.o)

# Default target
all: run

# Link the target executable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

# Compile .cpp files to .o files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up build artifacts
clean:
	rm -f $(OBJS) $(TARGET)

# Run the program
run: $(TARGET)
	./$(TARGET)
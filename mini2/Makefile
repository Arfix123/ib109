# Variables
CXX = mpic++
CXXFLAGS = -std=c++17 -Wall -pthread

# Target executable
TARGET = mini2

# Source files
SRCS = *.cpp

# Header files
HDRS = *.h *.hpp

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
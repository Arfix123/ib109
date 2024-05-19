# Target executable
TARGET = coins

# Default target
all: run

# Link the target executable
$(TARGET): *.cpp *.h
	mpic++ -std=c++20 -o $(TARGET) *.cpp *.h

# Clean up build artifacts
clean:
	rm -f $(TARGET)

# Run the program
run: $(TARGET)
	mpirun -np 6 $(TARGET)
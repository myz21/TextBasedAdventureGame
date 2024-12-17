CC = gcc
CFLAGS = -Wall -std=c11

# Source files
SRCS = TextBasedAdventureGame.c GameFunctions.c Player.c Room.c Enemy.c

# Object files
OBJS = $(SRCS:.c=.o)

# Executable name
TARGET = game.exe

# Default rule
all: $(TARGET)

# Linking object files to create the executable
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

# Compiling source files to object files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up generated files
clean:
	rm -f $(TARGET) $(OBJS)

# Run the game
run: $(TARGET)
	./$(TARGET)

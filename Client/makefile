
CC = gcc
CFLAGS = -Wall -Wextra

# List of source files
SRCS = client.c create_client.c Globals.c main_client.c Utilities.c

# Output executable
TARGET = main

all: $(TARGET)

$(TARGET): $(SRCS)
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -f $(TARGET)

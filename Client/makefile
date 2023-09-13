
CC = gcc
CFLAGS = -Wall -Wextra

# List of source files
SRCS = Client.c MainClient.c Utilities.c

# Output executable
TARGET = main

all: $(TARGET)

$(TARGET): $(SRCS)
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -f $(TARGET)

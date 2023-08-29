
CC = gcc
CFLAGS = -Wall -Wextra

# List of source files
SRCS = create_server.c deliting_server.c Globals.c main_server.c requests_server.c send_prints.c server.c Testing.c Tree.c Utilities.c

# Output executable
TARGET = main

all: $(TARGET)

$(TARGET): $(SRCS)
	$(CC) $(CFLAGS) -g -o $@ $^

clean:
	rm -f $(TARGET)

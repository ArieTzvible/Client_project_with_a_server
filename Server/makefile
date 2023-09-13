
CC = gcc
CFLAGS = -Wall -Wextra

# List of source files
SRCS = Create.c Deliting.c Globals.c MainServer.c Requests.c SendPrints.c Server.c Testing.c Tree.c Utilities.c

# Output executable
TARGET = main

all: $(TARGET)

$(TARGET): $(SRCS)
	$(CC) $(CFLAGS) -g -o $@ $^

clean:
	rm -f $(TARGET)

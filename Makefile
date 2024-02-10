CC = gcc
CFLAGS = -Wall -Wextra -Werror 
LDFLAGS = -lm  # Add any necessary linker flags or libraries here

SRCS = main.c avl.c test.c avl_tests.c# List all your source files here
OBJS = $(SRCS:.c=.o)

TARGET = main

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(TARGET) $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)

CC=gcc
CFLAGS=-g -std=c11 -pedantic -Wall -Wextra
LDLIBS= -lm

SRCS = $(wildcard *.c)
OBJS = $(SRCS:.c=.o)
EXEC = main

all: $(EXEC)

main-m.o: bitset.o main.c
	$(CC) $(CFLAGS) -DUSE_INLINE bitset.o -o -c main

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Linking
$(EXEC): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(EXEC)

# Clean target
clean:
	rm -f $(OBJS) $(EXEC)
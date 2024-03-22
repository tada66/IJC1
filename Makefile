CC=gcc
CFLAGS=-g -std=c11 -pedantic -Wall -Wextra -fsanitize=address
LDFLAGS=-g -std=c11 -pedantic -Wall -Wextra -lm -fsanitize=address

#SRCS = $(wildcard *.c)
#OBJS = $(SRCS:.c=.o)
#EXEC = main

all: primes primes-i

primes: primes.o eratosthenes.o #error.o
	$(CC) $(LDFLAGS) -o $@ $^

primes-i: primes-i.o eratosthenes-i.o #error.o
	$(CC) $(LDFLAGS) -DUSE_INLINE -o $@ $^

primes-i.o: primes.c bitset.h eratosthenes.h
	$(CC) $(CFLAGS) -c -o $@ primes.c -DUSE_INLINE

eratosthenes-i.o: eratosthenes.c eratosthenes.h bitset.h
	$(CC) $(CFLAGS) -c -o $@ eratosthenes.c -DUSE_INLINE

primes.o: primes.c bitset.h eratosthenes.h
	$(CC) $(CFLAGS) -c -o $@ primes.c

eratosthenes.o: eratosthenes.c eratosthenes.h bitset.h
	$(CC) $(CFLAGS) -c -o $@ eratosthenes.c

# Linking
#$(EXEC): $(OBJS)
#	$(CC) $(CFLAGS) $(OBJS) -o $(EXEC)

# Clean target
clean:
	rm *.o
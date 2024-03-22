# Makefile
# Řešení IJC-DU1, příklad a), 22.3.2024
# Autor: Tadeáš Horák, FIT
# Přeloženo: gcc 11.4.0
CC=gcc
CFLAGS=-g -std=c11 -pedantic -Wall -Wextra -fsanitize=address
LDFLAGS=-g -std=c11 -pedantic -Wall -Wextra -lm -fsanitize=address

#SRCS = $(wildcard *.c)
#OBJS = $(SRCS:.c=.o)
#EXEC = main

all: primes primes-i

primes: primes.o eratosthenes.o error.o
	$(CC) $(LDFLAGS) -o $@ $^

primes-i: primes-i.o eratosthenes-i.o error.o
	$(CC) $(LDFLAGS) -DUSE_INLINE -o $@ $^

primes-i.o: primes.c bitset.h eratosthenes.h
	$(CC) $(CFLAGS) -c -o $@ primes.c -DUSE_INLINE

eratosthenes-i.o: eratosthenes.c eratosthenes.h bitset.h
	$(CC) $(CFLAGS) -c -o $@ eratosthenes.c -DUSE_INLINE

primes.o: primes.c bitset.h eratosthenes.h
	$(CC) $(CFLAGS) -c -o $@ primes.c

eratosthenes.o: eratosthenes.c eratosthenes.h bitset.h
	$(CC) $(CFLAGS) -c -o $@ eratosthenes.c

error.o: error.c error.h
	$(CC) $(CFLAGS) -c -o $@ error.c

# Linking
#$(EXEC): $(OBJS)
#	$(CC) $(CFLAGS) $(OBJS) -o $(EXEC)

# Clean target
clean:
	rm *.o

run: all
	ulimit -s 100000 && ./primes 
	ulimit -s 100000 && ./primes-i
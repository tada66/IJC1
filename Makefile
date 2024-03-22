# Makefile
# Řešení IJC-DU1, příklad a), 22.3.2024
# Autor: Tadeáš Horák, FIT
# Přeloženo: gcc 11.4.0
CC=gcc
CFLAGS=-g -std=c11 -pedantic -Wall -Wextra -O2 -fsanitize=address
LDFLAGS=-g -std=c11 -pedantic -Wall -Wextra -O2 -fsanitize=address

#SRCS = $(wildcard *.c)
#OBJS = $(SRCS:.c=.o)
#EXEC = main

all: primes primes-i

primes: primes.o eratosthenes.o error.o
	$(CC) $(LDFLAGS) -o $@ $^ -lm

primes-i: primes-i.o eratosthenes-i.o error.o
	$(CC) $(LDFLAGS) -DUSE_INLINE -o $@ $^ -lm

primes-i.o: primes.c bitset.h eratosthenes.h
	$(CC) $(CFLAGS) -DUSE_INLINE -c -o $@ primes.c

eratosthenes-i.o: eratosthenes.c eratosthenes.h bitset.h
	$(CC) $(CFLAGS) -DUSE_INLINE -c -o $@ eratosthenes.c

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
.PHONY: clean
clean:
	rm *.o

.PHONY: run
run: all
	ulimit -s 100000 && ./primes 
	ulimit -s 100000 && ./primes-i
	make clean

.PHONY: zip
zip: all
	zip xhorakt00.zip *.c *.h Makefile
	make clean
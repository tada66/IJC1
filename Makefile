# Makefile
# Řešení IJC-DU1, příklad a), 22.3.2024
# Autor: Tadeáš Horák, FIT
# Přeloženo: gcc 11.4.0
# Vytvoření spustitelných binárních souborů primes, primes-i a no-comment
# primes-i využívá inline funkce místo maker
CC=gcc
CFLAGS=-g -std=c11 -pedantic -Wall -Wextra -O2
LDFLAGS=-g -std=c11 -pedantic -Wall -Wextra -O2	#-02 for optimalization, roughly halves the execute time

all: primes primes-i no-comment

primes: primes.o eratosthenes.o error.o
	$(CC) $(LDFLAGS) -o $@ $^ -lm

primes-i: primes-i.o eratosthenes-i.o error.o
	$(CC) $(LDFLAGS) -DUSE_INLINE -o $@ $^ -lm

no-comment: no-comment.o error.o
	$(CC) $(LDFLAGS) -o $@ $^

no-comment-o: no-comment.c
	$(CC) $(CFLAGS) -c -o $@ no-comment.c

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
	rm -f *.o

.PHONY: run
run: all
	ulimit -s 100000 && ./primes 
	ulimit -s 100000 && ./primes-i

.PHONY: zip
zip: all
	zip xhorakt00.zip *.c *.h Makefile
	make clean
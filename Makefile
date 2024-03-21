EXEC
CC=gcc
CFLAGS=-g -std=c11 -pedantic -Wall -Wextra
LDLIBS=-lm

all: main-i main-m

main-m.o: bitset.o main.c
	$(CC) $(CFLAGS) -DUsE_INLINE bitset.o -o -c main

main-i: 
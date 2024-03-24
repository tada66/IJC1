// primes.c
// Řešení IJC-DU1, příklad a), 21.3.2024
// Autor: Tadeáš Horák, FIT
// Přeloženo: gcc 11.4.0
// Výpočet 10 největších prvočísel až po 666 000 000 díky algoritmu Eratosthenovo síto
#include <time.h>
#include "eratosthenes.h"

#define ARRAY_SIZE 666000000
#define PRINT_SIZE 10

void printerat(bitset_t bit_array){ //Prints the last PRINT_SIZE prime numbers calculated by eratosthenes algorithm 
    unsigned long lastprimes[PRINT_SIZE] = {0, };
    int count = 9;
    for(unsigned long i=bitset_size(bit_array)-1; i>0; i--){
        if(bitset_getbit(bit_array, i)){
            lastprimes[count] = i;
            if(count==0)
                break;
            count--;
        }
    }
    for(int i=0; i<PRINT_SIZE; i++)
        printf("%ld\n", lastprimes[i]);
}

int main(){
    clock_t start = clock();    //Starts the clock

    bitset_create(bit_array, ARRAY_SIZE);
    eratosthenes(bit_array);    //Calculate primes
    printerat(bit_array);
    
    fprintf(stderr, "Time=%.3g\n", (double)(clock()-start)/CLOCKS_PER_SEC);
}
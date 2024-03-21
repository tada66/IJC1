#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "eratosthenes.c"

#define ARRAY_SIZE 666000000
#define PRINT_SIZE 10

void printerat(bitset_t bit_array){
    unsigned long lastprimes[PRINT_SIZE];
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
    clock_t start = clock();

    bitset_alloc(bit_array, ARRAY_SIZE);
    bitset_fill(bit_array, 1);
    printf("%ld", *bit_array);
    eratosthenes(bit_array);
    printerat(bit_array);
    
    fprintf(stderr, "Time=%.3g\n", (double)(clock()-start)/CLOCKS_PER_SEC);
}
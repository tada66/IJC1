#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
//maybe copy bitset.c here if inline doesnt work?

#include "bitset.h"
#ifdef USE_INLINE
extern inline void bitset_free(bitset_index_t *name);
extern inline unsigned long bitset_size(bitset_index_t *name);
extern inline void bitset_fill(bitset_index_t *name, bool set);
extern inline void bitset_setbit(bitset_index_t *name, unsigned long index, bool set);
extern inline unsigned long bitset_getbit(bitset_index_t *name, unsigned long index);
#endif

#define ARRAY_SIZE 666000000

int main(){
    clock_t start = clock();
    bitset_alloc(bit_array, ARRAY_SIZE);
    bitset_fill(bit_array, 1);
    unsigned long sqrtn = sqrt(ARRAY_SIZE);
    for(unsigned long i=2; i<=sqrtn; i++){
        if(bitset_getbit(bit_array, i)){
            for(unsigned long j=i*i; j<ARRAY_SIZE; j+=i){
                bitset_setbit(bit_array, j, 0);
            }
        }
    }
    unsigned long last10[10];
    int count = 9;
    for(unsigned long i=bitset_size(bit_array)-1; i>0; i--){
        if(bitset_getbit(bit_array, i)){
            last10[count] = i;
            if(count==0)
                break;
            count--;
        }
    }
    for(int i=0; i<10; i++)
        printf("%ld\n", last10[i]);
    fprintf(stderr, "Time=%.3g\n", (double)(clock()-start)/CLOCKS_PER_SEC);
    return 0;
}
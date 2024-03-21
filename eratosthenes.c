#include <stdio.h>
#include <math.h>
#include <stdlib.h>
//maybe copy bitset.c here if inline doesnt work?

#include "bitset.h"
#ifdef USE_INLINE
extern inline void bitset_free(bitset_index_t *name);
extern inline unsigned long bitset_size(bitset_index_t *name);
extern inline void bitset_fill(bitset_index_t *name, bool set);
extern inline void bitset_setbit(bitset_index_t *name, unsigned long index, bool set);
extern inline unsigned long bitset_getbit(bitset_index_t *name, unsigned long index);
#endif

#define ARRAY_SIZE 12000000

int main(){
    bitset_alloc(bit_array, ARRAY_SIZE);
    bitset_fill(bit_array, true);
    unsigned long sqrtn = sqrt(ARRAY_SIZE);
    for(unsigned long i=2; i<=sqrtn; i++){
        if(bitset_getbit(bit_array, i)){
            for(unsigned long j=i*i; j<ARRAY_SIZE; j+=i){
                bitset_setbit(bit_array, j, false);
            }
        }
    }
    for(unsigned long i=0; i<bitset_size(bit_array); i++){
        if(bitset_getbit(bit_array, i))
            printf("%ld, ", i);
    }
    printf("\n");
    return 0;
}
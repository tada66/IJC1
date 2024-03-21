#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

#include "bitset.h"
#ifdef USE_INLINE
extern inline void bitset_free(bitset_index_t *name);
extern inline unsigned long bitset_size(bitset_index_t *name);
extern inline void bitset_fill(bitset_index_t *name, bool set);
extern inline void bitset_setbit(bitset_index_t *name, unsigned long index, bool set);
extern inline unsigned long bitset_getbit(bitset_index_t *name, unsigned long index);
#endif

void eratosthenes(bitset_t bit_array){
    unsigned long size = bitset_size(bit_array);
    unsigned long sqrtn = sqrt(size);
    for(unsigned long i=2; i<=sqrtn; i++){
        if(bitset_getbit(bit_array, i)){
            for(unsigned long j=i*i; j<size; j+=i){
                bitset_setbit(bit_array, j, 0);
            }
        }
    }
}
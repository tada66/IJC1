// eratosthenes.c
// Řešení IJC-DU1, příklad a), 21.3.2024
// Autor: Tadeáš Horák, FIT
// Přeloženo: gcc 11.4.0
// Implementace algoritmu eratosthenova síta pro výpočet prvočísel
#include <math.h>

#include "eratosthenes.h"

#ifdef USE_INLINE
extern inline void bitset_free(bitset_index_t *name);
extern inline unsigned long bitset_size(bitset_index_t *name);
extern inline void bitset_fill(bitset_index_t *name, bool set);
extern inline void bitset_setbit(bitset_index_t *name, unsigned long index, bool set);
extern inline unsigned long bitset_getbit(bitset_index_t *name, unsigned long index);
#endif


void eratosthenes(bitset_t bit_array){
    bitset_fill(bit_array, 1);                  //Fill the whole array with 1s
    unsigned long size = bitset_size(bit_array);
    unsigned long sqrtn = sqrt(size);           //Square root is calculated and saved for use in for loops condition, this improves performance
    for(unsigned long i=2; i<=sqrtn; i++){
        if(bitset_getbit(bit_array, i)){
            for(unsigned long j=i*i; j<size; j+=i){     //https://en.wikipedia.org/wiki/Sieve_of_Eratosthenes
                bitset_setbit(bit_array, j, 0);
            }
        }
    }
}
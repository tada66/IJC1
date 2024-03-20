#include <stdbool.h>
#include <assert.h>

#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include "error.h"

typedef struct {
}bitset_t;

typedef unsigned long bitset_index_t;

#define bitset_index_bits(count) (count-1+16*sizeof(unsigned long))/sizeof(unsigned long)/8 

#define bitset_create(name,size)                            \
    static_assert(size > 0);                                \
    printf("%ld\n", bitset_index_bits(size));               \
    bitset_index_t name[bitset_index_bits(size)]= {size}



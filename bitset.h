#include <stdbool.h>
#include <assert.h>

#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include "error.h"

typedef struct {
}bitset_t;

typedef unsigned long bitset_index_t;


#define bitset_create(name,size)        \
    static_assert(size > 0);            \
    bitset_index_t name[(size-1+2*sizeof(unsigned long))/sizeof(unsigned long)]= {size}



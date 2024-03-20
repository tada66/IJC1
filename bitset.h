#include <stdbool.h>
#include <assert.h>

typedef struct {
}bitset_t;

typedef unsigned long bitset_index_t;

#define bitset_index_bits(count) (count-1+16*sizeof(unsigned long))/sizeof(unsigned long)/8 

#define bitset_create(name,size)                            \
    static_assert(size > 0);                                \
    printf("bitset_create: bytes=%ld\n", bitset_index_bits(size));               \
    bitset_index_t name[bitset_index_bits(size)]= {size}

#define bitset_alloc(name, size)                            \
    assert(size > 0);                                \
    printf("bitset_alloc: bytes=%ld\n", bitset_index_bits(size));               \
    bitset_index_t* name = calloc(bitset_index_bits(size), sizeof(unsigned long));   \
    if(&name == NULL)\
        fprintf(stderr, "bitset_alloc: Chyba alokace paměti");  /*TODO EXIT APP !!*/   \
    name[0] = size


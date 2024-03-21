#include <stdbool.h>
#include <assert.h>
#include <stdint.h>

typedef struct {
}bitset_t;

typedef unsigned long bitset_index_t;

#define bitset_index_bits(count) (count-1+16*sizeof(unsigned long))/sizeof(unsigned long)/8 

#define bitset_create(name,size)                            \
    static_assert(size > 0);                                \
    bitset_index_t name[bitset_index_bits(size)]= {size}

#define bitset_alloc(name, size)                            \
    assert(size > 0);                                \
    bitset_index_t* name = calloc(bitset_index_bits(size), sizeof(unsigned long));   \
    if(&name == NULL){\
        fprintf(stderr, "bitset_alloc: Chyba alokace paměti");  /*TODO EXIT APP !!*/   \
        exit(1);\
    }\
    name[0] = size

#define bitset_free(name)\
    free(&name);

#define bitset_size(name)\
    name[0]

#define bitset_fill(name, set)\
    for(int i=0; i<bitset_size(name)/sizeof(unsigned long)/8; i++)\
        if(set)\
            name[i+1]=-1;\
        else\
            name[i+1]=0

#define bitset_setbit(name, index, set)\
    do{\
    if(index>=bitset_size(name)){\
        fprintf(stderr, "Index out of range!\n");       /*THIS MUST BE DONE WITH ERROR_EXIT FROM ERROR.C */ \
        exit(1);\
    }\
    unsigned long num = name[index/(sizeof(unsigned long)*8)+1];\
    int ind = index%(sizeof(unsigned long)*8);\
    uint64_t bitscompare;\
    if(set){\
        bitscompare = 1ULL << ind;\
        int bits = sizeof(unsigned long)*8;\
        num = num | bitscompare;\
    }\
    else{\
        bitscompare = ~(1ULL << ind);\
        int bits = sizeof(unsigned long)*8;\
        num = num & bitscompare;\
    }\
    int bbits = sizeof(unsigned long)*8;\
    name[index/(sizeof(unsigned long)*8)+1] = num;\
    } while (0)

#define bitset_getbit(name, index)\
    ({ \
    if(index>=bitset_size(name)){\
        fprintf(stderr, "Index out of range!\n");       /*THIS MUST BE DONE WITH ERROR_EXIT FROM ERROR.C */ \
        exit(1);\
    }\
    unsigned long num = name[index / (sizeof(unsigned long)*8)+1]; \
    int bits = sizeof(unsigned long) * 8; \
    (num >> (bits - index % (sizeof(unsigned long) * 8))) & 1; \
})



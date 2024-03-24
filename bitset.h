// bitset.h
// Řešení IJC-DU1, příklad a), 20.3.2024
// Autor: Tadeáš Horák, FIT
// Přeloženo: gcc 11.4.0
// Makra a inline funkce pro práci s bitovým polem
#include <stdbool.h>
#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "error.h"

typedef unsigned long *bitset_t;

typedef unsigned long bitset_index_t;

#define bitset_index_bits(count) (count-1+16*sizeof(unsigned long))/sizeof(unsigned long)/8 

//Create the bit array in stack
#define bitset_create(name,size)                            \
    static_assert(size > 0);                                \
    bitset_index_t name[bitset_index_bits(size)]= {size}

//Allocate memory in heap and create the bit array 
#define bitset_alloc(name, size)                            \
    assert(size > 0);                                \
    bitset_t name = calloc(bitset_index_bits(size), sizeof(unsigned long));   \
    if(&name == NULL){\
        fprintf(stderr, "bitset_alloc: Chyba alokace paměti");\
        exit(1);\
    }\
    name[0] = size

//Create and alloc cannot be done by inline functions, however, the others can
#ifndef USE_INLINE  //If USE_INLINE is not set by -DUSE_INLINE flag we use macros

//frees the memory allocated by bitset_alloc
#define bitset_free(name)\
    free(&name);

//returns the requested size of the array
#define bitset_size(name)\
    name[0]

//Fills the whole array with 0s or 1s depending on 'set' (true=1s)
#define bitset_fill(name, set)\
    for(unsigned i=0; i<(bitset_size(name)+(sizeof(unsigned long)*8)-1)/sizeof(unsigned long)/8; i++)\
    {\
        if(set)\
            name[i+1]=-1;\
        else\
            name[i+1]=0;\
    }

//Set a single bit of the array to either 1 or 0
#define bitset_setbit(name, index, set)\
    do{\
    if(index>=bitset_size(name))\
        error_exit("bitset_setbit: Index %lu mimo rozsah 0..%lu",(unsigned long)index, bitset_size(name)-1);\
    unsigned long num = name[index/(sizeof(unsigned long)*8)+1];\
    int ind = index%(sizeof(unsigned long)*8);\
    uint64_t bitscompare;\
    if(set){\
        bitscompare = 1ULL << ind;\
        num = num | bitscompare;\
    }\
    else{\
        bitscompare = ~(1ULL << ind);\
        num = num & bitscompare;\
    }\
    name[index/(sizeof(unsigned long)*8)+1] = num;\
    } while (0)    

//Get the value of a single bit in the array
#define bitset_getbit(name, index)\
    (index>=bitset_size(name)) ? \
    (error_exit("bitset_getbit: Index %lu mimo rozsah 0..%lu",(unsigned long)index, bitset_size(name)-1),0) : \
    ((name[index / (sizeof(unsigned long) * 8)+1] >> (index % (sizeof(unsigned long) * 8))) & 1)

#else
    //frees the memory allocated by bitset_alloc
    inline void bitset_free(bitset_index_t *name){
        free(name);
    }

    //returns the requested size of the array
    inline unsigned long bitset_size(bitset_index_t *name){
        return name[0];
    }

    //Fills the whole array with 0s or 1s depending on 'set' (true=1s)
    inline void bitset_fill(bitset_index_t *name, bool set){
    for(unsigned i=0; i<(bitset_size(name)+(sizeof(unsigned long)*8)-1)/sizeof(unsigned long)/8; i++)
        if(set)
            name[i+1]=-1;
        else
            name[i+1]=0;
    }

    //Set a single bit of the array to either 1 or 0
    inline void bitset_setbit(bitset_index_t *name, unsigned long index, bool set){
        if(index>=bitset_size(name))
            error_exit("bitset_setbit: Index %lu mimo rozsah 0..%lu",(unsigned long)index, bitset_size(name)-1);\
        unsigned long num = name[index/(sizeof(unsigned long)*8)+1];
        int ind = index%(sizeof(unsigned long)*8);
        uint64_t bitscompare;
        if(set){
            bitscompare = 1ULL << ind;
            num = num | bitscompare;
        }
        else{
            bitscompare = ~(1ULL << ind);
            num = num & bitscompare;
        }
        name[index/(sizeof(unsigned long)*8)+1] = num;
    }

    //Get the value of a single bit in the array
    inline unsigned long bitset_getbit(bitset_index_t *name, unsigned long index){
        return (index>=bitset_size(name) && index<1) ? 
        (error_exit("bitset_getbit: Index %lu mimo rozsah 0..%lu",(unsigned long)index, bitset_size(name)-1),0) :
        ((name[index / (sizeof(unsigned long) * 8)+1] >> (index % (sizeof(unsigned long) * 8))) & 1);
    }

#endif

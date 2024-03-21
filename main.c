#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#ifdef USE_INLINE
#include "bitset.c"
#else
#include "bitset.h"
#endif

int main(){ 
    bitset_create(cpole, 128);
    printf("Size of arr=%ld\n", sizeof(cpole)*8);
    printf("declared=%ld\n", bitset_size(cpole));
    bitset_fill(cpole, true);
    bitset_setbit(cpole, 63, false);
    printf("getbit=%ld\n", bitset_getbit(cpole, 127));
    for(unsigned i=0; i<bitset_size(cpole)/sizeof(unsigned long)/8; i++){
        printf("%ld, ", cpole[i+1]);
    }
    printf("\n");

    int bits = sizeof(unsigned long)*8;
    for(int i = 1; i <= bits; i++)
        printf("%ld", (cpole[1] >> (bits - i)) & 1);
    
    printf("\n\n\n");
    /*
    bitset_alloc(apole, 128);
    printf("Size of arr=%ld\n", sizeof(apole)*8);
    printf("declared=%ld\n", bitset_size(apole));
    bitset_fill(apole, true);
    bitset_setbit(apole, 0, 1);
    for(int i=0; i<bitset_size(apole)/sizeof(unsigned long)/8; i++){
        printf("%ld, ", apole[i+1]);
    }
    printf("\n");*/
    return 0;
}
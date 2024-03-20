#include <stdlib.h>
#include <stdio.h>
#include "bitset.h"

void main(){
    bitset_create(cpole, 128);
    printf("Size of arr=%ld\n", sizeof(cpole)*8);
    printf("declared=%ld\n", bitset_size(cpole));
    bitset_fill(cpole, true);
    for(int i=0; i<bitset_size(cpole)/sizeof(unsigned long)/8+1; i++){
        printf("%ld, ", cpole[i]);
    }
    printf("\n");
    printf("\n\n\n");

    bitset_alloc(apole, 128);
    printf("Size of arr=%ld\n", sizeof(apole)*8);
    printf("declared=%ld\n", bitset_size(apole));
    bitset_fill(apole, true);
    for(int i=0; i<bitset_size(apole)/sizeof(unsigned long)/8+1; i++){
        printf("%ld, ", apole[i]);
    }
    printf("\n");
}
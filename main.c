#include <stdlib.h>
#include <stdio.h>
#include "bitset.h"

void main(){
    bitset_create(cpole, 128);
    printf("Size of arr=%ld\n", sizeof(cpole)*8);
    for(int i=0; i<sizeof(cpole)/sizeof(unsigned long); i++){
        printf("%ld, ", cpole[i]);
    }
    printf("\n\n\n");

    bitset_alloc(apole, 128);
    printf("Size of arr=%ld\n", sizeof(apole)*8);
    for(int i=0; i<sizeof(apole)/sizeof(unsigned long); i++){
        printf("%ld, ", apole[i]);
    }
    printf("\n");
}
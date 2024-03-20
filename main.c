#include <stdlib.h>
#include <stdio.h>
#include "bitset.h"

void main(){
    bitset_create(bruhpole, 50);
    printf("Size of arr=%ld\n", sizeof(bruhpole));
    for(int i=0; i<sizeof(bruhpole)/sizeof(unsigned long); i++){
        printf("%ld, ", bruhpole[i]);
    }
    printf("\n");
}
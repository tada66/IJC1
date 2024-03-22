// no-comment.c
// Řešení IJC-DU1, příklad a), 21.3.2024
// Autor: Tadeáš Horák, FIT
// Přeloženo: gcc 11.4.0
// Program pro odstranění všech komentářů ze souboru dodaného argumentem, případně ze stdin
#include <stdio.h>

#include "error.h"

int main(int argc, char **argv){
    if(argc>2)
        error_exit("Příliš mnoho argumentů!\n");
    FILE *file;
    if(argc==2)
        file = fopen(argv[1], "r");
    else
        file = stdin;
    if(file==NULL)
        error_exit("Soubor %s není přístupný!", argv[1]);
    int state = 0;
    int c;
    while ((c=getc(file)) != EOF) {
        switch(state) {
            case 0: if(c=='/') state=1;
                else if (c=='"') { state=7; putchar(c); }
                else if (c=='\'') { state=9; putchar(c); }
                else putchar(c);
                break;
            case 1: if(c=='/') state=2;
                else if(c=='*') state=5;
                else { state=0; putchar('/'); putchar(c); }
                break;
            case 2: if(c=='\n') { state=0; putchar('\n'); }
                else if(c=='\\') state=3;
                break;
            case 3: if(c=='\\') state=3;
                else if(c=='\n') state=4;
                else { state=2; }
                break;
            case 4: if(c=='\\') state=3;
                else if(c=='\n') { state=0; putchar('\n'); }
                else { state=2; }
                break;
            case 5: if(c=='*') state=6;
                break;
            case 6: if(c=='*') state=6; /*abc*  */ //valid comment
                else if (c=='/') { state=0; putchar(' '); }
                else state=5;
                break;
            case 7: if(c=='\\') { state=8; putchar('\\');} 
                else if(c=='"') { state=0; putchar('"'); }
                else { putchar(c);}
                break;
            case 8: state=7;
                putchar(c);
                break;
            case 9: if(c=='\\') { state=10; putchar('\\');} 
                else if(c=='\'') { state=0; putchar('\''); }
                else { putchar(c);}
                break;
            case 10: state=9;
                putchar(c);
                break;
        }
    }
    fclose(file);
    if(state!=0) 
        error_exit("Stavový automat skončil ve stavu %d! Neobsahuje soubor nezakončený komentář?\n", state);
}
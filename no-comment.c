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
        file = fopen(argv[1], "r");     //If an argument is provided, we assume it's a file and open it, otherwise use stdin
    else
        file = stdin;
    if(file==NULL)
        error_exit("Soubor %s není přístupný!", argv[1]);       //and we also have to check if that file can be opened
    int state = 0;  // 0=default state, not inside a comment, or quotes
    int c;
    while ((c=getc(file)) != EOF) {
        switch(state) {
            case 0: if(c=='/') state=1;     //default state
                else if (c=='"') { state=7; putchar(c); }
                else if (c=='\'') { state=9; putchar(c); }
                else putchar(c);
                break;
            case 1: if(c=='/') state=2;     //Start of a comment?
                else if(c=='*') state=5;
                else { state=0; putchar('/'); putchar(c); }
                break;
            case 2: if(c=='\n') { state=0; putchar('\n'); }     //Double slash comment, ignore all until end of line, which we print out
                else if(c=='\\') state=3;
                break;
            case 3: if(c=='\\') state=3;    //back slash added, we ignore one more line
                else if(c=='\n') state=4;
                else { state=2; }
                break;
            case 4: if(c=='\\') state=3;    //or more if more lines if more back slashes are added
                else if(c=='\n') { state=0; putchar('\n'); }
                else { state=2; }
                break;
            case 5: if(c=='*') state=6;     // we are in a /* comment, wait for * to signal end of comment 
                break;
            case 6: if(c=='*') state=6; /*abc*  */ //is a valid comment, you learn something new everyday
                else if (c=='/') { state=0; putchar(' '); } // */ comment has ended return to default state
                else state=5;
                break;
            case 7: if(c=='\\') { state=8; putchar('\\');}  // we are in double quotes, ignore all possible comments
                else if(c=='"') { state=0; putchar('"'); }
                else { putchar(c);}
                break;
            case 8: state=7;    // if there is an escape character before end quotes, ignore the quote
                putchar(c);
                break;
            case 9: if(c=='\\') { state=10; putchar('\\');}  // we are in single quotes, ignore all possible comments
                else if(c=='\'') { state=0; putchar('\''); }
                else { putchar(c);}
                break;
            case 10: state=9;   // if there is an escape character before end quotes, ignore the quote
                putchar(c);
                break;
        }
    }
    fclose(file);   //close file so dont have a memory leak
    if(state!=0)    //If we haven't returned to default state the file contains unclosed comment or quotes
        error_exit("Stavový automat skončil ve stavu %d! Neobsahuje soubor nezakončený komentář?\n", state);
}
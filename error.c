// error.c
// Řešení IJC-DU1, příklad a), 22.3.2024
// Autor: Tadeáš Horák, FIT
// Přeloženo: gcc 11.4.0
// Řízení chybových zpráv
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>

void warning(const char *fmt, ...){
    va_list args;
    va_start (args, fmt);
    fprintf(stderr, "Warning: ");
    vfprintf (stderr, fmt, args);
    fprintf(stderr, "\n");
    va_end (args);
}

void error_exit(const char *fmt, ...){
    va_list args;
    va_start (args, fmt);
    fprintf(stderr, "Error: ");
    vfprintf (stderr, fmt, args);
    fprintf(stderr, "\n");
    va_end (args);
    exit(1);
}
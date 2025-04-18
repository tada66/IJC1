// bitset.c
// Řešení IJC-DU1, příklad a), 20.3.2024
// Autor: Tadeáš Horák, FIT
// Přeloženo: gcc 11.4.0
// Prototypy inline funkcí v bitset.h
#include "bitset.h"

#ifdef USE_INLINE
extern inline void bitset_free(bitset_index_t *name);
extern inline unsigned long bitset_size(bitset_index_t *name);
extern inline void bitset_fill(bitset_index_t *name, bool set);
extern inline void bitset_setbit(bitset_index_t *name, unsigned long index, bool set);
extern inline unsigned long bitset_getbit(bitset_index_t *name, unsigned long index);
#endif

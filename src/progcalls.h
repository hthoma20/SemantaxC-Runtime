#ifndef PROGCALLS_H
#define PROGCALLS_H

#include "types.h"

/**
 * Pop:
 * 0 - Collectable* arg
 * 1 - Func* fun
 * Push:
 * 0 - void* result
 */
void invokefun();

/**
 * Pop:
 * 0 - Int* index
 * 1 - Array* array
 * Push:
 * 0 - void* result
 */
void arrayget();

/**
 * Pop:
 * 0 - Collectable* val
 * 1 - Int* index
 * 2 - Array* array
 * Push:
 */
void arrayset();

/**
 * Pop:
 * 0 - Func* supplier
 * 1 - Int* length
 * Push:
 * 0 - Array*
 */
void initarray();

/**
 * Pop:
 * 0 - Array* array
 * Push:
 * 0 - Int* length
 */
void arraylen();

/**
 * Pop:
 * 0 - String* str
 * Push:
 */
void printstring();

/**
 * Pop:
 * 0 - Int* n
 * Push:
 */
void printint();

/**
 * Pop:
 * 0 - Int* b
 * 1 - Int* a
 * Push:
 * 0 - Int* a + b
 */
void addint();

/**
 * Pop:
 * 0 - Int* n
 * Push:
 * 0 - Int* -n
 */
void negateint();

/**
 * Pop:
 * 0 - Int* a
 * 1 - Int* b
 * Push:
 * 0 - Bool* a >= b
 */
void gteint();

/**
 * Pop:
 * 0 - Int* a
 * 1 - Int* b
 * Push:
 * 0 - Bool* a > b
 */
void gtint();

/**
 * Pop:
 * 0 - Int* a
 * 1 - Int* b
 * Push:
 * 0 - Bool* a == b
 */
void eqint();

/**
 * Pop:
 * 0 - Bool* b
 * Push:
 * 0 - Bool* !b
 */
void negatebool();

/**
 * Pop:
 * 0 - Bool* a
 * 1 - Bool* b
 * Push:
 * 0 - Bool* a and b
 */
void andbool();

/**
 * Pop:
 * 0 - Bool* a
 * 1 - Bool* b
 * Push:
 * 0 - Bool* a or b
 */
void orbool();

/**
 * Pop:
 * 0 - Bool* a
 * 1 - Bool* b
 * Push:
 * 0 - Bool* a == b
 */
void eqbool();



#endif
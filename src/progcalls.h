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
 * 0 - Int* sum
 */
void addint();

#endif
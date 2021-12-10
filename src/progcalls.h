#ifndef PROGCALLS_H
#define PROGCALLS_H

#include "types.h"

void* invokefun(Func* fun, void* arg);

void* arrayget(Array* array, Int* index);
void arrayset(Array* array, Int* index, void* val);
Array* initarray(Int* length, Func* supplier);
Int* arraylen(Array* array);

void printstring(String* str);
void printint(Int* n);

Int* addint(Int* a, Int* b);

#endif
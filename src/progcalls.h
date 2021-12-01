#ifndef PROGCALLS_H
#define PROGCALLS_H

#include "types.h"

void* invokefun(Func* fun, void* arg);

void* arrayget(Array* array, Int* index);
void arrayset(Array* array, Int* index, void* val);
void* initarray(Int* length, Func* supplier);
Int* arraylen(Array* array);


#endif
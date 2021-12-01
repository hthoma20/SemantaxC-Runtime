#ifndef TYPES_H
#define TYPES_H

#include "allocator.h"

struct Int : Collectable {
    int val;
};

Int* new_Int(int val);

struct Bool : Collectable {
    bool val;
};

Bool* new_Bool(bool val);

// An array will be allocated at a size larger than this struct, the memory block
// will also hold the data for the array. The lenght of the array can be determined
// via the number of pointers in the gcHeader
struct Array : Collectable { };

struct Func : Collectable {
    void* closure;
    void* (*fun)(void*, void*);
};

Func* new_Func(void* closure, void* (*fun)(void*, void*));


#endif
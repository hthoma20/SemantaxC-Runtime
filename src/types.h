#ifndef TYPES_H
#define TYPES_H

#include <string>

#include "allocator.h"

struct Int : Collectable {
    int val;
};

/**
 * Pop:
 * Push:
 * 0 - Int*
 */
void new_Int(int val);

struct Bool : Collectable {
    bool val;
};

/**
 * Pop:
 * Push:
 * 0 - Bool*
 */
void new_Bool(bool val);

// An array will be allocated at a size larger than this struct, the memory block
// will also hold the data for the array. The lenght of the array can be determined
// via the number of pointers in the gcHeader
struct Array : Collectable { };

/**
 * Pop:
 * 0 - (size)th element
 * 1 - (size-1)th element
 * (size-1) - first element
 * Push
 * 0 - Array* with the popped elements
 */
void new_Array(int size);

/**
 * internal function, doesn't follow stack convention
 * return a pointer to the address of the given index in the given array
 */
void** arrayLocation(Array* array, int index);

// Similar to an array, a string will be allocated lager than this struct, it will
// contain the data for the string, encoded in UTF-8
struct String : Collectable { };

/**
 * Pop:
 * Push:
 * 0 - String*
 */
void new_String(std::string val);

struct Func : Collectable {
    Collectable* closure;
    void (*fun)();
};

/**
 * Pop:
 * 0 - void* closure
 * Push:
 * 0 - Func*
 */
void new_Func(void (*fun)());

struct Variable : Collectable {
    Collectable* val;
};

/**
 * Pop:
 * Push:
 * 0 - Variable*
 */
void new_Variable();


#endif
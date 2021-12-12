#include <stdio.h>

#include "types.h"

void invokefun() {

    Collectable* arg = popRoot();
    Func* fun = (Func*) popRoot();

    {
        pushRoot(arg);
        pushRoot(fun->closure);
    }
    fun->fun();
}

// internal fucnction, doesn't follow stack convention
void** arrayLocation(Array* array, Int* index) {
    char* rawPointer = (char*) array;
    int byteOffset = sizeof(GcHeader) + index->val * sizeof(void*);

    char* rawLocation = rawPointer + byteOffset;
    return (void**) rawLocation;
}

void arrayget() {
    Int* index = (Int*) popRoot();
    Array* array = (Array*) popRoot();
    pushRoot((Collectable*) *arrayLocation(array, index));
}

void arrayset() {
    Collectable* val = popRoot();
    Int* index = (Int*) popRoot();
    Array* array = (Array*) popRoot();
    
    *arrayLocation(array, index) = val;
}

struct Arg_initarray : Collectable {
    Int* index;
};

/**
 * Internal function
 * Pop:
 * 0 - Int* index
 * Push:
 * 0 - Arg_initarray*
 */
void new_Arg_initarray() {
    Arg_initarray* obj = (Arg_initarray*) gcalloc(sizeof(Arg_initarray), 1);
    obj->index = (Int*) popRoot();
    pushRoot(obj);
}

void initarray() {
    Func* supplier = (Func*) getRoot(0);
    Int* length = (Int*) getRoot(1);

    // initialize array with 0 pointers so that the garbage collector doesn't try to trace
    // non-relevant pointers
    Array* array = (Array*) gcalloc(sizeof(Array) + (length->val * sizeof(void*)), 0);
    pushRoot(array);


    // top of stack: array, supplier, length

    for (int i = 0; i < length->val; i++) {
            { new_Int(i); }
        new_Arg_initarray();
        Arg_initarray* arg = (Arg_initarray*) popRoot();

        // invoke wants arg, supplier
        pushRoot(supplier);
        pushRoot(arg);
        invokefun();
        Collectable* val = popRoot();

        // arrayset wants val, index, array
        pushRoot(array);
        new_Int(i);
        pushRoot(val);
        arrayset();

        // mark that now each of the filled elements needs to be traced during GC
        array->header.pointers = i + 1;
    }

    popRoots(3); // pop: array, supplier, length
    pushRoot(array);
}

void arraylen() {
    Array* array = (Array*) popRoot();

    new_Int(array->header.pointers);
}

void printstring() {
    String* str = (String*) popRoot();
    char* rawPointer = (char*) str;
    printf("%s", rawPointer + sizeof(GcHeader));
}

void printint() {
    Int* n = (Int*) popRoot();
    printf("%d", n->val);
}

void addint() {
    Int* b = (Int*) popRoot();
    Int* a = (Int*) popRoot();

    new_Int(a->val + b->val);
}
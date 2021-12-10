#include <stdio.h>

#include "types.h"

void* invokefun(Func* fun, void* arg) {
    fun->fun(fun->closure, arg);
}


void** arrayLocation(Array* array, Int* index) {
    char* rawPointer = (char*) array;
    int byteOffset = sizeof(GcHeader) + index->val * sizeof(void*);

    char* rawLocation = rawPointer + byteOffset;
    return (void**) rawLocation;
}

void* arrayget(Array* array, Int* index) {
    return *arrayLocation(array, index);
}

void arrayset(Array* array, Int* index, void* val) {
    *arrayLocation(array, index) = val;
}

struct Arg_initarray : Collectable {
    Int* index;
};

Arg_initarray* new_Arg_initarray(Int* index) {
    Arg_initarray* obj = (Arg_initarray*) gcalloc(sizeof(Arg_initarray), 1);
    obj->index = index;
    return obj;
}

Array* initarray(Int* length, Func* supplier) {
    Array* array = (Array*) gcalloc(sizeof(Array) + (length->val * sizeof(void*)), length->val);

    for (int i = 0; i < length->val; i++) {
        Arg_initarray* arg = new_Arg_initarray(new_Int(i));
        void* val = invokefun(supplier, arg);
        arrayset(array, arg->index, val);
    }

    return array;
}

Int* arraylen(Array* array) {
    return new_Int(array->header.pointers);
}

void printstring(String* str) {
    char* rawPointer = (char*) str;
    printf("%s", rawPointer + sizeof(GcHeader));
}

void printint(Int* n) {
    printf("%d", n->val);
}

Int* addint(Int* a, Int* b) {
    return new_Int(a->val + b->val);
}
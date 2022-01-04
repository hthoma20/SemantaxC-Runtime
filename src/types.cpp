#include <string.h>

#include "types.h"

using namespace std;

void new_Int(int val) {
    Int* obj = (Int*) gcalloc(sizeof(Int), 0);
    obj->val = val;
    pushRoot(obj);
}

void new_Bool(bool val) {
    Bool* obj = (Bool*) gcalloc(sizeof(Bool), 0);
    obj->val = val;
    pushRoot(obj);
}

void** arrayLocation(Array* array, int index) {
    char* rawPointer = (char*) array;
    int byteOffset = sizeof(GcHeader) + index * sizeof(void*);

    char* rawLocation = rawPointer + byteOffset;
    return (void**) rawLocation;
}

void new_Array(int size) {
    // top of stack is "size" number of pointers to add to the new array

    // initialize array with 0 pointers so that the garbage collector doesn't try to trace
    // non-relevant pointers
    Array* array = (Array*) gcalloc(sizeof(Array) + (size * sizeof(void*)), 0);

    // fill in the array from the front (top of object) for GC
    for (int i = 0; i < size; i++) {
        // first element is burried in the stack
        *arrayLocation(array, i) = getRoot(size-i-1);

        // mark that now each of the filled elements needs to be traced during GC
        array->header.pointers = i + 1;
    }

    popRoots(size);
    pushRoot(array);
}



void new_Func(void (*fun)()) {
    Func* func = (Func*) gcalloc(sizeof(Func), 1);
    func->closure = popRoot();
    func->fun = fun;
    pushRoot(func);
}


void new_String(string val) {
    int length = val.length();
    String* str = (String*) gcalloc(sizeof(String) + (length+1)*(sizeof(char)), 0);

    char* valPointer = ((char*) str) + sizeof(GcHeader);

    for (int i = 0; i < length; i++) {
        valPointer[i] = val[i];
    }
    valPointer[length] = '\0';
    
    pushRoot(str);
}

void new_Variable() {
    Variable* var = (Variable*) gcalloc(sizeof(Variable), 1);
    var->val = nullptr;
    pushRoot(var);
}
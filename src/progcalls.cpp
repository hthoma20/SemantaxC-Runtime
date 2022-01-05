#include <stdio.h>

#include "types.h"

void invokefun() {

    Collectable* arg = popRoot();
    Func* fun = (Func*) popRoot();

    {
        pushRoot(fun->closure);
        pushRoot(arg);
    }
    fun->fun();
}

void arrayget() {
    Int* index = (Int*) popRoot();
    Array* array = (Array*) popRoot();
    pushRoot((Collectable*) *arrayLocation(array, index->val));
}

void arrayset() {
    Collectable* val = popRoot();
    Int* index = (Int*) popRoot();
    Array* array = (Array*) popRoot();
    
    *arrayLocation(array, index->val) = val;
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

    for (int i = 0; i < length->val; i++) {
            { new_Int(i); }
        new_Arg_initarray();
        Arg_initarray* arg = (Arg_initarray*) popRoot();

        // invoke wants arg, supplier
        pushRoot(supplier);
        pushRoot(arg);
        invokefun(); // leave this value on top of the stack for new_Array
    }

    // pop all the values and push the array itself
    new_Array(length->val);
    Array* array = (Array*) getRoot(0);

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

void printbool() {
    Bool* b = (Bool*) popRoot();
    if (b->val) {
        printf("true");
    }
    else {
        printf("false");
    }
}

void addint() {
    Int* b = (Int*) popRoot();
    Int* a = (Int*) popRoot();

    new_Int(a->val + b->val);
}

void negateint() {
    Int* n = (Int*) popRoot();
    new_Int(-(n->val));
}

void gteint() {
    Int* b = (Int*) popRoot();
    Int* a = (Int*) popRoot();

    new_Bool(a->val >= b->val);
}

void gtint() {
    Int* b = (Int*) popRoot();
    Int* a = (Int*) popRoot();

    new_Bool(a->val > b->val);
}

void eqint() {
    Int* b = (Int*) popRoot();
    Int* a = (Int*) popRoot();

    new_Bool(a->val == b->val);
}

void negatebool() {
    Bool* b = (Bool*) popRoot();
    new_Bool(!(b->val));
}

void andbool() {
    Bool* b = (Bool*) popRoot();
    Bool* a = (Bool*) popRoot();

    new_Bool(a->val && b->val);
}

void orbool() {
    Bool* b = (Bool*) popRoot();
    Bool* a = (Bool*) popRoot();

    new_Bool(a->val || b->val);
}

void eqbool() {
    Bool* b = (Bool*) popRoot();
    Bool* a = (Bool*) popRoot();

    new_Bool(a->val == b->val);
}


#include "types.h"

using namespace std;

Int* new_Int(int val) {
    Int* obj = (Int*) gcalloc(sizeof(Int), 0);
    obj->val = val;
    return obj;
}

Bool* new_Bool(bool val) {
    Bool* obj = (Bool*) gcalloc(sizeof(Bool), 0);
    obj->val = val;
    return obj;
}

Func* new_Func(void* closure, void* (*fun)(void*, void*)) {
    Func* func = (Func*) gcalloc(sizeof(Func), 1);
    func->closure = closure;
    func->fun = fun;
    return func;
}

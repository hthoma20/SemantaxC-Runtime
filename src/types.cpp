#include <string.h>

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


String* new_String(string val) {
    int length = val.length();
    String* str = (String*) gcalloc(sizeof(String) + (length+1)*(sizeof(char)), 0);

    char* valPointer = ((char*) str) + sizeof(GcHeader);

    for (int i = 0; i < length; i++) {
        valPointer[i] = val[i];
    }
    valPointer[length] = '\0';
    
    return str;
}


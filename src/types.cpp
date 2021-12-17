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
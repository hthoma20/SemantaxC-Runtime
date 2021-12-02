#include <iostream>
#include <vector>

#include "types.h"
#include "allocator.h"
#include "progcalls.h"

#include "progcalls_test.h"
#include "test_utils.h"

using namespace std;


struct arg_initializer : Collectable {
    Int* index;
};

// return the Int* passed in
// i.e initialize the array with 1,2,3,...n
void* initializer(void* _closure, void* _arg) {
    arg_initializer* arg = (arg_initializer*) _arg;
    return arg->index;
}

void testInitarray() {
    Array* array = initarray(new_Int(5), new_Func(nullptr, initializer));

    assertEqual(5, arraylen(array)->val);

    for (int i = 0; i < 5; i++) {
        assertEqual(i, ((Int*) arrayget(array, new_Int(i)))->val);
    }

    runGarbageCollector();
}

struct arg_add4 : Collectable {
    Int* n;
};

arg_add4* new_arg_add4(int n) {
    arg_add4* arg = (arg_add4*) gcalloc(sizeof(arg_add4), 1);
    arg->n = new_Int(n);
    return arg;
}

void* add4(void* _closure, void* _arg) {
    arg_add4* arg = (arg_add4*) _arg;
    return new_Int(arg->n->val + 4);
}

void testInvokefun() {
    Int* val1 = (Int*) invokefun(new_Func(nullptr, add4), new_arg_add4(0));
    Int* val2 = (Int*) invokefun(new_Func(nullptr, add4), new_arg_add4(6));

    assertEqual(4, val1->val);
    assertEqual(10, val2->val);

    runGarbageCollector();
}

void testProgcalls() {
    
    runTests("Progcalls tests", {
        testInitarray, testInvokefun
    });

}

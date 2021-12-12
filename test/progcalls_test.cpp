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
/**
 * Pop:
 * 0 - arg_initializer* arg 
 * Push:
 * 0 - Int* index
 */
void initializer() {
    popRoot(); // pop closure
    arg_initializer* arg = (arg_initializer*) popRoot();
    pushRoot(arg->index);
}

void testInitarray() {
    {
        new_Int(5);
            { pushRoot(nullptr); }
        new_Func(initializer);
    }
    initarray();
        Array* array = (Array*) getRoot(0); // leave array on the stack for the arraylen arg
    arraylen();
    Int* length = (Int*) popRoot();
    
    assertEqual(5, length->val);

    pushRoot(array);
    for (int i = 0; i < 5; i++) {
        
        {
            pushRoot(array);
            new_Int(i);
        }
        arrayget();
        // the array initilizer should have produced [0, 1, 2, 3, 4]
        Int* element = (Int*) popRoot();
        assertEqual(i, element->val);
    }
    popRoots(1);

    runGarbageCollector();
}

struct arg_add4 : Collectable {
    Int* n;
};

/**
 * Pop:
 * Push:
 * 0 - arg_add4*
 */
void new_arg_add4(int n) {
    arg_add4* arg = (arg_add4*) gcalloc(sizeof(arg_add4), 1);
    new_Int(n);
    arg->n = (Int*) popRoot();
    pushRoot(arg);
}

void add4() {
    Collectable* closure = popRoot();
    arg_add4* arg = (arg_add4*) popRoot();

    new_Int(arg->n->val + 4);
}

void testInvokefun() {

    {
        { pushRoot(nullptr); }
        new_Func(add4);
        new_arg_add4(0);
    }
    invokefun();
    Int* result = (Int*) popRoot();
    assertEqual(4, result->val);

    {
        {
            pushRoot(nullptr); 
        }
        new_Func(add4);
        new_arg_add4(6);
    }
    invokefun();
    result = (Int*) popRoot();    
    assertEqual(10, result->val);

    runGarbageCollector();
}

void testPrintstring() {
    
    cout << "printstring test:";
        { new_String("hello"); }
    printstring();
    cout << endl;

    runGarbageCollector();
}

void testPrintint() {
    
    cout << "printint test:";
        { new_Int(1234); }
    printint();
    cout << endl;

    runGarbageCollector();
}

void testAddInt() {
    {
        new_Int(5);
        new_Int(10);
    }
    addint();
    Int* sum = (Int*) popRoot();
    assertEqual(15, sum->val);

    {
        new_Int(2147483647);
        new_Int(-2147483647);
    }
    addint();
    sum = (Int*) popRoot();
    assertEqual(0, sum->val);

    runGarbageCollector();
}

void testProgcalls() {
    
    runTests("Progcalls tests", {
        testInitarray, testInvokefun, testPrintstring, testPrintint, testAddInt
    });

}

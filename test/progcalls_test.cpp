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
    arg_initializer* arg = (arg_initializer*) popRoot();
    popRoot(); // pop closure
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
    arg_add4* arg = (arg_add4*) popRoot();
    Collectable* closure = popRoot();

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

void testPrintbool() {
    
    cout << "printbool test:";
        { new_Bool(true); }
    printbool();
    cout << endl;

    runGarbageCollector();
}

void testAddint() {
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

void testNegateint() {
    {
        new_Int(5);
    }
    negateint();
    Int* n = (Int*) popRoot();
    assertEqual(-5, n->val);

    {
        new_Int(-200);
    }
    negateint();
    n = (Int*) popRoot();
    assertEqual(200, n->val);

    runGarbageCollector();
}

void testGteint() {
    {
        new_Int(5);
        new_Int(10);
    }
    gteint();
    Bool* result = (Bool*) popRoot();
    assertEqual(false, result->val);

    {
        new_Int(10);
        new_Int(5);
    }
    gteint();
    result = (Bool*) popRoot();
    assertEqual(true, result->val);

    {
        new_Int(10);
        new_Int(10);
    }
    gteint();
    result = (Bool*) popRoot();
    assertEqual(true, result->val);

    runGarbageCollector();
}

void testGtint() {
    {
        new_Int(5);
        new_Int(10);
    }
    gtint();
    Bool* result = (Bool*) popRoot();
    assertEqual(false, result->val);

    {
        new_Int(10);
        new_Int(5);
    }
    gtint();
    result = (Bool*) popRoot();
    assertEqual(true, result->val);

    {
        new_Int(10);
        new_Int(10);
    }
    gtint();
    result = (Bool*) popRoot();
    assertEqual(false, result->val);

    runGarbageCollector();
}

void testEqint() {
    {
        new_Int(5);
        new_Int(10);
    }
    eqint();
    Bool* result = (Bool*) popRoot();
    assertEqual(false, result->val);

    {
        new_Int(10);
        new_Int(5);
    }
    eqint();
    result = (Bool*) popRoot();
    assertEqual(false, result->val);

    {
        new_Int(10);
        new_Int(10);
    }
    eqint();
    result = (Bool*) popRoot();
    assertEqual(true, result->val);

    runGarbageCollector();
}

void testNegatebool() {
    {
        new_Bool(false);
    }
    negatebool();
    Bool* result = (Bool*) popRoot();
    assertEqual(true, result->val);

    {
        new_Bool(true);
    }
    negatebool();
    result = (Bool*) popRoot();
    assertEqual(false, result->val);

    runGarbageCollector();
}

void testAndbool() {
    {
        new_Bool(false);
        new_Bool(false);
    }
    andbool();
    Bool* result = (Bool*) popRoot();
    assertEqual(false, result->val);

    {
        new_Bool(false);
        new_Bool(true);
    }
    andbool();
    result = (Bool*) popRoot();
    assertEqual(false, result->val);

    {
        new_Bool(true);
        new_Bool(false);
    }
    andbool();
    result = (Bool*) popRoot();
    assertEqual(false, result->val);

    {
        new_Bool(true);
        new_Bool(true);
    }
    andbool();
    result = (Bool*) popRoot();
    assertEqual(true, result->val);

    runGarbageCollector();
}

void testOrbool() {
    {
        new_Bool(false);
        new_Bool(false);
    }
    orbool();
    Bool* result = (Bool*) popRoot();
    assertEqual(false, result->val);

    {
        new_Bool(false);
        new_Bool(true);
    }
    orbool();
    result = (Bool*) popRoot();
    assertEqual(true, result->val);

    {
        new_Bool(true);
        new_Bool(false);
    }
    orbool();
    result = (Bool*) popRoot();
    assertEqual(true, result->val);

    {
        new_Bool(true);
        new_Bool(true);
    }
    orbool();
    result = (Bool*) popRoot();
    assertEqual(true, result->val);

    runGarbageCollector();
}

void testEqbool() {
    {
        new_Bool(false);
        new_Bool(false);
    }
    eqbool();
    Bool* result = (Bool*) popRoot();
    assertEqual(true, result->val);

    {
        new_Bool(false);
        new_Bool(true);
    }
    eqbool();
    result = (Bool*) popRoot();
    assertEqual(false, result->val);

    {
        new_Bool(true);
        new_Bool(false);
    }
    eqbool();
    result = (Bool*) popRoot();
    assertEqual(false, result->val);

    {
        new_Bool(true);
        new_Bool(true);
    }
    eqbool();
    result = (Bool*) popRoot();
    assertEqual(true, result->val);

    runGarbageCollector();
}

void testProgcalls() {
    
    runTests("Progcalls tests", {
        testInitarray, testInvokefun, testPrintstring, testPrintint, testPrintbool,
        testAddint, testNegateint, testGteint, testGtint, testEqint,
        testEqint, testNegatebool, testAndbool, testOrbool, testEqbool
    });

}

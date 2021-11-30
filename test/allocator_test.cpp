#include <iostream>
#include <algorithm>
#include <vector>

#include "../src/allocator.h"

using namespace std;


int currentTestCase;

void printTestFailure(string message) {
    cout << "Test failure in test case [" << currentTestCase << "]" << endl;
    cout << "\t" <<  message << endl;
    exit(1);
}

void assertAllocated(Collectable* allocation) {
    if (!count(getAllocations()->begin(), getAllocations()->end(), allocation)) {
        printTestFailure("Allocation not tracked");
    }
}

void assertNotAllocated(Collectable* allocation) {
    if (count(getAllocations()->begin(), getAllocations()->end(), allocation)) {
        printTestFailure("Allocation is allocated");
    }
}

void assertAllocationsEmpty() {
    if (getAllocations()->size() != 0) {
        printTestFailure("Allocations non-empty after test case");
    }

    if (getRootAllocations()->size() != 0) {
        printTestFailure("Root allocations non-empty after test case");
    }
}

struct Thing : Collectable {
    int x;
};

struct Owner : Collectable {
    Thing* thing;
    int x;
};

struct Recursive : Collectable {
    Recursive* pointer;
};


Thing* newThing(int x) {
    Thing* thing = (Thing*) gcalloc(sizeof(Thing), 0);
    thing->x = x;
    return thing;
}

Owner* newOwner(Thing* thing) {
    Owner* owner = (Owner*) gcalloc(sizeof(Owner), 1);
    owner->thing = thing;
    return owner;
}

Recursive* newRecursive() {
    return (Recursive*) gcalloc(sizeof(Recursive), 1);
}

void testSingleNonRootAllocation() {
    Thing* thing = newThing(5);

    assertAllocated(thing);
    runGarbageCollector();
    assertNotAllocated(thing);
}

void testSingleRootAllocation() {
    Thing* thing = newThing(5);

    pushRoot(thing);
    runGarbageCollector();

    assertAllocated(thing);

    popRoot(1);
    runGarbageCollector();
    assertNotAllocated(thing);
}

void testSingleThingMultipleOwners() {
    Owner* owner1 = newOwner(nullptr);
    Owner* owner2 = newOwner(nullptr);
    Thing* thing = newThing(1);

    assertAllocated(owner1);
    assertAllocated(owner2);
    assertAllocated(thing);

    owner1->thing = thing;
    owner2->thing = thing;
    
    pushRoot(owner1);
    pushRoot(owner2);
    

    runGarbageCollector();
    
    assertAllocated(owner1);
    assertAllocated(owner2);
    assertAllocated(thing);

    // pop owner2
    popRoot(1);  

    runGarbageCollector();
    
    // since owner2 is no longer a root, it should be freed
    // since owner1 points to thing, thing should still be allocated
    assertNotAllocated(owner2);
    assertAllocated(owner1);
    assertAllocated(thing);

    // pop owner1
    popRoot(1);

    runGarbageCollector();

    // now nothing should point to thing and it should be freed
    assertNotAllocated(owner1);
    assertNotAllocated(thing); 
}


void testCyclicAllocation() {
    Recursive* r1 = newRecursive();
    Recursive* r2 = newRecursive();

    r1->pointer = r2;
    r2->pointer = r1;

    pushRoot(r2);

    runGarbageCollector();
    assertAllocated(r1);
    assertAllocated(r2);

    popRoot(1);
    runGarbageCollector();
    assertNotAllocated(r1);
    assertNotAllocated(r2);
}



int main(int argc, char* argv[]) {

    setAutomaticCollection(false);

    vector<void (*)()> testCases = {
        testSingleNonRootAllocation, testSingleRootAllocation, testSingleThingMultipleOwners,
        testCyclicAllocation
    };

    currentTestCase = 0;

    for (auto testCase : testCases) {
        testCase();
        assertAllocationsEmpty();
        currentTestCase++;
    }

    cout << "All " << testCases.size() << " tests passed." << endl;

    finalizeGarbageCollector();
}
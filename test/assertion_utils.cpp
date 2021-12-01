#include <algorithm>
#include <iostream>

#include "assertion_utils.h"
#include "../src/allocator.h"

using namespace std;

string currentTestCase;

void setTestCase(string newTestCase) {
    currentTestCase = newTestCase;
}

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

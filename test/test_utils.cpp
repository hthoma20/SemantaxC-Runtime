#include <algorithm>
#include <iostream>
#include <string>

#include "test_utils.h"
#include "allocator.h"

using namespace std;

string currentCaseName;
int currentCaseIndex;

void runTests(std::string caseName, std::vector<void (*)()> testCases) {
    currentCaseName = caseName;
    currentCaseIndex = 0;

    for (auto testCase : testCases) {
        testCase();
        assertAllocationsEmpty();
        currentCaseIndex++;
    }

    cout << caseName << ":" << endl;
    cout << "\tAll " << testCases.size() << " tests passed." << endl;
}


void printTestFailure(string message) {
    cout << "Test failure in test case {" << currentCaseName << "}[" << currentCaseIndex << "]" << endl;
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

void assertEqual(int expected, int actual) {
    if (expected != actual) {
        printTestFailure("Expected [" + to_string(expected) + "], recieved [" + to_string(actual) + "]");
    }
}

void assertEqual(bool expected, bool actual) {
    if (expected != actual) {
        printTestFailure("Expected [" + to_string(expected) + "], recieved [" + to_string(actual) + "]");
    }
}

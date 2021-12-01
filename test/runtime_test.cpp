
#include <iostream>

#include "allocator.h"

#include "test_utils.h"
#include "allocator_test.h"
#include "progcalls_test.h"

using namespace std;

int main(int argc, char* argv[]) {

    setAutomaticCollection(false);

    runTests("Full test suite", {
        testAllocator, testProgcalls
    });

    finalizeGarbageCollector();
}
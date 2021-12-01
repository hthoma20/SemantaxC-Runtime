#ifndef TEST_UTILS_H
#define TEST_UTILS_H

#include <string>
#include <vector>

#include "allocator.h"

void printTestFailure(std::string message);

void assertAllocated(Collectable* allocation);

void assertNotAllocated(Collectable* allocation);

void assertAllocationsEmpty();

void runTests(std::string caseName, std::vector<void (*)()> testCases);

#endif
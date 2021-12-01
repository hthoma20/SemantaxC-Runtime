#ifndef ASSERTION_UTILS_H
#define ASSERTION_UTILS_H

#include "allocator.h"

void printTestFailure(std::string message);

void assertAllocated(Collectable* allocation);

void assertNotAllocated(Collectable* allocation);

void assertAllocationsEmpty();

void setTestCase(std::string testCase);

#endif
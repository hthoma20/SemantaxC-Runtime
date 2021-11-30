#include <iostream>
#include <vector>

#include "allocator.h"

using namespace std;


vector<Collectable*>* allocations = new vector<Collectable*>();
vector<Collectable*> rootAllocations;


bool AUTOMATIC_COLLECTION = true;

void setAutomaticCollection(bool autoCollectionEnabled) {
    AUTOMATIC_COLLECTION = autoCollectionEnabled;
}

bool shouldRunGarbageCollector() {
    return AUTOMATIC_COLLECTION;
}

/**
 * Allocate memory and track it for garbage collection.
 */
Collectable* gcalloc(size_t size, uint pointers) {
    if (shouldRunGarbageCollector()) {
        runGarbageCollector();
    }

    Collectable* allocation = (Collectable*) malloc(size);
    allocation->header.pointers = pointers;
    allocation->header.marked = false;

    allocations->push_back(allocation);

    return allocation;
}

/**
 * Mark the given allocation as reachable, as well as all
 * of its transivively reachable children
 */
void markTransitive(Collectable* allocation) {
    if (allocation->header.marked) {
        return;
    }

    allocation->header.marked = true;

    for (uint i = 0; i < allocation->header.pointers; i++) {

        char* rawPointer = (char*) allocation;
        int byteOffset = sizeof(GcHeader) + i * sizeof(Collectable*);

        char* rawChildLocation = rawPointer + byteOffset;
        Collectable** childLocation = (Collectable**) rawChildLocation;

        Collectable* child = *childLocation;

        markTransitive(child);
    }
}


void runGarbageCollector() {
    // Mark all allocations as unreachable
    for (Collectable* allocation : *allocations) {
        allocation->header.marked = false;
    }

    // Mark all reachable allocations as such
    for (Collectable* rootAllocation : rootAllocations) {
        markTransitive(rootAllocation);
    }

    // Collect all the marked allocations, and free the others
    vector<Collectable*>* markedAllocations = new vector<Collectable*>();
    for (Collectable* allocation : *allocations) {
        if (allocation->header.marked) {
            markedAllocations->push_back(allocation);
        }
        else {
            free(allocation);
        }
    }
    delete allocations;
    allocations = markedAllocations;
}

/**
 * Free all allocated memory
 */
void finalizeGarbageCollector() {
    rootAllocations.clear();
    runGarbageCollector();
    delete allocations;
}


/**
 * Mark that the given collectable is a root of the object tree
 */
void pushRoot(Collectable* collectable) {
    rootAllocations.push_back(collectable);
}

/**
 * Pop the top root objects off of the root stack
 */
void popRoot(int count) {
    rootAllocations.erase(rootAllocations.end()-count, rootAllocations.end());
}

void dumpAllocation(Collectable* allocation) {
    printf("\t%p (%d, %d)\n", allocation, allocation->header.pointers, allocation->header.marked);
}

void memDump() {
    printf("roots:\n");
    for (Collectable* allocation : rootAllocations) {
        dumpAllocation(allocation);
    }
    printf("allocations:\n");
    for (Collectable* allocation : *allocations) {
        dumpAllocation(allocation);
    }
    printf("\n");
}

vector<Collectable*>* getAllocations() {
    return allocations;
}

vector<Collectable*>* getRootAllocations() {
    return &rootAllocations;
}




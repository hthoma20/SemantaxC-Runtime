#ifndef ALLOCATOR_H
#define ALLOCATOR_H

#include <cstdlib>
#include <vector>

typedef unsigned int uint;

struct GcHeader {
    uint pointers;
    bool marked;
};

struct Collectable {
    GcHeader header; 
};

/**
 * Allocate memory and track it for garbage collection.
 */
Collectable* gcalloc(std::size_t size, uint pointers);


/**
 * Free all memory which was allocated with gcalloc and is
 * no longer transitively reachable by any of the roots
 */
void runGarbageCollector();

/**
 * Free all allocated memory
 */
void finalizeGarbageCollector();

/**
 * Mark that the given collectable is a root of the object tree
 */
void pushRoot(Collectable* Collectable);

/**
 * Pop the top root objects off of the root stack
 */
void popRoot(int count);

/**
 * Print a dump of the current allocated memory
 */
void memDump();

/** 
 * Set whether or not garbage collection should be performed during
 * gcalloc. When this is true, runGarbageCollector will be called
 * when neccesary before allocating memory. When false, gcalloc will
 * never attempt garbage collection.
 * 
 * true by defualt
 * 
 * Set this flag to true when running tests so that garbage collection
 * runs only when requested
 */
void setAutomaticCollection(bool autoCollectionEnabled);

/**
 * Return the allocations, this can be used for assertions during testing
 */
std::vector<Collectable*>* getAllocations();
std::vector<Collectable*>* getRootAllocations();


#endif

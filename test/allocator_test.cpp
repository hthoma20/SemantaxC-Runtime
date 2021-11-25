#include <iostream>

#include "../src/allocator.h"


using namespace std;

struct Thing : Collectable {
    public:
    int x;
};

struct Owner : Collectable {
    public:
    Thing* thing;
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


int main(int argc, char* argv[]) {

    setAutomaticCollection(false);

    printf("Header: %lu\n", sizeof(GcHeader));
    printf("Collectable*: %lu\n", sizeof(Collectable*));

    Owner* owner1 = newOwner(nullptr);
    cout << "allocate owner1" << endl;
    memDump();

    Owner* owner2 = newOwner(nullptr);
    cout << "allocate owner2" << endl;
    memDump();

    Thing* thing = newThing(1);
    cout << "allocate thing" << endl;
    memDump();

    owner1->thing = thing;
    owner2->thing = thing;
    
    pushRoot(owner1);
    pushRoot(owner2);
    cout << "mark roots" << endl;
    memDump();

    runGarbageCollector();
    cout << "run gc" << endl;
    memDump();

    popRoot(1);
    cout << "pop root" << endl;
    memDump();

    runGarbageCollector();
    cout << "run gc" << endl;
    memDump();

    popRoot(1);
    cout << "pop root" << endl;
    memDump();

    runGarbageCollector();
    cout << "run gc" << endl;
    memDump();

    finalizeGarbageCollector();
    malloc(4);
}
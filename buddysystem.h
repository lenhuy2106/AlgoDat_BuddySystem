#ifndef BUDDYSYSTEM_H
#define BUDDYSYSTEM_H
#include "freelists.h"

class BuddySystem {
private:
	Heap* heap;
	FreeLists* freeLists;
public:
    BuddySystem(Heap* heap);
    POSITION Allocate(POSITION p);
    POSITION NewMem(POSITION p);
    void DisposeMem (POSITION p);
};

#endif // BUDDYSYSTEM_H

#ifndef BUDDYSYSTEM_H
#define BUDDYSYSTEM_H
#include "freelists.h"

class BuddySystem {
private:
	Heap* heap;
	FreeLists* freeLists;
public:
    BuddySystem(Heap* heap);
    POSITION Allocate(POSITION p, int k);
    POSITION NewMem(POSITION p);
    FreeLists* GetFreeLists();
    void DisposeMem (POSITION p);
    int  SizeOfBlock(POSITION p);

};

#endif // BUDDYSYSTEM_H

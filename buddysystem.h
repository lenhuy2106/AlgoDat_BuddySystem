#ifndef BUDDYSYSTEM_H
#define BUDDYSYSTEM_H
#include "freelists.h"

class BuddySystem {
private:
    Heap* heap;
    FreeLists* freeLists;
public:
    BuddySystem(int m);
    POSITION Allocate(POSITION p, int k);
    POSITION NewMem(POSITION p);
    FreeLists* GetFreeLists();
    void DisposeMem (POSITION p);
    int  SizeOfBlock(POSITION p);
    void ShowHeap();
    BuddySystem(const BuddySystem& ref);
    BuddySystem& operator=(const BuddySystem& ref);
    ~BuddySystem();
};

#endif // BUDDYSYSTEM_H

#include "buddysystem.h"

BuddySystem::BuddySystem(Heap* heap) {
	freeLists = new FreeLists(heap);
}

POSITION BuddySystem::Allocate (POSITION p) {
    POSITION tmp;
    for (tmp = p; freeLists->GetFromFree(tmp) < 0; tmp++) {
    }
    while (tmp != p) {
        freeLists->AddToFree(tmp - 1);
        tmp--;
    }
    freeLists->AddToFree(tmp);
    return tmp;
}

POSITION BuddySystem::NewMem (POSITION p) {
    POSITION tmp = p;
    if (fListsVec[p].size () == 0) {
        Allocate(tmp);
//      catch arrayOutOfIndex!
	}
    heap->SetVal(p, 1);
    return p;
}

void BuddySystem::DisposeMem (POSITION p) {
	freeLists->AddToFree(p);
}

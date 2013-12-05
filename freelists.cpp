#include "freelists.h"

FreeLists::FreeLists (int m) : Heap (m) {

    vector<int> newHeapVec (m, 0);
    heapVec = newHeapVec;
    vector<int> freeList;

    vector<vector<int> > fListsVec (m+1, freeList);
    fListsVec[m] = heapVec;
}

void FreeLists::AddToFree (POSITION p) {

//  position and size inserted ?
    fListsVec[p].insert (fListsVec[p].begin(), p);
}

POSITION FreeLists::GetFromFree (POSITION k) {

    if (fListsVec[k].size () > 0) {

        POSITION tmp = fListsVec[k].front ();
        fListsVec[k].erase (fListsVec[k].begin());
        return tmp;

    } else {
        return PSEUDO;
    }
}

#ifndef BUDDYSYSTEM_H
#define BUDDYSYSTEM_H
#include "freelists.h"

class BuddySystem : public FreeLists {

public:
    BuddySystem (int m);

    POSITION Allocate (POSITION p) {

        POSITION tmp;
        for (tmp = p; GetFromFree (tmp) < 0; tmp++) {
        }
        while (tmp != p) {
            AddToFree (tmp - 1);
            tmp--;
        }
        AddToFree (tmp);
        return tmp;
    }

    POSITION NewMem (POSITION p) {

        POSITION tmp = p;
        if (fListsVec[p].size () == 0)
            Allocate (tmp);
//      catch arrayOutOfIndex!
        heapVec[p] = 1;
        return p;
    }

    void DisposeMem (POSITION p) {
        AddToFree (p);
    }
};

#endif // BUDDYSYSTEM_H

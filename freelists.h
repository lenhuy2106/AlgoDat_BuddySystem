#ifndef FREELISTS_H
#define FREELISTS_H

#include <vector>
#include "heap.h"
using namespace std;

class FreeLists : public Heap {

private:
    POSITION top;
    int size;

public:
    FreeLists (int m);
    inline int GetSize () { return size; }
    inline bool EmptyFree () { return (size == 0); }
    void AddToFree (POSITION p);
    POSITION GetFromFree (POSITION k);
     vector<vector<int> > fListsVec;
};

#endif // FREELISTS_H

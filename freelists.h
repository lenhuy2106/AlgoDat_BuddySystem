#ifndef FREELISTS_H
#define FREELISTS_H

#include "heap.h"

class FreeLists {

private:
    Heap* heap;
    POSITION top;
    int size;
    // Positions of the first element of the free lists
    int* lists;

    bool removeFromFreeList(POSITION p, int size);
public:
    FreeLists(Heap* heap);
    inline int GetPos(int k) { return lists[k]; }
    void ShowLists();
    inline int GetSize () { return size; }
    inline bool EmptyFree () { return (size == 0); }
    void AddToFree (POSITION p, int size);
    POSITION GetFromFree (POSITION k);
    FreeLists(const FreeLists& ref);
    FreeLists& operator=(const FreeLists& ref);
    ~FreeLists();
};

#endif // FREELISTS_H

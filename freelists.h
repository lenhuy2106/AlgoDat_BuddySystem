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
    void ShowLinkedNext(int linkedPos);
    inline int GetSize () { return size; }
    inline bool EmptyFree () { return (size == 0); }
    void AddToFree (POSITION p, int size);
    POSITION GetFromFree (POSITION k);
};

#endif // FREELISTS_H

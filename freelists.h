#ifndef FREELISTS_H
#define FREELISTS_H

#include "heap.h"
using namespace std;

#define NO_FREE_LIST -1

#define OFFSET_RESERVED 0
#define OFFSET_SIZE 1
#define OFFSET_NEXT 2

class FreeLists {

private:
	Heap* heap;
    POSITION top;
    int size;
	// Positions of the first element of the free lists
	int* lists;
public:
    FreeLists(Heap* heap);
    inline int GetSize () { return size; }
    inline bool EmptyFree () { return (size == 0); }
    void AddToFree (POSITION p, int size);
    POSITION GetFromFree (POSITION k);
};

#endif // FREELISTS_H

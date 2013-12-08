#ifndef FREELISTS_H
#define FREELISTS_H

#include "heap.h"
#include <string>
#include <iostream>
using namespace std;

class FreeLists {

private:
	Heap* heap;
    POSITION top;
    int size;
	// Positions of the first element of the free lists
	int* lists;
public:
    FreeLists(Heap* heap);
    // -- prefer GetPos()
    inline int* GetLists() { return lists; }
    void ShowLists();
    inline int GetSize () { return size; }
    inline bool EmptyFree () { return (size == 0); }
    void AddToFree (POSITION p, int size);
    POSITION GetFromFree (POSITION k);
};

#endif // FREELISTS_H

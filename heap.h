#ifndef HEAP_H
#define HEAP_H
#define PSEUDO -1
#include <vector>
#include <iostream>

using namespace std;
typedef int POSITION;
typedef int ATOM;

class Heap {

public:
    Heap (int m);
    Heap (const Heap& ref);
    Heap& operator = (const Heap& ref);
    ~Heap ();
    vector<int> heapVec;
    ATOM val;

    inline void SetVal (POSITION p, ATOM val) {

        heapVec[p] = val;
    }

    inline int GetVal (POSITION p) {

        return heapVec[p]; }
};

#endif // HEAP_H

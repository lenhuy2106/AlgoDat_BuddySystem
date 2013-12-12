#ifndef HEAP_H
#define HEAP_H

#define PSEUDO -1
#define OFFSET_RESERVED 0
#define OFFSET_SIZE 1
#define OFFSET_NEXT 2

#include <math.h>
#include <iostream>
using namespace std;

typedef int POSITION;
typedef int ATOM;

class Heap {
private:
	int m;
    // in bytes
	int length;
    int* data;
    int atoms;
public:
    Heap(int m);
    int GetM();
    int PowToAtoms(int k);
    int GetLength();
    void SetBlock(int pos, int res, int k, int val);
    void Show();
    void SetVal(POSITION p, ATOM val);
    int SizeToPow(int size);
    int GetVal(POSITION p);
};

#endif // HEAP_H

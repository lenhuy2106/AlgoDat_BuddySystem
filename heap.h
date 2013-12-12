#ifndef HEAP_H
#define HEAP_H

#define PSEUDO -1
#define OFFSET_RESERVED 0
#define OFFSET_SIZE 1
#define OFFSET_NEXT 2

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
    void SetFreeBlock(int pos, int k, int next);
	void SetReservedBlock(int pos, int k);
    void Show();
    void SetVal(POSITION p, ATOM val);
    int GetVal(POSITION p);
};

#endif // HEAP_H

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
public:
    Heap(int m);
	int getM();
    int powToAtoms(int k);
    int getLength();
    void setBlock(int res, int k, int val);

    inline void SetVal(POSITION p, ATOM val);
    inline int GetVal(POSITION p);
};

#endif // HEAP_H

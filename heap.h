#ifndef HEAP_H
#define HEAP_H

#define PSEUDO -1

typedef int POSITION;
typedef int ATOM;

class Heap {
private:
	int m;
	int length;
	int* data;
public:
    Heap(int m);
	int getM();
	int getLength();
    inline void SetVal(POSITION p, ATOM val);
    inline int GetVal(POSITION p);
};

#endif // HEAP_H

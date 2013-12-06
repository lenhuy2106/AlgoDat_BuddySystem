#include <cmath>
#include "heap.h"
using namespace std;

Heap::Heap(int m) {
	this->m = m;

    // length = powToLength(m);
    length = (int)ceil((2 ^ m + 2) / (float)sizeof(ATOM));
    data = new ATOM[length];
}

int Heap::getM() {
	return m;
}

int Heap::getLength() {
	return length;
}

void Heap::setBlock(int res, int k, int next) {
    SetVal(0 + OFFSET_RESERVED, res);
    SetVal(0 + OFFSET_SIZE, 2 ^ k);
    SetVal(0 + OFFSET_NEXT, next);
}

int powToLength(int k) {
    return (int)ceil((2 ^ k) / (float)sizeof(ATOM));
}

inline void Heap::SetVal(POSITION p, ATOM val) {
	data[p] = val;
}

inline int Heap::GetVal(POSITION p) {
	return data[p];
}

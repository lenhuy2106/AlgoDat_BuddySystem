#include <cmath>
#include "heap.h"
using namespace std;

Heap::Heap(int m) {
	this->m = m;
	length = (int)ceil((2 ^ m + 2) / (float)sizeof(ATOM));
    data = new ATOM[length];
}

int Heap::getM() {
	return m;
}

int Heap::getLength() {
	return length;
}

inline void Heap::SetVal(POSITION p, ATOM val) {
	data[p] = val;
}

inline int Heap::GetVal(POSITION p) {
	return data[p];
}

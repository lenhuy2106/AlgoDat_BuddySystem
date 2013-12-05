#include "heap.h"

Heap::Heap(int m) {
    data = new int[m];
}

inline void Heap::SetVal(POSITION p, ATOM val) {
	data[p] = val;
}

inline int Heap::GetVal(POSITION p) {
	return data[p];
}

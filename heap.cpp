#include "heap.h"

Heap::Heap(int m) {
	this->m = m;
    // extra 2 Einheiten ?
    length = pow(2, m) + 2;
    data = new ATOM[length];

    // Initial free block for the whole heap
    SetBlock(0, 0, m, PSEUDO);
}

int Heap::GetM() {
	return m;
}

int Heap::GetLength() {
	return length;
}

/*
 *Sets a block in heap.
 *param pos: position of block to set
 *      res: reserved mark
 *      size: power of 2
 *      next: position of successor (same size)
 */
void Heap::SetBlock(int pos, int res, int k, int next) {
    SetVal(pos + OFFSET_RESERVED, res);
    SetVal(pos + OFFSET_SIZE, k);
    SetVal(pos + OFFSET_NEXT, next);
}

int Heap::PowToAtoms(int k) {
    return pow(2, k);
}

inline void Heap::SetVal(POSITION p, ATOM val) {
    data[p] = val;
}

// -- inline: undefined
int Heap::GetVal(POSITION p) {
    return data[p];
}

void Heap::Show() {
    cout << "-----------------" << endl;
    cout << "Pos\tVal" << endl;
    cout << "-----------------" << endl;
    for (ATOM i = 0; i <= length; i++) cout << i << ":\t" << data[i] << endl;
    cout << "-----------------" << endl;
}


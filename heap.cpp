#include <math.h>
#include "heap.h"
#include <iostream>
using namespace std;

Heap::Heap(int m) {
	this->m = m;
    length = pow(2, m) + 2;
    atoms = PowToAtoms(m) - 1;
    // extra 2 bytes ?
    data = new ATOM[atoms];
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
    SetVal(pos + OFFSET_SIZE, pow(2, k));
    SetVal(pos + OFFSET_NEXT, next);
}

int Heap::PowToAtoms(int k) {
    return pow(2, k) / sizeof(ATOM);
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
    for (ATOM i = 0; i <= atoms; i++) cout << i << ":\t" << data[i] << endl;
    cout << "-----------------" << endl;
}

/*
 *returns log base2 of a block size
 */
int Heap::SizeToPow(int size) {
    return log2(size);
}

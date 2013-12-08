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

void Heap::SetBlock(int res, int k, int next) {
    SetVal(0 + OFFSET_RESERVED, res);
    SetVal(0 + OFFSET_SIZE, 2 ^ k);
    SetVal(0 + OFFSET_NEXT, next);
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
    for (ATOM i = 0; i <= atoms; i++) cout << data[i] << endl;
}

/*
 *returns log base2 of a block size
 */
int Heap::SizeToPow(int size) {
    return log(size) / log(2);
}

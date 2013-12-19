#include "heap.h"

#include <cmath>
#include <iostream>

using namespace std;

Heap::Heap(int m) {
    this->m = m;
    // extra 2 Einheiten ?
    length = pow(2, m) + 2;
    data = new ATOM[length];

    // Initial free block for the whole heap
    SetFreeBlock(0, m, PSEUDO);
}

Heap::Heap(const Heap& ref) {
    m = ref.m;
    length = ref.length;
    data = new int[length];
    for(int i = 0; i < length; i++)
        data[i] = ref.data[i];
}

Heap& Heap::operator=(const Heap& ref) {
    delete[] data;
    m = ref.m;
    length = ref.length;
    data = new ATOM[length];
    for(int i = 0; i < length; i++)
        data[i] = ref.data[i];
    return *this;
}

Heap::~Heap() {
   delete[] data;
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
void Heap::SetFreeBlock(int pos, int k, int next) {
    SetVal(pos + OFFSET_RESERVED, 0);
    SetVal(pos + OFFSET_SIZE, k);
    SetVal(pos + OFFSET_NEXT, next);
}

void Heap::SetReservedBlock(int pos, int k) {
    SetVal(pos + OFFSET_RESERVED, 1);
    SetVal(pos + OFFSET_SIZE, k);
}

int Heap::PowToAtoms(int k) {
    return pow(2, k);
}

void Heap::Show() {
    cout << "-----------------" << endl;
    cout << "Pos\tVal" << endl;
    cout << "-----------------" << endl;
    for (ATOM i = 0; i <= length; i++) cout << i << ":\t" << data[i] << endl;
    cout << "-----------------" << endl;
}


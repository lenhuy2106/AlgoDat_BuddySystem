#include "buddysystem.h"
#include <math.h>
#include <iostream>

using namespace std;

BuddySystem::BuddySystem(int m) {
    m = ceil(log(m) / log(2));
    heap = new Heap(m);
    freeLists = new FreeLists(heap);
}


BuddySystem::BuddySystem(const BuddySystem& ref) {
    heap = new Heap(*ref.heap);
    freeLists = new FreeLists(*ref.freeLists);
}

BuddySystem& BuddySystem::operator=(const BuddySystem& ref) {
    if (this != &ref) {
        delete heap;
        delete freeLists;
        heap = new Heap(*ref.heap);
        freeLists = new FreeLists(*ref.freeLists);
    }

    return *this;
}

BuddySystem::~BuddySystem() {
    delete heap;
    delete freeLists;
}

POSITION BuddySystem::Allocate(POSITION p, int k) {
    // Get the next lower valid p
    int blockSize = pow(2, k);
    p = (p / blockSize) * blockSize;

    int currentSize = SizeOfBlock(p);
    int intendedSize = k;

    if (currentSize < intendedSize) {
        return PSEUDO; // Block is to small
    }

    if (currentSize > intendedSize) {
        while (intendedSize != currentSize) {
            // Split block in two equal halfs
            currentSize--;
            heap->SetReservedBlock(p, currentSize);

            // Add new right buddy to the free list
            int nextBlock = heap->PowToAtoms(currentSize);
            freeLists->AddToFree(p + nextBlock, currentSize);
        }
    } else {
        heap->SetReservedBlock(p, k);
    }

    return p;
}

/*
 *  Reserves new memory block.
 *  parameter size: size in words
 *  returns int: position of new block
 *          -1: n
 */
POSITION BuddySystem::NewMem(int size) {
    // ValidateSize() - has to be at least 2^2 bytes to store essentials
    int k = 0;

    while (size + 2 > pow(2, k)) k++;
    cout << "Reserving " << pow(2, k) << " words block..." << endl;

    // -- CheckBlockFree()
    // -- CheckBlockEnoughSize()
    // lists.FindFitOrGreater()
    for (int tmp = k; tmp <= freeLists->GetSize(); tmp++) {
        int position = freeLists->GetFromFree(tmp);
        if (position != PSEUDO) {
            return Allocate(position, k);
        }
    }
    return PSEUDO;
}

/*
 *  Disposes reserved memory block.
 *  p: intended position
 */
void BuddySystem::DisposeMem(POSITION p) {
    // ReservedCheck(p)
    if (heap->GetVal(p) == 0)
        cout << "Block at position "<< p << " already free." << endl;

    else if (heap->GetVal(p) == 1)
        freeLists->AddToFree(p, SizeOfBlock(p));

    else cout << "Block at position "<< p << " not found." <<  endl;

}

/*
 *returns size of a block
 */
int BuddySystem::SizeOfBlock(POSITION p) {
    return heap->GetVal(p + 1);
}

FreeLists* BuddySystem::GetFreeLists() { return freeLists; }

void BuddySystem::ShowHeap() {
    heap->Show();
}

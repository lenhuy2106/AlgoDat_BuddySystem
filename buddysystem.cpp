#include "buddysystem.h"

#include <iostream>

using namespace std;

BuddySystem::BuddySystem(Heap* heap) {
    this->heap = heap;
	freeLists = new FreeLists(heap);
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
 *  parameter k: power of size
 *  returns int: position of new block
 *          -1: n
 */
POSITION BuddySystem::NewMem(int k) {
    // -- ValidateSize() - has to be at least 2^2 bytes to store essentials
    if (k < 2) {
        return PSEUDO;
    }

    // -- CheckBlockFree()
    // -- CheckBlockEnoughSize()
    int tmp;
    int result = PSEUDO;

    // lists.FindFitOrGreater()
    for (tmp = k; tmp <= freeLists->GetSize(); tmp++) {
        if (freeLists->GetPos(tmp) != PSEUDO) {
            result = freeLists->GetPos(tmp);
            Allocate(result, k);
            break;
        }
    }
    return result;
}

/*
 *  Disposes reserved memory block.
 *  p: intended position
 */
void BuddySystem::DisposeMem(POSITION p) {
    // ReservedCheck(p)
        // -- isMark()
    if (heap->GetVal(p) == 0)
        cout << "Block at position "<< p << " already free." << endl;

    else if (heap->GetVal(p) == 1)
        freeLists->AddToFree(p, SizeOfBlock(p));

    else // -- if (heap.FirstSize(p))
        cout << "Block at position "<< p << " not found." <<  endl;
    // -- else AddToFreeListElse(p)
}

/*
 *returns size of a block
 */
int BuddySystem::SizeOfBlock(POSITION p) {
    return heap->GetVal(p + 1);
}

FreeLists* BuddySystem::GetFreeLists() { return freeLists; }

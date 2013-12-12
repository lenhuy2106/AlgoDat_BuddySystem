#include "buddysystem.h"

BuddySystem::BuddySystem(Heap* heap) {
    this->heap = heap;
	freeLists = new FreeLists(heap);
}

POSITION BuddySystem::Allocate(POSITION p, int k) {

    int intendedSize = k;
    int currentSize = SizeOfBlock(p);
    int diff = currentSize;
    int blockPos = freeLists->GetFromFree(diff);
    int nextBlock;

    if (intendedSize != currentSize) {
        // DeleteOrigEntry()

        while (intendedSize != currentSize) {
            diff--;
            nextBlock = heap->PowToAtoms(diff);
            // SplitInHalf()
            heap->SetBlock(p, 1, diff, blockPos);
            heap->SetBlock(p + nextBlock, 1, diff, blockPos);

            // UpdateFree()
            freeLists->AddToFree((p + nextBlock), diff);

            // difference in size k(p) and k(allocate)
            currentSize = SizeOfBlock(p);

            // -- UpdateSuc()
        }
    } else {
        heap->SetBlock(p, 1, k, blockPos);
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
        freeLists->AddToFree(p, heap->SizeToPow(SizeOfBlock(p)));

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

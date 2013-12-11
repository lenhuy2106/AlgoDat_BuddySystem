#include "buddysystem.h"
#include <math.h>

BuddySystem::BuddySystem(Heap* heap) {
    this->heap = heap;
	freeLists = new FreeLists(heap);
}

POSITION BuddySystem::Allocate(POSITION p, int k) {

    int intendedSize = pow(2, k);
    int currentSize = SizeOfBlock(p);
    int diff = heap->SizeToPow(currentSize);

    // -- test: +1 ( remove after testing! ) -> why wrong sizeToPow()??
    // -- bug: freeLists updates

if ( intendedSize != currentSize) {


    // DeleteOrigEntry()
    freeLists->GetFromFree(diff);

    while ( intendedSize != currentSize) {

        diff--;
        // SplitInHalf()
        heap->SetBlock(p, 1, diff, freeLists->GetPos(k));
        heap->SetBlock(p + heap->PowToAtoms(diff), 1, diff, freeLists->GetPos(k));

        freeLists->AddToFree((p + heap->PowToAtoms(diff)), diff);

        // difference in size k(p) and k(allocate)
        currentSize = SizeOfBlock(p);
    }

} else {

    freeLists->GetFromFree(diff);
    heap->SetBlock(p, 1, k, freeLists->GetPos(k));
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

    // -- CheckBlockFree()
    // -- CheckBlockEnoughSize()
    // -- ValidateSize() - has to be at least 2^4 bytes to store essentials
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
    if (heap->GetVal(p) == 0) cout << "Block at position "<< p << " already free." << endl;
    else if (heap->GetVal(p) == 1) freeLists->AddToFree(p, heap->SizeToPow(SizeOfBlock(p)));

    else // -- if (heap.FirstSize(p))
        cout << "Block at position "<< p << " not found." <<  endl;
    // -- else AddToFreeListElse(p)
}

/*
 *returns size of a block
 */
int BuddySystem::SizeOfBlock(POSITION p) {
    // -- segmentation fault
    return heap->GetVal(p + 1);
}

FreeLists* BuddySystem::GetFreeLists() { return freeLists; }

#include "buddysystem.h"
#include <math.h>

BuddySystem::BuddySystem(Heap* heap) {
    this->heap = heap;
	freeLists = new FreeLists(heap);
}

POSITION BuddySystem::Allocate(POSITION p, int k) {

    int currentSize = pow(2, k);
    int intendedSize = SizeOfBlock(p);

    // -- test: +1 ( remove after testing! ) -> why wrong sizeToPow()??
    int diff = heap->SizeToPow(SizeOfBlock(p)) + 1;

if ( currentSize != intendedSize) {

        // DeleteOrigEntry()
    freeLists->GetFromFree(heap->SizeToPow(SizeOfBlock(p)) + 1);

    while ( currentSize != intendedSize) {

        diff--;
        // SplitInHalf()

            // SetResMark(p1)
        heap->SetVal(p + OFFSET_RESERVED, 1);
            // SetNewSize(p1)
        heap->SetVal(p + OFFSET_SIZE, pow(2, diff));
            // ? -- SetNewSuc(p1)
        heap->SetVal(p + OFFSET_NEXT, freeLists->GetPos(k));

            // SetResMark(p2)
        heap->SetVal((p + heap->PowToAtoms(diff)) + OFFSET_RESERVED, 1);
            // SetNewSize(p2)
        heap->SetVal((p + heap->PowToAtoms(diff)) + OFFSET_SIZE, pow(2, diff));
            // SetNewSucc(p2):
        heap->SetVal((p + heap->PowToAtoms(diff)) + OFFSET_NEXT, freeLists->GetPos(k));

        // if (heap.FirstSize(p2, 2^k)) : Not neccessary ( NewMem allocates first element in lists )
        freeLists->AddToFree((p + heap->PowToAtoms(diff)), diff);

        // else AddToFreeListElse(p, k-1) : Not neccessary ( It's always the first fitting one )

        // difference in size k(p) and k(allocate)
        intendedSize = SizeOfBlock(p);
    }

} else {

        // DeleteOrigEntry()
    freeLists->GetFromFree(heap->SizeToPow(SizeOfBlock(p)));
        // SetResMark(p1)
    heap->SetVal(p + OFFSET_RESERVED, 1);
        // SetNewSize(p1)
    heap->SetVal(p + OFFSET_SIZE, pow(2, k));
        // ? -- SetNewSuc(p1)
    heap->SetVal(p + OFFSET_NEXT, freeLists->GetPos(k));
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
    try {
        if (heap->GetVal(p) != 1) throw "No Reserved Block: ";
        else
        // -- if (heap.FirstSize(p))
            freeLists->AddToFree(p, heap->SizeToPow(SizeOfBlock(p)));
        // -- else AddToFreeListElse(p)
    }
    catch (string s) {
        cout << s << "at Heap Position " << p << endl;
    }
}

/*
 *returns size of a block
 */
int BuddySystem::SizeOfBlock(POSITION p) {
    // -- segmentation fault
    return heap->GetVal(p + 1);
}

FreeLists* BuddySystem::GetFreeLists() { return freeLists; }

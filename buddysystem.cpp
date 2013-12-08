#include "buddysystem.h"
#include <math.h>

BuddySystem::BuddySystem(Heap* heap) {
    this->heap = heap;
	freeLists = new FreeLists(heap);
}

POSITION BuddySystem::Allocate(POSITION p, int k) {

    // -- test: +1 ( remove after testing! )
    int currentSize = pow(2, k);
    int intendedSize = SizeOfBlock(p);
    int diff = heap->SizeToPow(SizeOfBlock(p)) + 1;

    // -- CheckBlockFree()
    // -- CheckBlockEnoughSize()
    // -- DeleteOrigEntry()

    while ( currentSize != intendedSize) {

        diff--;
        // SplitInHalf()
            // -- SetSuccessor()
            // -- UpdateFreeLists()

            // SetResMark(p1)
        heap->SetVal(p + OFFSET_RESERVED, 1);
            // SetNewSize(p1)
        heap->SetVal(p + OFFSET_SIZE, pow(2, diff));
            // SetResMark(p2)
        heap->SetVal((p + heap->PowToAtoms(diff)), 1);
            // SetNewSize(p2)
        heap->SetVal((p + heap->PowToAtoms(diff)) + OFFSET_SIZE, pow(2, diff));

        // -- if (heap.FirstSize(p2, 2^k))
        freeLists->AddToFree((p + heap->PowToAtoms(diff)), diff);

        // test()
        heap->Show();

        // -- else AddToFreeListElse(p, k-1)

        // difference in size k(p) and k(allocate)
        intendedSize = SizeOfBlock(p);
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

    // -- ValidateSize() - has to be at least 2^4 bytes to store essentials
    int tmp;
    int result = PSEUDO;

    // lists.FindFitOrGreater()
    for (tmp = k; tmp <= freeLists->GetSize(); tmp++) {
        if (freeLists->GetLists()[tmp] != PSEUDO) {
            result = freeLists->GetLists()[tmp];
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

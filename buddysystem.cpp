#include "buddysystem.h"
#include <math.h>

BuddySystem::BuddySystem(Heap* heap) {
	freeLists = new FreeLists(heap);
}

POSITION BuddySystem::Allocate(POSITION p, int k) {

    // -- CheckBlockFree()
    // -- CheckBlockEnoughSize()
    // -- DeleteOrigEntry()

    while (SizeOfBlock(p) != pow(2, k)) {
        // SplitInHalf()
            // SetNewSize(p1)
        heap->SetVal(p + 1, pow(2, k-1));
            // SetNewSize(p2)
        heap->SetVal((p + heap->PowToAtoms(k)) / 2, pow(2, k-1));

        // -- if (heap.FirstSize(p2, 2^k))
            freeLists->AddToFree(p, k-1);

        // -- else AddToFreeListElse(p, k-1)
        k--;
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
int BuddySystem::SizeOfBlock(POSITION position) {
    // -- segmentation fault
    return heap->GetVal(position + 1);
}

FreeLists* BuddySystem::GetFreeLists() { return freeLists; }

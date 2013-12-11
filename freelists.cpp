#include "freelists.h"

FreeLists::FreeLists(Heap* heap) {
	this->heap = heap;
    size = heap->GetM();
	lists = new int[size];

	// Set all free lists to an empty state (except the last)
    for (int i = 0; i < size; i++) {
        lists[i] = PSEUDO;
	}

    // Initial free block for the whole heap
    heap->SetBlock(0,0,heap->GetM(),PSEUDO);
    lists[heap->GetM()] = 0;
}

void FreeLists::AddToFree(POSITION position, int k) {

// ? -- FreeSpaceCheck
//    try {
//
//        for (int i = 0; i <= size; i++) {
//            if (i >= position || i <= position + heap->PowToAtoms(k)) throw 1;
//        }
    heap->SetBlock(position,0, k, lists[k]);
        lists[k] = position;
//    }
//    catch (int i) {
//        cout << "Exception: Overwriting existing block." << endl;
//    }
}

POSITION FreeLists::GetFromFree(int k) {

    int position;

//  returns -1 if k invalid
    if (k <= heap->GetM() && k >= 0) {
        position = lists[k];
        // -- CheckIfFirst()
        lists[k] = heap->GetVal(position + OFFSET_NEXT);
    } else position = PSEUDO;
    return position;
}

void FreeLists::ShowLists() {
    for (int i = 0; i <= GetSize(); i++) cout << GetPos(i) << endl;
}

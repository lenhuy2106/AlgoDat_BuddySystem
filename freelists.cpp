#include "freelists.h"

FreeLists::FreeLists(Heap* heap) {
	this->heap = heap;
	size = heap->getM() + 1;
	lists = new int[size];

	// Set all free lists to an empty state (except the last)
	for (int i = 0; i < heap->getM(); i++) {
        lists[i] = PSEUDO;
	}

	// Initial free block for the whole heap
    heap->setBlock(0,heap->getM(),PSEUDO);
	lists[heap->getM()] = 0;
}

void FreeLists::AddToFree(POSITION position, int k) {

    try {
        // Checking free space in freelists
        for (int i = 0; i <= size; i++) {
            if (i >= position || i <= position + heap->powToLength(k)) throw "Overwriting existing block.";
        }
        heap->setBlock(0, k , lists[k]);
        lists[k] = position;
    }
    catch (string s) {
        cout << "Exception: " << s << endl;
    }
}

POSITION FreeLists::GetFromFree(int k) {

    int position = lists[k];

//  returns -1 if k invalid
    if (k <= heap->getM()) {
        lists[k] = heap->GetVal(position + OFFSET_NEXT);
    } else position = PSEUDO;
	return position;
}

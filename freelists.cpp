#include "freelists.h"

FreeLists::FreeLists(Heap* heap) {
	this->heap = heap;
	size = heap->getM() + 1;
	lists = new int[size];

	// Set all free lists to an empty state (except the last)
	for (int i = 0; i < heap->getM(); i++) {
		lists[i] = NO_FREE_LIST;
	}

	// Initial free block for the whole heap
	heap->SetVal(0 + OFFSET_RESERVED, 0);
	heap->SetVal(0 + OFFSET_SIZE, 2 ^ heap->getM());
	heap->SetVal(0 + OFFSET_NEXT, NO_FREE_LIST);
	lists[heap->getM()] = 0;
}

void FreeLists::AddToFree(POSITION position, int k) {
	// TODO: Check if we have enough free space.
	// TODO: Align position?

	heap->SetVal(position + OFFSET_RESERVED, 0);
	heap->SetVal(position + OFFSET_SIZE, 2 ^ k);
	heap->SetVal(position + OFFSET_NEXT, lists[k]);
	lists[k] = position;
}

POSITION FreeLists::GetFromFree(int k) {
	// TODO: Validate k

	int position = lists[k];
	lists[k] = heap->GetVal(position + OFFSET_NEXT);

	return position;
}

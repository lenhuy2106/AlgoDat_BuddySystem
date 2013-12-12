#include "freelists.h"
#include <iostream>
#include <cmath>

using namespace std;

FreeLists::FreeLists(Heap* heap) {
	this->heap = heap;
    size = heap->GetM();
	lists = new int[size];

	// Set all free lists to an empty state (except the last)
    for (int i = 0; i < size; i++) {
        lists[i] = PSEUDO;
	}
    lists[heap->GetM()] = 0;
}

void FreeLists::AddToFree(POSITION position, int k) {
    heap->SetFreeBlock(position, k, lists[k]);
    lists[k] = position;

	// Merge with buddy
	if (k < heap->GetM()) {
		int buddyPosition = position ^ (int)pow(2, k);
		bool isBuddyReserved = (1 == heap->GetVal(buddyPosition + OFFSET_RESERVED));
		int buddySize = heap->GetVal(buddyPosition + OFFSET_SIZE);
		if (!isBuddyReserved && buddySize == k) {
			int leftBuddyPosition = min<int>(position, buddyPosition);
			int rightBuddyPosition = max<int>(position, buddyPosition);
		
			removeFromFreeList(leftBuddyPosition, k);
			removeFromFreeList(rightBuddyPosition, k);

			// Merge (recursive)
			AddToFree(leftBuddyPosition, k + 1);
		}
	}
}

POSITION FreeLists::GetFromFree(int k) {
    int position;

	//  returns -1 if k invalid
    if (k >= 0 && k <= heap->GetM()) {
        position = lists[k];
		if (position != PSEUDO) {
			lists[k] = heap->GetVal(position + OFFSET_NEXT);
		}
    } else {
		position = PSEUDO;
	}

    return position;
}

void FreeLists::ShowLists() {

    cout << "-----------------" << endl;
    cout << "Size\tFPos" << endl;
    cout << "-----------------" << endl;
    for (int i = 0; i <= GetSize(); i++) {
        cout << i << ":\t";

        if (GetPos(i) != PSEUDO) {
           ShowLinkedNext(i);
           cout << GetPos(i) << endl;
        }
        else cout << endl;
    }
    cout << "-----------------" << endl;
}

void FreeLists::ShowLinkedNext(int linkedPos) {
    int cur = heap->GetVal(GetPos(linkedPos) + OFFSET_NEXT);

    while (cur != PSEUDO) {
        cout << cur << "\t";
        cur = heap->GetVal(cur + OFFSET_NEXT);
    }
}

bool FreeLists::removeFromFreeList(POSITION p, int k) {
	int previousPosition = PSEUDO;
	int currentPosition = lists[k];
	while (currentPosition != PSEUDO && currentPosition != p) {
		previousPosition = currentPosition;
		currentPosition = heap->GetVal(currentPosition + OFFSET_NEXT);
	}
	if (currentPosition != PSEUDO) {
		int nextPosition = heap->GetVal(p + OFFSET_NEXT);
		if (previousPosition == PSEUDO) {
			// Removed free block is the first in the free list
			lists[k] = nextPosition;
		} else {
			heap->SetVal(previousPosition + OFFSET_NEXT, nextPosition);
		}
		return true;
	} else {
		return false;
	}
}

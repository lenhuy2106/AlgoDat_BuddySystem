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

FreeLists::FreeLists(const FreeLists& ref) {
    heap = new Heap(*ref.heap);
    size = ref.size;
    lists = new int[size];
    for(int i = 0; i < size; i++)
       lists[i] = ref.lists[i];
    }

FreeLists& FreeLists::operator=(const FreeLists& ref) {
    if (this != &ref) {
        delete heap;
        delete[] lists;
        heap = new Heap(*ref.heap);
        size = ref.size;
        lists = new int[size];
        for(int i = 0; i < size; i++) {
            lists[i] = ref.lists[i];
        }
    }
    
    return *this;
}

FreeLists::~FreeLists() {
    delete[] lists;
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

    cout << "---------------------" << endl;
    cout << "k\tsize\tindex" << endl;
    cout << "---------------------" << endl;
    for (int k = 0; k <= GetSize(); k++) {
        cout << k << '\t';

        int blockSize = pow(2, k);
        cout << blockSize << '\t';

        int position = GetPos(k);
        while (position != PSEUDO) {
            int index = position / blockSize;
            cout << index << '\t';
            position = heap->GetVal(position + OFFSET_NEXT);
        }
        
        cout << endl;
    }
    cout << "---------------------" << endl;
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

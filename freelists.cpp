#include <math.h>
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
    heap->SetBlock(position,0, k, lists[k]);
    lists[k] = position;
}

POSITION FreeLists::GetFromFree(int k) {
    int position;

//  returns -1 if k invalid
    if (k >= 0 && k <= heap->GetM()) {
        position = lists[k];
        lists[k] = heap->GetVal(position + OFFSET_NEXT);
    } else position = PSEUDO;
    return position;
}

void FreeLists::ShowLists() {

    cout << "-----------------" << endl;
    cout << "Size\tFPos" << endl;
    cout << "-----------------" << endl;
    for (int i = 0; i <= GetSize(); i++) {
        cout << pow(2,i) << ":\t";

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

#include "buddysystem.h"

#include <iostream>
using namespace std;

#define M 5

void printOptions();
void doAction(char action);

Heap* heap = new Heap(M);
BuddySystem* buddySystem = new BuddySystem(heap);

int main(int argc, char* argv[]) {

    // test()
    cout << buddySystem->SizeOfBlock(0) << endl;

    char action;
    do {
        printOptions();
        cout << "> ";
        cin >> action;
        doAction(action);
    } while (action != 'q');

    return 0;
}

void printOptions() {
    cout << "Options:" << endl;
    cout << "> (s)how heap" << endl;
    cout << "> (l)ists" << endl;
    cout << "> (n)ew memory: Size in Power of 2" << endl;
    cout << "> (d)ispose memory: Size in Power of 2" << endl;

    cout << "> (q)uit" << endl;
}

void doAction(char action) {
    int size;
    int position;

    switch (action) {
        case 's':
        heap->Show();
            break;
        case 'n':
        cin >> size;
        buddySystem->NewMem(size);
            break;
        case 'd':
        cin >> position;
        buddySystem->DisposeMem(position);
        case 'l':
        buddySystem->GetFreeLists()->ShowLists();
            break;
    }
}

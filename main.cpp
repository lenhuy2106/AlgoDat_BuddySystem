#include "buddysystem.h"
#include <iostream>
#define M 7

using namespace std;

void printOptions();
void doAction(char action);

Heap* heap = new Heap(M);
BuddySystem* buddySystem = new BuddySystem(heap);

int main() {

    cout << "-----------------" << endl;
    cout << "BUDDY - MEMORY" << endl;
    char action;
    do {
        printOptions();
        cout << "-----------------" << endl << "> ";
        cin >> action;
        doAction(action);
    } while (action != 'q');

    return 0;
}

void printOptions() {

    cout << "-----------------" << endl;
    cout << " Options" << endl;
    cout << "-----------------" << endl;
    cout << "> (s)how heap" << endl;
    cout << "> (f)ree-lists" << endl;
    cout << "> (n)ew memory" << endl;
    cout << "> (d)ispose memory" << endl;
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
        cout << " Power of 2: ";
            cin >> size;
            if (buddySystem->NewMem(size) == PSEUDO) {
                cout << "Error";
            }
            break;
        case 'd':
            cout << " Position: ";
            cin >> position;
                buddySystem->DisposeMem(position);
            break;
        case 'f':
            buddySystem->GetFreeLists()->ShowLists();
            break;
    }
}

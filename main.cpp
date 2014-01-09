#include "buddysystem.h"
#include <iostream>
#define M 500 // number of words

using namespace std;

void printOptions();
void doAction(BuddySystem &buddySystem, char action);

int main() {
    BuddySystem buddySystem(M);

    cout << "-----------------" << endl;
    cout << "BUDDY - MEMORY" << endl;
    char action;
    do {
        printOptions();
        cout << "-----------------" << endl << "> ";
        cin >> action;
        doAction(buddySystem, action);
    } while (action != 'q');

    return 0;
}

void printOptions() {

    cout << "-----------------" << endl;
    cout << " Options" << endl;
    cout << "-----------------" << endl;
    cout << "(s)how heap" << endl;
    cout << "(f)ree-lists" << endl;
    cout << "(n)ew memory" << endl;
    cout << "(d)ispose memory" << endl;
    cout << "(q)uit" << endl;
}

void doAction(BuddySystem &buddySystem, char action) {
    int size;
    int position;
    int newPos;

    switch (action) {
        case 's':
            buddySystem.ShowHeap();
            break;
        case 'n':
            cout << " In words: ";
            cin >> size;
            newPos = buddySystem.NewMem(size);
            if ( newPos == PSEUDO)
                cout << "Failed" << endl;
            else cout << "Succeded at position " << newPos << endl;
            break;
        case 'd':
            cout << " Position: ";
            cin >> position;
                buddySystem.DisposeMem(position);
            break;
        case 'f':
            buddySystem.GetFreeLists().ShowLists();
            break;
    }
}

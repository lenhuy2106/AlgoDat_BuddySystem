#include "buddysystem.h"

#include <iostream>
using namespace std;

#define M 16

void printOptions();
void doAction(char action);

Heap* heap = new Heap(M);
BuddySystem* buddySystem = new BuddySystem(heap);

int main()
{
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
    cout << "(a)llocate" << endl;
    cout << "(n)ew memory" << endl;
    cout << "(d)ispose memory" << endl;
    cout << "(q)uit" << endl;
}

void doAction(char action) {
    switch (action) {
        case 'a':
            // TODO
            break;
        case 'n':
            // TODO
            break;
        case 'd':
            // TODO
            break;
    }
}

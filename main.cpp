#include "buddysystem.h"

#include <iostream>
using namespace std;

BuddySystem* buddySystem = new BuddySystem(7);

int main(int argc, const char* argv[])
{
	/* TODO: fix
	buddySystem->fListsVec[2].size();

    for (int i = 0; i < buddySystem->heapVec.size (); i++) {
        cout << buddySystem->heapVec[i] << endl;
	}
	*/

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

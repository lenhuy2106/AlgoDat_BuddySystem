#include "buddysystem.h"

using namespace std;

int main()
{
    cout << "Hello World!" << endl;

    BuddySystem* buddySystem = new BuddySystem(7);

//    buddySystem->NewMem(2);
    buddySystem->fListsVec[2].size();

    for (int i = 0; i < buddySystem->heapVec.size (); i++)
        cout << buddySystem->heapVec[i] << endl;

    return 0;
}

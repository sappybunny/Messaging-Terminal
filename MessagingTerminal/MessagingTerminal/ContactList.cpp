#include "ContactList.h"

using namespace std;

ContactList::ContactList()
{
    // Constructor
}

int ContactList::prompt()
{
    cout << "[1] Campbell Jack \n";
    cout << "[2] Olivia Gray \n";
    cout << "[0] EXIT \n";
    cout.flush();
    return 0;
}

int ContactList::getInput()
{
    if (fgets(inputBuffer, sizeof inputBuffer, stdin) == NULL)
    {
        throw runtime_error("Failed to read from stdin!");
        return -1;
    }

    MessageDisplay md;

    switch (inputBuffer[0])
    {
    case '1':
        // Contact number 1
        md.menuLoop();

        return 0;
        break;
    case '2':
        // Contact number 2

        return 0;
        break;

    case '0':
        return -1;
        break;

    default:
        return 1;
        break;
    }
    return 0;
}

int ContactList::menuLoop()
{
    do
    {
        prompt();
    } while (getInput() >= 0);
    return 0;
}

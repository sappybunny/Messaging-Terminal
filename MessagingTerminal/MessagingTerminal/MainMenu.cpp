#include "MainMenu.h"

using namespace std;

enum MenuState currentState;

MainMenu::MainMenu()
{
    // Constructor
    currentState = MAIN;
}

int MainMenu::prompt()
{
    cout << "[1] Show Contact List \n";
    cout << "[2] Add a New Contact \n";
    cout << "[3] Remove a Contact \n";
    cout.flush();

    return 0;
}

int MainMenu::getInput()
{
    if (fgets(inputBuffer, sizeof inputBuffer, stdin) == NULL)
    {
        throw runtime_error("Failed to read from stdin!");
        return -1;
    }

    switch (inputBuffer[0])
    {
    case '1':
    {
        // Show Contact List
        ContactList cl;
        cl.menuLoop();
        return 0;
        break;
    }
    case '2':
    {
        // Add a New Contact

        return 0;
        break;
    }

    case '0':
    {
        return -1;
        break;
    }
    default:
    {
        return 1;
        break;
    }
    }
    return 0;
}

int MainMenu::menuLoop()
{
    ContactList cl;
    cl.menuLoop();
    do
    {
        switch (currentState)
        {
        case MAIN:
        {
            prompt();
            getInput();
            break;
        }
        case CONTACT_LIST:
        {
            
            break;
        }
        case CONTACT_ADD:
        {
            break;
        }
        case CONTACT_REMOVE:
        {
            break;
        }
        }
    } while (currentState != CONTACT_REMOVE);
    return 0;
}

int main()
{
    MainMenu mm;
    mm.menuLoop();
}
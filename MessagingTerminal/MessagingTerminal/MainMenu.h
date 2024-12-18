#pragma once

#include <iostream>

#include "ContactList.h"
#include "IMenu.h"

enum MenuState
{
    MAIN = 0,
    CONTACT_LIST = 1,
    CONTACT_ADD = 2,
    CONTACT_REMOVE = 3,
    MESSAGE_CONTACT = 4
};

class MainMenu: public IMenu
{
    public:
    MainMenu();
    public:
    int prompt();
    int menuLoop();
    int getInput();
};
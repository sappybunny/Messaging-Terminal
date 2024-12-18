#pragma once


#include <iostream>
#include <stdio.h>

#include "IMenu.h"
#include "MessageDisplay.h"

class ContactList: public IMenu
{
    public:
    ContactList();
    public:
    int prompt();
    int getInput();
    int menuLoop();
};
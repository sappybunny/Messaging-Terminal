#pragma once

#include <string>
#include <iostream>

#include "BufferHandler.h"
#include "IMenu.h"

class MessageDisplay: public IMenu
{
    public:
    std::string recipientName;
    char messageBuffer[1024];

    public:
    MessageDisplay();

    public:
    int prompt();
    int getInput();
    int menuLoop();

};
#pragma once


class IMenu 
{
    protected:
    char inputBuffer[64];
    public:
    virtual int prompt() = 0;
    virtual int menuLoop() = 0;
    virtual int getInput() = 0;
};
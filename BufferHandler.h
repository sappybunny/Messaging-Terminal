#pragma once

#include <string>
#include <stdexcept>
#include <stdio.h>

class BufferHandler
{
    public:
    BufferHandler()
    {
        // Constructor
    }
    protected:
    int writeStringToBufferFile(string filename, string message);
    string readStringFromBufferFile(string filename);
};
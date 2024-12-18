#pragma once

#include <string>
#include <stdexcept>
#include <stdio.h>

class BufferHandler
{
    public:
    BufferHandler();
    public:
    int writeStringToBufferFile(const char* filename, char* messageBuffer);
    std::string readStringFromBufferFile(const char* filename);
};
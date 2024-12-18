#include "BufferHandler.h"
using namespace std;

BufferHandler::BufferHandler()
{
    // Constructor
}

int BufferHandler::writeStringToBufferFile(const char* filename, char *messageBuffer)
{
    FILE* fp;
    fopen_s(&fp, filename, "a+");
    if (fp == NULL)
    {
        throw runtime_error("Failed to open or create file!");
        return -1;
    }

    char lengthBuffer[8];
    // TODO THIS CAUSES CRASH
    snprintf(lengthBuffer, sizeof lengthBuffer, "%i", strlen(messageBuffer));

    // Write message length at start of line
    if (fputs(lengthBuffer, fp) < 0)
    {
        throw runtime_error("Failed to write to file!");
        return -1;
    }
    free(lengthBuffer);

    // Write x00 NULL char after message length
    if (fputc('\0', fp) < 0)
    {
        throw runtime_error("Failed to write to file!");
        return -1;
    }

    // Write message after x00 NULL char
    if (fwrite(messageBuffer, sizeof messageBuffer[0], strlen(messageBuffer), fp) < 0)
    {
        throw runtime_error("Failed to write to file!");
        return -1;
    }

    return 0;
}

// MUST HANDLE NULL BYTES AND EOL CHARACTERS (x00, x0A)!!!
string BufferHandler::readStringFromBufferFile(const char* filename)
{

    FILE* fp;
    fopen_s(&fp, filename, "r");

    if (fp == NULL)
    {
        throw runtime_error("Failed to open file!");
        return "";
    }

    int messageLength;

    if (fscanf_s(fp, "%d", &messageLength) != 1)
    {
        throw runtime_error("Failed to read message length from file!");
        return "";
    }

    // Instantiate a string of '\0' with length of the message
    string message(messageLength, '\0');
    if (fread(&message[0], sizeof &message[0], message.length(), fp) < messageLength)
    {
        throw runtime_error("Failed to read message from file!");
        return "";
    }

    return message;
}

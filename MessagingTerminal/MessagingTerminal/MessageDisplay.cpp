#include "MessageDisplay.h"

using namespace std;

MessageDisplay::MessageDisplay()
{
    // Constructor
}

int MessageDisplay::prompt()
{
    cout << "[Send]: ";
    cout.flush();
    return 0;
}

int MessageDisplay::getInput()
{
    if (fgets(messageBuffer, sizeof messageBuffer, stdin) == NULL)
    {
        throw runtime_error("Failed to read from stdin!");
        return -1;
    }
    // TODO: Send input to BufferHandler for output and cout "Sent Message!"
    BufferHandler bh;
    try
    {
        const char* myTest = "test";
        bh.writeStringToBufferFile(myTest, messageBuffer);
    }
    catch (string errorMessage)
    {
        cout << "Failed to write to outbound buffer! \n"
             << "Error: " << errorMessage << "\n";
        return -1;
    }

    cout << "Message Sent! \n";
}

int MessageDisplay::menuLoop()
{
    do
    {
        prompt();
    } while (getInput() >= 0);
    return 0;
}
#include <BufferHandler.h>
using namespace std;

class BufferHandler
{
    BufferHandler() 
    {
        // Constructor
    }

    int writeStringToBufferFile(string filename, string message)
    {
        FILE *fp = fopen(filename.c_str(), "ab");
        if (fp == NULL)
        {
            throw runtime_error("Failed to open or create file: '" + filename + "'!");
            return -1;
        }
        else
        {
            if (fprintf(fp, "%s\n", message.c_str()) < 0)
            {
                throw runtime_error("Failed to write to file: '" + filename + "'!");
                return -1;
            }
        }
        return 0;
    }

    // MUST HANDLE NULL BYTES AND EOL CHARACTERS (x00, x0A)!!!
    string readStringFromBufferFile(string filename)
    {

        FILE *fp = fopen(filename.c_str(), "rb");

        if (fp == NULL)
        {
            throw runtime_error("Failed to open file: '" + filename + "'!");
            return "";
        }

        int messageLength;

        if (fscanf(fp, "d", &messageLength) != 1)
        {
            throw runtime_error("Failed to read message length from file: '" + filename + "'!");
            return "";
        }

        // Instantiate a string of '\0' with length of the message
        string message(messageLength, '\0');
        if (fread(&message[0], sizeof &message[0], message.length(), fp) < messageLength)
        {
            throw runtime_error("Failed to read message from file: '" + filename + "'!");
            return "";
        }

        return message;
    }
};

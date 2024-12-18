

#include "Config.h"
#include "ISession.h"
#include <cstring>
#include <iostream>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#include <thread>

using namespace Config;
using namespace std;

class SessionClient: public ISession {
    protected:
    int clientSocket;
    int socketNumber;

    public:
    char sessionPayloadBuffer[8192];
    char sessionHeaderBuffer[16];
    char sessionReceiveBuffer[8208];

    // Constructor
    public:
    SessionClient() {
        clientSocket = startSocket();
        socketNumber = clientSocket;
    }


    private:
    int startSocket() {

        int socketNumber = socket(AF_INET, SOCK_STREAM, 0);

        return socketNumber;
    }

    public:
    int startClient() {

        sockaddr_in serverAddress;
        serverAddress.sin_family = AF_INET;
        serverAddress.sin_port = htons(PORT_APPLICATION);
        serverAddress.sin_addr.s_addr = INADDR_ANY;

        connect(clientSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress));

        return 1;
    }

    public:
    int sendMessage(const char* message, int length) {

        send(clientSocket, message, strlen(message), 0);

        return strlen(message);

    }
    
    // CLIENT-SERVER
    public:
    string receiveRaw() {

        int receivedLength = 0;
        receivedLength = recv(clientSocket, sessionReceiveBuffer, sizeof(sessionReceiveBuffer), 0);

        if (receivedLength > 0) {
            sessionReceiveBuffer[receivedLength] = '\0';
            string resultString(sessionReceiveBuffer);
            return resultString;
        } else {
            return "-1";
        }
    }



};

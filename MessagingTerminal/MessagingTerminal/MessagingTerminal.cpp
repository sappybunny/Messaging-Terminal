#include "MessagingTerminal.h"

using namespace std;
/*
class MessagingTerminal
{


    string promptSendMessageInput(string prompt)
    {
        string userInput;
        cout << prompt << ": ";

        getline(cin, userInput);

        if (userInput.length() <= 0)
        {
            throw invalid_argument("Invalid Input!");
            return "";
        }

        return userInput;
    }

    int MessageInputLoop(ISession &session)
    {
        string message;
        bool notExit = true;

        cout << "\nAt any point, type '@EXIT' to exit, and enter to send.";

        while (notExit)
        {
            message = promptSendMessageInput();
            if (message == "@EXIT")
            {
                break;
            }
            else
            {
                session.sendMessage(message.c_str(), message.length() + 1);
            }
        }
        return 1;
    }

    int CipherInputLoop(ISession &session, ICipher &cipher)
    {
        cout << "\nAt any point, type '@EXIT' to exit, and enter to send.";
        string message;
        string cipherMessage;
        bool notExit = true;
        while (notExit)
        {
            message = PromptSendMessageInput();
            if (message == "@EXIT")
            {
                break;
            }
            else
            {
                /*
                cout << "HERE IS THE SENT PLAINTEXT STUFF:\n";
                for (unsigned int i = 0; i <= message.length(); i++){
                    cout << message.c_str()[i] + 48;
                }
                */
                //cipherMessage = cipher.Encrypt(message);
                /*
                cout << "HERE IS THE SENT ENCRYPTED STUFF:\n";
                for (unsigned int i = 0; i <= cipherMessage.length(); i++){
                    cout << cipherMessage.c_str()[i] + 48;
                }
                */
               /*
                session.sendMessage(cipherMessage.c_str(), message.length() + 1);
            }
        }
        return 1;
    }

    void OutputMessage(string message)
    {
        cout << "Here is your message: ";
        cout << message << "\n";
        return;
    }

    int ServerMain(SessionServer &serverSession)
    {
        // Starts thread for initialising server and accepting client connections
        thread serverThread(&SessionServer::startServer, ref(serverSession));
        serverThread.detach();
        // serverSession.startServer();

        // Waits for a client to connect to the server before proceeding
        while (!serverSession.connected)
        {
            sleep(1);
            cout << ".";
            cout.flush();
        }

        switch (cryptChoice)
        {
        // Diffie-Hellman Symmetric Encryption is chosen
        case 1:
        {
            // Establish shared secret with connected host
            mpz_class symmetricKey = DHHandshake(serverSession);
            ICipher *cipherInterface;

            switch (cipherChoice)
            {
            // One-Time-Pad Cipher is chosen
            case 1:
            {
                OTP myOTP = OTP(symmetricKey, serverSession);
                cipherInterface = &myOTP;
            }
            break;
            // RC4A1 Cipher is chosen
            case 2:
            {
                RC4A1 myRC4A1 = RC4A1(symmetricKey);
                cipherInterface = &myRC4A1;
            }
            break;
            // VMPCA1 Cipher is chosen
            case 3:
            {
                VMPCA1 myVMPCA1 = VMPCA1(symmetricKey);
                cipherInterface = &myVMPCA1;
            }
            break;
            case 4:
            {
                RC4_drop512 myRC4_drop512 = RC4_drop512(symmetricKey, serverSession);
                cipherInterface = &myRC4_drop512;
            }
            }
            serverSession.receiverCipherStartMethod(*cipherInterface);
            /*
            thread receiverCipherThread(&SessionServer::receiverCipherStartMethod, ref(serverSession), ref(*cipherInterface));
            receiverCipherThread.detach();
            */
           /*
            while (true)
            {
                sleep(1);
            }
            break;
        }

            thread receiverThread(&SessionServer::receiverStartMethod, ref(serverSession));
            MessageInputLoop(serverSession);
        }

        return 1;
    }

    int ClientMain(SessionClient &clientSession)
    {
        // Initialises some session variables and attempts connection to server socket
        clientSession.startClient();

        switch (cryptChoice)
        {
        // Diffie-Hellman Symmetric Encryption is chosen
        case 1:
        {
            // Establish shared secret with connected host
            mpz_class symmetricKey = DHHandshake(clientSession);
            ICipher *cipherInterface;

            switch (cipherChoice)
            {
            // One-Time-Pad Cipher is chosen
            case 1:
            {
                OTP myOTP = OTP(symmetricKey, clientSession);
                cipherInterface = &myOTP;
            }
            break;
            // RC4A1 Cipher is chosen
            case 2:
            {
                RC4A1 myRC4A1 = RC4A1(symmetricKey);
                cipherInterface = &myRC4A1;
            }
            break;
            // VMPCA1 Cipher is chosen
            case 3:
            {
                VMPCA1 myVMPCA1 = VMPCA1(symmetricKey);
                cipherInterface = &myVMPCA1;
            }
            break;
            // RC4A2 Cipher is chosen
            case 4:
            {
                RC4_drop512 myRC4_drop512 = RC4_drop512(symmetricKey, clientSession);
                cipherInterface = &myRC4_drop512;
            }
            }
            // Encrypts input and sends to server
            CipherInputLoop(clientSession, *cipherInterface);
        }
        break;

        // No encryption chosen
        default:
        {
            // Sends input to server
            MessageInputLoop(clientSession);
        }
        break;
        }
        return 1;
    }
};

int main()
{

    string cryptChoiceStr = "-1";
    /*
    while(cryptChoiceStr != "1" and cryptChoiceStr != "2") {
        cout << "Type '1' for Diffie-Hellman Symmetric Encryption, type '2' for none: ";
        getline(cin, cryptChoiceStr);
    }
    cryptChoice = stoi(cryptChoiceStr);
    *//*
    cryptChoice = 1;

    string cipherChoiceStr = "-1";
    while (cipherChoiceStr != "1" and cipherChoiceStr != "2" and cipherChoiceStr != "3" and cipherChoiceStr != "4" and cryptChoice == 1)
    {
        cout << "Type '1' for One-Time-Pad XOR cipher, \n";
        cout << "Type '2' for RC4A1 stream cipher, \n";
        cout << "Type '3' for VMPC stream cipher. \n";
        cout << "Type '4' for RC4-drop512 stream cipher with S-Box. \n";
        cout.flush();
        getline(cin, cipherChoiceStr);
    }
    cipherChoice = stoi(cipherChoiceStr);

    string choice = "-1";
    while (choice != "1" and choice != "2")
    {
        cout << "Type '1' for client, type '2' for server: ";
        getline(cin, choice);
    }

    // Instantiates client object and runs client driver code
    if (choice == "1")
    {
        SessionClient clientSession;
        ClientMain(clientSession);
        // Instantiates server object and runs server driver code
    }
    else if (choice == "2")
    {
        SessionServer serverSession;
        ServerMain(serverSession);
        // Choosing neither?
    }
    else
    {
        return 0;
    }

    return 1;
}
*/

#include "GameManager.h"

SOCKET ListenSocket = INVALID_SOCKET;
SOCKET ClientSocket = INVALID_SOCKET;
SOCKET ConnectSocket = INVALID_SOCKET;


GameManager manager;

bool RunHost()
{
   WSADATA wsaData;
    int iResult;

    struct addrinfo* result = NULL;
    struct addrinfo hints;
    fd_set readfds = { 0 };
    TIMEVAL tv = { 0 };
    tv.tv_sec = 15;

    DWORD dwTimeoutVal = 5000;
    int iSelectReturnStatus = -1;

    int iSendResult;
    char recvbuf[DEFAULT_BUFLEN];
    int recvbuflen = DEFAULT_BUFLEN;

    // Initialize Winsock
    iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (iResult != 0) 
    {
        printf("WSAStartup failed with error: %d\n", iResult);
        return false;
    }

    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;
    hints.ai_flags = AI_PASSIVE;

    // Resolve the server address and port
    iResult = getaddrinfo(NULL, DEFAULT_PORT, &hints, &result);

    if (iResult != 0) 
    {
        printf("getaddrinfo failed with error: %d\n", iResult);
        WSACleanup();
        return false;
    }

    // Create a SOCKET for connecting to server
    ListenSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
    if (ListenSocket == INVALID_SOCKET) 
    {
        printf("socket failed with error: %ld\n", WSAGetLastError());
        freeaddrinfo(result);
        WSACleanup();
        return false;
    }

    // Setup the TCP listening socket
    iResult = bind(ListenSocket, result->ai_addr, (int)result->ai_addrlen);

    if (iResult == SOCKET_ERROR) 
    {
        printf("bind failed with error: %d\n", WSAGetLastError());
        freeaddrinfo(result);
        closesocket(ListenSocket);
        WSACleanup();
        return false;
    }

    freeaddrinfo(result);

    iResult = listen(ListenSocket, SOMAXCONN);
    std::cout << "Waiting on a connection..." << std::endl;
    if (iResult == SOCKET_ERROR) 
    {
        printf("listen failed with error: %d\n", WSAGetLastError());
        closesocket(ListenSocket);
        WSACleanup();
        return false;
    }

    FD_ZERO(&readfds);
    FD_SET(ListenSocket, &readfds);

    // Accept a client socket, accepts a single client
    std::cout << "Beginning 15 second accept timer" << std::endl;

    iSelectReturnStatus = select(0, &readfds, NULL, NULL, &tv);

    // Error on select
    if (iSelectReturnStatus == SOCKET_ERROR)
    {
        std::cout << "Select failed with SOCKET_ERROR" << std::endl;
    }

    // Select successful
    else if (iSelectReturnStatus)
    {
        // Connection established from Client to Server Socket
        if (FD_ISSET(ListenSocket, &readfds))
        {
            std::cout << "Accepting potential connection..." << std::endl;
            ClientSocket = accept(ListenSocket, NULL, NULL);

            if (ClientSocket == INVALID_SOCKET)
            {
                printf("accept failed with error: %d\n", WSAGetLastError());
                closesocket(ListenSocket);
                WSACleanup();
                return false;
            }

            else
            {
                // Set Receive Time out 
                setsockopt(ClientSocket, SOL_SOCKET, SO_RCVTIMEO, (const char*)&dwTimeoutVal, sizeof(dwTimeoutVal));

                // Set Send Time out
                setsockopt(ClientSocket, SOL_SOCKET, SO_SNDTIMEO, (const char*)&dwTimeoutVal, sizeof(dwTimeoutVal));
            }
        }
        
        // Connection established to invalid socket (Pretty impossible in my case)
        else
        {
            std::cout << "Invalid socket connection returned" << std::endl;
            closesocket(ListenSocket);
            WSACleanup();
            return false;
        }
    }
    else
    {
        std::cout << "Select function timed out" << std::endl;
        closesocket(ListenSocket);
        WSACleanup();
        return false;
    }

    std::cout << "Client connected to server!" << std::endl;

    // No longer need server socket
    closesocket(ListenSocket); 

    return true;
}

bool RunClient()
{
    WSADATA wsaData;
    struct addrinfo* result = NULL,
        * ptr = NULL,
        hints;
    const char* sendbuf = "";
    char recvbuf[DEFAULT_BUFLEN];
    int iResult;
    int recvbuflen = DEFAULT_BUFLEN;

    // Initialize Winsock
    iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (iResult != 0)
    {
        printf("WSAStartup failed with error: %d\n", iResult);
    }

    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;

    // Resolve the server address and port
    iResult = getaddrinfo("localhost", DEFAULT_PORT, &hints, &result);
    if (iResult != 0) 
    {
        printf("getaddrinfo failed with error: %d\n", iResult);
        WSACleanup();

    }

    // Attempt to connect to an address until one succeeds
    for (ptr = result; ptr != NULL; ptr = ptr->ai_next) 
    {

        // Create a SOCKET for connecting to server
        ConnectSocket = socket(ptr->ai_family, ptr->ai_socktype,
            ptr->ai_protocol);
        if (ConnectSocket == INVALID_SOCKET) 
        {
            printf("socket failed with error: %ld\n", WSAGetLastError());
            WSACleanup();
        }

        // Connect to server.
        std::cout << "Attempting to connect to Server..." << std::endl;
        iResult = connect(ConnectSocket, ptr->ai_addr, (int)ptr->ai_addrlen);
        if (iResult == SOCKET_ERROR) 
        {
            closesocket(ConnectSocket);
            ConnectSocket = INVALID_SOCKET;
            continue;
        }

        std::cout << "Connected to Server!" << std::endl;
        break;
    }

    freeaddrinfo(result);

    if (ConnectSocket == INVALID_SOCKET) 
    {
        printf("Unable to connect to server!\n");      
        WSACleanup();
        return false;
    }

    // Send an initial buffer
    iResult = send(ConnectSocket, sendbuf, (int)strlen(sendbuf), 0);
    if (iResult == SOCKET_ERROR) 
    {
        printf("send failed with error: %d\n", WSAGetLastError());
        closesocket(ConnectSocket);
        WSACleanup();
        return false;
    }

    printf("Bytes Sent: %ld\n", iResult); 

    return true;
}
#undef main
int main()
{
    bool isHost = false; // flag to pass to Run instance to decide turn order
    char networkRole = ' ';
    bool bIsRunning = true;
    while (bIsRunning == true)
    {
        std::cout << "Are you hosting? (y,n)" << std::endl;
        std::cout << "You can quit with q" << std::endl;

        std::cin >> networkRole;

        if (std::tolower(networkRole) == 'q')
        {
            bIsRunning = false;
        }
        else if (std::tolower(networkRole) == 'y')
        {
           
            if(RunHost() == true)
            {
                isHost = true;
                std::cout << "You are: O" << std::endl;
                manager.Init(isHost);
                manager.Run(isHost, ClientSocket);
                bIsRunning = false;
            }
            else
            {
                std::cout << "Server has gotten bored of waiting! Try again" << std::endl;
            }
        }
        else if (std::tolower(networkRole) == 'n')
        {
            if (RunClient() == true)
            {
                std::cout << "You are: X" << std::endl;
                manager.Init(isHost);
                manager.Run(isHost, ConnectSocket);
                bIsRunning = false;
            }
            else
            {
                std::cout << "Could not find a server to connect to or connection timed out! Try again..." << std::endl;
            }
        }
        else
        {
            std::cout << "Invalid character! Must be y/n" << std::endl;
        }
    }

    // cleanup
    closesocket(ClientSocket);
    closesocket(ConnectSocket);
    WSACleanup();

	return 0;
}




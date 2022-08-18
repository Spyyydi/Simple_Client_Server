#include <iostream>
#include <WinSock2.h>
#define PORT 8080
#define IPADDR "127.0.0.1"

#pragma warning(disable: 4996)

int main()
{
    WSAData wsaData;
    WORD DLLVersionRequested = MAKEWORD(2, 2);
    int err;

    err = WSAStartup(DLLVersionRequested, &wsaData);
    if (err != 0)
    {
        std::cout << "WSAStartup failed with error " << err << std::endl;
        WSACleanup();
        exit(EXIT_FAILURE);
    }

    SOCKADDR_IN addr;
    int sizeofaddr = sizeof(addr);
    addr.sin_addr.s_addr = inet_addr(IPADDR);
    addr.sin_port = htons(PORT);
    addr.sin_family = AF_INET;

    //create socket for listening
    SOCKET Listener = socket(AF_INET, SOCK_STREAM, NULL);
    if (Listener == INVALID_SOCKET)
    {
        std::cout << "Socket creation failed" << std::endl;
        WSACleanup();
        exit(EXIT_FAILURE);
    }

    //bind address and port to listening socket
    err = bind(Listener, (SOCKADDR*)&addr, sizeofaddr);
    if (err == SOCKET_ERROR)
    {
        std::cout << "Binding socket failed" << std::endl;
        closesocket(Listener);
        Listener = INVALID_SOCKET;
        WSACleanup();
        exit(EXIT_FAILURE);
    }

    //listen for connection attempt
    err = listen(Listener, SOMAXCONN);
    if (err == SOCKET_ERROR)
    {
        std::cout << "Listening socket failed" << std::endl;
        closesocket(Listener);
        Listener = INVALID_SOCKET;
        WSACleanup();
        exit(EXIT_FAILURE);
    }

    SOCKET ClientSocket; //create socket for new connection
    ClientSocket = accept(Listener, (SOCKADDR*)&addr, &sizeofaddr);
    if (ClientSocket == INVALID_SOCKET)
    {
        std::cout << "Accepting socket failed" << std::endl;
        closesocket(Listener);
        Listener = INVALID_SOCKET;
        WSACleanup();
        exit(EXIT_FAILURE);
    }
    else
    {
        std::cout << "Client connected!" << std::endl;
    }



    system("pause");
    return 0;
}
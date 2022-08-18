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

    SOCKET Connection = socket(AF_INET, SOCK_STREAM, NULL);
    err = connect(Connection, (SOCKADDR*)&addr, sizeofaddr);
    if (err == INVALID_SOCKET)
    {
        std::cout << "Error: Failed connect to server" << std::endl;
        WSACleanup();
        exit(EXIT_FAILURE);
    }

    std::cout << "Connected!" << std::endl;


    system("pause");
    return 0;
}
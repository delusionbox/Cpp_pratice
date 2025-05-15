#include <iostream>
#include <WinSock2.h>

#pragma comment(lib, "ws2_32.lib") // winsock library
using namespace std;

int main()
{
    WSADATA wsa;
    SOCKET serverSocket, clientSocket;
    sockaddr_in server, client;
    char buffer[1024] = {0};

    WSAStartup(MAKEWORD(2, 2), &wsa);
    serverSocket = socket(AF_INET, SOCK_STREAM, 0);

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(8888);

    bind(serverSocket, (sockaddr *)&server, sizeof(server));
    listen(serverSocket, 3);

    int clientSize = sizeof(client);
    clientSocket = accept(serverSocket, (sockaddr *)&client, &clientSize);

    recv(clientSocket, buffer, sizeof(buffer), 0);
    cout << "Client: " << buffer << endl;

    closesocket(clientSocket);
    closesocket(serverSocket);
    WSACleanup();

    return 0;
}
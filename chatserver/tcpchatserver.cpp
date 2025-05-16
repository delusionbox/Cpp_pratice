#include <iostream>
#include <thread>
#include <vector>
#include <winsock2.h>

#pragma comment(lib, "ws2_32.lib") // winsock library
using namespace std;

vector<SOCKET> clients;

void handle_client(SOCKET clientSocket)
{
    char buffer[1024];
    while (true)
    {
        memset(buffer, 0, sizeof(buffer));
        int bytesRecevied = recv(clientSocket, buffer, sizeof(buffer), 0);
        if (bytesRecevied <= 0)
        {
            cout << "Client disconnect\n";
            closesocket(clientSocket);
            return;
        }

        cout << "Client: " << buffer << endl;

        // all client send message
        for (SOCKET client : clients)
        {
            if (client != clientSocket)
            {
                send(client, buffer, bytesRecevied, 0);
            }
        }
    }
}

int main()
{

    WSADATA wsa;
    WSAStartup(MAKEWORD(2, 2), &wsa);

    SOCKET serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_port = htons(8888);

    bind(serverSocket, (sockaddr *)&serverAddr, sizeof(serverAddr));
    listen(serverSocket, 10);
    cout << "server listen 8888 port...\n";

    while (true)
    {
        sockaddr_in clientAddr;
        int addrLen = sizeof(clientAddr);
        SOCKET clientSocket = accept(serverSocket, (sockaddr *)&clientAddr, &addrLen);
        cout << "New Client Connect!\n";

        clients.push_back(clientSocket);
        thread clientThread(handle_client, clientSocket);
        clientThread.detach();
    }

    closesocket(serverSocket);
    WSACleanup();
    return 0;
}
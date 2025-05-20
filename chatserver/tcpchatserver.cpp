#include <iostream>
#include <thread>
#include <vector>
#include <map>
#include <algorithm>
#include <winsock2.h>

#pragma comment(lib, "ws2_32.lib") // winsock library
using namespace std;

vector<SOCKET> clients;
map<SOCKET, string> clientNames; // mapping client socket and nickname

void handle_client(SOCKET clientSocket)
{
    char buffer[1024];

    memset(buffer, 0, sizeof(buffer));
    recv(clientSocket, buffer, sizeof(buffer), 0);
    string clientName = buffer;
    clientNames[clientSocket] = clientName;

    cout << clientName << " is Connect! Hi~\n";

    while (true)
    {
        memset(buffer, 0, sizeof(buffer));
        int bytesRecevied = recv(clientSocket, buffer, sizeof(buffer), 0);
        if (bytesRecevied <= 0)
        {
            cout << clientName << " is disconnect\n";
            closesocket(clientSocket);
            auto it = find(clients.begin(), clients.end(), clientSocket);
            if (it != clients.end())
            {
                clients.erase(it);
            };
            // clients.erase(remove(clients.begin(), clients.end(), clientSocket), clients.end());
            // error: cannot convert 'std::vector<long long unsigned int>::iterator
            clientNames.erase(clientSocket);
            return;
        }

        string message = clientName + ": " + buffer;
        cout << message << endl;

        // all client send message
        for (SOCKET client : clients)
        {
            if (client != clientSocket)
            {
                send(client, message.c_str(), message.size(), 0);
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
        clients.push_back(clientSocket);

        thread clientThread(handle_client, clientSocket);
        clientThread.detach();
    }

    closesocket(serverSocket);
    WSACleanup();
    return 0;
}
#include <iostream>
#include <thread>
#include <string>
#include <winsock2.h>

#pragma comment(lib, "ws2_32.lib")

using namespace std;

void receiveMessage(SOCKET sock)
{
    char buffer[1024];
    while (true)
    {
        memset(buffer, 0, sizeof(buffer));
        int bytesReceived = recv(sock, buffer, sizeof(buffer), 0);
        if (bytesReceived > 0)
        {
            cout << "\nserver" << buffer << endl;
        }
    }
}

int main()
{
    WSADATA wsa;
    WSAStartup(MAKEWORD(2, 2), &wsa);

    SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
    sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    serverAddr.sin_port = htons(8888);

    if (connect(sock, (sockaddr *)&serverAddr, sizeof(serverAddr)) == 0)
    {
        cout << "Connected Server!";

        thread recvThread(receiveMessage, sock);
        recvThread.detach();

        char message[1024];
        while (true)
        {
            cin.getline(message, sizeof(message));
            send(sock, message, strlen(message), 0);
        }
    }

    closesocket(sock);
    WSACleanup();
    return 0;
}
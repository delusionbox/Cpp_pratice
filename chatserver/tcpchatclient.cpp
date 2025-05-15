#include <iostream>
#include <winsock2.h>

#pragma comment(lib, "ws2_32.lib")

using namespace std;

int main()
{
    WSADATA wsa;
    SOCKET sock;
    sockaddr_in server;
    char message[1024] = "Hello Server!";

    WSAStartup(MAKEWORD(2, 2), &wsa);
    sock = socket(AF_INET, SOCK_STREAM, 0);

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = inet_addr("127.0.0.1");
    server.sin_port = htons(8888);

    connect(sock, (sockaddr *)&server, sizeof(server));
    send(sock, message, sizeof(message), 0);

    closesocket(sock);
    WSACleanup();

    return 0;
}
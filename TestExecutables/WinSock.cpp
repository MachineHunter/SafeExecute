#include <winsock2.h>
#include <windows.h>
#include <ws2tcpip.h>
#include <string.h>
#include <stdio.h>
#pragma comment(lib,"ws2_32.lib")

int __cdecl main(int argc, char **argv) {
    WSADATA wsa;
    SOCKET sockfd;
    struct sockaddr_in cliaddr, servaddr;

    WSAStartup(MAKEWORD(2,2), &wsa);

    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(8000);
    InetPton(servaddr.sin_family, "127.0.0.1", &servaddr.sin_addr.S_un.S_addr);

    connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr));

	 char data[100] = "hogehoge";
    send(sockfd, data, sizeof(data), 0);
	 memset(data, 0, 100);
	 recv(sockfd, data, 100, 0);

    return 0;
}

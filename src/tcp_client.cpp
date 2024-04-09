//
// Created by drew.chase on 4/9/2024.
//

#include "tcp_client.h"


#ifdef __WIN32 || __WIN64
#include <winsock2.h>
#include <windows.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>
#pragma comment(lib, "ws2_32.lib") // Winsock Library
#else
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#endif

namespace cnet
{
    tcp_client tcp_client::connect(const std::string &host, const int port)
    {
        tcp_client client;
        client.host = host;
        client.port = port;

#ifdef __WIN32 || __WIN64
        WSAData wsaData;
        SOCKET ConnectSocket = INVALID_SOCKET;
        struct addrinfo *result = NULL,
            *ptr = NULL,
            hints;

#else
        // TODO: Implement for unix
#endif

        return client;
    }
} // cnet

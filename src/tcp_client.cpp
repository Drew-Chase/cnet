//
// Created by drew.chase on 4/9/2024.
//

#include "tcp_client.h"

#include <stdexcept>

#ifdef __WIN32
#include <winsock2.h>
#include <windows.h>
#include <ws2tcpip.h>
#include <cstdio>
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

#ifdef __WIN32
        //  initialize winsock
        WSADATA wsaData;
        client.iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
        if (client.iResult != 0)
        {
            throw std::runtime_error("WSAStartup failed: " + client.iResult);
        }
        // create socket
        client.sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
        if (client.sock == INVALID_SOCKET)
        {
            client.close();
            throw std::runtime_error("Error at socket(): " + WSAGetLastError());
        }
        // Specify the server address and port
        sockaddr_in serverAddr{};
        serverAddr.sin_family = AF_INET;
        serverAddr.sin_port = htons(port);
        serverAddr.sin_addr.s_addr = inet_addr(host.c_str());

        // Connect to server.
        client.iResult = ::connect(client.sock, reinterpret_cast<sockaddr *>(&serverAddr), sizeof(serverAddr));
        if (client.iResult == SOCKET_ERROR)
        {
            client.close();
            throw std::runtime_error("Error at connect(): " + WSAGetLastError());
        }


#else
        // TODO: Implement for unix
#endif

        return client;
    }

    void tcp_client::send(const std::string &message)
    {
#ifdef CNET_TCP_THREADSAFE
        std::lock_guard lock(mutex);
#endif
#ifdef __WIN32
        if (iResult = ::send(sock, message.c_str(), static_cast<int>(message.size()), 0); iResult == SOCKET_ERROR)
        {
            close();
            throw std::runtime_error("Error at send(): " + WSAGetLastError());
        }
#else
        // TODO: Implement for unix
#endif
    }


    std::string tcp_client::receive(const int buffer_size)
    {
#ifdef  __WIN32
        // The following code is suggested as an additional checking mechanism.
        // It checks if the socket is ready for reading.
        timeval timeout{};
        timeout.tv_sec = 0; // Zero timeout (poll)
        timeout.tv_usec = 0;
        fd_set fds;
        FD_ZERO(&fds);
        FD_SET(sock, &fds);
        if (const int select_result = select(0, &fds, nullptr, nullptr, &timeout); select_result > 0)
        {
            char recvBuffer[buffer_size];
            // The socket is ready for reading
            iResult = recv(sock, recvBuffer, buffer_size, 0);
            if (iResult > 0)
            {
                return std::string(recvBuffer, iResult);
            }
            if (iResult == 0)
            {
                return "";
            }
            close();
            throw std::runtime_error("Error at recv(): " + std::to_string(WSAGetLastError()));
        } else if (select_result == 0)
        {
            // The socket is not ready. Return an empty string or handle this case based on your needs.
            return "";
        } else
        {
            // There was an error with select()
            throw std::runtime_error("Error at select(): " + std::to_string(WSAGetLastError()));
        }
#else
        // TODO: Implement for unix
#endif
    }

    void tcp_client::close() const
    {
#ifdef __WIN32
        if (sock != INVALID_SOCKET)
        {
            closesocket(sock);
        }
        WSACleanup();
#else
        // TODO: Implement for unix
#endif
    }
} // cnet

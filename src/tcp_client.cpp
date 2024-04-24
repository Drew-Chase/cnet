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
// #include <openssl/openssl.h>
#pragma comment(lib, "ws2_32.lib") // Winsock Library
#else
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#endif
#include <iostream>

#include "openssl/ssl.h"
#include "openssl/err.h"

namespace cnet
{
    void tcp_client::create_ssl_handshake()
    {
        SSL_library_init();
        if (ssl_context == nullptr)
        {
            SSL_load_error_strings();
            ssl_context = SSL_CTX_new(SSLv23_client_method());

            if (ssl_context == nullptr)
            {
                ERR_print_errors_fp(stderr);
                throw std::runtime_error("Failed to create SSL context");
            }
        }
        ssl = SSL_new(ssl_context);
        SSL_set_fd(ssl, static_cast<int>(sock));
        if (SSL_connect(ssl) == -1)
        {
            ERR_print_errors_fp(stderr);
            throw std::runtime_error("Failed to create SSL connection");
        }
    }

    void tcp_client::write_ssl(const std::string &message) const
    {
        if (SSL_write(ssl, message.c_str(), static_cast<int>(message.size())) <= 0)
        {
            ERR_print_errors_fp(stderr);
            throw std::runtime_error("Failed to write to SSL connection");
        }
    }

    std::string tcp_client::read_ssl(const unsigned long long buffer_size) const
    {
        char buffer[buffer_size];
        if (SSL_read(ssl, buffer, static_cast<int>(buffer_size)) <= 0)
        {
            ERR_print_errors_fp(stderr);
            throw std::runtime_error("Failed to read from SSL connection");
        }
        return {buffer};
    }

    std::string tcp_client::read_ssl_until_eof() const
    {
        std::string response;
        constexpr unsigned long long buffer_size = 4096;
        char buffer[buffer_size] = {};
        while (true)
        {
            memset(buffer, 0, buffer_size); // zero out the buffer (clears any previous data)
            const int bytes = SSL_read(ssl, buffer, buffer_size);
            if (bytes <= 0)
            {
                if (bytes < 0)
                {
                    ERR_print_errors_fp(stderr);
                    throw std::runtime_error("Failed to read from SSL connection");
                }
                // The read operation returned 0, indicating that we have reached the EOF.
                break;
            }

            // Append only the part of buffer that was filled
            response.append(buffer, bytes);
            // check if the response ends with \r\n\r\n
            std::cout << response.substr(response.size() - 4) << std::endl;
            if (response.size() >= 4 && response.substr(response.size() - 4) == "\r\n\r\n" || response.find("\r\n\r\n") != std::string::npos)
            {
                break;
            }
        }

        return response;
    }

    tcp_client tcp_client::connect(const std::string &host, const unsigned int port)
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
            throw std::runtime_error("WSAStartup failed: " + std::to_string(client.iResult));
        }

        addrinfo *result = nullptr, hints{};
        const addrinfo *ptr = nullptr;

        ZeroMemory(&hints, sizeof(hints));
        hints.ai_family = AF_UNSPEC;
        hints.ai_socktype = SOCK_STREAM;
        hints.ai_protocol = IPPROTO_TCP;

        // resolve the server address and port
        client.iResult = getaddrinfo(host.c_str(), std::to_string(port).c_str(), &hints, &result);
        if (client.iResult != 0)
        {
            client.close();
            throw std::runtime_error("getaddrinfo failed: " + std::to_string(client.iResult));
        }

        // Attempt to connect to an address until one succeeds
        for (ptr = result; ptr != nullptr; ptr = ptr->ai_next)
        {
            client.sock = socket(ptr->ai_family, SOCK_STREAM, 0);
            if (client.sock == INVALID_SOCKET)
            {
                WSACleanup();
                throw std::runtime_error("Error at socket(): " + std::to_string(WSAGetLastError()));
            }


            // Connect to server.
            client.iResult = ::connect(client.sock, ptr->ai_addr, static_cast<int>(ptr->ai_addrlen));
            if (client.iResult == SOCKET_ERROR)
            {
                closesocket(client.sock);
                client.sock = INVALID_SOCKET;
                continue;
            }
            break;
        }

        // no longer need address info for server
        freeaddrinfo(result);


#else
        // TODO: Implement for unix
#endif

        client.is_open = true;
        return client;
    }


    void tcp_client::send(const std::string &message)
    {
        if (!is_open) throw std::runtime_error("Socket is not open");
#ifdef CNET_TCP_THREADSAFE
        std::lock_guard lock(mutex);
#endif
#ifdef __WIN32
        if (iResult = ::send(sock, message.c_str(), static_cast<int>(message.size()), 0); iResult == SOCKET_ERROR)
        {
            close();
            throw std::runtime_error("Error at send(): " + std::to_string(WSAGetLastError()));
        }
#else
        // TODO: Implement for unix
#endif
    }


    std::string tcp_client::receive(const unsigned long long buffer_size)
    {
        if (!is_open) throw std::runtime_error("Socket is not open");

#ifdef  __WIN32
        iResult = shutdown(sock, SD_SEND);
        if (iResult == SOCKET_ERROR)
        {
            close();
            throw std::runtime_error("Error at shutdown(): " + std::to_string(WSAGetLastError()));
        }

        char recvBuffer[buffer_size];
        do
        {
            iResult = recv(sock, recvBuffer, buffer_size, 0);
            if (iResult > 0)
                printf("Bytes received: %d\n", iResult);
            else if (iResult == 0)
                printf("Connection closed\n");
            else
                printf("recv failed: %d\n", WSAGetLastError());
        } while (iResult > 0);


        close();
        return {recvBuffer};
#else
        // TODO: Implement for unix

        return "";
#endif
    }

    void tcp_client::close()
    {
        if (!is_open) return;
        is_open = false;

        if (port == 443)
        {
            if (ssl != nullptr)
            {
                SSL_shutdown(ssl);
                SSL_free(ssl);
                ssl = nullptr;
            }
            if (ssl_context != nullptr)
            {
                SSL_CTX_free(ssl_context);
                ssl_context = nullptr;
            }
        }

#ifdef __WIN32
        if (sock != INVALID_SOCKET)
        {
            closesocket(sock);
            sock = INVALID_SOCKET;
        }
        WSACleanup();

#else
        // TODO: Implement for unix
#endif
    }
}

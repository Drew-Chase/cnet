//
// Created by drew.chase on 4/9/2024.
//

#ifndef TCP_CLIENT_H
#define TCP_CLIENT_H
#include <string>

namespace cnet
{
    class tcp_client
    {
    private:
        std::string host;
        int port;

    public:
        /**
         * @brief Establishes a TCP connection to a specified host and port.
         *
         * This method creates a TCP client object, sets the host and port variables of the client,
         * and initializes the necessary data structures for establishing a connection.
         *
         * On windows this will use the Winsock library to establish a connection.<br>
         * <b>See</b> <a href="https://learn.microsoft.com/en-us/windows/win32/winsock/complete-client-code">Microsoft Docs</a> for more information.
         *
         * On Unix systems this will use the socket library to establish a connection.<br>
         * <b>See</b> "https://www.linuxhowtos.org/C_C++/socket.htm" for more information.
         *
         * @param host The hostname or IP address of the server to connect to.
         * @param port The port number to connect to on the server.
         *
         * @return A TCP client object that represents the established connection.
         */
        static tcp_client connect(const std::string &host, int port);

        void send(std::string message);

        std::string receive();

        void close();
    };
} // cnet

#endif //TCP_CLIENT_H

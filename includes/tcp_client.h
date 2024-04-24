//
// Created by drew.chase on 4/9/2024.
//

#ifndef TCP_CLIENT_H
#define TCP_CLIENT_H
#ifdef CNET_TCP_THREADSAFE
#include <mutex>
#endif
#include <string>
#include "openssl/ssl3.h"

namespace cnet
{
    class tcp_client
    {
    protected:
        bool is_open = false;
        std::string host;
        unsigned int port = 0;
        int iResult = 0;
        unsigned long long sock = ~0; // ~0 is a common way to represent an invalid socket it equals -1 in two's complement


        SSL_CTX *ssl_context = nullptr;
        SSL *ssl = nullptr;
#ifdef CNET_TCP_THREADSAFE
        std::mutex mutex;
#endif

        /**
         * @brief Performs the SSL handshake to secure the established TCP connection.
         *
         * This method initializes the SSL library, creates and initializes the SSL context,
         * and sets the socket file descriptor for the SSL object.
         *
         * If the SSL handshake fails, an error message will be printed and a std::runtime_error will be thrown.
         */
       public:
        void create_ssl_handshake();

        /**
         * @brief Writes the given message to the SSL connection.
         *
         * This method writes the provided message to the SSL connection using the SSL_write function.
         * If the write operation fails, an error message is printed and an exception is thrown.
         *
         * @param message The message to be written to the SSL connection.
         * @throws std::runtime_error If the write operation fails.
         */
        void write_ssl(const std::string &message) const;

        /**
         * @brief Reads data from an SSL connection.
         *
         * This method reads data from an SSL connection and returns it as a string.
         *
         * @param buffer_size The size of the buffer to use for reading data.
         * @return A string containing the data read from the SSL connection.
         * @throws std::runtime_error If reading from the SSL connection fails.
         */
        [[nodiscard]] std::string read_ssl(unsigned long long buffer_size) const;

        /**
         * @brief Reads data from an SSL connection until the end of the file is reached.
         *
         * This method reads data from the SSL connection associated with the TCP client.
         * It continues reading data in a loop until the end of the file is reached.
         * The data is stored in a string and returned.
         *
         * If an error occurs during the read operation, an exception of type std::runtime_error is thrown.
         *
         * @return A string that contains the data read from the SSL connection.
         *
         * @throws std::runtime_error If an error occurs during the read operation.
         */
        [[nodiscard]] std::string read_ssl_until_eof() const;
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
        static tcp_client connect(const std::string &host, const unsigned int port);

        /**
         * @brief Sends a message over the TCP connection.
         *
         * This method is used to send a message over the established TCP connection. If the connection
         * is not open, a std::runtime_error will be thrown.
         *
         * If the port is 443, the message will be sent using TLS/SSL via write_ssl() method.
         * Otherwise, the message will be sent using the default send() functionality.
         *
         * @param message The message to be sent over the TCP connection.
         *
         * @throws std::runtime_error if the socket is not open or if there is an error during send().
         */
        void send(const std::string &message);

        /**
         * @brief Receives data from the TCP connection.
         *
         * This method reads the data from the TCP connection and returns it as a string.
         *
         * @param buffer_size The size of the receive buffer.
         * @return A string containing the received data.
         * @throws std::runtime_error If the socket is not open.
         */
        std::string receive(const unsigned long long buffer_size);

        /**
         * @brief Closes the TCP connection.
         *
         * This method closes the TCP connection by performing the necessary cleanup tasks.
         * If the connection uses SSL on port 443, it performs the SSL shutdown and frees the SSL context.
         * For Windows systems, it also closes the socket and performs the necessary cleanup.
         *
         * @note The close method will only close the connection if it is currently open.
         *
         * @see tcp_client::is_open
         * @see tcp_client::port
         * @see tcp_client::ssl
         * @see tcp_client::ssl_context
         */
        void close();

        /**
         * @brief Returns the socket file descriptor.
         *
         * This method returns the socket file descriptor of the TCP client object.
         *
         * @return The socket file descriptor.
         */
        [[nodiscard]] unsigned long long get_sock() const { return sock; }
    };
} // cnet

#endif //TCP_CLIENT_H

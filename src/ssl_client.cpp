#include "../includes/ssl_client.h"
#include "openssl/ssl.h.in"
#include <stdexcept>

ssl_client ssl_client::connect(const std::string &host, int port)
{
    ssl_client client;
    client.host = host;
    client.port = port;

    // Initialize the SSL library
    SSL_library_init();
    SSLeay_add_ssl_algorithms();

    // Create a new SSL context
    client.ssl_context = SSL_CTX_new(SSLv23_client_method());
    if (client.ssl_context == nullptr)
    {
        throw std::runtime_error("Failed to create SSL context");
    }

    // Create a new SSL connection state
    client.ssl = SSL_new(client.ssl_context);
    if (client.ssl == nullptr)
    {
        throw std::runtime_error("Failed to create SSL connection state");
    }

    // Create a new TCP connection
    // client.sock = cnet::tcp_client::connect(host, port).get_sock();
    client.sock = SSL_get_fd(client.ssl);


    // Set the file descriptor of the SSL connection
    SSL_set_fd(client.ssl, client.sock);

    // Initiate the SSL handshake
    if (SSL_connect(client.ssl) != 1)
    {
        throw std::runtime_error("Failed to establish SSL connection");
    }
    return client;
}

#ifndef SSL_H
#define SSL_H
#include <openssl/types.h>

#include "tcp_client.h"


class ssl_client : public cnet::tcp_client
{
private:
    SSL* ssl = nullptr;
    SSL_CTX* ssl_context = nullptr;
public:
    static ssl_client connect(const std::string &host, int port);
    void send(const std::string &message);
    std::string receive(int buffer_size);
    void close();




};


#endif

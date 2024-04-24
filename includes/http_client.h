//
// Created by drew.chase on 4/9/2024.
//

#ifndef HTTP_CLIENT_H
#define HTTP_CLIENT_H

#include "http_message.h"
#include "tcp_client.h"


namespace cnet
{
    class http_client
    {
    private:
        tcp_client tcp;
        http_message message;

        bool preflight_check();
        void parse_headers(std::string body);

        static std::string build_http_query(http_message &message);

    public:
        void make_request(http_message &message);
    };
} // cnet

#endif //HTTP_CLIENT_H

//
// Created by drew.chase on 4/9/2024.
//

#include "http_client.h"

#include <stdexcept>


namespace cnet
{
    void http_client::make_request(http_message &message)
    {
        tcp = tcp_client::connect(message.url.get_host(), message.url.get_port());
        if (!preflight_check(message))
        {
            throw std::runtime_error("Preflight check failed");
        }
    }

    bool http_client::preflight_check(http_message &message)
    {
        if (message.url.get_host().empty()) throw std::runtime_error("Host is empty");
        try
        {
            tcp.send("OPTIONS " + message.url.get_path() + " HTTP/1.1\n\r"
                     "Host:" + message.url.get_host() + "\r\n");
            const std::string response = tcp.receive(4096); // Setting the buffer size to 4KB, this should be overkill for an OPTIONS request, but it's a good size for a buffer.
            printf("%s\n", response.c_str());
            return true;
        } catch (...)
        {
            return false;
        }
    }

    std::string http_client::build_http_query(http_message &message)
    {
        std::string query = message.method + " " + message.url.get_path() + message.url.get_parameter_query() + " HTTP/1.1\n\r"
                            "Host: " + message.url.get_host() + "\r\n";

        if (!message.headers.empty())
        {
            for (auto &[key, value]: message.headers)
            {
                query += key + ": " + value + "\r\n";
            }
        }

        return query;
    }
} // cnet

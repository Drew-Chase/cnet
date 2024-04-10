//
// Created by drew.chase on 4/9/2024.
//

#include "http_client.h"

#include <stdexcept>


namespace cnet
{
    void http_client::make_request(http_message &message)
    {
        if(!preflight_check(message))
        {
            throw std::runtime_error("Preflight check failed");
        }
    }

    bool http_client::preflight_check(http_message &message)
    {
        if(message.url.get_host().empty()) throw std::runtime_error("Host is empty");
        if(message.url.get_port() == 0) throw std::runtime_error("Port is 0");


    }
} // cnet

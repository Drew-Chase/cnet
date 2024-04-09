//
// Created by drew.chase on 4/9/2024.
//

#include <iostream>

#include "http_client.h"


int main()
{
    cnet::http_client client;
    cnet::http_message message("https://postman-echo.com/get");
    client.make_request(message);
    if (message.is_sucess())
    {
        std::cout << message.body << std::endl;
    } else
    {
        fprintf(stderr, "%s responeded with status code %d\nBody:%s\n", message.url.c_str(), message.status_code, message.body.c_str());
    }


    return 0;
}

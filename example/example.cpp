//
// Created by drew.chase on 4/9/2024.
//

#include <stdexcept>

#include "http_client.h"
#include "tcp_client.h"
#include "uri-example.cpp"
using namespace cnet;

int main()
{
    try
    {
        http_client client;
        http_message message("https://postman-echo.com/get");
        client.make_request(message);
    } catch (std::runtime_error &e)
    {
        printf("%s\n", e.what());
    }

    // test_uri();


    // system("pause");
    return 0;
}

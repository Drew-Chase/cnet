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
    tcp_client tcp = tcp_client::connect("google.com", 443);
    tcp.send("GET /get HTTP/1.1\r\nHost: google.com\r\nConnection: keep-alive\r\nUser-Agent: CNET\r\n\r\n");
    const std::string response = tcp.receive(512); // Setting the buffer size to 4KB, this should be overkill for an OPTIONS request, but it's a good size for a buffer.
    tcp.close();
    printf("%s\n", response.c_str());

    // try
    // {
    //     http_client client;
    //     http_message message("https://google.com");
    //     client.make_request(message);
    // } catch (std::runtime_error &e)
    // {
    //     printf("%s\n", e.what());
    // }

    // test_uri();


    // system("pause");
    return 0;
}

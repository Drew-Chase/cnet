//
// Created by drew.chase on 4/9/2024.
//

#include "http_client.h"

#include <iostream>
#include <stdexcept>


namespace cnet
{
    void http_client::make_request(http_message &message)
    {
        this->message = message;
        tcp = tcp_client::connect(message.url.get_host(), message.url.get_port());
        if (message.url.get_port() == 443) tcp.create_ssl_handshake();
        if (!preflight_check())
        {
            throw std::runtime_error("Preflight check failed");
        }
        std::string response;
        if (message.url.get_port() == 443)
        {
            tcp.write_ssl(build_http_query(this->message));
            response = tcp.read_ssl(4096);
        } else
        {
            tcp.send(build_http_query(this->message));
            response = tcp.receive(4096);
        }
        this->message.body = response;
        parse_headers(response);


        tcp.close();
    }

    bool http_client::preflight_check()
    {
        if (message.url.get_host().empty()) throw std::runtime_error("Host is empty");
        try
        {
            const std::string msg = "HEAD " + message.url.get_path() + " HTTP/1.1\r\n"
                                    "Host:" + message.url.get_host() + "\r\n\r\n";
            std::string response;
            if (message.url.get_port() == 443)
            {
                tcp.write_ssl(msg);
                response = tcp.read_ssl(4096);
            } else
            {
                tcp.send(msg);
                response = tcp.receive(4096); // Setting the buffer size to 4KB, this should be overkill for an OPTIONS request, but it's a good size for a buffer.
            }
            parse_headers(response);
            return true;
        } catch (std::exception &e)
        {
            return false;
        }
    }

    void http_client::parse_headers(std::string body)
    {
        const std::string delimiter = "\r\n";
        size_t pos = 0;
        while ((pos = body.find(delimiter)) != std::string::npos)
        {
            std::string token = body.substr(0, pos);
            body.erase(0, pos + 2);
            if (token.empty()) continue;
            if (token.find("HTTP") != std::string::npos)
            {
                message.status_code = std::stoi(token.substr(token.find(' ') + 1, 3));
            } else
            {
                const size_t colon_pos = token.find(':');
                const std::string key = token.substr(0, colon_pos);
                const std::string value = token.substr(colon_pos + 1);
                message.headers[key] = value;

                if (key == "Content-Length")
                {
                    message.content_length = std::stoi(value);
                }
                if (key == "Content-Type")
                {
                    message.content_type = value;
                }
            }
        }
        message.body = body;
    }

    std::string http_client::build_http_query(http_message &message)
    {
        std::string query = http_method_to_str(message.method) + " " + message.url.get_path() + message.url.get_parameter_query() + " HTTP/1.1\n\r"
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

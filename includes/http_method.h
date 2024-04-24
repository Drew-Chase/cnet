//
// Created by drew.chase on 4/9/2024.
//

#ifndef HTTP_METHOD_H
#define HTTP_METHOD_H
#include <stdexcept>

namespace cnet
{
    /**
     * @enum http_method
     * @brief Enumeration of HTTP methods.
     *
     * This enumeration defines the various HTTP methods that can be used in an HTTP request.
     */
    enum class http_method
    {
        GET,
        POST,
        PUT,
        DELETE,
        HEAD,
        OPTIONS,
        PATCH,
        TRACE,
        CONNECT,
    };

    static std::string http_method_to_str(const http_method method)
    {
        switch (method)
        {
            case http_method::GET:
                return "GET";
            case http_method::POST:
                return "POST";
            case http_method::PUT:
                return "PUT";
            case http_method::DELETE:
                return "DELETE";
            case http_method::HEAD:
                return "HEAD";
            case http_method::OPTIONS:
                return "OPTIONS";
            case http_method::PATCH:
                return "PATCH";
            case http_method::TRACE:
                return "TRACE";
            case http_method::CONNECT:
                return "CONNECT";
        }
        throw std::runtime_error("Invalid HTTP method");
    }

    static http_method strto_http_method(std::string method)
    {
        // convert method to uppercase
        for (char &c: method)
        {
            c = static_cast<char>(toupper(c));
        }

        if (method == "GET")
        {
            return http_method::GET;
        }
        if (method == "POST")
        {
            return http_method::POST;
        }
        if (method == "HEAD")
        {
            return http_method::HEAD;
        }
        if (method == "PUT")
        {
            return http_method::PUT;
        }
        if (method == "DELETE")
        {
            return http_method::DELETE;
        }
        if (method == "OPTIONS")
        {
            return http_method::OPTIONS;
        }
        if (method == "TRACE")
        {
            return http_method::TRACE;
        }
        if (method == "CONNECT")
        {
            return http_method::CONNECT;
        }
        if (method == "PATCH")
        {
            return http_method::PATCH;
        }
        throw std::runtime_error("Invalid HTTP method: " + method);
    }
}

#endif //HTTP_METHOD_H

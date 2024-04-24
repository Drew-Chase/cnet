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

    static http_method parse_http_method(std::string method)
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

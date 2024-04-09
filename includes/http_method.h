//
// Created by drew.chase on 4/9/2024.
//

#ifndef HTTP_METHOD_H
#define HTTP_METHOD_H

namespace cnet
{
    /**
     * @enum http_method
     * @brief Enumeration of HTTP methods.
     *
     * This enumeration defines the various HTTP methods that can be used in an HTTP request.
     */
    enum http_method
    {
        GET,
        POST,
        PUT,
        DELETE,
        HEAD,
        OPTIONS,
        PATCH,
        TRACE,
        CONNECT
    };
}

#endif //HTTP_METHOD_H

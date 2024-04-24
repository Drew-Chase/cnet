//
// Created by drew.chase on 4/9/2024.
//

#ifndef HTTP_RESPONSE_H
#define HTTP_RESPONSE_H
#include <map>
#include <string>
#include <utility>
#include "http_method.h"
#include "uri.h"

namespace cnet
{
    /**
     * @brief A message representing an HTTP request and response.
     * This object is used to send and receive HTTP messages.
     * @code{.cpp}
     * cnet::http_message message("https://example.com");
     * @endcode
     * or if you want a http method other than GET
     * @code{.cpp}
     * cnet::http_message message("https://example.com", cnet::http_method::GET);
     * @endcode
     */
    struct http_message
    {
        /**
         * @brief The URL of the HTTP message.
         *
         * This variable represents the URL of an HTTP message. It is a string that stores the URL.
         *
         * Example Usage:
         * @code
         * std::string url = "https://www.example.com";
         * @endcode
         *
         * @see http_message
         * @see http_method
         */
        uri url;
        /**
         * @brief Represents an HTTP method.
         */
        http_method method = http_method::GET;
        /**
         * @brief The body of the HTTP message.
         *
         * This variable represents the body of an HTTP message. It is a string that stores the content of the message body.
         *
         * Example Usage:
         * @code{.cpp}
         * std::string body = "Hello, World!";
         * @endcode
         *
         * @see http_message
         * @see http_message.h
         */
        std::string body;
        /**
         * @brief The Content-Type of an HTTP message.
         *
         * This variable stores the Content-Type of an HTTP message. The Content-Type
         * specifies the media type of the data transmitted in the message body.

         * The Content-Type is a string representation of the media type in the format
         * `type/subtype`. Examples of Content-Type values include "text/plain",
         * "application/json", "image/jpeg", etc.
         */
        std::string content_type;
        /**
         * @brief The length of the content in bytes.
         *
         * This variable represents the length of the content in bytes. It is of type unsigned long long, which ensures that it can hold large values. The value is specified in bytes, which is the standard unit for measuring file sizes and network data transfer. The content length is often used in HTTP headers to indicate the length of the message body in requests and responses.
         *
         * Example usage:
         *
         * @code{.cpp}
         * unsigned long long content_length = 1024;
         * @endcode
         *
         * The content_length variable is used to store the size of a file or the size of data being transferred over a network. It can be assigned a value using an assignment statement, just like any other variable. The value should be specified in bytes as an unsigned long long integer.
         */
        unsigned long long content_length;
        /**
         * @brief The MIME types accepted by the receiver.
         *
         * The accept variable is a std::string object that represents the MIME types
         * accepted by the receiver. This string can contain one or more MIME types
         * separated by commas. The receiver will interpret this information to determine
         * which types of data it can process.
         *
         * For example, if the accept variable is set to "text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,*/
        std::string accept;

        /**
         * @brief A map to store HTTP headers.
         *
         * This map is used to store the headers of an HTTP message. It uses string keys and string values.
         */
        std::map<std::string, std::string> headers;
        /**
         * @brief The HTTP status code of a response.
         *
         * The status code indicates the outcome of an HTTP request.
         * It provides information about whether the request was successful,
         * encountered an error, or requires further action.
         */
        int status_code = 0;
        /**
         * @brief Checks if the HTTP status code indicates a successful response.
         *
         * A successful response is indicated by a status code between 200 and 399 (inclusive).
         *
         * @return True if the status code indicates a successful response, false otherwise.
         */
        [[nodiscard]] bool is_sucess() const { return status_code >= 200 && status_code < 400; };
        /**
         * @brief Check if the HTTP response is a redirect.
         *
         * This method checks if the status code of the HTTP response falls within the range 300-399,
         * indicating a redirect.
         *
         * @return True if the response is a redirect, false otherwise.
         */
        [[nodiscard]] bool is_redirect() const { return status_code >= 300 && status_code < 400; };
        /**
         * @brief Check if the HTTP status code represents a client error.
         *
         * A client error is indicated by a status code in the range 400-499.
         *
         * @return True if the status code is a client error, false otherwise.
         */
        [[nodiscard]] bool is_client_error() const { return status_code >= 400 && status_code < 500; };
        /**
         * @brief Check if the HTTP response status code indicates a server error.
         *
         * This method checks if the status code of an HTTP response falls within the range 500-599,
         * which corresponds to server errors.
         *
         * @return True if the status code is a server error, false otherwise.
         */
        [[nodiscard]] bool is_server_error() const { return status_code >= 500 && status_code < 600; };
        /**
         * @brief Checks if the HTTP message represents an error.
         *
         * This method checks if the HTTP message has a status code indicating an error.
         * An error can be either a client error (status code between 400 and 499) or
         * a server error (status code between 500 and 599).
         *
         * @return True if the HTTP message represents an error, false otherwise.
         */
        [[nodiscard]] bool is_error() const { return is_client_error() || is_server_error(); };
        /**
         * @brief Check if the HTTP status code falls within the Informational range.
         *
         * This method checks whether the HTTP status code of the HTTP message is in the range 100 to 199, which represents
         * Informational status codes according to the HTTP/1.1 specification.
         *
         * @return `true` if the status code is within the Informational range, `false` otherwise.
         */
        [[nodiscard]] bool is_informational() const { return status_code >= 100 && status_code < 200; };
        /**
         * Checks if the HTTP request is successful.
         *
         * @return true if the status code of the HTTP response is 200, false otherwise.
         */
        [[nodiscard]] bool is_ok() const { return status_code == 200; };
        /**
         * @brief Checks if the HTTP response status code indicates that the resource was created.
         *
         * This method checks if the status code of an HTTP response is 201, which indicates that the resource
         * was created successfully.
         *
         * @return true if the resource was created, false otherwise.
         */
        [[nodiscard]] bool is_created() const { return status_code == 201; };
        /**
         * @brief Checks if the HTTP response status code is 202 (Accepted).
         *
         * @return True if the response status code is 202 (Accepted), false otherwise.
         */
        [[nodiscard]] bool is_accepted() const { return status_code == 202; };
        /**
         * @brief Checks if the HTTP response has a "204 No Content" status code.
         *
         * A "204 No Content" status code indicates that the server successfully processed the request, but is not returning any content in the response body.
         * This method checks if the status code of the HTTP response is equal to 204.
         *
         * @return True if the status code is 204, false otherwise.
         */
        [[nodiscard]] bool is_no_content() const { return status_code == 204; };
        /**
         * @brief Checks if the HTTP status code is 205 (Reset Content).
         *
         * The function checks whether the status code of the HTTP message is 205,
         * which indicates that the server has successfully fulfilled the request
         * and that the user agent should reset the document view that caused the
         * request to be sent.
         *
         * @return true if the status code is 205 (Reset Content), false otherwise.
         */
        [[nodiscard]] bool is_reset_content() const { return status_code == 205; };
        /**
         * Check if the HTTP response has a status code of 206 (Partial Content).
         *
         * @return True if the status code is 206, otherwise false.
         */
        [[nodiscard]] bool is_partial_content() const { return status_code == 206; };
        /**
         * @brief Checks if the HTTP response status code is 300 Multiple Choices.
         *
         * This method checks if the HTTP response status code is 300, which indicates
         * that the requested resource has multiple choices available.
         *
         * @return true if the status code is 300, false otherwise.
         *
         * @see http_message
         */
        [[nodiscard]] bool is_multiple_choices() const { return status_code == 300; };
        /**
         * Check if the HTTP response status code is a moved permanently status code (301).
         *
         * @return True if the status code is 301 (moved permanently), false otherwise.
         */
        [[nodiscard]] bool is_moved_permanently() const { return status_code == 301; };
        /**
         * @brief Checks if the HTTP status code is found (302).
         *
         * @return True if the status code is 302, false otherwise.
         */
        [[nodiscard]] bool is_found() const { return status_code == 302; };
        /**
         * Check if the HTTP response status code is 303 (See Other).
         *
         * @return True if the status code is 303 (See Other), false otherwise.
         */
        [[nodiscard]] bool is_see_other() const { return status_code == 303; };
        /**
         * @brief Check if the status code is 304 (Not Modified).
         *
         * @details This method checks if the status code of the HTTP message is 304, indicating that the requested resource has not been modified since the last request.
         *
         * @return True if the status code is 304, false otherwise.
         *
         * @see http_message
         */
        [[nodiscard]] bool is_not_modified() const { return status_code == 304; };
        /**
         * @brief Checks if the HTTP response status code is a temporary redirect (status code 307).
         *
         * A temporary redirect response status code indicates that the requested resource has been temporarily moved to a different URL.
         *
         * @return true if the status code is 307 (temporary redirect), false otherwise.
         */
        [[nodiscard]] bool is_temporary_redirect() const { return status_code == 307; };
        /**
         * @brief Check if the HTTP response is a permanent redirect.
         *
         * A permanent redirect is indicated by the HTTP status code 308.
         *
         * @return True if the response is a permanent redirect, false otherwise.
         */
        [[nodiscard]] bool is_permanent_redirect() const { return status_code == 308; };
        /**
         * @brief Checks if the HTTP request is a bad request (status code 400).
         *
         * This method checks the status code of an HTTP request to determine if it is a bad request.
         * A bad request implies that the server was unable to understand the request due to malformed syntax
         * or other errors on the client side.
         *
         * @return True if the HTTP request is a bad request, False otherwise.
         */
        [[nodiscard]] bool is_bad_request() const { return status_code == 400; };
        /**
         * @brief Checks if the HTTP response is unauthorized.
         *
         * This method checks if the HTTP response status code equals 401, which indicates an unauthorized request.
         *
         * @return true if the response is unauthorized, false otherwise.
         */
        [[nodiscard]] bool is_unauthorized() const { return status_code == 401; };
        /**
         * Checks if the HTTP response status code is 403 (Forbidden).
         *
         * @return True if the HTTP response status code is 403, false otherwise.
         */
        [[nodiscard]] bool is_forbidden() const { return status_code == 403; };
        /**
         * @brief Checks if the status code indicates a "Not Found" response.
         *
         * This method checks if the status code of the HTTP message is 404.
         *
         * @return True if the status code is 404, false otherwise.
         */
        [[nodiscard]] bool is_not_found() const { return status_code == 404; };
        /**
         * @brief Constructs an http_message object with the specified URL.
         * This constructor can be used to create an http_message object to send an HTTP request to the specified URL.
         *
         * @param url The URL to send the request to.
         */
        explicit http_message(std::string url): url(uri(std::move(url))) {};
        /**
         * @brief Constructs an HTTP message with the given URL.
         *
         * An HTTP message is used to represent an HTTP request or response.
         * The URL parameter specifies the target of the message.
         *
         * @param url The URL of the HTTP message.
         */
        explicit http_message(uri url): url(std::move(url)) {};
        /**
         * @brief Constructs an HTTP message object with the given URL and request method.
         *
         * This constructor is used to initialize a message representing an HTTP request or response.
         *
         * @param url The URL for the message, as a string.
         * @param method The HTTP method for the request, as a constant http_method object.
         *
         * Example Usage:
         * @code{.cpp}
         * http_message message("https://example.com", http_method::GET);
         * @endcode
         */
        http_message(std::string url, const http_method method): url(uri(std::move(url))), method(method) {};
        /**
         * @brief Constructs an http_message object with the given URL and HTTP method.
         *
         * @param url The URL for the HTTP request or response.
         * @param method The HTTP method to be used for the message.
         *
         * @code{.cpp}
         * // Example usage:
         * uri url("https://example.com");
         * http_message message(url, http_method::GET);
         * @endcode
         */
        http_message(uri url, const http_method method): url(std::move(url)), method(method) {};
    };
}

#endif //HTTP_RESPONSE_H

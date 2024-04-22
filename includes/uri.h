//
// Created by drew.chase on 4/10/2024.
//

#ifndef URI_H
#define URI_H
#include <map>
#include <string>

#define MAX_PORT 65535
#define MIN_PORT 0
#define HTTP_PORT 80
#define HTTPS_PORT 443
#define FTP_PORT 21
#define SSH_PORT 22
#define TELNET_PORT 23
#define SMTP_PORT 25
#define DNS_PORT 53
#define DHCP_PORT 67

namespace cnet
{
    class uri
    {
    private:
        std::string host;
        std::string path = "/";
        std::string scheme = "http";
        std::string fragment; // after #
        unsigned int port = ~0;
        std::map<std::string, std::string> parameters;

    public:
        /**
         * @brief Default constructor for the uri class.
         *
         * This constructor initializes a uri object with default values for host, path, scheme, port, and fragment.
         */
        uri();

        /**
         * @brief Constructs a URI object from the given URL.
         *
         * This constructor initializes a URI object by parsing the given URL and extracting
         * the scheme, host, port, path, fragment, and parameters.
         *
         * @param url The URL string to construct the URI from.
         * @throws std::invalid_argument if the URL is not valid.
         */
        explicit uri(std::string url);


        /**
         * @brief Adds a parameter to the URI.
         *
         * This method adds a key-value parameter to the URI. The parameter will be included in the URI's query string.
         * If the parameter key already exists, the previous value will be replaced.
         *
         * @param key The key of the parameter. It should be a non-empty string.
         * @param value The value of the parameter. It can be any string.
         */
        void add_parameter(const std::string &key, const std::string &value);

        /**
         * @brief Adds a parameter to the URI.
         *
         * This method adds a key-value parameter pair to the URI's parameter list.
         *
         * @param key The key of the parameter.
         * @param value The value of the parameter.
         */
        void add_parameter(const std::string &key, int value);

        /**
         * @brief Adds a parameter to the URI object.
         *
         * This method adds a parameter to the URI object by inserting the key-value pair into the parameters map.
         *
         * @param key The key of the parameter to add.
         * @param value The value of the parameter to add.
         *
         * @note The key and value must both be of type std::string.
         *
         * @details The add_parameter method can be used to add a new parameter to the URI object. The key and value
         * arguments must both be of type std::string. The method inserts the key-value pair into the parameters map
         * of the URI object.
         *
         * Example usage:
         * @code
         * uri myUri("http://example.com");
         * myUri.add_parameter("param1", "value1");
         * @endcode
         *
         * @see uri::set_parameters
         */
        void add_parameter(const std::string &key, double value);

        /**
         * @brief Adds a parameter to the URI.
         *
         * This method adds a parameter to the URI by inserting a key-value pair into the parameters map.
         *
         * @param key The key of the parameter.
         * @param value The value of the parameter.
         */
        void add_parameter(const std::string &key, float value);

        /**
         * @brief Adds a boolean parameter to the URI.
         *
         * This method adds a boolean parameter to the URI by inserting a key-value pair into the parameters map.
         *
         * @param key The key of the parameter.
         * @param value The value of the parameter.
         */
        void add_parameter(const std::string &key, bool value);

        /**
         * Add a parameter to the URI.
         *
         * This method adds a parameter with the specified key and value to the URI's parameters.
         *
         * @param key The key of the parameter.
         * @param value The value of the parameter.
         */
        void add_parameter(const std::string &key, char value);

        /**
         * @brief Adds a parameter to the URI.
         *
         * This method adds a key-value parameter to the URI. The parameter is stored in the internal map of parameters.
         *
         * @param key The key of the parameter.
         * @param value The value of the parameter.
         */
        void add_parameter(const std::string &key, char *value);

        /**
         * \brief Adds a parameter to the URI.
         *
         * This method adds a parameter to the URI using the provided key-value pair.
         * The key must be a string, and the value can be either a string or a C-style
         * string.
         *
         * \param key The key of the parameter.
         * \param value The value of the parameter. Can be either a string or a C-style string.
         *
         * \note If the parameter with the same key already exists, its value will be overwritten.
         */
        void add_parameter(const std::string &key, const char *value);

        /**
         * @brief Adds a parameter to the URI.
         *
         * This method adds a parameter to the URI by inserting the key-value pair into the parameters map.
         *
         * @param key The key of the parameter.
         * @param value The value of the parameter.
         */
        void add_parameter(const std::string &key, long value);

        /**
         * Adds a parameter to the URI.
         *
         * @param key The key of the parameter.
         * @param value The value of the parameter.
         */
        void add_parameter(const std::string &key, long long value);

        /**
         * @brief Adds a parameter with an unsigned long value to the URI.
         *
         * @param key The key of the parameter.
         * @param value The unsigned long value of the parameter.
         */
        void add_parameter(const std::string &key, unsigned long value);

        /**
         * @brief Add a parameter to the URI.
         *
         * This function adds a parameter to the URI object. The parameter is added to the `parameters` map, with the key-value pair specified by the parameters of this function.
         *
         * @param key The key of the parameter to add.
         * @param value The value of the parameter to add. Only unsigned long long values are supported.
         */
        void add_parameter(const std::string &key, unsigned long long value);

        /**
         * @brief Adds a parameter with an unsigned int value to the URI.
         *
         * This method adds a parameter with an unsigned int value to the URI. The parameter is inserted into the parameters
         * map using the specified key. The unsigned int value is converted to a string using std::to_string before insertion.
         *
         * @param key   The key of the parameter.
         * @param value The value of the parameter as an unsigned int.
         */
        void add_parameter(const std::string &key, unsigned int value);

        /**
         * @brief Add a parameter to the URI object.
         *
         * This method adds a parameter to the URI object by inserting a key-value pair into the parameters map.
         *
         * @param key The key of the parameter.
         *
         * @param value The value of the parameter.
         *
         * @return void
         */
        void add_parameter(const std::string &key, unsigned short value);

        /**
         * @brief Adds a parameter with a short value to the URI.
         *
         * This function adds a parameter to the URI by inserting a key-value pair into the parameters map.
         * The key is of type std::string and the value is of type short.
         *
         * @param key The key of the parameter.
         * @param value The value of the parameter.
         */
        void add_parameter(const std::string &key, short value);

        /**
         * @brief Add a parameter to the URI object.
         *
         * This method adds a parameter to the URI object. The parameter consists of a key and a value.
         * The key is a string that represents the name of the parameter, and the value is an unsigned
         * char that represents the value of the parameter.
         *
         * @param key The name of the parameter.
         * @param value The value of the parameter.
         */
        void add_parameter(const std::string &key, unsigned char value);

        /**
         * @brief Adds a parameter to the URI.
         *
         * @param key The key of the parameter.
         * @param value The value of the parameter (signed char).
         */
        void add_parameter(const std::string &key, signed char value);

        /**
         * @brief Sets the port of the URI.
         *
         * This function sets the port of the URI object to the specified value.
         *
         * @param port The port number to set for the URI.
         *
         * @return void
         */
        void set_port(int port);

        /**
         * Sets the scheme of the URI.
         *
         * @param scheme The scheme to set.
         */
        void set_scheme(std::string scheme);

        /**
         * Sets the host of the URI.
         *
         * @param host The host to set.
         */
        void set_host(std::string host);

        /**
         * @brief Sets the path of the URL.
         *
         * This method sets the path of the URL represented by the `uri` class object.
         *
         * @param path The new path to be set.
         *
         * @return None.
         */
        void set_path(std::string path);

        /**
         * Sets the fragment of the URI.
         *
         * @param fragment The fragment string to set.
         */
        void set_fragment(std::string fragment);

        /**
         * @brief Sets the parameters of the URI.
         *
         * This method allows you to set the parameters of the URI by providing a map
         * of key-value pairs. The existing parameters will be replaced with the new ones.
         *
         * @param parameters The parameters to set. The keys and values should be of type std::string.
         */
        void set_parameters(std::map<std::string, std::string> parameters);

        /**
         * Returns the host component of the URI.
         *
         * @return The host component of the URI as a string.
         */
        std::string get_host();

        /**
         * @brief Get the path component of the URI.
         *
         * The path component of a URI is the part after the hostname and before any query parameters or fragment identifier.
         *
         * @return The path component of the URI.
         */
        std::string get_path();

        /**
         * Returns the scheme of the URI.
         *
         * @return The scheme of the URI.
         */
        std::string get_scheme();

        /**
         * Returns the port number of the URI.
         *
         * @return The port number.
         */
        [[nodiscard]] unsigned int get_port() const;

        /**
         * Get the fragment of the URI.
         *
         * The fragment is the part of the URI that appears after the '#' character.
         * If no fragment is present, an empty string is returned.
         *
         * @return The fragment of the URI.
         */
        std::string get_fragment();

        /**
         * Get the parameters of the URI.
         *
         * @return A map containing the parameters of the URI.
         */
        std::map<std::string, std::string> get_parameters();

        /**
         * @brief Retrieves the parameter query string for the uri object.
         *
         * This method constructs a parameter query string by concatenating the key-value pairs from the parameters map.
         * The keys are separated from the values by an equal sign (=), and each key-value pair is separated by an ampersand (&).
         * The order of the parameters in the query string is reversed compared to the order in the parameters map.
         * If the parameters map is empty, an empty string is returned.
         *
         * @return The parameter query string for the uri object.
         */
        std::string get_parameter_query();

        /**
         * @brief Clear all parameters in the URI object.
         *
         * This method clears all parameters in the URI object. It removes all key-value pairs from the parameters container.
         * After this method is called, the URI object will not have any parameters.
         */
        void clear_parameters();

        /**
         * Convert the URI object to a string representation.
         *
         * The resulting string is in the format: {scheme}://{host}:{port}{path}?{parameters}#{fragment}.
         * If the default value of any component (e.g., scheme, port, path, etc.) is used, it will not be included in the string.
         *
         * @return The URI as a string.
         */
        std::string to_string();

        /**
         * @brief Validates a URL.
         *
         * This method checks if a given URL is valid. The URL must have a scheme
         * followed by a colon and a path. The scheme must contain at least one
         * character and can only consist of alphanumeric characters, plus (+),
         * minus (-), and dot (.) characters. The path must not be empty.
         *
         * @param uri The URL to validate.
         * @return Returns true if the URL is valid, false otherwise.
         */
        static bool validate_url(const std::string &uri);

        /**
         * @brief Tries to create a URI object from the given URL string.
         *
         * This method attempts to create a URI object by parsing the given URL string and extracting
         * the scheme, host, port, path, fragment, and parameters. If the URL is valid, the constructed
         * URI object is stored in the 'result' parameter.
         *
         * @param url The URL string to create the URI from.
         * @param result The URI object where the constructed URI is stored if the URL is valid.
         * @return true if the URI object was created successfully, false otherwise.
         */
        static bool try_create(const std::string &url, uri &result);
    };
}


#endif //URI_H

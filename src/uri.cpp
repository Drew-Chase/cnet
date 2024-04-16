//
// Created by drew.chase on 4/10/2024.
//

#include <utility>

#include "../includes/uri.h"

#include <stdexcept>
#include <windows.h>

namespace cnet
{
    uri::uri(std::string url)
    {
        if (!validate_url(url))
        {
            throw std::invalid_argument("Invalid URL");
        }
        std::string temp = std::move(url);
        if (temp.find("://") != std::string::npos)
        {
            scheme = temp.substr(0, temp.find("://"));
            temp = temp.substr(temp.find("://") + 3);
        }
        if (temp.find(':') != std::string::npos)
        {
            host = temp.substr(0, temp.find(':'));
            temp = temp.substr(temp.find(':') + 1);
            port = std::stoi(temp.substr(0, temp.find('/')));
            temp = temp.substr(temp.find('/') + 1);
        } else
        {
            host = temp.substr(0, temp.find('/'));
            temp = temp.substr(temp.find('/') + 1);
        }

        if (port == ~0)
        {
            if (scheme == "https")
            {
                port = HTTPS_PORT;
            } else if (scheme == "ftp")
            {
                port = FTP_PORT;
            } else if (scheme == "ssh")
            {
                port = SSH_PORT;
            } else if (scheme == "telnet")
            {
                port = TELNET_PORT;
            } else if (scheme == "smtp")
            {
                port = SMTP_PORT;
            } else if (scheme == "dns")
            {
                port = DNS_PORT;
            } else if (scheme == "dhcp")
            {
                port = DHCP_PORT;
            } else
            {
                // "http" or default
                port = HTTP_PORT;
            }
        } else if (port < MIN_PORT || port > MAX_PORT)
        {
            throw std::invalid_argument("Invalid port number");
        }

        if (temp.find('?') != std::string::npos)
        {
            path = temp.substr(0, temp.find('?'));
            temp = temp.substr(temp.find('?') + 1);
            while (temp.find('&') != std::string::npos)
            {
                std::string key = temp.substr(0, temp.find('='));
                temp = temp.substr(temp.find('=') + 1);
                std::string value = temp.substr(0, temp.find('&'));

                if (value.find('#') != std::string::npos) // remove fragment
                    value = value.substr(0, value.find('#'));

                temp = temp.substr(temp.find('&') + 1);
                parameters.insert(std::pair<std::string, std::string>(key, value));
            }
            std::string key = temp.substr(0, temp.find('='));
            temp = temp.substr(temp.find('=') + 1);
            std::string value = temp;
            if (value.find('#') != std::string::npos) // remove fragment
                value = value.substr(0, value.find('#'));
            parameters.insert(std::pair(key, value));
        } else
        {
            path = temp;
        }
        if (path.find('#') != std::string::npos)
        {
            fragment = path.substr(path.find('#') + 1);
            path = path.substr(0, path.find('#'));
        }

        if (path[0] != '/')
        {
            path = "/" + path;
        }
    }

    uri::uri()
    {
        host = "";
        path = "";
        scheme = "";
        port = 80;
        fragment = "";
    }

    void uri::add_parameter(const std::string &key, const std::string &value)
    {
        if (value.find('#') != std::string::npos)
        {
            this->parameters.insert(std::pair(key, value.substr(0, value.find('#'))));
        } else
        {
            this->parameters.insert(std::pair(key, value));
        }
    }

    void uri::add_parameter(const std::string &key, const int value)
    {
        add_parameter(key, std::to_string(value));
    }

    void uri::add_parameter(const std::string &key, const double value)
    {
        add_parameter(key, std::to_string(value));
    }

    void uri::add_parameter(const std::string &key, const float value)
    {
        add_parameter(key, std::to_string(value));
    }

    void uri::add_parameter(const std::string &key, const bool value)
    {
        add_parameter(key, value ? "true" : "false");
    }

    void uri::add_parameter(const std::string &key, const char value)
    {
        add_parameter(key, std::to_string(value));
    }

    void uri::add_parameter(const std::string &key, char *value)
    {
        add_parameter(key, std::string(value));
    }

    void uri::add_parameter(const std::string &key, const char *value)
    {
        add_parameter(key, std::string(value));
    }

    void uri::add_parameter(const std::string &key, const long value)
    {
        add_parameter(key, std::to_string(value));
    }

    void uri::add_parameter(const std::string &key, const long long value)
    {
        add_parameter(key, std::to_string(value));
    }

    void uri::add_parameter(const std::string &key, const unsigned long value)
    {
        add_parameter(key, std::to_string(value));
    }

    void uri::add_parameter(const std::string &key, const unsigned long long value)
    {
        add_parameter(key, std::to_string(value));
    }

    void uri::add_parameter(const std::string &key, const unsigned int value)
    {
        add_parameter(key, std::to_string(value));
    }

    void uri::add_parameter(const std::string &key, const unsigned short value)
    {
        add_parameter(key, std::to_string(value));
    }

    void uri::add_parameter(const std::string &key, const short value)
    {
        add_parameter(key, std::to_string(value));
    }

    void uri::add_parameter(const std::string &key, const unsigned char value)
    {
        add_parameter(key, std::to_string(value));
    }

    void uri::add_parameter(const std::string &key, const signed char value)
    {
        add_parameter(key, std::to_string(value));
    }

    void uri::set_port(const int port)
    {
        if (port < MIN_PORT || port > MAX_PORT)
        {
            throw std::invalid_argument("Invalid port number");
        }
        this->port = port;
    }

    void uri::set_scheme(std::string scheme)
    {
        this->scheme = std::move(scheme);
    }

    void uri::set_host(std::string host)
    {
        this->host = std::move(host);
    }

    void uri::set_path(std::string path)
    {
        this->path = std::move(path);
    }

    void uri::set_fragment(std::string fragment)
    {
        this->fragment = std::move(fragment);
    }


    void uri::set_parameters(std::map<std::string, std::string> parameters)
    {
        this->parameters = std::move(parameters);
    }

    std::string uri::get_host()
    {
        return host;
    }

    std::string uri::get_path()
    {
        return path;
    }

    std::string uri::get_scheme()
    {
        return scheme;
    }

    int uri::get_port() const
    {
        return port;
    }

    std::string uri::get_fragment()
    {
        return fragment;
    }

    std::map<std::string, std::string> uri::get_parameters()
    {
        return parameters;
    }

    std::string uri::get_parameter_query()
    {
        if (!parameters.empty())
        {
            std::string query;
            query += "?";
            for (auto it = parameters.rbegin(); it != parameters.rend(); ++it) // reverse the order of the parameters.
            {
                query += it->first + "=";
                query += it->second + "&";
            }
            query.pop_back();
            return query;
        }
        return "";
    }

    void uri::clear_parameters()
    {
        parameters.clear();
    }

    std::string uri::to_string()
    {
        std::string url = scheme + "://" + host;
        if (port != 80)
        {
            url += ":" + std::to_string(port);
        } else
        {
            url += host;
        }
        url += path;
        url += get_parameter_query();
        if (!fragment.empty())
        {
            url += "#" + fragment;
        }


        return url;
    }

    bool uri::validate_url(const std::string &uri)
    {
        const size_t colon_pos = uri.find(':');

        // A valid URI should have a colon (to separate the scheme and the rest of the URI)
        if (colon_pos == std::string::npos)
        {
            return false;
        }

        // Scheme must have at least one character before the colon
        std::string scheme = uri.substr(0, colon_pos);
        if (scheme.empty())
        {
            return false;
        }

        // check each character of scheme, it should contain only alphanumeric and + or - or .
        for (const char &c: scheme)
        {
            if (!(isalnum(c) || c == '+' || c == '-' || c == '.'))
            {
                return false;
            }
        }

        // The path (the sequence of characters from the colon to the first ? or # or the end of the string) must not be an empty string
        if (const std::string path = uri.substr(colon_pos + 1); path.empty())
        {
            return false;
        }

        // check the port number
        if (const size_t port_pos = uri.find(':', colon_pos + 1); port_pos != std::string::npos)
        {
            const std::string port = uri.substr(port_pos + 1);
            if (port.empty())
            {
                return false;
            }
            for (const char &c: port)
            {
                if (!isdigit(c))
                {
                    return false;
                }
            }
            if (const int port_number = std::stoi(uri.substr(port_pos + 1)); port_number < MIN_PORT || port_number > MAX_PORT)
            {
                return false;
            }
        }

        // If there are valid scheme and path, then it's a valid URI
        return true;
    }

    bool uri::try_create(const std::string &url, uri &result)
    {
        if (validate_url(url))
        {
            result = uri(url);
            return true;
        }
        return false;
    }
}

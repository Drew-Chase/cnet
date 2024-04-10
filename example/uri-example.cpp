//
// Created by drew.chase on 4/10/2024.
//
#include "uri.h"

static void test_uri()
{
    // Check if a url string is a valid uri.
    const bool is_valid = uri::validate_url("google.com");
    printf("Is Valid: %s\n", is_valid ? "true" : "false");

    // Create a uri object
    uri url("https://www.google.com:80/search?q=uri#super_cool_news"); // This will throw an exception if the url is invalid

    // Safely create a uri object
    uri safe;
    if (uri::try_create("https://www.google.com:80/search?q=uri#fragment", safe))
    {
        // Do something with the uri object
    }

    // set the port
    url.set_port(8080);
    // get the port
    const int port = url.get_port();

    // set the host
    url.set_host("www.example.com");
    // get the host
    const std::string host = url.get_host();

    // set the path
    url.set_path("/search");
    // get the path
    const std::string path = url.get_path();

    //set the scheme
    url.set_scheme("http");
    // get the scheme
    const std::string scheme = url.get_scheme();

    // set the fragement
    url.set_fragment("fragment"); // this is the part of the url after the #
    // get the fragment
    const std::string fragment = url.get_fragment();

    // clear existing parameters
    url.clear_parameters();
    // set a parameter
    url.add_parameter("query", "uri"); // this will add ?query=uri to the url
    url.add_parameter("other", false); // this will add &other=false to the url
    url.add_parameter("number", 5); // this will add &number=5 to the url
    // get a parameter
    const std::map<std::string, std::string> parameters = url.get_parameters();

    // convert a uri object to a string
    const std::string url_string = url.to_string();
    printf("URL: %s\n", url_string.c_str());
}

//
// Created by drew_ on 4/15/2024.
//


#include <cstdio>

#include "http_client.h"
#include "ANSIConsoleColors/ANSIConsoleColors.h"
#include "cclip/cclip.hpp"
#include "uri.h"
using namespace colors;

int main(const int argc, char *argv[])
{
    cclip::options_manager options_manager("cnet (C++ Networking Library)");
    options_manager.add_option("h", "help", "Prints this message", false, false);
    options_manager.add_option("u", "url", "Sets the url of the interaction", false, true);
    options_manager.add_option("vd", "validate", "Validates the inputted fields", false, false);
    options_manager.add_option("o", "output", "Sets the output file", false, true);
    options_manager.add_option("i", "input", "Sets the input url list", false, true);
    options_manager.add_option("c", "continue", "To allow the download to be continued if it was stopped", false, false);
    options_manager.add_option("s", "silent", "Silences the output", false, false);
    options_manager.add_option("v", "verbose", "Enables verbose output", false, false);
    options_manager.add_option("m", "method", "Sets the method of the request, (GET, POST, HEAD, etc)", false, true);
    options_manager.add_option("b", "body", "Sets the body of the request", false, true);
    options_manager.add_option("hd", "header", R"(Sets the header of the request in a json format. Ex {Accept: "application/json", Content-Type: "application/json"})", false, true);
    options_manager.add_option("a", "preallocate", "Preallocates the file size before downloading", false, false);
    options_manager.add_option("r", "retry", "Sets the number of times to retry the download", false, true);
    options_manager.add_option("m", "max-retires", "Sets the maximum number of retries", false, true);
    options_manager.add_option("mt", "max-threads", "Sets the maximum number of threads to use", false, true);
    options_manager.add_option("im", "in-memory", "Downloads the file in memory first.", false, false);
    options_manager.add_option("t", "timeout", "Sets the timeout of the request", false, true);
    options_manager.add_option("p", "parts", "Sets the number of parts to download the file in, this can increase the speed of the download", false, true);
    options_manager.add_option("f", "force", "Forces the download to start even if the file already exists", false, false);

    options_manager.parse(argc, argv);

    if (options_manager.is_present("h"))
    {
        options_manager.print_help();
        return 0;
    }

    if (options_manager.is_present("vd"))
    {
        if (options_manager.is_present("u"))
        {
            const auto url = options_manager.get_option("u")->argument;
            if (cnet::uri uri; cnet::uri::try_create(url, uri))
            {
                printf("%sURI is VALID:%s %s\n", ConsoleColors::GetColorCode(ColorCodes::Green).c_str(), ConsoleColors::GetColorCode(ColorCodes::Yellow).c_str(), url);
            } else
            {
                printf("%sURI is INVALID:%s %s\n", ConsoleColors::GetColorCode(ColorCodes::Red).c_str(), ConsoleColors::GetColorCode(ColorCodes::Yellow).c_str(), url);
            }
            ConsoleColors::ResetConsoleColor();
        }

        return 0;
    }

    const char *method = options_manager.is_present("m") ? options_manager.get_option("m")->argument : nullptr;
    const char *body = options_manager.is_present("b") ? options_manager.get_option("b")->argument : nullptr;
    const char *header = options_manager.is_present("hd") ? options_manager.get_option("hd")->argument : nullptr;
    if (options_manager.is_present("u"))
    {
        if (options_manager.is_present("i"))
        {
            fprintf(stderr, "%s-i and -u cannot be used together, the input file will be ignored.%s\n", ConsoleColors::GetColorCode(ColorCodes::Red).c_str(), ConsoleColors::GetColorCode(ColorCodes::Default).c_str());
        }
        cnet::http_client client;
        cnet::http_message message(options_manager.get_option("u")->argument);
        if (method != nullptr)
        {
            try
            {
                message.method = cnet::strto_http_method(method);
            } catch (std::runtime_error &e)
            {
                fprintf(stderr, "%s%s%s\n", ConsoleColors::GetColorCode(ColorCodes::Red).c_str(), e.what(), ConsoleColors::GetColorCode(ColorCodes::Default).c_str());
                return 1;
            }
        }
        client.make_request(message);
        printf(message.body.c_str());
    }
}

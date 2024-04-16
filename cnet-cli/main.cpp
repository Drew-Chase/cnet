//
// Created by drew_ on 4/15/2024.
//


#include <cstdio>
#include "cclip.hpp"
#include "uri.h"

int main(const int argc, char *argv[])
{
    printf("Hello world");
    cclip::options_manager options_manager("cnet (C++ Networking Library)");
    options_manager.add_option("h", "help", "Prints this message", false, false);
    options_manager.add_option("u", "url", "Sets the url of the interaction", false, true);
    options_manager.add_option("vd", "validate", "Validates the inputted fields", false, false);

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
                printf("✅ URI is valid: %s", uri.to_string().c_str());
            } else
            {
                printf("❌ URI is invalid: %s", url);
            }
        }
    }


    return 0;
}

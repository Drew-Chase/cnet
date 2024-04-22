//
// Created by drew_ on 4/15/2024.
//


#include <cstdio>
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
    }
}

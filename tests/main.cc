// (C) 2013 Sebastian Mach (1983), this file is published under the terms of the
// GNU General Public License, Version 3 (a.k.a. GPLv3).
// See COPYING in the root-folder of the excygen project folder.

#include <iostream>

#define CATCH_CONFIG_RUNNER
#include "catch.hpp"
#include <limits>

int main(int argc, char *argv[]) {
    std::cout << "IMPORTANT: The units test assume IEEE 754 floating point conformance.\n"
                 "           Some tests, esp. NaN and Infinity checks, may and will fail\n"
                 "           with non-conforming floating point optimizations, e.g. g++'\n"
                 "           '-ffast-math', enabled.\n";

    if (!std::numeric_limits<float>::is_iec559 || !std::numeric_limits<double>::is_iec559) {
        std::cout << "WARNING: 'float' or 'double' are not IEEE 754. Some tests may fail or "
                     "are left out completely. You are probably still able to use the library\n";
    }
    // see also https://github.com/philsquared/Catch/blob/master/docs/own-main.md
    return Catch::Session().run(argc, argv);
}

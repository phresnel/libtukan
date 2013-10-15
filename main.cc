#define CATCH_CONFIG_RUNNER
#include "catch.hpp"

namespace gaudy
{

}



int unit_tests(int argc, char *argv[]) {
    // see also https://github.com/philsquared/Catch/blob/master/docs/own-main.md
    return Catch::Session().run(argc, argv);
}

int main(int argc, char *argv[]) {
    if (argc >= 2 && argv[1]==std::string("test")) {
        // Short circuit the CLI arguments.
        argc -= 2;
        argv += 2;
        std::vector<std::string> args;
        args.push_back("gaudy test");
        while (*argv != 0) {
            args.push_back(*argv);
            ++argv;
        }
        std::vector<char*> args_c_str;
        for (auto &s : args)
            args_c_str.emplace_back(const_cast<char*>(s.c_str()));
        return unit_tests(args_c_str.size(), &args_c_str[0]);
    }
}

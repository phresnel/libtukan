// (C) 2013 Sebastian Mach (1983), this file is published under the terms of the
// GNU General Public License, Version 3 (a.k.a. GPLv3).
// See COPYING in the root-folder of the excygen project folder.


#include "gaudy/Nanometer.hh"
#include "gaudy/Interval.hh"
#include "gaudy/rel_equal.hh"
#include "gaudy/Spectrum.hh"

#include <vector>
#include <valarray>
#include <iostream>
#include <stdexcept>


namespace gaudy {

    inline
    std::ostream& operator<< (std::ostream &os, Nanometer const &nm) {
        return os << static_cast<float>(nm) << "nm";
    }

    inline
    std::ostream& operator<< (std::ostream &os, SpectrumSample const &ss) {
        return os << ss.wavelength << ":" << ss.amplitude;
    }

    inline
    std::ostream& operator<< (std::ostream &os, Spectrum const &spec) {
        os << "spectrum{" << spec.lambda_min() << ".." << spec.lambda_max() << ", [";
        if (!spec.empty())
            os << spec[0];
        for (size_t i=1; i!=spec.size(); ++i)
            os << ", " << spec[i];
        return os << "]}";
    }
}


#define CATCH_CONFIG_RUNNER
#include "catch.hpp"

int main(int argc, char *argv[]) {
    // see also https://github.com/philsquared/Catch/blob/master/docs/own-main.md
    return Catch::Session().run(argc, argv);
}

// (C) 2013 Sebastian Mach (1983), this file is published under the terms of the
// GNU General Public License, Version 3 (a.k.a. GPLv3).
// See COPYING in the root-folder of the excygen project folder.

#include "tukan/gammas.hh"
#include "tukan/algorithm/rel_equal.hh"
#include "catch.hpp"

TEST_CASE("tukan/gammas", "gamma correction tests") {

    using tukan::rel_equal;

    SECTION("gamma 1.0") {
        // Values from Bruce Lindblooms companding calculator:
        // * http://www.brucelindbloom.com/CompandCalculator.html
        auto g = tukan::gamma::_1_0;
        REQUIRE(g.to_nonlinear(0.1)   == rel_equal(0.100, tukan::epsilon, 0.0002));
        REQUIRE(g.to_nonlinear(0.25)  == rel_equal(0.250, tukan::epsilon, 0.0002));
        REQUIRE(g.to_nonlinear(0.5)   == rel_equal(0.500, tukan::epsilon, 0.0002));
        REQUIRE(g.to_nonlinear(0.75)  == rel_equal(0.750, tukan::epsilon, 0.0002));
        REQUIRE(g.to_nonlinear(1.0)   == rel_equal(1.000, tukan::epsilon, 0.0002));

        REQUIRE(g.to_linear(0.100) == rel_equal(0.1, tukan::epsilon, 0.0002));
        REQUIRE(g.to_linear(0.250) == rel_equal(0.25, tukan::epsilon, 0.0002));
        REQUIRE(g.to_linear(0.500) == rel_equal(0.5, tukan::epsilon, 0.0002));
        REQUIRE(g.to_linear(0.750) == rel_equal(0.75, tukan::epsilon, 0.0002));
        REQUIRE(g.to_linear(1.000) == rel_equal(1.0, tukan::epsilon, 0.0002));
    }

    SECTION("gamma 1.8") {
        // Values from Bruce Lindblooms companding calculator:
        // * http://www.brucelindbloom.com/CompandCalculator.html
        auto g = tukan::gamma::_1_8;
        REQUIRE(g.to_nonlinear(0.1)   == rel_equal(0.2783, tukan::epsilon, 0.0002));
        REQUIRE(g.to_nonlinear(0.25)  == rel_equal(0.4629, tukan::epsilon, 0.0002));
        REQUIRE(g.to_nonlinear(0.5)   == rel_equal(0.6804, tukan::epsilon, 0.0002));
        REQUIRE(g.to_nonlinear(0.75)  == rel_equal(0.8523, tukan::epsilon, 0.0002));
        REQUIRE(g.to_nonlinear(1.0)   == rel_equal(1.0000, tukan::epsilon, 0.0002));

        REQUIRE(g.to_linear(0.2783) == rel_equal(0.1, tukan::epsilon, 0.0004));
        REQUIRE(g.to_linear(0.4629) == rel_equal(0.25, tukan::epsilon, 0.0002));
        REQUIRE(g.to_linear(0.6804) == rel_equal(0.5, tukan::epsilon, 0.0002));
        REQUIRE(g.to_linear(0.8523) == rel_equal(0.75, tukan::epsilon, 0.0002));
        REQUIRE(g.to_linear(1.0000) == rel_equal(1.0, tukan::epsilon, 0.0002));
    }

    SECTION("gamma 2.2") {
        // Values from Bruce Lindblooms companding calculator:
        // * http://www.brucelindbloom.com/CompandCalculator.html
        auto g = tukan::gamma::_2_2;
        REQUIRE(g.to_nonlinear(0.1)   == rel_equal(0.3511, tukan::epsilon, 0.0002));
        REQUIRE(g.to_nonlinear(0.25)  == rel_equal(0.5325, tukan::epsilon, 0.0002));
        REQUIRE(g.to_nonlinear(0.5)   == rel_equal(0.7297, tukan::epsilon, 0.0002));
        REQUIRE(g.to_nonlinear(0.75)  == rel_equal(0.8774, tukan::epsilon, 0.0002));
        REQUIRE(g.to_nonlinear(1.0)   == rel_equal(1.0000, tukan::epsilon, 0.0002));

        REQUIRE(g.to_linear(0.3511) == rel_equal(0.1, tukan::epsilon, 0.0002));
        REQUIRE(g.to_linear(0.5325) == rel_equal(0.25, tukan::epsilon, 0.0002));
        REQUIRE(g.to_linear(0.7297) == rel_equal(0.5, tukan::epsilon, 0.0002));
        REQUIRE(g.to_linear(0.8774) == rel_equal(0.75, tukan::epsilon, 0.0002));
        REQUIRE(g.to_linear(1.0000) == rel_equal(1.0, tukan::epsilon, 0.0002));
    }

    SECTION("sRGB gamma") {
        // Using http://www.brucelindbloom.com/ColorCalculator.html (*)
        // ((*) trick is to first convert a linear RGB into XYZ, and the latter then back to
        //      non-linear RGB)
        auto g = tukan::gamma::sRGB;
        REQUIRE(g.to_nonlinear(0.002)     == rel_equal(0.025856, tukan::epsilon, 0.0008));
        REQUIRE(g.to_nonlinear(0.0031307) == rel_equal(0.040441, tukan::epsilon, 0.0002));
        REQUIRE(g.to_nonlinear(0.0031308) == rel_equal(0.040454, tukan::epsilon, 0.0002)); // breakpoint
        REQUIRE(g.to_nonlinear(0.004)     == rel_equal(0.050712, tukan::epsilon, 0.0002));

        REQUIRE(g.to_nonlinear(0.1)   == rel_equal(0.349190, tukan::epsilon, 0.0002));
        REQUIRE(g.to_nonlinear(0.25)  == rel_equal(0.537099, tukan::epsilon, 0.0002));
        REQUIRE(g.to_nonlinear(0.5)   == rel_equal(0.735356, tukan::epsilon, 0.0002));
        REQUIRE(g.to_nonlinear(0.75)  == rel_equal(0.880825, tukan::epsilon, 0.0002));
        REQUIRE(g.to_nonlinear(1.0)   == rel_equal(1.000000, tukan::epsilon, 0.0002));

        REQUIRE(g.to_linear(0.025856) == rel_equal(0.002, tukan::epsilon, 0.0008));
        REQUIRE(g.to_linear(0.040441) == rel_equal(0.0031307, tukan::epsilon, 0.0002));
        REQUIRE(g.to_linear(0.040454) == rel_equal(0.0031308, tukan::epsilon, 0.0002));
        REQUIRE(g.to_linear(0.050712) == rel_equal(0.004, tukan::epsilon, 0.0002));

        REQUIRE(g.to_linear(0.349190) == rel_equal(0.1, tukan::epsilon, 0.0002));
        REQUIRE(g.to_linear(0.537099) == rel_equal(0.25, tukan::epsilon, 0.0002));
        REQUIRE(g.to_linear(0.735356) == rel_equal(0.5, tukan::epsilon, 0.0002));
        REQUIRE(g.to_linear(0.880825) == rel_equal(0.75, tukan::epsilon, 0.0002));
        REQUIRE(g.to_linear(1.000000) == rel_equal(1.0, tukan::epsilon, 0.0002));
    }

    SECTION("L* gamma") {
        // Using http://www.brucelindbloom.com/ColorCalculator.html (*)
        // ((*) trick is to first convert a linear RGB into XYZ, and the latter then back to
        //      non-linear RGB)
        auto g = tukan::gamma::L;

        REQUIRE(g.to_nonlinear(0.000109) == rel_equal(0.001, tukan::epsilon, 0.001));
        REQUIRE(g.to_nonlinear(0.007750) == rel_equal(0.07, tukan::epsilon, 0.0002));
        REQUIRE(g.to_nonlinear(0.008856) == rel_equal(0.08, tukan::epsilon, 0.0002)); // breakpoint
        REQUIRE(g.to_nonlinear(0.010010) == rel_equal(0.09, tukan::epsilon, 0.0002));

        REQUIRE(g.to_nonlinear(0.1)  == rel_equal(0.378423, tukan::epsilon, 0.0002));
        REQUIRE(g.to_nonlinear(0.25) == rel_equal(0.570755, tukan::epsilon, 0.0002));
        REQUIRE(g.to_nonlinear(0.5)  == rel_equal(0.760692, tukan::epsilon, 0.0002));
        REQUIRE(g.to_nonlinear(0.75) == rel_equal(0.893930, tukan::epsilon, 0.0002));
        REQUIRE(g.to_nonlinear(1.0)  == rel_equal(1.000000, tukan::epsilon, 0.0002));


        REQUIRE(g.to_linear(0.001) == rel_equal(0.000109, tukan::epsilon, 0.0002));
        REQUIRE(g.to_linear(0.07)  == rel_equal(0.007750, tukan::epsilon, 0.0002));
        REQUIRE(g.to_linear(0.08)  == rel_equal(0.008856, tukan::epsilon, 0.0002)); // breakpoint
        REQUIRE(g.to_linear(0.09)  == rel_equal(0.010010, tukan::epsilon, 0.0002));

        REQUIRE(g.to_linear(0.378423) == rel_equal(0.1, tukan::epsilon, 0.0002));
        REQUIRE(g.to_linear(0.570755) == rel_equal(0.25, tukan::epsilon, 0.0002));
        REQUIRE(g.to_linear(0.760692) == rel_equal(0.5, tukan::epsilon, 0.0002));
        REQUIRE(g.to_linear(0.893930) == rel_equal(0.75, tukan::epsilon, 0.0002));
        REQUIRE(g.to_linear(1.000000) == rel_equal(1.0, tukan::epsilon, 0.0002));
    }
}

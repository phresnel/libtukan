// (C) 2013 Sebastian Mach (1983), this file is published under the terms of the
// GNU General Public License, Version 3 (a.k.a. GPLv3).
// See COPYING in the root-folder of the excygen project folder.

#include "gaudy/Spectrum.hh"
#include "catch.hpp"

bool is_nan_or_infinity (float f) {
    return (f != f) || (f==1.0f/0.0f) || (f==-1.0f/0.0f);
}

TEST_CASE("gaudy/Spectrum", "Spectrum Tests")
{
    using namespace gaudy;

    auto spec = Spectrum(400_nm, 800_nm, std::vector<float>({1, 2}));

    REQUIRE(400_nm == spec.lambda_min());
    REQUIRE(800_nm == spec.lambda_max());

    REQUIRE_FALSE(spec.empty());
    REQUIRE(spec.size() == 2);

    REQUIRE_THROWS(spec.at(-1));
    REQUIRE_NOTHROW(spec.at(0));
    REQUIRE_NOTHROW(spec.at(1));
    REQUIRE_THROWS(spec.at(2));
    REQUIRE_THROWS(spec.at(3));

    REQUIRE_NOTHROW(spec(0));
    REQUIRE_NOTHROW(spec(1));
    REQUIRE_THROWS(spec(1.01));
    REQUIRE_THROWS(spec(-0.01));
    REQUIRE_THROWS(spec(1.01));

    REQUIRE_NOTHROW(spec(400_nm));
    REQUIRE_NOTHROW(spec(400.1_nm));
    REQUIRE_NOTHROW(spec(800_nm));
    REQUIRE_THROWS(spec(399.9_nm));
    REQUIRE_THROWS(spec(800.1_nm));
    REQUIRE_THROWS(spec(-1_nm));

    REQUIRE_NOTHROW(spec(Interval<float>(0,1)));
    REQUIRE_NOTHROW(spec(Interval<float>(0,0)));
    REQUIRE_NOTHROW(spec(Interval<float>(1,1)));
    REQUIRE_THROWS(spec(Interval<float>(-0.001,1)));
    REQUIRE_THROWS(spec(Interval<float>(-2,-1)));
    REQUIRE_THROWS(spec(Interval<float>(1,2)));

    REQUIRE(spec[0] == SpectrumSample(400_nm, 1.0f));
    REQUIRE(spec[1] == SpectrumSample(800_nm, 2.0f));

    REQUIRE(spec(0)     == SpectrumSample(400_nm,   1.0f));
    REQUIRE(spec(0.25)  == SpectrumSample(500_nm,   1.25f));
    REQUIRE(spec(0.5)   == SpectrumSample(600_nm,   1.5f));
    REQUIRE(spec(0.75)  == SpectrumSample(700_nm,   1.75f));
    REQUIRE(rel_equal (spec(0.999), SpectrumSample(799.6_nm, 1.999f)));
    REQUIRE(spec(1)     == SpectrumSample(800_nm,   2.0f));

    REQUIRE(spec(400_nm)   == SpectrumSample(400_nm,   1.0f));
    REQUIRE(spec(500_nm)   == SpectrumSample(500_nm,   1.25f));
    REQUIRE(spec(600_nm)   == SpectrumSample(600_nm,   1.5f));
    REQUIRE(spec(700_nm)   == SpectrumSample(700_nm,   1.75f));
    REQUIRE(spec(799.6_nm) == SpectrumSample(799.6_nm, 1.999f));
    REQUIRE(spec(800_nm)   == SpectrumSample(800_nm,   2.0f));

    REQUIRE(spec(Interval<float>(0,1)) == SpectrumSample(600_nm, 1.5f));
    REQUIRE(spec(Interval<float>(0.5,1)) == SpectrumSample(700_nm, 1.75f));
    REQUIRE(spec(Interval<float>(0.75,1)) == SpectrumSample(750_nm, 1.875f));


    spec = Spectrum(400_nm, 800_nm, std::vector<float>({1, 2, 9}));
    REQUIRE_FALSE(is_nan_or_infinity(spec(Interval<float>(0, 0.001)).amplitude));
    REQUIRE_FALSE(is_nan_or_infinity(spec(Interval<float>(0, 0)).amplitude));
    REQUIRE_FALSE(is_nan_or_infinity(spec(Interval<float>(0.2, 0.2)).amplitude));
    REQUIRE_FALSE(is_nan_or_infinity(spec(Interval<float>(1, 1)).amplitude));

    REQUIRE(spec(0)    == SpectrumSample(400_nm, 1));
    REQUIRE(spec(0.25) == SpectrumSample(500_nm, 1.5));
    REQUIRE(spec(0.5)  == SpectrumSample(600_nm, 2));
    REQUIRE(spec(0.75) == SpectrumSample(700_nm, 5.5));
    REQUIRE(spec(1)    == SpectrumSample(800_nm, 9));

    REQUIRE(spec(400_nm) == SpectrumSample(400_nm, 1));
    REQUIRE(spec(600_nm) == SpectrumSample(600_nm, 2));
    REQUIRE(spec(800_nm) == SpectrumSample(800_nm, 9));

    REQUIRE(spec(Interval<float>(0   , 0   )) == SpectrumSample(400_nm, 1  ));
    REQUIRE(spec(Interval<float>(0   , 0.5 )) == SpectrumSample(500_nm, 1.5));
    REQUIRE(rel_equal(spec(Interval<float>(0   , 1  )), SpectrumSample(600_nm, 3.5)));
    REQUIRE(spec(Interval<float>(0.5 , 1   )) == SpectrumSample(700_nm, 5.5));
    REQUIRE(spec(Interval<float>(0.75, 1   )) == SpectrumSample(750_nm, 7.25));
    REQUIRE(spec(Interval<float>(1   , 1   )) == SpectrumSample(800_nm, 9  ));
    REQUIRE(spec(Interval<float>(0   , 0.25)) == SpectrumSample(450_nm, 1.25));
    REQUIRE(spec(Interval<float>(0.25, 1   )) == SpectrumSample(650_nm, 4.25));

    spec = Spectrum(400_nm, 800_nm, std::vector<float>({1, 2, 9, 3, 7}));
    REQUIRE(spec(0)     == SpectrumSample(400_nm, 1));
    REQUIRE(spec(0.125) == SpectrumSample(450_nm, 1.5));
    REQUIRE(spec(0.25)  == SpectrumSample(500_nm, 2));
    REQUIRE(spec(0.5)   == SpectrumSample(600_nm, 9));
    REQUIRE(spec(0.75)  == SpectrumSample(700_nm, 3));
    REQUIRE(spec(0.875) == SpectrumSample(750_nm, 5));
    REQUIRE(spec(1)     == SpectrumSample(800_nm, 7));

    REQUIRE(spec(400_nm) == SpectrumSample(400_nm, 1));
    REQUIRE(spec(600_nm) == SpectrumSample(600_nm, 9));
    REQUIRE(spec(800_nm) == SpectrumSample(800_nm, 7));

    REQUIRE(spec(Interval<float>(0    , 0  )) == SpectrumSample(400_nm, 1  ));
    REQUIRE(spec(Interval<float>(0    , 0.5)) == SpectrumSample(500_nm, 3.5));
    REQUIRE(spec(Interval<float>(0    , 1  )) == SpectrumSample(600_nm, 4.5));
    REQUIRE(rel_equal(spec(Interval<float>(0.5, 1  )), SpectrumSample(700_nm, 5.5)));
    REQUIRE(spec(Interval<float>(1    , 1  )) == SpectrumSample(800_nm, 7  ));
    REQUIRE(rel_equal(spec(Interval<float>(0.125, 1  )), SpectrumSample(625_nm, 4.964285714)));
}

// (C) 2013 Sebastian Mach (1983), this file is published under the terms of the
// GNU General Public License, Version 3 (a.k.a. GPLv3).
// See COPYING in the root-folder of the excygen project folder.

#include "gaudy/Interval.hh"
#include "gaudy/Nanometer.hh"
#include "catch.hpp"

TEST_CASE("gaudy/Interval", "Interval tests")
{
    using namespace gaudy;
    REQUIRE_THROWS(Interval<float>(1,0));
    REQUIRE_NOTHROW(Interval<float>(1,1));
    REQUIRE_NOTHROW(Interval<float>(-1,1));
    REQUIRE_THROWS(Interval<Nanometer>(1_nm,0_nm));
    REQUIRE_NOTHROW(Interval<Nanometer>(1_nm,1_nm));
    REQUIRE_NOTHROW(Interval<Nanometer>(-1_nm,1_nm));

    REQUIRE(optional<Interval<float>>() == intersection(Interval<float>(0,1), Interval<float>(2,3)));
    REQUIRE(optional<Interval<float>>() == intersection(Interval<float>(3,4), Interval<float>(1,2)));
    REQUIRE(Interval<float>(1,2) == intersection(Interval<float>(1,2), Interval<float>(0,4)));
    REQUIRE(Interval<float>(0,2) == intersection(Interval<float>(0,2), Interval<float>(0,4)));
    REQUIRE(Interval<float>(-4,-3) == intersection(Interval<float>(-5,-3), Interval<float>(-4,-2)));

    REQUIRE(Interval<float>(1,2) == Interval<float>(1,2));
    REQUIRE_FALSE(Interval<float>(1.5,2) == Interval<float>(1,2));
    REQUIRE(Interval<float>(1.5,2) != Interval<float>(1,2));
    REQUIRE_FALSE(Interval<float>(1,2) != Interval<float>(1,2));

    REQUIRE(length(Interval<float>(1,2)) == 1);
    REQUIRE(length(Interval<float>(-1,1)) == 2);

    REQUIRE(interval(1,2) == Interval<int>(1,2));
    REQUIRE(interval(1.f,2.f) == Interval<float>(1.f,2.f));
}

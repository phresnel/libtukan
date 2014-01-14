// (C) 2013 Sebastian Mach (1983), this file is published under the terms of the
// GNU General Public License, Version 3 (a.k.a. GPLv3).
// See COPYING in the root-folder of the excygen project folder.

#include "gaudy/Nanometer.hh"
#include "catch.hpp"

TEST_CASE("gaudy/Nanometer", "Nanometer tests")
{
    using namespace gaudy;

    REQUIRE(1_nm == 1_nm);
    REQUIRE(1_nm != 2_nm);
    REQUIRE(rel_equal(1_nm, 1_nm));
    REQUIRE((1_nm - 1_nm) == 0_nm);
    REQUIRE((1_nm + 1_nm) == 2_nm);
    REQUIRE((1_nm * 2_nm) == 2_nm);
    REQUIRE((1_nm / 2_nm) == 0.5_nm);
    REQUIRE((1_nm - 1) == 0_nm);
    REQUIRE((1_nm + 1) == 2_nm);
    REQUIRE((1_nm * 2) == 2_nm);
    REQUIRE((1_nm / 2) == 0.5_nm);
    REQUIRE((1 - 1_nm) == 0_nm);
    REQUIRE((1 + 1_nm) == 2_nm);
    REQUIRE((1 * 2_nm) == 2_nm);
    REQUIRE((1 / 2_nm) == 0.5_nm);
    REQUIRE((1_nm -= 1_nm) == 0_nm);
    REQUIRE((1_nm += 1_nm) == 2_nm);
    REQUIRE((1_nm *= 2_nm) == 2_nm);
    REQUIRE((1_nm /= 2_nm) == 0.5_nm);
    REQUIRE((1_nm -= 1) == 0_nm);
    REQUIRE((1_nm += 1) == 2_nm);
    REQUIRE((1_nm *= 2) == 2_nm);
    REQUIRE((1_nm /= 2) == 0.5_nm);
    REQUIRE(-(-1_nm) == 1_nm);
    REQUIRE(+1_nm == 1_nm);
}

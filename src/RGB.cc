// (C) 2013 Sebastian Mach (1983), this file is published under the terms of the
// GNU General Public License, Version 3 (a.k.a. GPLv3).
// See COPYING in the root-folder of the excygen project folder.
#include "gaudy/RGB.hh"
//#include "gaudy/LinearRGB.hh"
#include "catch.hpp"


#include <iostream>
namespace gaudy {
    template <typename T, template <typename> class RGBSpace>
    inline
    std::ostream& operator<< (std::ostream &os, RGB<T, RGBSpace> const &rhs) {
        return os << "rgb{" << rhs.r << ";" << rhs.g << ";" << rhs.b << "}";
    }

    template <typename T>
    inline
    std::ostream& operator<< (std::ostream &os, XYZ<T> const &rhs) {
        return os << "XYZ{" << rhs.X << ";" << rhs.Y << ";" << rhs.Z << "}";
    }
}

TEST_CASE("gaudy/RGB", "RGB tests") {

    using namespace gaudy;
    using RGB = RGB<float, sRGB>;

    SECTION("array interface") {
        REQUIRE(RGB(1,2,3)[0] == 1);
        REQUIRE(RGB(1,2,3)[1] == 2);
        REQUIRE(RGB(1,2,3)[2] == 3);
        REQUIRE(RGB(1,2,3).size() == 3);
        REQUIRE(3 == size(RGB()));

        REQUIRE_NOTHROW(RGB().at(0));
        REQUIRE_NOTHROW(RGB().at(1));
        REQUIRE_NOTHROW(RGB().at(2));
        REQUIRE_THROWS(RGB().at(3));
        REQUIRE_THROWS(RGB().at(4));
        REQUIRE_THROWS(RGB().at(454545456));
    }

    SECTION("assignment and comparison") {
        REQUIRE(RGB()      == rel_equal(RGB()));
        REQUIRE(RGB(0,0,0) == rel_equal(RGB()));
        REQUIRE(RGB()      != rel_equal(RGB(1,2,3)));
    }
}

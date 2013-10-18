// (C) 2013 Sebastian Mach (1983), this file is published under the terms of the
// GNU General Public License, Version 3 (a.k.a. GPLv3).
// See COPYING in the root-folder of the excygen project folder.

#include "gaudy/RGB.hh"
#include "catch.hpp"


#include <iostream>
namespace gaudy {
    inline
    std::ostream& operator<< (std::ostream &os, RGB const &rhs) {
        return os << "rgb{" << rhs.r << ";" << rhs.g << ";" << rhs.b << "}";
    }
}


TEST_CASE("gaudy/RGB", "RGB tests")
{
    using namespace gaudy;

    SECTION("assignment and comparison") {
        REQUIRE(RGB()==RGB());
        REQUIRE(RGB(0,0,0)==RGB());
        REQUIRE(RGB()!=RGB(1,2,3));

        REQUIRE((RGB()+=RGB())           == RGB());
        REQUIRE((RGB()+=RGB(1,2,3))      == RGB(1,2,3));
        REQUIRE((RGB(1,2,3)+=RGB(5,6,7)) == RGB(6,8,10));

        REQUIRE((RGB()-=RGB())           == RGB());
        REQUIRE((RGB()-=RGB(1,2,3))      == RGB(-1,-2,-3));
        REQUIRE((RGB(1,2,3)-=RGB(5,6,7)) == RGB(-4,-4,-4));

        REQUIRE((RGB()*=RGB())           == RGB());
        REQUIRE((RGB()*=RGB(1,2,3))      == RGB(0,0,0));
        REQUIRE((RGB(1,2,3)*=RGB(5,6,7)) == RGB(5,12,21));

        REQUIRE((RGB()/=RGB(1,2,3))      == RGB(0,0,0));
        REQUIRE((RGB(3,6,9)/=RGB(3,2,1)) == RGB(1,3,9));

        REQUIRE((RGB()+=1)      == RGB(1,1,1));
        REQUIRE((RGB()+=-2)     == RGB(-2,-2,-2));
        REQUIRE((RGB(1,2,3)+=5) == RGB(6,7,8));

        REQUIRE((RGB()-=1)      == RGB(-1,-1,-1));
        REQUIRE((RGB()-=-2)     == RGB(2,2,2));
        REQUIRE((RGB(1,2,3)-=5) == RGB(-4,-3,-2));

        REQUIRE((RGB()*=1)      == RGB());
        REQUIRE((RGB()*=-2)     == RGB(0,0,0));
        REQUIRE((RGB(1,2,3)*=5) == RGB(5,10,15));

        REQUIRE((RGB()/=1)       == RGB(0,0,0));
        REQUIRE((RGB(3,6,9)/=-2) == RGB(-1.5,-3,-4.5));
    }

    SECTION("arithmetics") {
        REQUIRE((RGB()+RGB())           == RGB());
        REQUIRE((RGB()+RGB(1,2,3))      == RGB(1,2,3));
        REQUIRE((RGB(1,2,3)+RGB(5,6,7)) == RGB(6,8,10));

        REQUIRE((RGB()-RGB())           == RGB());
        REQUIRE((RGB()-RGB(1,2,3))      == RGB(-1,-2,-3));
        REQUIRE((RGB(1,2,3)-RGB(5,6,7)) == RGB(-4,-4,-4));

        REQUIRE((RGB()*RGB())           == RGB());
        REQUIRE((RGB()*RGB(1,2,3))      == RGB(0,0,0));
        REQUIRE((RGB(1,2,3)*RGB(5,6,7)) == RGB(5,12,21));

        REQUIRE((RGB()/RGB(1,2,3))      == RGB(0,0,0));
        REQUIRE((RGB(3,6,9)/RGB(3,2,1)) == RGB(1,3,9));

        REQUIRE((RGB()+1)      == RGB(1,1,1));
        REQUIRE((RGB()+-2)     == RGB(-2,-2,-2));
        REQUIRE((RGB(1,2,3)+5) == RGB(6,7,8));

        REQUIRE((RGB()-1)      == RGB(-1,-1,-1));
        REQUIRE((RGB()- -2)    == RGB(2,2,2));
        REQUIRE((RGB(1,2,3)-5) == RGB(-4,-3,-2));

        REQUIRE((RGB()*1)      == RGB());
        REQUIRE((RGB()*-2)     == RGB(0,0,0));
        REQUIRE((RGB(1,2,3)*5) == RGB(5,10,15));

        REQUIRE((RGB()/1)       == RGB(0,0,0));
        REQUIRE((RGB(3,6,9)/-2) == RGB(-1.5,-3,-4.5));
    }
}

TEST_CASE("gaudy/RGB/IEEE 754 NaNs and Infinities", "IEEE 754 Conformance")
{
    if (!std::numeric_limits<float>::is_iec559 || !std::numeric_limits<double>::is_iec559)
        FAIL("float/double are not IEEE 754; IEEE 754 Tests skipped.");

    using namespace gaudy;

    // infinity
    REQUIRE((RGB(1,2,3)/=RGB())  == RGB(1/.0f, 1/.0f, 1/.0f));
    REQUIRE((RGB(1,2,3)/=0)      == RGB(1/.0f, 1/.0f, 1/.0f));

    // NaN
    REQUIRE_FALSE(RGB() == (RGB()/=RGB()));
    REQUIRE(RGB() != (RGB()/=RGB()));
    REQUIRE((RGB(1/.0f, 1/.0f, 1/.0f)       *= RGB(0,0,0)) != RGB(0,0,0));
    REQUIRE_FALSE((RGB(1/.0f, 1/.0f, 1/.0f) *= RGB(0,0,0)) == RGB(0,0,0));
    REQUIRE((RGB(0,0,0) *= RGB(1/.0f, 1/.0f, 1/.0f))       != RGB(0,0,0));

    REQUIRE_FALSE(RGB() == (RGB()/=0));
    REQUIRE(RGB() != (RGB()/=0));
    REQUIRE((RGB(1/.0f, 1/.0f, 1/.0f)       *= 0) != RGB(0,0,0));
    REQUIRE_FALSE((RGB(1/.0f, 1/.0f, 1/.0f) *= 0) == RGB(0,0,0));
    REQUIRE((RGB(0,0,0) *= (1/.0f)              ) != RGB(0,0,0));
}

TEST_CASE("gaudy/RGB/cmath", "RGB cmath tests")
{
    using namespace gaudy;
    const RGB v {0.6, 0.4, 0.8};
    const RGB w {0.9, 0.2, 0.7};
    const RGB x {1.9, 4, 8.7};
    const auto a = 2., b = 11., c = 0.5;

    SECTION("trigonometric") {
        REQUIRE(sin(v)     == rel_equal(RGB(sin(v.r),       sin(v.g),        sin(v.b))));
        REQUIRE(cos(v)     == rel_equal(RGB(cos(v.r),       cos(v.g),        cos(v.b))));
        REQUIRE(tan(v)     == rel_equal(RGB(tan(v.r),       tan(v.g),        tan(v.b))));
        REQUIRE(acos(v)    == rel_equal(RGB(acos(v.r),      acos(v.g),       acos(v.b))));
        REQUIRE(asin(v)    == rel_equal(RGB(asin(v.r),      asin(v.g),       asin(v.b))));
        REQUIRE(atan(v)    == rel_equal(RGB(atan(v.r),      atan(v.g),       atan(v.b))));
        REQUIRE(atan2(v,w) == rel_equal(RGB(atan2(v.r,w.r), atan2(v.g, w.g), atan2(v.b, w.b))));
    }

    SECTION("hyperbolic") {
        REQUIRE(cosh(v)  == rel_equal(RGB(cosh(v.r),  cosh(v.g),  cosh(v.b))));
        REQUIRE(sinh(v)  == rel_equal(RGB(sinh(v.r),  sinh(v.g),  sinh(v.b))));
        REQUIRE(tanh(v)  == rel_equal(RGB(tanh(v.r),  tanh(v.g),  tanh(v.b))));
        REQUIRE(acosh(x) == rel_equal(RGB(acosh(x.r), acosh(x.g), acosh(x.b))));
        REQUIRE(asinh(x) == rel_equal(RGB(asinh(x.r), asinh(x.g), asinh(x.b))));
        REQUIRE(atanh(v) == rel_equal(RGB(atanh(v.r), atanh(v.g), atanh(v.b))));
    }

    SECTION("exponential and logarithmic") {

    }

    SECTION("power functions") {
        REQUIRE(pow(v,x) == rel_equal(RGB(pow(v.r, x.r), pow(v.g, x.g), pow(v.b, x.b))));
        REQUIRE(pow(a,w) == rel_equal(RGB(pow(a, w.r),   pow(a, w.g),   pow(a, w.b))));
        REQUIRE(pow(b,w) == rel_equal(RGB(pow(b, w.r),   pow(b, w.g),   pow(b, w.b))));
        REQUIRE(pow(c,w) == rel_equal(RGB(pow(c, w.r),   pow(c, w.g),   pow(c, w.b))));
        REQUIRE(pow(x,a) == rel_equal(RGB(pow(x.r, a),   pow(x.g, a),   pow(x.b, a))));
        REQUIRE(pow(x,b) == rel_equal(RGB(pow(x.r, b),   pow(x.g, b),   pow(x.b, b))));
        REQUIRE(pow(x,c) == rel_equal(RGB(pow(x.r, c),   pow(x.g, c),   pow(x.b, c))));

        REQUIRE(sqrt(v) == rel_equal(RGB(sqrt(v.r), sqrt(v.g), sqrt(v.b))));
        REQUIRE(sqrt(x) == rel_equal(RGB(sqrt(x.r), sqrt(x.g), sqrt(x.b))));

        REQUIRE(cbrt(v) == rel_equal(RGB(cbrt(v.r), cbrt(v.g), cbrt(v.b))));
        REQUIRE(cbrt(x) == rel_equal(RGB(cbrt(x.r), cbrt(x.g), cbrt(x.b))));

        REQUIRE(hypot(v,x) == rel_equal(RGB(hypot(v.r, x.r), hypot(v.g, x.g), hypot(v.b, x.b))));
        REQUIRE(hypot(a,w) == rel_equal(RGB(hypot(a, w.r),   hypot(a, w.g),   hypot(a, w.b))));
        REQUIRE(hypot(b,w) == rel_equal(RGB(hypot(b, w.r),   hypot(b, w.g),   hypot(b, w.b))));
        REQUIRE(hypot(c,w) == rel_equal(RGB(hypot(c, w.r),   hypot(c, w.g),   hypot(c, w.b))));
        REQUIRE(hypot(x,a) == rel_equal(RGB(hypot(x.r, a),   hypot(x.g, a),   hypot(x.b, a))));
        REQUIRE(hypot(x,b) == rel_equal(RGB(hypot(x.r, b),   hypot(x.g, b),   hypot(x.b, b))));
        REQUIRE(hypot(x,c) == rel_equal(RGB(hypot(x.r, c),   hypot(x.g, c),   hypot(x.b, c))));
    }
}

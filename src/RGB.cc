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

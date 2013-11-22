// (C) 2013 Sebastian Mach (1983), this file is published under the terms of the
// GNU General Public License, Version 3 (a.k.a. GPLv3).
// See COPYING in the root-folder of the excygen project folder.

#include "gaudy/LinearRGB.hh"
#include "gaudy/algorithm/lerp.hh"
#include "catch.hpp"
#include <vector>
#include <list>

TEST_CASE("algorithm/lerp", "lerp tests")
{
    using gaudy::lerp;
    using gaudy::lerp_sat;
    using gaudy::Interval;
    using gaudy::interval;
    using RGB = gaudy::LinearRGB<float, gaudy::sRGB>;

    SECTION("lerp(a,b, f)") {
        REQUIRE(lerp(1,2,  0.5) == 1.5);
        REQUIRE(lerp(-1,1, 0.5) == 0);
        REQUIRE(lerp(-1,1, 1.5) == 2);
        REQUIRE(lerp(-1,1, 2)   == 3);
        REQUIRE(lerp(-1,1, -1)  == -3);
        REQUIRE(lerp(-1,1, -1.5) == -4);
        REQUIRE(lerp(-1,1, -2)   == -5);
        REQUIRE(lerp(RGB(0,0,0), RGB(1,2,3), 0.0         ) == RGB(0,0,0));
        REQUIRE(lerp(RGB(0,0,0), RGB(1,2,3), 0.5         ) == RGB(0.5,1,1.5));
        REQUIRE(lerp(RGB(0,0,0), RGB(1,2,3), 1.0         ) == RGB(1,2,3));
        REQUIRE(lerp(RGB(0,0,0), RGB(1,2,3), RGB(0,0.5,1)) == RGB(0,1,3));
        REQUIRE(lerp(RGB(0,0,0), 1         , RGB(0,0.5,1)) == RGB(0,0.5,1));
        REQUIRE(lerp(0         , 1         , RGB(0,0.5,1)) == RGB(0,0.5,1));
        REQUIRE(lerp(RGB(0,0,0), RGB(1,2,3), 2.0         ) == RGB(2,4,6));
        REQUIRE(lerp(RGB(0,0,0), RGB(1,2,3), -1.0        ) == RGB(-1,-2,-3));
    }

    SECTION("lerp([a..b], f)") {
        REQUIRE(lerp(interval(1,2),  0.5) == 1.5);
        REQUIRE(lerp(interval(-1,1), 0.5) == 0);
        REQUIRE(lerp(interval(-1,1), 1.5) == 2);
        REQUIRE(lerp(interval(-1,1), 2)   == 3);
        REQUIRE(lerp(interval(-1,1), -1)  == -3);
        REQUIRE(lerp(interval(-1,1), -1.5) == -4);
        REQUIRE(lerp(interval(-1,1), -2)   == -5);

        REQUIRE(lerp(interval(-1,1), RGB(-1,0.5,2) == RGB(-3,0,3)));
    }

    SECTION("lerp_sat(a,b, f)") {
        REQUIRE(lerp_sat(1,2,  0.5) == 1.5);
        REQUIRE(lerp_sat(-1,1, 0.5) == 0);
        REQUIRE(lerp_sat(-1,1, 1.5) == 1);
        REQUIRE(lerp_sat(-1,1, 2)   == 1);
        REQUIRE(lerp_sat(-1,1, -1)  == -1);
        REQUIRE(lerp_sat(-1,1, -1.5) == -1);
        REQUIRE(lerp_sat(-1,1, -2)   == -1);
        REQUIRE(lerp_sat(RGB(0,0,0), RGB(1,2,3), 0.0         ) == RGB(0,0,0));
        REQUIRE(lerp_sat(RGB(0,0,0), RGB(1,2,3), 0.5         ) == RGB(0.5,1,1.5));
        REQUIRE(lerp_sat(RGB(0,0,0), RGB(1,2,3), 1.0         ) == RGB(1,2,3));
        REQUIRE(lerp_sat(RGB(0,0,0), RGB(1,2,3), RGB(0,0.5,1)) == RGB(0,1,3));
        REQUIRE(lerp_sat(RGB(0,0,0), 1         , RGB(0,0.5,1)) == RGB(0,0.5,1));
        REQUIRE(lerp_sat(0         , 1         , RGB(0,0.5,1)) == RGB(0,0.5,1));
        REQUIRE(lerp_sat(RGB(0,0,0), RGB(1,2,3), 2.0         ) == RGB(1,2,3));
        REQUIRE(lerp_sat(RGB(0,0,0), RGB(1,2,3), -1.0        ) == RGB(0,0,0));
    }

    SECTION("lerp_sat([a..b], f)") {
        REQUIRE(lerp_sat(interval(1,2),  0.5) == 1.5);
        REQUIRE(lerp_sat(interval(-1,1), 0.5) == 0);
        REQUIRE(lerp_sat(interval(-1,1), 1.5) == 1);
        REQUIRE(lerp_sat(interval(-1,1), 2)   == 1);
        REQUIRE(lerp_sat(interval(-1,1), -1)  == -1);
        REQUIRE(lerp_sat(interval(-1,1), -1.5) == -1);
        REQUIRE(lerp_sat(interval(-1,1), -2)   == -1);

        REQUIRE(lerp(interval(-1,1), RGB(-1,0.5,2) == RGB(-1,0,2)));
    }

    SECTION("lerp_sat({x_1,x_2,..,x_n}, f)") {
        REQUIRE_THROWS(lerp_sat(std::initializer_list<int>{},  0.0));
        REQUIRE(lerp_sat({2},  0.0) == 2);
        REQUIRE(lerp_sat({2},  1.0) == 2);
        REQUIRE(lerp_sat({2},  0.5) == 2);
        REQUIRE(lerp_sat({2},  0.0) == 2);
        REQUIRE(lerp_sat({0,1},  0.0) == 0);
        REQUIRE(lerp_sat({0,1},  1.0) == 1);
        REQUIRE(lerp_sat({0,1,2},  0.75) == 1.5);
        REQUIRE(lerp_sat({2,1,2},  0.75) == 1.5);
        REQUIRE(lerp_sat({2,1,2},  0.25) == 1.5);
        REQUIRE(lerp_sat({2,1,2},  0.5 ) == 1  );
        REQUIRE(lerp_sat({2,1,2},  0.0 ) == 2  );
        REQUIRE(lerp_sat({2,1,2},  1.0 ) == 2  );
        REQUIRE(lerp_sat({2,1,2}, -1.0 ) == 2  );
        REQUIRE(lerp_sat({2,1,2},  2.0 ) == 2  );

        //REQUIRE(lerp_sat({RGB(1,1,1),RGB(1,2,1)},  0.5 ) == RGB(1,1.5,1) );
    }

    SECTION("lerp_sat(RandomAccessIterator, RandomAccessIterator, f)") {
        using gaudy::lerp_sat;
        std::vector<int> vec = {1,2,3};
        using Iter = std::list<int>::iterator;
        REQUIRE(lerp_sat(begin(vec), end(vec), 0.5) == 2);
        REQUIRE(lerp_sat(vec.begin(), vec.end(), 0.5) == 2);

        std::list<int> lst = {7,9};
        REQUIRE(lerp_sat(begin(lst), end(lst), 0.5) == 8);

        int arr[] = {1,2,3,4};
        REQUIRE(lerp_sat(std::begin(arr), std::end(arr), 0.5) == 2.5);
    }

    SECTION("lerp_sat(range, f)") {
        using gaudy::lerp_sat;
        std::vector<int> vec = {1,2,3};
        using Iter = std::list<int>::iterator;
        REQUIRE(lerp_sat(vec, 0.5) == 2);

        std::list<int> lst = {7,9};
        REQUIRE(lerp_sat(lst, 0.5) == 8);
    }
}

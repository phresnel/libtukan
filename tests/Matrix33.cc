// (C) 2013 Sebastian Mach (1983), this file is published under the terms of the
// GNU General Public License, Version 3 (a.k.a. GPLv3).
// See COPYING in the root-folder of the excygen project folder.
#include "catch.hpp"
#include "gaudy/Matrix33.hh"

namespace gaudy {
    template <typename T>
    std::ostream& operator<< (std::ostream &os, Matrix33<T> const &m) {
        return os //<< std::fixed
                  << "{(" << m._11 << "," << m._12 << "," << m._13 << "),"
                  << "(" << m._21 << "," << m._22 << "," << m._23 << "),"
                  << "(" << m._31 << "," << m._32 << "," << m._33 << ")}";
    }
}

TEST_CASE("gaudy/Matrix33", "Matrix33 math ops correctness") {
    using gaudy::Matrix33;

    Matrix33<float> a {1,2,3,
                       4,5,6,
                       7,0,9};
    Matrix33<float> b {1,1,0,
                       0,1,1,
                       0,1,0};
    REQUIRE(a==a);
    REQUIRE(a==rel_equal(a*1.00000001f));
    REQUIRE(a!=b);
    REQUIRE(!(a!=a));
    REQUIRE(!(a==b));
    REQUIRE(determinant(a) == gaudy::rel_equal(-48.f));
    REQUIRE(determinant(b) == gaudy::rel_equal(-1.f));
    REQUIRE((a*inverse(a)) == rel_equal(Matrix33<float>(), gaudy::epsilon, 0.000001));
    REQUIRE(((a*b)*inverse(b)) == rel_equal(a));

    float inf = 1.f / 0.f;
    REQUIRE(inverse(Matrix33<float>{1,2,3,4,5,6,7,8,9})
            == Matrix33<float>(-inf, inf, -inf, inf, -inf, inf, -inf, inf, -inf)
           );

    REQUIRE(transpose(a) == rel_equal(Matrix33<float>(1,4,7,
                                                      2,5,0,
                                                      3,6,9)));
}

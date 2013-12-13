// (C) 2013 Sebastian Mach (1983), this file is published under the terms of the
// GNU General Public License, Version 3 (a.k.a. GPLv3).
// See COPYING in the root-folder of the excygen project folder.
#include "gaudy/RGBSpace.hh"
#include "gaudy/Matrix33.hh"
#include "catch.hpp"

namespace gaudy {
    template <typename T>
    std::ostream& operator<< (std::ostream &os, Matrix33<T> const &m) {
        return os //<< std::fixed
                  << "{(" << m._11 << "," << m._12 << "," << m._13 << "),"
                  << "(" << m._21 << "," << m._22 << "," << m._23 << "),"
                  << "(" << m._31 << "," << m._32 << "," << m._33 << ")}";
    }

    template <typename T>
    inline
    std::ostream& operator<< (std::ostream &os, RGBSpace<T> const &rhs) {
        return os << "rgb-space{"
                  << "to-xyz{\n"
                  << rhs.rgb_to_xyz
                  << "}\n"
                  << "to-rgb{\n"
                  << rhs.xyz_to_rgb
                  << "}"
                  << "}";
    }
}


TEST_CASE("gaudy/RGBSpace", "RGBSpace tests") {
    using namespace gaudy;

    // The following matrices are from Bruce Lindblooms site:
    REQUIRE(AdobeRGB<float>().rgb_to_xyz == rel_equal(Matrix33<float>
                                                  {0.5767309,  0.1855540,  0.1881852,
                                                   0.2973769,  0.6273491,  0.0752741,
                                                   0.0270343,  0.0706872,  0.9911085},
                                                   gaudy::epsilon, 0.0000025));
    REQUIRE(AdobeRGB<float>().xyz_to_rgb == rel_equal(Matrix33<float>
                                                  {2.0413690, -0.5649464, -0.3446944,
                                                  -0.9692660,  1.8760108,  0.0415560,
                                                   0.0134474, -0.1183897,  1.0154096},
                                                   gaudy::epsilon, 0.0000025));


    REQUIRE(sRGB<float>().rgb_to_xyz == rel_equal(Matrix33<float>
                                                  {0.4124564, 0.3575761, 0.1804375,
                                                   0.2126729, 0.7151522, 0.0721750,
                                                   0.0193339, 0.1191920, 0.9503041},
                                                   gaudy::epsilon, 0.000001));
    REQUIRE(sRGB<float>().xyz_to_rgb == rel_equal(Matrix33<float>
                                                  {3.2404542, -1.5371385, -0.4985314,
                                                  -0.9692660,  1.8760108,  0.0415560,
                                                   0.0556434, -0.2040259,  1.0572252},
                                                   gaudy::epsilon, 0.000001));
}

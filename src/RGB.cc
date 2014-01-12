// (C) 2013 Sebastian Mach (1983), this file is published under the terms of the
// GNU General Public License, Version 3 (a.k.a. GPLv3).
// See COPYING in the root-folder of the excygen project folder.
#include "gaudy/RGB.hh"
//#include "gaudy/RGB.hh"
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

    SECTION("array interface") {
        using RGB = RGB<float, sRGB>;
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
        using RGB = RGB<float, sRGB>;
        REQUIRE(RGB()      == rel_equal(RGB()));
        REQUIRE(RGB(0,0,0) == rel_equal(RGB()));
        REQUIRE(RGB()      != rel_equal(RGB(1,2,3)));
    }

    SECTION("XYZ/RGB conversion (against Bruce Lindblooms color space calculator)") {
        using RGBSpace = AppleRGB<float>;

        { RGB<float, AppleRGB> rgb {-0.749988, 0.600315, 0.960963};
          XYZ<float>                 xyz {0.03, 0.2, 0.9};

          REQUIRE(static_cast<XYZ<float>>    (rgb)  == rel_equal(xyz, gaudy::epsilon, 0.0001));
          REQUIRE((static_cast<decltype(rgb)>(xyz))  == rel_equal(rgb, gaudy::epsilon, 0.0001)); }

        { RGB<float, AdobeRGB> rgb {-0.630084, 0.646867, 0.948696};
          XYZ<float>                 xyz {0.03, 0.2, 0.9};
          REQUIRE(static_cast<XYZ<float>>    (rgb)   == rel_equal(xyz, gaudy::epsilon, 0.0001));
          REQUIRE((static_cast<decltype(rgb)>(xyz))  == rel_equal(rgb, gaudy::epsilon, 0.0001)); }

        { RGB<float, BestRGB>  rgb {-0.553127,0.582417,1.044189};
          XYZ<float>                 xyz {0.03, 0.2, 0.9};
          REQUIRE(static_cast<XYZ<float>>    (rgb)   == rel_equal(xyz, gaudy::epsilon, 0.0001));
          REQUIRE((static_cast<decltype(rgb)>(xyz))  == rel_equal(rgb, gaudy::epsilon, 0.0001)); }

        { RGB<float, BetaRGB>  rgb {-0.530159,0.627250,1.056539};
          XYZ<float>                 xyz {0.03, 0.2, 0.9};
          REQUIRE(static_cast<XYZ<float>>    (rgb)   == rel_equal(xyz, gaudy::epsilon, 0.0001));
          REQUIRE((static_cast<decltype(rgb)>(xyz))  == rel_equal(rgb, gaudy::epsilon, 0.0001)); }

        { RGB<float, BruceRGB> rgb {-0.753376,0.646867,0.948153};
          XYZ<float>                 xyz {0.03, 0.2, 0.9};
          REQUIRE(static_cast<XYZ<float>>    (rgb)   == rel_equal(xyz, gaudy::epsilon, 0.0001));
          REQUIRE((static_cast<decltype(rgb)>(xyz))  == rel_equal(rgb, gaudy::epsilon, 0.0001)); }

        { RGB<float, CIERGB>   rgb {-0.750904,0.620013,0.955966};
          XYZ<float>                 xyz {0.03, 0.2, 0.9};
          REQUIRE(static_cast<XYZ<float>>    (rgb)   == rel_equal(xyz, gaudy::epsilon, 0.0001));
          REQUIRE((static_cast<decltype(rgb)>(xyz))  == rel_equal(rgb, gaudy::epsilon, 0.0001)); }

        { RGB<float, ColorMatchRGB> rgb {-0.694736,0.595039,1.135352};
          XYZ<float>                 xyz {0.03, 0.2, 0.9};
          REQUIRE(static_cast<XYZ<float>>    (rgb)   == rel_equal(xyz, gaudy::epsilon, 0.0001));
          REQUIRE((static_cast<decltype(rgb)>(xyz))  == rel_equal(rgb, gaudy::epsilon, 0.0001)); }

        { RGB<float, DonRGB4>  rgb {-0.554315,0.617836,1.050117};
          XYZ<float>                 xyz {0.03, 0.2, 0.9};
          REQUIRE(static_cast<XYZ<float>>    (rgb)   == rel_equal(xyz, gaudy::epsilon, 0.0001));
          REQUIRE((static_cast<decltype(rgb)>(xyz))  == rel_equal(rgb, gaudy::epsilon, 0.0001)); }

        { RGB<float, ECIRGBv2> rgb {-0.606068,0.646403,1.058212};
          XYZ<float>                 xyz {0.03, 0.2, 0.9};
          REQUIRE(static_cast<XYZ<float>>    (rgb)   == rel_equal(xyz, gaudy::epsilon, 0.0001));
          REQUIRE((static_cast<decltype(rgb)>(xyz))  == rel_equal(rgb, gaudy::epsilon, 0.0001)); }

        { RGB<float, EktaSpacePS5> rgb {-0.584171,0.639524,1.056725};
          XYZ<float>                 xyz {0.03, 0.2, 0.9};
          REQUIRE(static_cast<XYZ<float>>    (rgb)   == rel_equal(xyz, gaudy::epsilon, 0.0001));
          REQUIRE((static_cast<decltype(rgb)>(xyz))  == rel_equal(rgb, gaudy::epsilon, 0.0001)); }

        { RGB<float, NTSCRGB>  rgb {-0.585995,0.616329,0.896257};
          XYZ<float>                 xyz {0.03, 0.2, 0.9};
          REQUIRE(static_cast<XYZ<float>>    (rgb)   == rel_equal(xyz, gaudy::epsilon, 0.0001));
          REQUIRE((static_cast<decltype(rgb)>(xyz))  == rel_equal(rgb, gaudy::epsilon, 0.0001)); }

        { RGB<float, PALSECAMRGB>  rgb {-0.801697,0.646867,0.962180};
          XYZ<float>                 xyz {0.03, 0.2, 0.9};
          REQUIRE(static_cast<XYZ<float>>    (rgb)   == rel_equal(xyz, gaudy::epsilon, 0.0001));
          REQUIRE((static_cast<decltype(rgb)>(xyz))  == rel_equal(rgb, gaudy::epsilon, 0.0001)); }

        { RGB<float, ProPhotoRGB> rgb {-0.203111,0.515859,1.049379};
          XYZ<float>                 xyz {0.03, 0.2, 0.9};
          REQUIRE(static_cast<XYZ<float>>    (rgb)   == rel_equal(xyz, gaudy::epsilon, 0.0001));
          REQUIRE((static_cast<decltype(rgb)>(xyz))  == rel_equal(rgb, gaudy::epsilon, 0.0001)); }

        { RGB<float, SMPTE_C>  rgb {-0.867953,0.655706,0.956825};
          XYZ<float>                 xyz {0.03, 0.2, 0.9};
          REQUIRE(static_cast<XYZ<float>>    (rgb)   == rel_equal(xyz, gaudy::epsilon, 0.0001));
          REQUIRE((static_cast<decltype(rgb)>(xyz))  == rel_equal(rgb, gaudy::epsilon, 0.0001)); }

        { RGB<float, sRGB>     rgb {-0.831663,0.652674,0.960445};
          XYZ<float>                 xyz {0.03, 0.2, 0.9};
          REQUIRE(static_cast<XYZ<float>>    (rgb)   == rel_equal(xyz, gaudy::epsilon, 0.0001));
          REQUIRE((static_cast<decltype(rgb)>(xyz))  == rel_equal(rgb, gaudy::epsilon, 0.0001)); }

        { RGB<float, WideGamutRGB> rgb {-0.522585,0.608080,1.061892};
          XYZ<float>                 xyz {0.03, 0.2, 0.9};
          REQUIRE(static_cast<XYZ<float>>    (rgb)   == rel_equal(xyz, gaudy::epsilon, 0.0001));
          REQUIRE((static_cast<decltype(rgb)>(xyz))  == rel_equal(rgb, gaudy::epsilon, 0.0001)); }
    }

}

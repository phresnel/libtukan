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

    template <typename T, template <typename> class RGBSpace>
    inline
    std::ostream& operator<< (std::ostream &os, LinearRGB<T, RGBSpace> const &rhs) {
        return os << "linear-rgb{" << rhs.r << ";" << rhs.g << ";" << rhs.b << "}";
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

    SECTION("LinearRGB/RGB conversion (against Bruce Lindblooms color space calculator)") {
        { RGB<float, AppleRGB> rgb {-0.142278, 0.401344, 0.974406};
          LinearRGB<float, AppleRGB> xyz {-0.029898, 0.193344, 0.954404};
          REQUIRE(static_cast<decltype(xyz)>(rgb)  == rel_equal(xyz, gaudy::epsilon, 0.0001));
          REQUIRE((static_cast<decltype(rgb)>(xyz))  == rel_equal(rgb, gaudy::epsilon, 0.0001)); }

        { RGB<float, AdobeRGB> rgb {0.203131, 0.481157, 0.953237};
          LinearRGB<float, AdobeRGB> xyz {0.029999, 0.200001, 0.900000};
          REQUIRE(static_cast<decltype(xyz)>    (rgb)   == rel_equal(xyz, gaudy::epsilon, 0.0001));
          REQUIRE((static_cast<decltype(rgb)>(xyz))  == rel_equal(rgb, gaudy::epsilon, 0.0001)); }

        { RGB<float, BestRGB>  rgb {0.289813,0.483750,1.048368};
          LinearRGB<float, BestRGB>  xyz {0.065563,0.202379,1.109507};
          REQUIRE(static_cast<decltype(xyz)>    (rgb)   == rel_equal(xyz, gaudy::epsilon, 0.0001));
          REQUIRE((static_cast<decltype(rgb)>(xyz))  == rel_equal(rgb, gaudy::epsilon, 0.0001)); }

        { RGB<float, BetaRGB>  rgb {0.310037,0.495079,1.063490};
          LinearRGB<float, BetaRGB> xyz {0.076052, 0.212953, 1.145020};
          REQUIRE(static_cast<decltype(xyz)>    (rgb)   == rel_equal(xyz, gaudy::epsilon, 0.0001));
          REQUIRE((static_cast<decltype(rgb)>(xyz))  == rel_equal(rgb, gaudy::epsilon, 0.0001)); }

        { RGB<float, BruceRGB> rgb {-0.121926,0.481157,0.952491};
          LinearRGB<float, BruceRGB> xyz {-0.009759, 0.200001, 0.898450};
          REQUIRE(static_cast<decltype(xyz)>    (rgb)   == rel_equal(xyz, gaudy::epsilon, 0.0001));
          REQUIRE((static_cast<decltype(rgb)>(xyz))  == rel_equal(rgb, gaudy::epsilon, 0.0001)); }

        { RGB<float, CIERGB>   rgb {-0.314105,0.535848,0.959798};
          LinearRGB<float, CIERGB>   xyz {-0.078265,0.253450,0.913684};
          REQUIRE(static_cast<decltype(xyz)>    (rgb)   == rel_equal(xyz, gaudy::epsilon, 0.0001));
          REQUIRE((static_cast<decltype(rgb)>(xyz))  == rel_equal(rgb, gaudy::epsilon, 0.0001)); }

        { RGB<float, ColorMatchRGB> rgb {-0.087471, 0.387903, 1.148061};
          LinearRGB<float, ColorMatchRGB> xyz {-0.012455, 0.181845, 1.282145};
          REQUIRE(static_cast<decltype(xyz)>    (rgb)   == rel_equal(xyz, gaudy::epsilon, 0.0001));
          REQUIRE((static_cast<decltype(rgb)>(xyz))  == rel_equal(rgb, gaudy::epsilon, 0.0001)); }

        { RGB<float, DonRGB4>  rgb {0.289199,0.494499,1.054430};
          LinearRGB<float, DonRGB4>  xyz {0.065258, 0.212405, 1.123671};
          REQUIRE(static_cast<decltype(xyz)>    (rgb)   == rel_equal(xyz, gaudy::epsilon, 0.0001));
          REQUIRE((static_cast<decltype(rgb)>(xyz))  == rel_equal(rgb, gaudy::epsilon, 0.0001)); }

        { RGB<float, ECIRGBv2> rgb {0.279822,0.461805,1.067076};
          LinearRGB<float, ECIRGBv2> xyz {0.054508, 0.154024, 1.183696};
          REQUIRE(static_cast<decltype(xyz)>    (rgb)   == rel_equal(xyz, gaudy::epsilon, 0.0001));
          REQUIRE((static_cast<decltype(rgb)>(xyz))  == rel_equal(rgb, gaudy::epsilon, 0.0001)); }

        { RGB<float, EktaSpacePS5> rgb {0.314850,0.522972,1.063523};
          LinearRGB<float, EktaSpacePS5>  xyz {0.078673, 0.240244, 1.145099};
          REQUIRE(static_cast<decltype(xyz)>    (rgb)   == rel_equal(xyz, gaudy::epsilon, 0.0001));
          REQUIRE((static_cast<decltype(rgb)>(xyz))  == rel_equal(rgb, gaudy::epsilon, 0.0001)); }

        { RGB<float, NTSCRGB>  rgb {0.274961,0.432376,0.905162};
          LinearRGB<float, NTSCRGB>  xyz {0.058398, 0.158087, 0.803151};
          REQUIRE(static_cast<decltype(xyz)>    (rgb)   == rel_equal(xyz, gaudy::epsilon, 0.0001));
          REQUIRE((static_cast<decltype(rgb)>(xyz))  == rel_equal(rgb, gaudy::epsilon, 0.0001)); }

        { RGB<float, PALSECAMRGB>  rgb {-0.195848,0.481157,0.971689};
          LinearRGB<float, PALSECAMRGB>   xyz {-0.027683, 0.200001,0.938771};
          REQUIRE(static_cast<decltype(xyz)>    (rgb)   == rel_equal(xyz, gaudy::epsilon, 0.0001));
          REQUIRE((static_cast<decltype(rgb)>(xyz))  == rel_equal(rgb, gaudy::epsilon, 0.0001)); }

        { RGB<float, ProPhotoRGB> rgb {0.412551,0.410791,1.053870};
          LinearRGB<float, ProPhotoRGB> xyz {0.203170,0.201612,1.099049};
          REQUIRE(static_cast<decltype(xyz)>    (rgb)   == rel_equal(xyz, gaudy::epsilon, 0.0001));
          REQUIRE((static_cast<decltype(rgb)>(xyz))  == rel_equal(rgb, gaudy::epsilon, 0.0001)); }

        { RGB<float, SMPTE_C>  rgb {-0.279477,0.472821,0.965304};
          LinearRGB<float, SMPTE_C> xyz {-0.060529, 0.192457,0.925255};
          REQUIRE(static_cast<decltype(xyz)>    (rgb)   == rel_equal(xyz, gaudy::epsilon, 0.0001));
          REQUIRE((static_cast<decltype(rgb)>(xyz))  == rel_equal(rgb, gaudy::epsilon, 0.0001)); }

        { RGB<float, sRGB>     rgb {-0.214220,0.484530,0.968603};
          LinearRGB<float, sRGB>                 xyz {-0.037710, 0.200001, 0.930057};
          REQUIRE(static_cast<decltype(xyz)>    (rgb)   == rel_equal(xyz, gaudy::epsilon, 0.0001));
          REQUIRE((static_cast<decltype(rgb)>(xyz))  == rel_equal(rgb, gaudy::epsilon, 0.0001)); }

        { RGB<float, WideGamutRGB> rgb {0.234925,0.519946,1.068428};
          LinearRGB<float, WideGamutRGB> xyz {0.041309, 0.237196, 1.156750};
          REQUIRE(static_cast<decltype(xyz)>    (rgb)   == rel_equal(xyz, gaudy::epsilon, 0.0001));
          REQUIRE((static_cast<decltype(rgb)>(xyz))  == rel_equal(rgb, gaudy::epsilon, 0.0001)); }
    }

    SECTION("XYZ/RGB conversion (against Bruce Lindblooms color space calculator)") {
        { RGB<float, AppleRGB> rgb {-0.749988, 0.600315, 0.960963};
          XYZ<float>                 xyz {0.03, 0.2, 0.9};
          REQUIRE(static_cast<decltype(xyz)>    (rgb)  == rel_equal(xyz, gaudy::epsilon, 0.0001));
          REQUIRE((static_cast<decltype(rgb)>(xyz))  == rel_equal(rgb, gaudy::epsilon, 0.0001)); }

        { RGB<float, AdobeRGB> rgb {-0.630084, 0.646867, 0.948696};
          XYZ<float>                 xyz {0.03, 0.2, 0.9};
          REQUIRE(static_cast<decltype(xyz)>    (rgb)   == rel_equal(xyz, gaudy::epsilon, 0.0001));
          REQUIRE((static_cast<decltype(rgb)>(xyz))  == rel_equal(rgb, gaudy::epsilon, 0.0001)); }

        { RGB<float, BestRGB>  rgb {-0.553127,0.582417,1.044189};
          XYZ<float>                 xyz {0.03, 0.2, 0.9};
          REQUIRE(static_cast<decltype(xyz)>    (rgb)   == rel_equal(xyz, gaudy::epsilon, 0.0001));
          REQUIRE((static_cast<decltype(rgb)>(xyz))  == rel_equal(rgb, gaudy::epsilon, 0.0001)); }

        { RGB<float, BetaRGB>  rgb {-0.530159,0.627250,1.056539};
          XYZ<float>                 xyz {0.03, 0.2, 0.9};
          REQUIRE(static_cast<decltype(xyz)>    (rgb)   == rel_equal(xyz, gaudy::epsilon, 0.0001));
          REQUIRE((static_cast<decltype(rgb)>(xyz))  == rel_equal(rgb, gaudy::epsilon, 0.0001)); }

        { RGB<float, BruceRGB> rgb {-0.753376,0.646867,0.948153};
          XYZ<float>                 xyz {0.03, 0.2, 0.9};
          REQUIRE(static_cast<decltype(xyz)>    (rgb)   == rel_equal(xyz, gaudy::epsilon, 0.0001));
          REQUIRE((static_cast<decltype(rgb)>(xyz))  == rel_equal(rgb, gaudy::epsilon, 0.0001)); }

        { RGB<float, CIERGB>   rgb {-0.750904,0.620013,0.955966};
          XYZ<float>                 xyz {0.03, 0.2, 0.9};
          REQUIRE(static_cast<decltype(xyz)>    (rgb)   == rel_equal(xyz, gaudy::epsilon, 0.0001));
          REQUIRE((static_cast<decltype(rgb)>(xyz))  == rel_equal(rgb, gaudy::epsilon, 0.0001)); }

        { RGB<float, ColorMatchRGB> rgb {-0.694736,0.595039,1.135352};
          XYZ<float>                 xyz {0.03, 0.2, 0.9};
          REQUIRE(static_cast<decltype(xyz)>    (rgb)   == rel_equal(xyz, gaudy::epsilon, 0.0001));
          REQUIRE((static_cast<decltype(rgb)>(xyz))  == rel_equal(rgb, gaudy::epsilon, 0.0001)); }

        { RGB<float, DonRGB4>  rgb {-0.554315,0.617836,1.050117};
          XYZ<float>                 xyz {0.03, 0.2, 0.9};
          REQUIRE(static_cast<decltype(xyz)>    (rgb)   == rel_equal(xyz, gaudy::epsilon, 0.0001));
          REQUIRE((static_cast<decltype(rgb)>(xyz))  == rel_equal(rgb, gaudy::epsilon, 0.0001)); }

        { RGB<float, ECIRGBv2> rgb {-0.606068,0.646403,1.058212};
          XYZ<float>                 xyz {0.03, 0.2, 0.9};
          REQUIRE(static_cast<decltype(xyz)>    (rgb)   == rel_equal(xyz, gaudy::epsilon, 0.0001));
          REQUIRE((static_cast<decltype(rgb)>(xyz))  == rel_equal(rgb, gaudy::epsilon, 0.0001)); }

        { RGB<float, EktaSpacePS5> rgb {-0.584171,0.639524,1.056725};
          XYZ<float>                 xyz {0.03, 0.2, 0.9};
          REQUIRE(static_cast<decltype(xyz)>    (rgb)   == rel_equal(xyz, gaudy::epsilon, 0.0001));
          REQUIRE((static_cast<decltype(rgb)>(xyz))  == rel_equal(rgb, gaudy::epsilon, 0.0001)); }

        { RGB<float, NTSCRGB>  rgb {-0.585995,0.616329,0.896257};
          XYZ<float>                 xyz {0.03, 0.2, 0.9};
          REQUIRE(static_cast<decltype(xyz)>    (rgb)   == rel_equal(xyz, gaudy::epsilon, 0.0001));
          REQUIRE((static_cast<decltype(rgb)>(xyz))  == rel_equal(rgb, gaudy::epsilon, 0.0001)); }

        { RGB<float, PALSECAMRGB>  rgb {-0.801697,0.646867,0.962180};
          XYZ<float>                 xyz {0.03, 0.2, 0.9};
          REQUIRE(static_cast<decltype(xyz)>    (rgb)   == rel_equal(xyz, gaudy::epsilon, 0.0001));
          REQUIRE((static_cast<decltype(rgb)>(xyz))  == rel_equal(rgb, gaudy::epsilon, 0.0001)); }

        { RGB<float, ProPhotoRGB> rgb {-0.203111,0.515859,1.049379};
          XYZ<float>                 xyz {0.03, 0.2, 0.9};
          REQUIRE(static_cast<decltype(xyz)>    (rgb)   == rel_equal(xyz, gaudy::epsilon, 0.0001));
          REQUIRE((static_cast<decltype(rgb)>(xyz))  == rel_equal(rgb, gaudy::epsilon, 0.0001)); }

        { RGB<float, SMPTE_C>  rgb {-0.867953,0.655706,0.956825};
          XYZ<float>                 xyz {0.03, 0.2, 0.9};
          REQUIRE(static_cast<decltype(xyz)>    (rgb)   == rel_equal(xyz, gaudy::epsilon, 0.0001));
          REQUIRE((static_cast<decltype(rgb)>(xyz))  == rel_equal(rgb, gaudy::epsilon, 0.0001)); }

        { RGB<float, sRGB>     rgb {-0.831663,0.652674,0.960445};
          XYZ<float>                 xyz {0.03, 0.2, 0.9};
          REQUIRE(static_cast<decltype(xyz)>    (rgb)   == rel_equal(xyz, gaudy::epsilon, 0.0001));
          REQUIRE((static_cast<decltype(rgb)>(xyz))  == rel_equal(rgb, gaudy::epsilon, 0.0001)); }

        { RGB<float, WideGamutRGB> rgb {-0.522585,0.608080,1.061892};
          XYZ<float>                 xyz {0.03, 0.2, 0.9};
          REQUIRE(static_cast<decltype(xyz)>    (rgb)   == rel_equal(xyz, gaudy::epsilon, 0.0001));
          REQUIRE((static_cast<decltype(rgb)>(xyz))  == rel_equal(rgb, gaudy::epsilon, 0.0001)); }
    }

}

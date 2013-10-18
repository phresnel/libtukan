// (C) 2013 Sebastian Mach (1983), this file is published under the terms of the
// GNU General Public License, Version 3 (a.k.a. GPLv3).
// See COPYING in the root-folder of the excygen project folder.
#ifndef RGB_HH_INCLUDED_20131017
#define RGB_HH_INCLUDED_20131017

#include "rel_equal.hh"

namespace gaudy {

    //---------------------------------------------------------------------------------------------
    // RGB
    //---------------------------------------------------------------------------------------------

    // -- structure -------------------------------------------------------------------------------
    struct RGB {
        float r=0, g=0, b=0;

        constexpr RGB() noexcept = default;
        constexpr RGB(float r, float g, float b) noexcept : r(r), g(g), b(b) {}

        RGB& operator+= (RGB rhs) noexcept;
        RGB& operator-= (RGB rhs) noexcept;
        RGB& operator*= (RGB rhs) noexcept;
        RGB& operator/= (RGB rhs) noexcept;

        RGB& operator+= (float rhs) noexcept;
        RGB& operator-= (float rhs) noexcept;
        RGB& operator*= (float rhs) noexcept;
        RGB& operator/= (float rhs) noexcept;
    };


    // -- relation --------------------------------------------------------------------------------
    constexpr bool operator== (RGB lhs, RGB rhs) noexcept;
    constexpr bool operator!= (RGB lhs, RGB rhs) noexcept;
    constexpr bool rel_equal (RGB lhs, RGB rhs,
                              float max_rel_diff=std::numeric_limits<float>::epsilon() ) noexcept;
}

#include <ostream>
namespace gaudy {

    // -- arithmetics -----------------------------------------------------------------------------
    constexpr RGB operator+ (RGB lhs, RGB rhs) noexcept;
    constexpr RGB operator- (RGB lhs, RGB rhs) noexcept;
    constexpr RGB operator* (RGB lhs, RGB rhs) noexcept;
    constexpr RGB operator/ (RGB lhs, RGB rhs) noexcept;

    constexpr RGB operator+ (RGB lhs, float rhs) noexcept;
    constexpr RGB operator- (RGB lhs, float rhs) noexcept;
    constexpr RGB operator* (RGB lhs, float rhs) noexcept;
    constexpr RGB operator/ (RGB lhs, float rhs) noexcept;

    constexpr RGB operator+ (float lhs, RGB rhs) noexcept;
    constexpr RGB operator- (float lhs, RGB rhs) noexcept;
    constexpr RGB operator* (float lhs, RGB rhs) noexcept;
    constexpr RGB operator/ (float lhs, RGB rhs) noexcept;

}


#include <cmath>
namespace gaudy {

    // -- <cmath> ---------------------------------------------------------------------------------


    //-- -- -- -- --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  -- --
    // Info: While glibcxx defines some (many? (all?)) cmath functions as constexpr, this is not
    //       sanctioned  by  the  C++11  standard,  therefore we are not making the  promise  of
    //       constexpr, as such code is non-portable.
    //-- -- -- -- --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  -- --


    // trigonometric
    inline RGB cos(RGB v) noexcept { return RGB{std::cos(v.r), std::cos(v.g), std::cos(v.b)}; }
    inline RGB sin(RGB v) noexcept { return RGB{std::sin(v.r), std::sin(v.g), std::sin(v.b)}; }
    inline RGB tan(RGB v) noexcept { return RGB{std::tan(v.r), std::tan(v.g), std::tan(v.b)}; }
    inline RGB acos(RGB v) noexcept { return RGB{std::acos(v.r), std::acos(v.g), std::acos(v.b)}; }
    inline RGB asin(RGB v) noexcept { return RGB{std::asin(v.r), std::asin(v.g), std::asin(v.b)}; }
    inline RGB atan(RGB v) noexcept { return RGB{std::atan(v.r), std::atan(v.g), std::atan(v.b)}; }
    inline RGB atan2(RGB v, RGB w) noexcept { return RGB{std::atan2(v.r,w.r),
                                                         std::atan2(v.g,w.g),
                                                         std::atan2(v.b,w.b)}; }

    // hyperbolic
    inline RGB cosh(RGB v) noexcept { return RGB{std::cosh(v.r), std::cosh(v.g), std::cosh(v.b)}; }
    inline RGB sinh(RGB v) noexcept { return RGB{std::sinh(v.r), std::sinh(v.g), std::sinh(v.b)}; }
    inline RGB tanh(RGB v) noexcept { return RGB{std::tanh(v.r), std::tanh(v.g), std::tanh(v.b)}; }
    inline RGB acosh(RGB v) noexcept { return RGB{std::acosh(v.r), std::acosh(v.g), std::acosh(v.b)}; }
    inline RGB asinh(RGB v) noexcept { return RGB{std::asinh(v.r), std::asinh(v.g), std::asinh(v.b)}; }
    inline RGB atanh(RGB v) noexcept { return RGB{std::atanh(v.r), std::atanh(v.g), std::atanh(v.b)}; }

    // exponential and logarithmic

    // power

    // error and gamma

    // rounding and remainder

    // floating point manipulation

    // min, max, difference

    // other

    // classification functions

    // comparison functions


    //---------------------------------------------------------------------------------------------
    // implementation
    //---------------------------------------------------------------------------------------------
    inline RGB& RGB::operator+= (RGB rhs) noexcept {
        r += rhs.r;
        g += rhs.g;
        b += rhs.b;
        return *this;
    }

    inline RGB& RGB::operator-= (RGB rhs) noexcept {
        r -= rhs.r;
        g -= rhs.g;
        b -= rhs.b;
        return *this;
    }

    inline RGB& RGB::operator*= (RGB rhs) noexcept {
        r *= rhs.r;
        g *= rhs.g;
        b *= rhs.b;
        return *this;
    }

    inline RGB& RGB::operator/= (RGB rhs) noexcept {
        r /= rhs.r;
        g /= rhs.g;
        b /= rhs.b;
        return *this;
    }

    inline RGB& RGB::operator+= (float rhs) noexcept {
        r += rhs;
        g += rhs;
        b += rhs;
        return *this;
    }

    inline RGB& RGB::operator-= (float rhs) noexcept {
        r -= rhs;
        g -= rhs;
        b -= rhs;
        return *this;
    }

    inline RGB& RGB::operator*= (float rhs) noexcept {
        r *= rhs;
        g *= rhs;
        b *= rhs;
        return *this;
    }

    inline RGB& RGB::operator/= (float rhs) noexcept {
        r /= rhs;
        g /= rhs;
        b /= rhs;
        return *this;
    }


    // relation
    constexpr bool operator== (RGB lhs, RGB rhs) noexcept {
        return lhs.r==rhs.r && lhs.g==rhs.g && lhs.b==rhs.b;
    }
    constexpr bool operator!= (RGB lhs, RGB rhs) noexcept {
        return !(lhs == rhs);
    }
    constexpr bool rel_equal (RGB lhs, RGB rhs, float max_rel_diff) noexcept
    {
        return rel_equal (lhs.r, rhs.r, max_rel_diff)
            && rel_equal (lhs.g, rhs.g, max_rel_diff)
            && rel_equal (lhs.b, rhs.b, max_rel_diff)
        ;
    }


    // arithmetics
    constexpr RGB operator+ (RGB lhs, RGB rhs) noexcept {
        return {lhs.r+rhs.r, lhs.g+rhs.g, lhs.b+rhs.b};
    }
    constexpr RGB operator- (RGB lhs, RGB rhs) noexcept {
        return {lhs.r-rhs.r, lhs.g-rhs.g, lhs.b-rhs.b};
    }
    constexpr RGB operator* (RGB lhs, RGB rhs) noexcept {
        return {lhs.r*rhs.r, lhs.g*rhs.g, lhs.b*rhs.b};
    }
    constexpr RGB operator/ (RGB lhs, RGB rhs) noexcept {
        return {lhs.r/rhs.r, lhs.g/rhs.g, lhs.b/rhs.b};
    }

    constexpr RGB operator+ (RGB lhs, float rhs) noexcept {
        return {lhs.r+rhs, lhs.g+rhs, lhs.b+rhs};
    }
    constexpr RGB operator- (RGB lhs, float rhs) noexcept {
        return {lhs.r-rhs, lhs.g-rhs, lhs.b-rhs};
    }
    constexpr RGB operator* (RGB lhs, float rhs) noexcept {
        return {lhs.r*rhs, lhs.g*rhs, lhs.b*rhs};
    }
    constexpr RGB operator/ (RGB lhs, float rhs) noexcept {
        return {lhs.r/rhs, lhs.g/rhs, lhs.b/rhs};
    }

    constexpr RGB operator+ (float lhs, RGB rhs) noexcept {
        return {lhs+rhs.r, lhs+rhs.g, lhs+rhs.b};
    }
    constexpr RGB operator- (float lhs, RGB rhs) noexcept {
        return {lhs-rhs.r, lhs-rhs.g, lhs-rhs.b};
    }
    constexpr RGB operator* (float lhs, RGB rhs) noexcept {
        return {lhs*rhs.r, lhs*rhs.g, lhs*rhs.b};
    }
    constexpr RGB operator/ (float lhs, RGB rhs) noexcept {
        return {lhs/rhs.r, lhs/rhs.g, lhs/rhs.b};
    }
}

#endif // RGB_HH_INCLUDED_20131017

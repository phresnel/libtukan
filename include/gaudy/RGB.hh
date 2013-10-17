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

    // structure
    struct RGB {
        float r=0, g=0, b=0;

        constexpr RGB() noexcept = default;
        constexpr RGB(float r, float g, float b) noexcept : r(r), g(g), b(b) {}

        RGB& operator+= (RGB const &rhs) noexcept;
        RGB& operator-= (RGB const &rhs) noexcept;
        RGB& operator*= (RGB const &rhs) noexcept;
        RGB& operator/= (RGB const &rhs) noexcept;

        RGB& operator+= (float rhs) noexcept;
        RGB& operator-= (float rhs) noexcept;
        RGB& operator*= (float rhs) noexcept;
        RGB& operator/= (float rhs) noexcept;
    };


    // relation
    constexpr bool operator== (RGB const &lhs, RGB const &rhs) noexcept;
    constexpr bool operator!= (RGB const &lhs, RGB const &rhs) noexcept;
    inline bool rel_equal (RGB const &lhs, RGB const &rhs,
                           float max_rel_diff=std::numeric_limits<float>::epsilon()
                          ) noexcept;

    // arithmetics
    constexpr RGB operator+ (RGB const &lhs, RGB const &rhs) noexcept;
    constexpr RGB operator- (RGB const &lhs, RGB const &rhs) noexcept;
    constexpr RGB operator* (RGB const &lhs, RGB const &rhs) noexcept;
    constexpr RGB operator/ (RGB const &lhs, RGB const &rhs) noexcept;

    constexpr RGB operator+ (RGB const &lhs, float rhs) noexcept;
    constexpr RGB operator- (RGB const &lhs, float rhs) noexcept;
    constexpr RGB operator* (RGB const &lhs, float rhs) noexcept;
    constexpr RGB operator/ (RGB const &lhs, float rhs) noexcept;

    constexpr RGB operator+ (float lhs, RGB const &rhs) noexcept;
    constexpr RGB operator- (float lhs, RGB const &rhs) noexcept;
    constexpr RGB operator* (float lhs, RGB const &rhs) noexcept;
    constexpr RGB operator/ (float lhs, RGB const &rhs) noexcept;






    //---------------------------------------------------------------------------------------------
    // implementation
    //---------------------------------------------------------------------------------------------
    inline RGB& RGB::operator+= (RGB const &rhs) noexcept {
        r += rhs.r;
        g += rhs.g;
        b += rhs.b;
        return *this;
    }

    inline RGB& RGB::operator-= (RGB const &rhs) noexcept {
        r -= rhs.r;
        g -= rhs.g;
        b -= rhs.b;
        return *this;
    }

    inline RGB& RGB::operator*= (RGB const &rhs) noexcept {
        r *= rhs.r;
        g *= rhs.g;
        b *= rhs.b;
        return *this;
    }

    inline RGB& RGB::operator/= (RGB const &rhs) noexcept {
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
    constexpr bool operator== (RGB const &lhs, RGB const &rhs) noexcept {
        return lhs.r==rhs.r && lhs.g==rhs.g && lhs.b==rhs.b;
    }
    constexpr bool operator!= (RGB const &lhs, RGB const &rhs) noexcept {
        return !(lhs == rhs);
    }
    inline bool rel_equal (RGB const &lhs, RGB const &rhs, float max_rel_diff) noexcept
    {
        return rel_equal (lhs.r, rhs.r, max_rel_diff)
            && rel_equal (lhs.g, rhs.g, max_rel_diff)
            && rel_equal (lhs.b, rhs.b, max_rel_diff)
        ;
    }


    // arithmetics
    constexpr RGB operator+ (RGB const &lhs, RGB const &rhs) noexcept {
        return {lhs.r+rhs.r, lhs.g+rhs.g, lhs.b+rhs.b};
    }
    constexpr RGB operator- (RGB const &lhs, RGB const &rhs) noexcept {
        return {lhs.r-rhs.r, lhs.g-rhs.g, lhs.b-rhs.b};
    }
    constexpr RGB operator* (RGB const &lhs, RGB const &rhs) noexcept {
        return {lhs.r*rhs.r, lhs.g*rhs.g, lhs.b*rhs.b};
    }
    constexpr RGB operator/ (RGB const &lhs, RGB const &rhs) noexcept {
        return {lhs.r/rhs.r, lhs.g/rhs.g, lhs.b/rhs.b};
    }

    constexpr RGB operator+ (RGB const &lhs, float rhs) noexcept {
        return {lhs.r+rhs, lhs.g+rhs, lhs.b+rhs};
    }
    constexpr RGB operator- (RGB const &lhs, float rhs) noexcept {
        return {lhs.r-rhs, lhs.g-rhs, lhs.b-rhs};
    }
    constexpr RGB operator* (RGB const &lhs, float rhs) noexcept {
        return {lhs.r*rhs, lhs.g*rhs, lhs.b*rhs};
    }
    constexpr RGB operator/ (RGB const &lhs, float rhs) noexcept {
        return {lhs.r/rhs, lhs.g/rhs, lhs.b/rhs};
    }

    constexpr RGB operator+ (float lhs, RGB const &rhs) noexcept {
        return {lhs+rhs.r, lhs+rhs.g, lhs+rhs.b};
    }
    constexpr RGB operator- (float lhs, RGB const &rhs) noexcept {
        return {lhs-rhs.r, lhs-rhs.g, lhs-rhs.b};
    }
    constexpr RGB operator* (float lhs, RGB const &rhs) noexcept {
        return {lhs*rhs.r, lhs*rhs.g, lhs*rhs.b};
    }
    constexpr RGB operator/ (float lhs, RGB const &rhs) noexcept {
        return {lhs/rhs.r, lhs/rhs.g, lhs/rhs.b};
    }
}

#endif // RGB_HH_INCLUDED_20131017

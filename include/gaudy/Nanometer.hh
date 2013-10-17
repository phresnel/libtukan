// (C) 2013 Sebastian Mach (1983), this file is published under the terms of the
// GNU General Public License, Version 3 (a.k.a. GPLv3).
// See COPYING in the root-folder of the excygen project folder.
#ifndef NANOMETER_HH_INCLUDED_20131017
#define NANOMETER_HH_INCLUDED_20131017

#include <limits>
#include "rel_equal.hh"

namespace gaudy {
    //----------------------------------------------------------------------------------------------
    // Nanometer
    //----------------------------------------------------------------------------------------------
    struct Nanometer {
        constexpr explicit Nanometer (float nm=0) noexcept : nm_(nm) {}
        constexpr explicit operator float() noexcept { return nm_; }

        Nanometer& operator+= (Nanometer rhs) noexcept { nm_+=rhs.nm_; return *this; }
        Nanometer& operator-= (Nanometer rhs) noexcept { nm_-=rhs.nm_; return *this; }
        Nanometer& operator*= (Nanometer rhs) noexcept { nm_*=rhs.nm_; return *this; }
        Nanometer& operator/= (Nanometer rhs) noexcept { nm_/=rhs.nm_; return *this; }

        Nanometer& operator+= (float rhs) noexcept { nm_+=rhs; return *this; }
        Nanometer& operator-= (float rhs) noexcept { nm_-=rhs; return *this; }
        Nanometer& operator*= (float rhs) noexcept { nm_*=rhs; return *this; }
        Nanometer& operator/= (float rhs) noexcept { nm_/=rhs; return *this; }
    private:
        float nm_;
    };

    // relation
    constexpr inline bool operator== (Nanometer lhs, Nanometer rhs) noexcept {
        return static_cast<float>(lhs) == static_cast<float>(rhs);
    }
    constexpr inline bool operator!= (Nanometer lhs, Nanometer rhs) noexcept {
        return !(lhs == rhs);
    }
    inline bool rel_equal (Nanometer lhs, Nanometer rhs,
                    float max_rel_diff=std::numeric_limits<float>::epsilon())
    {
        return rel_equal (static_cast<float>(lhs), static_cast<float>(rhs), max_rel_diff);
    }

    constexpr inline bool operator> (Nanometer lhs, Nanometer rhs) noexcept {
        return static_cast<float>(lhs) > static_cast<float>(rhs);
    }
    constexpr inline bool operator< (Nanometer lhs, Nanometer rhs) noexcept {
        return static_cast<float>(lhs) < static_cast<float>(rhs);
    }
    constexpr inline bool operator>= (Nanometer lhs, Nanometer rhs) noexcept {
        return static_cast<float>(lhs) >= static_cast<float>(rhs);
    }
    constexpr inline bool operator<= (Nanometer lhs, Nanometer rhs) noexcept {
        return static_cast<float>(lhs) <= static_cast<float>(rhs);
    }

    // arithmetic
    constexpr inline Nanometer operator+ (Nanometer rhs) noexcept {
        return rhs;
    }
    constexpr inline Nanometer operator- (Nanometer rhs) noexcept {
        return Nanometer(-static_cast<float>(rhs));
    }

    constexpr inline Nanometer operator+ (Nanometer lhs, Nanometer rhs) noexcept {
        return Nanometer(static_cast<float>(lhs) + static_cast<float>(rhs));
    }
    constexpr inline Nanometer operator+ (float lhs, Nanometer rhs) noexcept {
        return Nanometer(lhs + static_cast<float>(rhs));
    }
    constexpr inline Nanometer operator+ (Nanometer lhs, float rhs) noexcept {
        return Nanometer(static_cast<float>(lhs) + rhs);
    }

    constexpr inline Nanometer operator- (Nanometer lhs, Nanometer rhs) noexcept {
        return Nanometer(static_cast<float>(lhs) - static_cast<float>(rhs));
    }
    constexpr inline Nanometer operator- (float lhs, Nanometer rhs) noexcept {
        return Nanometer(lhs - static_cast<float>(rhs));
    }
    constexpr inline Nanometer operator- (Nanometer lhs, float rhs) noexcept {
        return Nanometer(static_cast<float>(lhs) - rhs);
    }

    constexpr inline Nanometer operator* (Nanometer lhs, Nanometer rhs) noexcept {
        return Nanometer(static_cast<float>(lhs) * static_cast<float>(rhs));
    }
    constexpr inline Nanometer operator* (float lhs, Nanometer rhs) noexcept {
        return Nanometer(lhs * static_cast<float>(rhs));
    }
    constexpr inline Nanometer operator* (Nanometer lhs, float rhs) noexcept {
        return Nanometer(static_cast<float>(lhs) * rhs);
    }

    constexpr inline Nanometer operator/ (Nanometer lhs, Nanometer rhs) noexcept {
        return Nanometer(static_cast<float>(lhs) / static_cast<float>(rhs));
    }
    constexpr inline Nanometer operator/ (float lhs, Nanometer rhs) noexcept {
        return Nanometer(lhs / static_cast<float>(rhs));
    }
    constexpr inline Nanometer operator/ (Nanometer lhs, float rhs) noexcept {
        return Nanometer(static_cast<float>(lhs) / rhs);
    }

    // literals ------------------------------------------------------------------------------------
    inline constexpr Nanometer operator"" _nm (long double nm) noexcept {
        return Nanometer(nm);
    }
    inline constexpr Nanometer operator"" _nm (unsigned long long nm) noexcept {
        return Nanometer(nm);
    }
}

#endif // NANOMETER_HH_INCLUDED_20131017

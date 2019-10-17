// (C) 2013 Sebastian Mach (1983), this file is published under the terms of the
// GNU General Public License, Version 3 (a.k.a. GPLv3).
// See COPYING in the root-folder of the excygen project folder.
#ifndef LINEARRGB_HH_INCLUDED_20131017
#define LINEARRGB_HH_INCLUDED_20131017

#include "algorithm/rel_equal.hh"
#include "traits/traits.hh"
#include <functional>
#include <algorithm>
#include <cmath>
#include <stdexcept>
#include "RGBSpace.hh"
#include "XYZ.hh"

namespace tukan {

    //---------------------------------------------------------------------------------------------
    // RGB
    // ---
    //
    // About
    // -----
    // LinearRGB represents a working color which you can add, subtract, multiply et cetera.
    // The gamma value for a linear RGB is 1, even though the associated color space might have
    // non-linear gamma. If you later want to write an image-file with proper non-linear RGB,
    // like an sRGB file, you must first convert to (nonlinear) RGB, which is then gamma-corrected.
    //
    // Meta
    // ----
    // Using -O3, benchmarks/IndexingOperator.cc shows that there is no performance difference
    // between indexing and direct member access with 'g++ (Ubuntu/Linaro 4.7.3-1ubuntu1) 4.7.3'.
    //---------------------------------------------------------------------------------------------

    // -- structure -------------------------------------------------------------------------------
    template <typename T, template <typename> class RGBSpace>
    struct LinearRGB {

        // Data.
        T r=T(0), g=T(0), b=T(0);


        // Construction.
        constexpr LinearRGB() noexcept : r(T(0)), g(T(0)), b(T(0)) {}
        constexpr LinearRGB(T r, T g, T b) noexcept : r(r), g(g), b(b) {}
        constexpr explicit LinearRGB(T f) noexcept  : r(f), g(f), b(f) {}


        // Conversion.
        constexpr explicit operator XYZ<T> () noexcept;
        constexpr explicit LinearRGB (XYZ<T>) noexcept;


        // Assignment.
        LinearRGB& operator+= (LinearRGB rhs) noexcept;
        LinearRGB& operator-= (LinearRGB rhs) noexcept;
        LinearRGB& operator*= (LinearRGB rhs) noexcept;
        LinearRGB& operator/= (LinearRGB rhs) noexcept;

        LinearRGB& operator+= (T rhs) noexcept;
        LinearRGB& operator-= (T rhs) noexcept;
        LinearRGB& operator*= (T rhs) noexcept;
        LinearRGB& operator/= (T rhs) noexcept;


        // Array interface.
        constexpr T  at         (size_t idx) const ;
        constexpr T  operator[] (size_t idx) const noexcept;
        T& at         (size_t idx) ;
        T& operator[] (size_t idx) noexcept;

        constexpr size_t size() const noexcept ; // Always "3".


        // Meta.
        using value_type = T;
        template <typename N> using rebind_value_type = LinearRGB<N, RGBSpace>;


    private:
        static T LinearRGB::* const offsets_[3];
    };


    template <typename T, template <typename> class RGBSpace>
    constexpr size_t size(LinearRGB<T, RGBSpace> const &v) noexcept { return v.size(); }


    // -- relation --------------------------------------------------------------------------------
    template <typename T, template <typename> class RGBSpace> constexpr bool operator== (LinearRGB<T, RGBSpace> lhs, LinearRGB<T, RGBSpace> rhs) noexcept;
    template <typename T, template <typename> class RGBSpace> constexpr bool operator!= (LinearRGB<T, RGBSpace> lhs, LinearRGB<T, RGBSpace> rhs) noexcept;
    template <typename T, template <typename> class RGBSpace> constexpr bool rel_equal (LinearRGB<T, RGBSpace> lhs, LinearRGB<T, RGBSpace> rhs,
                                                    T max_rel_diff=std::numeric_limits<T>::epsilon() ) noexcept;

    // -- sign ------------------------------------------------------------------------------------
    template <typename T, template <typename> class RGBSpace> constexpr LinearRGB<T, RGBSpace> operator- (LinearRGB<T, RGBSpace> rhs) noexcept { return {-rhs.r, -rhs.g, -rhs.b}; }
    template <typename T, template <typename> class RGBSpace> constexpr LinearRGB<T, RGBSpace> operator+ (LinearRGB<T, RGBSpace> rhs) noexcept { return rhs; }

    // -- arithmetics -----------------------------------------------------------------------------
    template <typename T, template <typename> class RGBSpace> constexpr LinearRGB<T, RGBSpace> operator+ (LinearRGB<T, RGBSpace> lhs, LinearRGB<T, RGBSpace> rhs) noexcept;
    template <typename T, template <typename> class RGBSpace> constexpr LinearRGB<T, RGBSpace> operator- (LinearRGB<T, RGBSpace> lhs, LinearRGB<T, RGBSpace> rhs) noexcept;
    template <typename T, template <typename> class RGBSpace> constexpr LinearRGB<T, RGBSpace> operator* (LinearRGB<T, RGBSpace> lhs, LinearRGB<T, RGBSpace> rhs) noexcept;
    template <typename T, template <typename> class RGBSpace> constexpr LinearRGB<T, RGBSpace> operator/ (LinearRGB<T, RGBSpace> lhs, LinearRGB<T, RGBSpace> rhs) noexcept;

    template <typename T, template <typename> class RGBSpace> constexpr LinearRGB<T, RGBSpace> operator+ (LinearRGB<T, RGBSpace> lhs, typename LinearRGB<T, RGBSpace>::value_type rhs) noexcept;
    template <typename T, template <typename> class RGBSpace> constexpr LinearRGB<T, RGBSpace> operator- (LinearRGB<T, RGBSpace> lhs, typename LinearRGB<T, RGBSpace>::value_type rhs) noexcept;
    template <typename T, template <typename> class RGBSpace> constexpr LinearRGB<T, RGBSpace> operator* (LinearRGB<T, RGBSpace> lhs, typename LinearRGB<T, RGBSpace>::value_type rhs) noexcept;
    template <typename T, template <typename> class RGBSpace> constexpr LinearRGB<T, RGBSpace> operator/ (LinearRGB<T, RGBSpace> lhs, typename LinearRGB<T, RGBSpace>::value_type rhs) noexcept;

    template <typename T, template <typename> class RGBSpace> constexpr LinearRGB<T, RGBSpace> operator+ (typename LinearRGB<T, RGBSpace>::value_type lhs, LinearRGB<T, RGBSpace> rhs) noexcept;
    template <typename T, template <typename> class RGBSpace> constexpr LinearRGB<T, RGBSpace> operator- (typename LinearRGB<T, RGBSpace>::value_type lhs, LinearRGB<T, RGBSpace> rhs) noexcept;
    template <typename T, template <typename> class RGBSpace> constexpr LinearRGB<T, RGBSpace> operator* (typename LinearRGB<T, RGBSpace>::value_type lhs, LinearRGB<T, RGBSpace> rhs) noexcept;
    template <typename T, template <typename> class RGBSpace> constexpr LinearRGB<T, RGBSpace> operator/ (typename LinearRGB<T, RGBSpace>::value_type lhs, LinearRGB<T, RGBSpace> rhs) noexcept;

    // -- algorithms ------------------------------------------------------------------------------
    // Note: we do not offer constexpr were the C++11 <algorithms> library does neither.
    // Note: these are implemented here instead of algorithms.hh, and directly in terms of LinearRGB,
    //       because otherwise they are ambiguous wrt std::min and std::max.
    template <typename T, template <typename> class RGBSpace> LinearRGB<T, RGBSpace> min (LinearRGB<T, RGBSpace> lhs, LinearRGB<T, RGBSpace> rhs) noexcept;
    template <typename T, template <typename> class RGBSpace> LinearRGB<T, RGBSpace> min (typename LinearRGB<T, RGBSpace>::value_type lhs, LinearRGB<T, RGBSpace> rhs) noexcept;
    template <typename T, template <typename> class RGBSpace> LinearRGB<T, RGBSpace> min (LinearRGB<T, RGBSpace> lhs, typename LinearRGB<T, RGBSpace>::value_type rhs) noexcept;

    template <typename T, template <typename> class RGBSpace> LinearRGB<T, RGBSpace> max (LinearRGB<T, RGBSpace> lhs, LinearRGB<T, RGBSpace> rhs) noexcept;
    template <typename T, template <typename> class RGBSpace> LinearRGB<T, RGBSpace> max (typename LinearRGB<T, RGBSpace>::value_type lhs, LinearRGB<T, RGBSpace> rhs) noexcept;
    template <typename T, template <typename> class RGBSpace> LinearRGB<T, RGBSpace> max (LinearRGB<T, RGBSpace> lhs, typename LinearRGB<T, RGBSpace>::value_type rhs) noexcept;

}

#include "inl/LinearRGB.inl.hh"
#include "cmath.hh"

#endif // LINEARRGB_HH_INCLUDED_20131017

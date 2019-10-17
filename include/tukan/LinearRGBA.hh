// (C) 2013 Sebastian Mach (1983), this file is published under the terms of the
// GNU General Public License, Version 3 (a.k.a. GPLv3).
// See COPYING in the root-folder of the excygen project folder.
#ifndef LINEARRGBA_HH_INCLUDED_20181205
#define LINEARRGBA_HH_INCLUDED_20181205

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
    // RGBA
    // ----
    //
    // About
    // -----
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
    struct LinearRGBA {

        // Data.
        T r=T(0), g=T(0), b=T(0), a=T(0);


        // Construction.
        constexpr LinearRGBA() noexcept : r(T(0)), g(T(0)), b(T(0)), a(T(0)) {}
        constexpr LinearRGBA(T r, T g, T b, T alpha) noexcept : r(r), g(g), b(b), a(alpha) {}


        // Conversion.
        // TODO: Find a meaningful conversion. Probably it'll be a plain old
        //       function/ctor, like 'auto col = LinearRGBA::FromXYZ(xyz, 1.0)'


        // Assignment.
        LinearRGBA& operator+= (LinearRGBA rhs) noexcept;
        LinearRGBA& operator-= (LinearRGBA rhs) noexcept;
        LinearRGBA& operator*= (LinearRGBA rhs) noexcept;
        LinearRGBA& operator/= (LinearRGBA rhs) noexcept;

        LinearRGBA& operator+= (T rhs) noexcept;
        LinearRGBA& operator-= (T rhs) noexcept;
        LinearRGBA& operator*= (T rhs) noexcept;
        LinearRGBA& operator/= (T rhs) noexcept;


        // Array interface.
        constexpr T  at         (size_t idx) const ;
        constexpr T  operator[] (size_t idx) const noexcept;
        T& at         (size_t idx) ;
        T& operator[] (size_t idx) noexcept;

        constexpr size_t size() const noexcept ; // Always "4".


        // Meta.
        using value_type = T;
        template <typename N> using rebind_value_type = LinearRGBA<N, RGBSpace>;


    private:
        static T LinearRGBA::* const offsets_[4];
    };


    template <typename T, template <typename> class RGBSpace>
    constexpr size_t size(LinearRGBA<T, RGBSpace> const &v) noexcept { return v.size(); }


    // -- relation --------------------------------------------------------------------------------
    template <typename T, template <typename> class RGBSpace> constexpr bool operator== (LinearRGBA<T, RGBSpace> lhs, LinearRGBA<T, RGBSpace> rhs) noexcept;
    template <typename T, template <typename> class RGBSpace> constexpr bool operator!= (LinearRGBA<T, RGBSpace> lhs, LinearRGBA<T, RGBSpace> rhs) noexcept;
    template <typename T, template <typename> class RGBSpace> constexpr bool rel_equal  (LinearRGBA<T, RGBSpace> lhs, LinearRGBA<T, RGBSpace> rhs,
                                                    T max_rel_diff=std::numeric_limits<T>::epsilon() ) noexcept;


    // -- sign ------------------------------------------------------------------------------------
    template <typename T, template <typename> class RGBSpace> constexpr LinearRGBA<T, RGBSpace> operator- (LinearRGBA<T, RGBSpace> rhs) noexcept { return {-rhs.r, -rhs.g, -rhs.b}; }
    template <typename T, template <typename> class RGBSpace> constexpr LinearRGBA<T, RGBSpace> operator+ (LinearRGBA<T, RGBSpace> rhs) noexcept { return rhs; }

    // -- arithmetics -----------------------------------------------------------------------------
    template <typename T, template <typename> class RGBSpace> constexpr LinearRGBA<T, RGBSpace> operator+ (LinearRGBA<T, RGBSpace> lhs, LinearRGBA<T, RGBSpace> rhs) noexcept;
    template <typename T, template <typename> class RGBSpace> constexpr LinearRGBA<T, RGBSpace> operator- (LinearRGBA<T, RGBSpace> lhs, LinearRGBA<T, RGBSpace> rhs) noexcept;
    template <typename T, template <typename> class RGBSpace> constexpr LinearRGBA<T, RGBSpace> operator* (LinearRGBA<T, RGBSpace> lhs, LinearRGBA<T, RGBSpace> rhs) noexcept;
    template <typename T, template <typename> class RGBSpace> constexpr LinearRGBA<T, RGBSpace> operator/ (LinearRGBA<T, RGBSpace> lhs, LinearRGBA<T, RGBSpace> rhs) noexcept;

    template <typename T, template <typename> class RGBSpace> constexpr LinearRGBA<T, RGBSpace> operator+ (LinearRGBA<T, RGBSpace> lhs, typename LinearRGBA<T, RGBSpace>::value_type rhs) noexcept;
    template <typename T, template <typename> class RGBSpace> constexpr LinearRGBA<T, RGBSpace> operator- (LinearRGBA<T, RGBSpace> lhs, typename LinearRGBA<T, RGBSpace>::value_type rhs) noexcept;
    template <typename T, template <typename> class RGBSpace> constexpr LinearRGBA<T, RGBSpace> operator* (LinearRGBA<T, RGBSpace> lhs, typename LinearRGBA<T, RGBSpace>::value_type rhs) noexcept;
    template <typename T, template <typename> class RGBSpace> constexpr LinearRGBA<T, RGBSpace> operator/ (LinearRGBA<T, RGBSpace> lhs, typename LinearRGBA<T, RGBSpace>::value_type rhs) noexcept;

    template <typename T, template <typename> class RGBSpace> constexpr LinearRGBA<T, RGBSpace> operator+ (typename LinearRGBA<T, RGBSpace>::value_type lhs, LinearRGBA<T, RGBSpace> rhs) noexcept;
    template <typename T, template <typename> class RGBSpace> constexpr LinearRGBA<T, RGBSpace> operator- (typename LinearRGBA<T, RGBSpace>::value_type lhs, LinearRGBA<T, RGBSpace> rhs) noexcept;
    template <typename T, template <typename> class RGBSpace> constexpr LinearRGBA<T, RGBSpace> operator* (typename LinearRGBA<T, RGBSpace>::value_type lhs, LinearRGBA<T, RGBSpace> rhs) noexcept;
    template <typename T, template <typename> class RGBSpace> constexpr LinearRGBA<T, RGBSpace> operator/ (typename LinearRGBA<T, RGBSpace>::value_type lhs, LinearRGBA<T, RGBSpace> rhs) noexcept;

    // -- algorithms ------------------------------------------------------------------------------
    // Note: we do not offer constexpr were the C++11 <algorithms> library does neither.
    // Note: these are implemented here instead of algorithms.hh, and directly in terms of LinearRGBA,
    //       because otherwise they are ambiguous wrt std::min and std::max.
    template <typename T, template <typename> class RGBSpace> LinearRGBA<T, RGBSpace> min (LinearRGBA<T, RGBSpace> lhs, LinearRGBA<T, RGBSpace> rhs) noexcept;
    template <typename T, template <typename> class RGBSpace> LinearRGBA<T, RGBSpace> min (typename LinearRGBA<T, RGBSpace>::value_type lhs, LinearRGBA<T, RGBSpace> rhs) noexcept;
    template <typename T, template <typename> class RGBSpace> LinearRGBA<T, RGBSpace> min (LinearRGBA<T, RGBSpace> lhs, typename LinearRGBA<T, RGBSpace>::value_type rhs) noexcept;

    template <typename T, template <typename> class RGBSpace> LinearRGBA<T, RGBSpace> max (LinearRGBA<T, RGBSpace> lhs, LinearRGBA<T, RGBSpace> rhs) noexcept;
    template <typename T, template <typename> class RGBSpace> LinearRGBA<T, RGBSpace> max (typename LinearRGBA<T, RGBSpace>::value_type lhs, LinearRGBA<T, RGBSpace> rhs) noexcept;
    template <typename T, template <typename> class RGBSpace> LinearRGBA<T, RGBSpace> max (LinearRGBA<T, RGBSpace> lhs, typename LinearRGBA<T, RGBSpace>::value_type rhs) noexcept;

}

#include "inl/LinearRGBA.inl.hh"
#include "cmath.hh"

#endif // LINEARRGBA_HH_INCLUDED_20181205

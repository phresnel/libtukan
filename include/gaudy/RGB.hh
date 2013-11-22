// (C) 2013 Sebastian Mach (1983), this file is published under the terms of the
// GNU General Public License, Version 3 (a.k.a. GPLv3).
// See COPYING in the root-folder of the excygen project folder.
#ifndef RGB_HH_INCLUDED_20131017
#define RGB_HH_INCLUDED_20131017

#include "rel_equal.hh"
#include "traits/traits.hh"
#include <functional>
#include <algorithm>
#include <cmath>
#include <stdexcept>
#include "RGBSpace.hh"

namespace gaudy {

    //---------------------------------------------------------------------------------------------
    // RGB
    // ---
    //
    // About
    // -----
    // Using -O3, benchmarks/IndexingOperator.cc shows that there is no performance difference
    // between indexing and direct member access with 'g++ (Ubuntu/Linaro 4.7.3-1ubuntu1) 4.7.3'.
    //---------------------------------------------------------------------------------------------

    // -- structure -------------------------------------------------------------------------------
    template <typename T, template <typename> class RGBSpace>
    struct basic_rgb {

        // Data.
        T r=0, g=0, b=0;


        // Construction.
        constexpr basic_rgb() noexcept = default;
        constexpr basic_rgb(T r, T g, T b) noexcept : r(r), g(g), b(b) {}
        constexpr explicit basic_rgb(T f) noexcept  : r(f), g(f), b(f) {}


        // Assignment.
        basic_rgb& operator+= (basic_rgb rhs) noexcept;
        basic_rgb& operator-= (basic_rgb rhs) noexcept;
        basic_rgb& operator*= (basic_rgb rhs) noexcept;
        basic_rgb& operator/= (basic_rgb rhs) noexcept;

        basic_rgb& operator+= (T rhs) noexcept;
        basic_rgb& operator-= (T rhs) noexcept;
        basic_rgb& operator*= (T rhs) noexcept;
        basic_rgb& operator/= (T rhs) noexcept;


        // Array interface.
        constexpr T  at         (size_t idx) const ;
        constexpr T  operator[] (size_t idx) const noexcept;
        T& at         (size_t idx) ;
        T& operator[] (size_t idx) noexcept;

        constexpr size_t size() const noexcept ; // Always "3".


        // Meta.
        using value_type = T;
        template <typename N> using rebind_value_type = basic_rgb<N, RGBSpace>;


    private:
        static T basic_rgb::* const offsets_[3];
    };


    template <typename T, template <typename> class RGBSpace>
    constexpr size_t size(basic_rgb<T, RGBSpace> const &v) noexcept { return v.size(); }


    // -- relation --------------------------------------------------------------------------------
    template <typename T, template <typename> class RGBSpace> constexpr bool operator== (basic_rgb<T, RGBSpace> lhs, basic_rgb<T, RGBSpace> rhs) noexcept;
    template <typename T, template <typename> class RGBSpace> constexpr bool operator!= (basic_rgb<T, RGBSpace> lhs, basic_rgb<T, RGBSpace> rhs) noexcept;
    template <typename T, template <typename> class RGBSpace> constexpr bool rel_equal (basic_rgb<T, RGBSpace> lhs, basic_rgb<T, RGBSpace> rhs,
                                                    T max_rel_diff=std::numeric_limits<T>::epsilon() ) noexcept;

    // -- sign ------------------------------------------------------------------------------------
    template <typename T, template <typename> class RGBSpace> constexpr basic_rgb<T, RGBSpace> operator- (basic_rgb<T, RGBSpace> rhs) noexcept { return {-rhs.r, -rhs.g, -rhs.b}; }
    template <typename T, template <typename> class RGBSpace> constexpr basic_rgb<T, RGBSpace> operator+ (basic_rgb<T, RGBSpace> rhs) noexcept { return rhs; }

    // -- arithmetics -----------------------------------------------------------------------------
    template <typename T, template <typename> class RGBSpace> constexpr basic_rgb<T, RGBSpace> operator+ (basic_rgb<T, RGBSpace> lhs, basic_rgb<T, RGBSpace> rhs) noexcept;
    template <typename T, template <typename> class RGBSpace> constexpr basic_rgb<T, RGBSpace> operator- (basic_rgb<T, RGBSpace> lhs, basic_rgb<T, RGBSpace> rhs) noexcept;
    template <typename T, template <typename> class RGBSpace> constexpr basic_rgb<T, RGBSpace> operator* (basic_rgb<T, RGBSpace> lhs, basic_rgb<T, RGBSpace> rhs) noexcept;
    template <typename T, template <typename> class RGBSpace> constexpr basic_rgb<T, RGBSpace> operator/ (basic_rgb<T, RGBSpace> lhs, basic_rgb<T, RGBSpace> rhs) noexcept;

    template <typename T, template <typename> class RGBSpace> constexpr basic_rgb<T, RGBSpace> operator+ (basic_rgb<T, RGBSpace> lhs, typename basic_rgb<T, RGBSpace>::value_type rhs) noexcept;
    template <typename T, template <typename> class RGBSpace> constexpr basic_rgb<T, RGBSpace> operator- (basic_rgb<T, RGBSpace> lhs, typename basic_rgb<T, RGBSpace>::value_type rhs) noexcept;
    template <typename T, template <typename> class RGBSpace> constexpr basic_rgb<T, RGBSpace> operator* (basic_rgb<T, RGBSpace> lhs, typename basic_rgb<T, RGBSpace>::value_type rhs) noexcept;
    template <typename T, template <typename> class RGBSpace> constexpr basic_rgb<T, RGBSpace> operator/ (basic_rgb<T, RGBSpace> lhs, typename basic_rgb<T, RGBSpace>::value_type rhs) noexcept;

    template <typename T, template <typename> class RGBSpace> constexpr basic_rgb<T, RGBSpace> operator+ (typename basic_rgb<T, RGBSpace>::value_type lhs, basic_rgb<T, RGBSpace> rhs) noexcept;
    template <typename T, template <typename> class RGBSpace> constexpr basic_rgb<T, RGBSpace> operator- (typename basic_rgb<T, RGBSpace>::value_type lhs, basic_rgb<T, RGBSpace> rhs) noexcept;
    template <typename T, template <typename> class RGBSpace> constexpr basic_rgb<T, RGBSpace> operator* (typename basic_rgb<T, RGBSpace>::value_type lhs, basic_rgb<T, RGBSpace> rhs) noexcept;
    template <typename T, template <typename> class RGBSpace> constexpr basic_rgb<T, RGBSpace> operator/ (typename basic_rgb<T, RGBSpace>::value_type lhs, basic_rgb<T, RGBSpace> rhs) noexcept;

    // -- algorithms ------------------------------------------------------------------------------
    // Note: we do not offer constexpr were the C++11 <algorithms> library does neither.
    template <typename T, template <typename> class RGBSpace> basic_rgb<T, RGBSpace> min (basic_rgb<T, RGBSpace> lhs, basic_rgb<T, RGBSpace> rhs) noexcept;
    template <typename T, template <typename> class RGBSpace> basic_rgb<T, RGBSpace> min (typename basic_rgb<T, RGBSpace>::value_type lhs, basic_rgb<T, RGBSpace> rhs) noexcept;
    template <typename T, template <typename> class RGBSpace> basic_rgb<T, RGBSpace> min (basic_rgb<T, RGBSpace> lhs, typename basic_rgb<T, RGBSpace>::value_type rhs) noexcept;

    template <typename T, template <typename> class RGBSpace> basic_rgb<T, RGBSpace> max (basic_rgb<T, RGBSpace> lhs, basic_rgb<T, RGBSpace> rhs) noexcept;
    template <typename T, template <typename> class RGBSpace> basic_rgb<T, RGBSpace> max (typename basic_rgb<T, RGBSpace>::value_type lhs, basic_rgb<T, RGBSpace> rhs) noexcept;
    template <typename T, template <typename> class RGBSpace> basic_rgb<T, RGBSpace> max (basic_rgb<T, RGBSpace> lhs, typename basic_rgb<T, RGBSpace>::value_type rhs) noexcept;

}

#include "RGB.inl.hh"
#include "cmath.hh"

#endif // RGB_HH_INCLUDED_20131017

// (C) 2013 Sebastian Mach (1983), this file is published under the terms of the
// GNU General Public License, Version 3 (a.k.a. GPLv3).
// See COPYING in the root-folder of the excygen project folder.
#ifndef XYZ_HH_INCLUDED_20131206
#define XYZ_HH_INCLUDED_20131206

#include "algorithm/rel_equal.hh"
#include "traits/traits.hh"
#include <functional>
#include <algorithm>
#include <cmath>
#include <stdexcept>

namespace gaudy {

    //---------------------------------------------------------------------------------------------
    // XYZ
    // ---
    //
    // About
    // -----
    // Using -O3, benchmarks/IndexingOperator.cc shows that there is no performance difference
    // between indexing and direct member access with 'g++ (Ubuntu/Linaro 4.7.3-1ubuntu1) 4.7.3'.
    //---------------------------------------------------------------------------------------------

    // -- structure -------------------------------------------------------------------------------
    template <typename T>
    struct XYZ {

        // Data.
        T X=0, Y=0, Z=0;


        // Construction.
        constexpr XYZ() noexcept = default;
        constexpr XYZ(T X, T Y, T Z) noexcept : X(X), Y(Y), Z(Z) {}
        constexpr explicit XYZ(T f) noexcept  : X(f), Y(f), Z(f) {}


        // Conversion.


        // Assignment.
        XYZ& operator+= (XYZ rhs) noexcept;
        XYZ& operator-= (XYZ rhs) noexcept;
        XYZ& operator*= (XYZ rhs) noexcept;
        XYZ& operator/= (XYZ rhs) noexcept;

        XYZ& operator+= (T rhs) noexcept;
        XYZ& operator-= (T rhs) noexcept;
        XYZ& operator*= (T rhs) noexcept;
        XYZ& operator/= (T rhs) noexcept;


        // Array interface.
        constexpr T  at         (size_t idx) const ;
        constexpr T  operator[] (size_t idx) const noexcept;
        T& at         (size_t idx) ;
        T& operator[] (size_t idx) noexcept;

        constexpr size_t size() const noexcept ; // Always "3".


        // Meta.
        using value_type = T;
        template <typename N> using rebind_value_type = XYZ<N>;


    private:
        static T XYZ::* const offsets_[3];
    };


    template <typename T>
    constexpr size_t size(XYZ<T> const &v) noexcept { return v.size(); }


    // -- relation --------------------------------------------------------------------------------
    template <typename T> constexpr bool operator== (XYZ<T> lhs, XYZ<T> rhs) noexcept;
    template <typename T> constexpr bool operator!= (XYZ<T> lhs, XYZ<T> rhs) noexcept;
    template <typename T> constexpr bool rel_equal (XYZ<T> lhs, XYZ<T> rhs,
                                                    T max_rel_diff=std::numeric_limits<T>::epsilon() ) noexcept;

    // -- sign ------------------------------------------------------------------------------------
    template <typename T> constexpr XYZ<T> operator- (XYZ<T> rhs) noexcept { return {-rhs.X, -rhs.Y, -rhs.Z}; }
    template <typename T> constexpr XYZ<T> operator+ (XYZ<T> rhs) noexcept { return rhs; }

    // -- arithmetics -----------------------------------------------------------------------------
    template <typename T> constexpr XYZ<T> operator+ (XYZ<T> lhs, XYZ<T> rhs) noexcept;
    template <typename T> constexpr XYZ<T> operator- (XYZ<T> lhs, XYZ<T> rhs) noexcept;
    template <typename T> constexpr XYZ<T> operator* (XYZ<T> lhs, XYZ<T> rhs) noexcept;
    template <typename T> constexpr XYZ<T> operator/ (XYZ<T> lhs, XYZ<T> rhs) noexcept;

    template <typename T> constexpr XYZ<T> operator+ (XYZ<T> lhs, typename XYZ<T>::value_type rhs) noexcept;
    template <typename T> constexpr XYZ<T> operator- (XYZ<T> lhs, typename XYZ<T>::value_type rhs) noexcept;
    template <typename T> constexpr XYZ<T> operator* (XYZ<T> lhs, typename XYZ<T>::value_type rhs) noexcept;
    template <typename T> constexpr XYZ<T> operator/ (XYZ<T> lhs, typename XYZ<T>::value_type rhs) noexcept;

    template <typename T> constexpr XYZ<T> operator+ (typename XYZ<T>::value_type lhs, XYZ<T> rhs) noexcept;
    template <typename T> constexpr XYZ<T> operator- (typename XYZ<T>::value_type lhs, XYZ<T> rhs) noexcept;
    template <typename T> constexpr XYZ<T> operator* (typename XYZ<T>::value_type lhs, XYZ<T> rhs) noexcept;
    template <typename T> constexpr XYZ<T> operator/ (typename XYZ<T>::value_type lhs, XYZ<T> rhs) noexcept;

    // -- algorithms ------------------------------------------------------------------------------
    // Note: we do not offer constexpr were the C++11 <algorithms> library does neither.
    // Note: these are implemented here instead of algorithms.hh, and directly in terms of XYZ,
    //       because otherwise they are ambiguous wrt std::min and std::max.
    template <typename T> XYZ<T> min (XYZ<T> lhs, XYZ<T> rhs) noexcept;
    template <typename T> XYZ<T> min (typename XYZ<T>::value_type lhs, XYZ<T> rhs) noexcept;
    template <typename T> XYZ<T> min (XYZ<T> lhs, typename XYZ<T>::value_type rhs) noexcept;

    template <typename T> XYZ<T> max (XYZ<T> lhs, XYZ<T> rhs) noexcept;
    template <typename T> XYZ<T> max (typename XYZ<T>::value_type lhs, XYZ<T> rhs) noexcept;
    template <typename T> XYZ<T> max (XYZ<T> lhs, typename XYZ<T>::value_type rhs) noexcept;

}

#include "XYZ.inl.hh"
#include "cmath.hh"

#endif // XYZ_HH_INCLUDED_20131206

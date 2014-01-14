// (C) 2013 Sebastian Mach (1983), this file is published under the terms of the
// GNU General Public License, Version 3 (a.k.a. GPLv3).
// See COPYING in the root-folder of the excygen project folder.
#ifndef MATRIX33_HH_INCLUDED_20131209
#define MATRIX33_HH_INCLUDED_20131209

#include "../algorithm/rel_equal.hh"

namespace gaudy { namespace detail {

    template <typename T>
    struct Matrix33 {
        T _11=1, _12=0, _13=0,
          _21=0, _22=1, _23=0,
          _31=0, _32=0, _33=1;

        Matrix33() = default;
        Matrix33(T _11, T _12, T _13,
            T _21, T _22, T _23,
            T _31, T _32, T _33)
        : _11(_11), _12(_12), _13(_13),
          _21(_21), _22(_22), _23(_23),
          _31(_31), _32(_32), _33(_33)
        {}
    };

    template <typename T> constexpr bool operator== (Matrix33<T> const &m, Matrix33<T> const &n) noexcept;
    template <typename T> constexpr bool operator!= (Matrix33<T> const &m, Matrix33<T> const &n) noexcept;
    template <typename T> constexpr T determinant(Matrix33<T> const &m) noexcept;
    template <typename T> constexpr Matrix33<T> operator* (Matrix33<T> const &m, T f) noexcept;
    template <typename T> constexpr Matrix33<T> operator* (T f, Matrix33<T> const &m) noexcept;
    template <typename T> constexpr Matrix33<T> operator* (Matrix33<T> const &m, Matrix33<T> const &n) noexcept;
    template <typename T> constexpr Matrix33<T> inverse (Matrix33<T> const &m) noexcept;
    template <typename T> constexpr Matrix33<T> transpose (Matrix33<T> const &m) noexcept;

    template <typename T> constexpr bool rel_equal (detail::Matrix33<T> const &lhs,
                                                    detail::Matrix33<T> const &rhs,
                                                    T max_rel_diff=std::numeric_limits<T>::epsilon()
                                                   ) noexcept;
} }

#include "Matrix33.inl.hh"

#endif // MATRIX33_HH_INCLUDED_20131209

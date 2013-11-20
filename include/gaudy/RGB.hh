// (C) 2013 Sebastian Mach (1983), this file is published under the terms of the
// GNU General Public License, Version 3 (a.k.a. GPLv3).
// See COPYING in the root-folder of the excygen project folder.
#ifndef RGB_HH_INCLUDED_20131017
#define RGB_HH_INCLUDED_20131017

#include "rel_equal.hh"
#include <functional>
#include <algorithm>
#include <cmath>
#include <stdexcept>

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
    template <typename T>
    struct basic_rgb {
        using value_type = T;

        T r=0, g=0, b=0;

        constexpr basic_rgb() noexcept = default;
        constexpr basic_rgb(T r, T g, T b) noexcept : r(r), g(g), b(b) {}
        constexpr explicit basic_rgb(T f) noexcept  : r(f), g(f), b(f) {}

        basic_rgb& operator+= (basic_rgb rhs) noexcept;
        basic_rgb& operator-= (basic_rgb rhs) noexcept;
        basic_rgb& operator*= (basic_rgb rhs) noexcept;
        basic_rgb& operator/= (basic_rgb rhs) noexcept;

        basic_rgb& operator+= (T rhs) noexcept;
        basic_rgb& operator-= (T rhs) noexcept;
        basic_rgb& operator*= (T rhs) noexcept;
        basic_rgb& operator/= (T rhs) noexcept;

        // Array interface.
        T& operator[] (size_t idx) noexcept { return this->*offsets_[idx]; }
        constexpr T operator[] (size_t idx) const noexcept { return this->*offsets_[idx]; }
        T& at (size_t idx) {
            if (idx>=size()) // TODO: check if the negative check is faster.
                throw std::out_of_range("basic_rgb: out of range access");
            return this->*offsets_[idx];
        }
        constexpr T at (size_t idx) const {
            if (idx>=size()) // TODO: check if the negative check is faster.
                throw std::out_of_range("basic_rgb: out of range access");
            return this->*offsets_[idx];
        }
        constexpr size_t size() const noexcept { return 3; }

    private:
        static T basic_rgb::* const offsets_[3];
    };

    template <typename T>
    T basic_rgb<T>::* const basic_rgb<T>::offsets_[3] = {
        &basic_rgb<T>::r,
        &basic_rgb<T>::g,
        &basic_rgb<T>::b
    };

    template <typename T>
    constexpr size_t size(basic_rgb<T> const &v) noexcept { return v.size(); }



    // -- apply: this maps some function over all elements and returns the result ------------------
    // Unary
    template <typename T, typename Fun>
    constexpr auto apply (basic_rgb<T> operand, Fun fun)
      -> basic_rgb<decltype (fun(operand.r))>
    {
        return {fun(operand.r), fun(operand.g), fun(operand.b)};
    }

    // Binary
    template <typename T, typename U, typename Fun>
    constexpr auto apply (basic_rgb<T> lhs, basic_rgb<U> rhs, Fun fun)
      -> basic_rgb<decltype (fun(lhs.r, rhs.r))>
    {
        return {fun(lhs.r, rhs.r), fun(lhs.g, rhs.g), fun(lhs.b, rhs.b)};
    }

    template <typename T, typename U, typename Fun>
    constexpr auto apply (basic_rgb<T> lhs, U rhs, Fun fun)
      -> basic_rgb<decltype (fun(lhs.r, rhs))>
    {
        return {fun(lhs.r, rhs), fun(lhs.g, rhs), fun(lhs.b, rhs)};
    }

    template <typename T, typename U, typename Fun>
    constexpr auto apply (T lhs, basic_rgb<U> rhs, Fun fun)
      -> basic_rgb<decltype (fun(lhs, rhs.r))>
    {
        return {fun(lhs, rhs.r), fun(lhs, rhs.g), fun(lhs, rhs.b)};
    }


    template <typename T, typename U, typename Fun>
    constexpr auto apply (basic_rgb<T> lhs, basic_rgb<U> *rhs, Fun fun)
      -> basic_rgb<decltype (fun(lhs.r, &rhs->r))>
    {
        return {fun(lhs.r, &rhs->r), fun(lhs.g, &rhs->g), fun(lhs.b, &rhs->b)};
    }

    template <typename T, typename U, typename Fun>
    constexpr auto apply (T lhs, basic_rgb<U> *rhs, Fun fun)
      -> basic_rgb<decltype (fun(lhs, &rhs->r))>
    {
        return {fun(lhs, &rhs->r), fun(lhs, &rhs->g), fun(lhs, &rhs->b)};
    }


    // Ternary
    template <typename T, typename U, typename V, typename Fun>
    constexpr auto apply (basic_rgb<T> a, basic_rgb<U> b, basic_rgb<V> c, Fun fun)
      -> basic_rgb<decltype (fun(a.r, b.r, c.r))>
    {
        return {fun(a.r, b.r, c.r), fun(a.g, b.g, c.g), fun(a.b, b.b, c.b)};
    }

    template <typename T, typename U, typename V, typename Fun>
    constexpr auto apply (basic_rgb<T> a, basic_rgb<U> b, V c, Fun fun)
      -> basic_rgb<decltype (fun(a.r, b.r, c))>
    {
        return {fun(a.r, b.r, c), fun(a.g, b.g, c), fun(a.b, b.b, c)};
    }

    template <typename T, typename U, typename V, typename Fun>
    constexpr auto apply (basic_rgb<T> a, U b, basic_rgb<V> c, Fun fun)
      -> basic_rgb<decltype (fun(a.r, b, c.r))>
    {
        return {fun(a.r, b, c.r), fun(a.g, b, c.g), fun(a.b, b, c.b)};
    }

    template <typename T, typename U, typename V, typename Fun>
    constexpr auto apply (basic_rgb<T> a, U b, V c, Fun fun)
      -> basic_rgb<decltype (fun(a.r, b, c))>
    {
        return {fun(a.r, b, c), fun(a.g, b, c), fun(a.b, b, c)};
    }

    template <typename T, typename U, typename V, typename Fun>
    constexpr auto apply (T a, basic_rgb<U> b, basic_rgb<V> c, Fun fun)
      -> basic_rgb<decltype (fun(a, b.r, c.r))>
    {
        return {fun(a, b.r, c.r), fun(a, b.g, c.g), fun(a, b.b, c.b)};
    }

    template <typename T, typename U, typename V, typename Fun>
    constexpr auto apply (T a, basic_rgb<U> b, V c, Fun fun)
      -> basic_rgb<decltype (fun(a, b.r, c))>
    {
        return {fun(a, b.r, c), fun(a, b.g, c), fun(a, b.b, c)};
    }

    template <typename T, typename U, typename V, typename Fun>
    constexpr auto apply (T a, U b, basic_rgb<V> c, Fun fun)
      -> basic_rgb<decltype (fun(a, b, c.r))>
    {
        return {fun(a, b, c.r), fun(a, b, c.g), fun(a, b, c.b)};
    }

    template <typename T, typename U, typename V, typename Fun>
    constexpr auto apply (basic_rgb<T> a, basic_rgb<U> b, basic_rgb<V> *c, Fun fun)
      -> basic_rgb<decltype (fun(a.r, b.r, &c->r))>
    {
        return {fun(a.r, b.r, &c->r), fun(a.g, b.g, &c->g), fun(a.b, b.b, &c->b)};
    }

    template <typename T, typename U, typename V, typename Fun>
    constexpr auto apply (basic_rgb<T> a, U b, basic_rgb<V> *c, Fun fun)
      -> basic_rgb<decltype (fun(a.r, b, &c->r))>
    {
        return {fun(a.r, b, &c->r), fun(a.g, b, &c->g), fun(a.b, b, &c->b)};
    }

    template <typename T, typename U, typename V, typename Fun>
    constexpr auto apply (T a, basic_rgb<U> b, basic_rgb<V> *c, Fun fun)
      -> basic_rgb<decltype (fun(a, b.r, &c->r))>
    {
        return {fun(a, b.r, &c->r), fun(a, b.g, &c->g), fun(a, b.b, &c->b)};
    }



    using RGB = basic_rgb<float>;


    // -- relation --------------------------------------------------------------------------------
    template <typename T> constexpr bool operator== (basic_rgb<T> lhs, basic_rgb<T> rhs) noexcept;
    template <typename T> constexpr bool operator!= (basic_rgb<T> lhs, basic_rgb<T> rhs) noexcept;
    template <typename T> constexpr bool rel_equal (basic_rgb<T> lhs, basic_rgb<T> rhs,
                                                    T max_rel_diff=std::numeric_limits<T>::epsilon() ) noexcept;

    // -- sign ------------------------------------------------------------------------------------
    template <typename T> constexpr basic_rgb<T> operator- (basic_rgb<T> rhs) noexcept { return {-rhs.r, -rhs.g, -rhs.b}; }
    template <typename T> constexpr basic_rgb<T> operator+ (basic_rgb<T> rhs) noexcept { return rhs; }

    // -- arithmetics -----------------------------------------------------------------------------
    template <typename T> constexpr basic_rgb<T> operator+ (basic_rgb<T> lhs, basic_rgb<T> rhs) noexcept;
    template <typename T> constexpr basic_rgb<T> operator- (basic_rgb<T> lhs, basic_rgb<T> rhs) noexcept;
    template <typename T> constexpr basic_rgb<T> operator* (basic_rgb<T> lhs, basic_rgb<T> rhs) noexcept;
    template <typename T> constexpr basic_rgb<T> operator/ (basic_rgb<T> lhs, basic_rgb<T> rhs) noexcept;

    template <typename T> constexpr basic_rgb<T> operator+ (basic_rgb<T> lhs, typename basic_rgb<T>::value_type rhs) noexcept;
    template <typename T> constexpr basic_rgb<T> operator- (basic_rgb<T> lhs, typename basic_rgb<T>::value_type rhs) noexcept;
    template <typename T> constexpr basic_rgb<T> operator* (basic_rgb<T> lhs, typename basic_rgb<T>::value_type rhs) noexcept;
    template <typename T> constexpr basic_rgb<T> operator/ (basic_rgb<T> lhs, typename basic_rgb<T>::value_type rhs) noexcept;

    template <typename T> constexpr basic_rgb<T> operator+ (typename basic_rgb<T>::value_type lhs, basic_rgb<T> rhs) noexcept;
    template <typename T> constexpr basic_rgb<T> operator- (typename basic_rgb<T>::value_type lhs, basic_rgb<T> rhs) noexcept;
    template <typename T> constexpr basic_rgb<T> operator* (typename basic_rgb<T>::value_type lhs, basic_rgb<T> rhs) noexcept;
    template <typename T> constexpr basic_rgb<T> operator/ (typename basic_rgb<T>::value_type lhs, basic_rgb<T> rhs) noexcept;

    // -- algorithms ------------------------------------------------------------------------------
    // Note: we do not offer constexpr were the C++11 <algorithms> library does neither.
    template <typename T> basic_rgb<T> min (basic_rgb<T> lhs, basic_rgb<T> rhs) noexcept;
    template <typename T> basic_rgb<T> min (typename basic_rgb<T>::value_type lhs, basic_rgb<T> rhs) noexcept;
    template <typename T> basic_rgb<T> min (basic_rgb<T> lhs, typename basic_rgb<T>::value_type rhs) noexcept;

    template <typename T> basic_rgb<T> max (basic_rgb<T> lhs, basic_rgb<T> rhs) noexcept;
    template <typename T> basic_rgb<T> max (typename basic_rgb<T>::value_type lhs, basic_rgb<T> rhs) noexcept;
    template <typename T> basic_rgb<T> max (basic_rgb<T> lhs, typename basic_rgb<T>::value_type rhs) noexcept;

    //Implementation notes:
    // Some operator overloads use basic_rgb<T>::value_type instead of just plain T. This is because
    // with plain T, the operators are deduced on both the lhs AND rhs, leading to ambiguities when
    // using e.g. 'basic_rgb<float> foo; foo += 1;', where there is an int added to a float-RGB.
    // Using basic_rgb::value_type prevents type deduction on the scalar argument.
}

#include "cmath.hh"

namespace gaudy {

    //---------------------------------------------------------------------------------------------
    // implementation
    //---------------------------------------------------------------------------------------------
    template <typename T>
    inline basic_rgb<T>& basic_rgb<T>::operator+= (basic_rgb<T> rhs) noexcept {
        r += rhs.r;
        g += rhs.g;
        b += rhs.b;
        return *this;
    }

    template <typename T>
    inline basic_rgb<T>& basic_rgb<T>::operator-= (basic_rgb<T> rhs) noexcept {
        r -= rhs.r;
        g -= rhs.g;
        b -= rhs.b;
        return *this;
    }

    template <typename T>
    inline basic_rgb<T>& basic_rgb<T>::operator*= (basic_rgb<T> rhs) noexcept {
        r *= rhs.r;
        g *= rhs.g;
        b *= rhs.b;
        return *this;
    }

    template <typename T>
    inline basic_rgb<T>& basic_rgb<T>::operator/= (basic_rgb<T> rhs) noexcept {
        r /= rhs.r;
        g /= rhs.g;
        b /= rhs.b;
        return *this;
    }

    template <typename T>
    inline basic_rgb<T>& basic_rgb<T>::operator+= (T rhs) noexcept {
        r += rhs;
        g += rhs;
        b += rhs;
        return *this;
    }

    template <typename T>
    inline basic_rgb<T>& basic_rgb<T>::operator-= (T rhs) noexcept {
        r -= rhs;
        g -= rhs;
        b -= rhs;
        return *this;
    }

    template <typename T>
    inline basic_rgb<T>& basic_rgb<T>::operator*= (T rhs) noexcept {
        r *= rhs;
        g *= rhs;
        b *= rhs;
        return *this;
    }

    template <typename T>
    inline basic_rgb<T>& basic_rgb<T>::operator/= (T rhs) noexcept {
        r /= rhs;
        g /= rhs;
        b /= rhs;
        return *this;
    }


    // relation
    template <typename T>
    constexpr bool operator== (basic_rgb<T> lhs, basic_rgb<T> rhs) noexcept {
        return lhs.r==rhs.r && lhs.g==rhs.g && lhs.b==rhs.b;
    }
    template <typename T>
    constexpr bool operator!= (basic_rgb<T> lhs, basic_rgb<T> rhs) noexcept {
        return !(lhs == rhs);
    }
    template <typename T>
    constexpr bool rel_equal (basic_rgb<T> lhs, basic_rgb<T> rhs, T max_rel_diff) noexcept
    {
        return rel_equal (lhs.r, rhs.r, max_rel_diff)
            && rel_equal (lhs.g, rhs.g, max_rel_diff)
            && rel_equal (lhs.b, rhs.b, max_rel_diff)
        ;
    }


    // arithmetics
    template <typename T>
    constexpr basic_rgb<T> operator+ (basic_rgb<T> lhs, basic_rgb<T> rhs) noexcept {
        return {lhs.r+rhs.r, lhs.g+rhs.g, lhs.b+rhs.b};
    }
    template <typename T>
    constexpr basic_rgb<T> operator- (basic_rgb<T> lhs, basic_rgb<T> rhs) noexcept {
        return {lhs.r-rhs.r, lhs.g-rhs.g, lhs.b-rhs.b};
    }
    template <typename T>
    constexpr basic_rgb<T> operator* (basic_rgb<T> lhs, basic_rgb<T> rhs) noexcept {
        return {lhs.r*rhs.r, lhs.g*rhs.g, lhs.b*rhs.b};
    }
    template <typename T>
    constexpr basic_rgb<T> operator/ (basic_rgb<T> lhs, basic_rgb<T> rhs) noexcept {
        return {lhs.r/rhs.r, lhs.g/rhs.g, lhs.b/rhs.b};
    }

    template <typename T>
    constexpr basic_rgb<T> operator+ (basic_rgb<T> lhs, typename basic_rgb<T>::value_type rhs) noexcept {
        return {lhs.r+rhs, lhs.g+rhs, lhs.b+rhs};
    }
    template <typename T>
    constexpr basic_rgb<T> operator- (basic_rgb<T> lhs, typename basic_rgb<T>::value_type rhs) noexcept {
        return {lhs.r-rhs, lhs.g-rhs, lhs.b-rhs};
    }
    template <typename T>
    constexpr basic_rgb<T> operator* (basic_rgb<T> lhs, typename basic_rgb<T>::value_type rhs) noexcept {
        return {lhs.r*rhs, lhs.g*rhs, lhs.b*rhs};
    }
    template <typename T>
    constexpr basic_rgb<T> operator/ (basic_rgb<T> lhs, typename basic_rgb<T>::value_type rhs) noexcept {
        return {lhs.r/rhs, lhs.g/rhs, lhs.b/rhs};
    }

    template <typename T>
    constexpr basic_rgb<T> operator+ (typename basic_rgb<T>::value_type lhs, basic_rgb<T> rhs) noexcept {
        return {lhs+rhs.r, lhs+rhs.g, lhs+rhs.b};
    }
    template <typename T>
    constexpr basic_rgb<T> operator- (typename basic_rgb<T>::value_type lhs, basic_rgb<T> rhs) noexcept {
        return {lhs-rhs.r, lhs-rhs.g, lhs-rhs.b};
    }
    template <typename T>
    constexpr basic_rgb<T> operator* (typename basic_rgb<T>::value_type lhs, basic_rgb<T> rhs) noexcept {
        return {lhs*rhs.r, lhs*rhs.g, lhs*rhs.b};
    }
    template <typename T>
    constexpr basic_rgb<T> operator/ (typename basic_rgb<T>::value_type lhs, basic_rgb<T> rhs) noexcept {
        return {lhs/rhs.r, lhs/rhs.g, lhs/rhs.b};
    }


    // algorithms
    template <typename T>
    inline basic_rgb<T> min(basic_rgb<T> x, basic_rgb<T> y) noexcept {
        using std::min;
        return { min(x.r, y.r),
                 min(x.g, y.g),
                 min(x.b, y.b) };
    }
    template <typename T>
    inline basic_rgb<T> max(basic_rgb<T> x, basic_rgb<T> y) noexcept {
        using std::max;
        return { max(x.r, y.r),
                 max(x.g, y.g),
                 max(x.b, y.b) };
    }

    template <typename T>
    inline basic_rgb<T> min(basic_rgb<T> x, typename basic_rgb<T>::value_type y) noexcept {
        using std::min;
        return { min(x.r, y),
                 min(x.g, y),
                 min(x.b, y) };
    }
    template <typename T>
    inline basic_rgb<T> max(basic_rgb<T> x, typename basic_rgb<T>::value_type y) noexcept {
        using std::max;
        return { max(x.r, y),
                 max(x.g, y),
                 max(x.b, y) };
    }

    template <typename T>
    inline basic_rgb<T> min(typename basic_rgb<T>::value_type x, basic_rgb<T> y) noexcept {
        using std::min;
        return { min(x, y.r),
                 min(x, y.g),
                 min(x, y.b) };
    }
    template <typename T>
    inline basic_rgb<T> max(typename basic_rgb<T>::value_type x, basic_rgb<T> y) noexcept {
        using std::max;
        return { max(x, y.r),
                 max(x, y.g),
                 max(x, y.b) };
    }
}


#endif // RGB_HH_INCLUDED_20131017

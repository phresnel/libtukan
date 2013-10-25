// (C) 2013 Sebastian Mach (1983), this file is published under the terms of the
// GNU General Public License, Version 3 (a.k.a. GPLv3).
// See COPYING in the root-folder of the excygen project folder.
#ifndef RGB_HH_INCLUDED_20131017
#define RGB_HH_INCLUDED_20131017

#include "rel_equal.hh"
#include <functional>

namespace gaudy {

    //---------------------------------------------------------------------------------------------
    // RGB
    //---------------------------------------------------------------------------------------------

    // -- structure -------------------------------------------------------------------------------
    template <typename T>
    struct basic_rgb {
        using value_type = T;

        T r=0, g=0, b=0;

        constexpr basic_rgb() noexcept = default;
        constexpr basic_rgb(T r, T g, T b) noexcept : r(r), g(g), b(b) {}

        basic_rgb& operator+= (basic_rgb rhs) noexcept;
        basic_rgb& operator-= (basic_rgb rhs) noexcept;
        basic_rgb& operator*= (basic_rgb rhs) noexcept;
        basic_rgb& operator/= (basic_rgb rhs) noexcept;

        basic_rgb& operator+= (T rhs) noexcept;
        basic_rgb& operator-= (T rhs) noexcept;
        basic_rgb& operator*= (T rhs) noexcept;
        basic_rgb& operator/= (T rhs) noexcept;
    };

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


    //Implementation notes:
    // Some operator overloads use basic_rgb<T>::value_type instead of just plain T. This is because
    // with plain T, the operators are deduced on both the lhs AND rhs, leading to ambiguities when
    // using e.g. 'basic_rgb<float> foo; foo += 1;', where there is an int added to a float-RGB.
    // Using basic_rgb::value_type prevents type deduction on the scalar argument.
}


#include <cmath>
namespace gaudy {

    // -- trigonometric ----------------------------------------------------------------------------
    template <typename T> basic_rgb<T>  cos (basic_rgb<T> v) noexcept ;
    template <typename T> basic_rgb<T>  sin (basic_rgb<T> v) noexcept ;
    template <typename T> basic_rgb<T>  tan (basic_rgb<T> v) noexcept ;

    template <typename T> basic_rgb<T> acos (basic_rgb<T> v) noexcept ;
    template <typename T> basic_rgb<T> asin (basic_rgb<T> v) noexcept ;
    template <typename T> basic_rgb<T> atan (basic_rgb<T> v) noexcept ;

    template <typename T> basic_rgb<T> atan2 (basic_rgb<T> v, basic_rgb<T> w) noexcept ;
    template <typename T> basic_rgb<T> atan2 (basic_rgb<T> v, typename basic_rgb<T>::value_type w) noexcept ;
    template <typename T> basic_rgb<T> atan2 (typename basic_rgb<T>::value_type v, basic_rgb<T> w) noexcept ;

    // -- hyperbolic -------------------------------------------------------------------------------
    template <typename T> basic_rgb<T>  cosh (basic_rgb<T> v) noexcept ;
    template <typename T> basic_rgb<T>  sinh (basic_rgb<T> v) noexcept ;
    template <typename T> basic_rgb<T>  tanh (basic_rgb<T> v) noexcept ;
    template <typename T> basic_rgb<T> acosh (basic_rgb<T> v) noexcept ;
    template <typename T> basic_rgb<T> asinh (basic_rgb<T> v) noexcept ;
    template <typename T> basic_rgb<T> atanh (basic_rgb<T> v) noexcept ;

    // -- exponential and logarithmic --------------------------------------------------------------
    template <typename T> basic_rgb<T> exp   (basic_rgb<T> v) noexcept ;
    template <typename T> basic_rgb<T> frexp (basic_rgb<T> v, basic_rgb<int> *exp)   noexcept ;
    template <typename T> basic_rgb<T> ldexp (basic_rgb<T> sig, basic_rgb<int> exp)  noexcept ;
    template <typename T> basic_rgb<T> log   (basic_rgb<T> v) noexcept ;
    template <typename T> basic_rgb<T> log10 (basic_rgb<T> v) noexcept ;
    template <typename T> basic_rgb<T> modf  (basic_rgb<T> v, basic_rgb<T> *intpart)  noexcept ;
    template <typename T> basic_rgb<T> exp2  (basic_rgb<T> v) noexcept ;
    template <typename T> basic_rgb<T> expm1 (basic_rgb<T> v) noexcept ;

    template <typename T> basic_rgb<int> ilogb (basic_rgb<T> v) noexcept ;
    template <typename T> basic_rgb<T>   log1p (basic_rgb<T> v) noexcept ;
    template <typename T> basic_rgb<T>   log2  (basic_rgb<T> v) noexcept ;

    template <typename T> basic_rgb<T> scalbn  (basic_rgb<T> v, basic_rgb<int> n) noexcept ;
    template <typename T> basic_rgb<T> scalbn  (basic_rgb<T> v, int n) noexcept ;
    template <typename T> basic_rgb<T> scalbln (basic_rgb<T> v, basic_rgb<long> n) noexcept ;
    template <typename T> basic_rgb<T> scalbln (basic_rgb<T> v, long n) noexcept ;


    // -- power ------------------------------------------------------------------------------------
    template <typename T> basic_rgb<T> pow (basic_rgb<T> v, basic_rgb<T> w) noexcept ;
    template <typename T> basic_rgb<T> pow (basic_rgb<T> v, typename basic_rgb<T>::value_type w) noexcept ;
    template <typename T> basic_rgb<T> pow (typename basic_rgb<T>::value_type v, basic_rgb<T> w) noexcept ;

    template <typename T> basic_rgb<T> sqrt (basic_rgb<T> v) noexcept ;
    template <typename T> basic_rgb<T> cbrt (basic_rgb<T> v) noexcept ;

    template <typename T> basic_rgb<T> hypot (basic_rgb<T> v, basic_rgb<T> w) noexcept ;
    template <typename T> basic_rgb<T> hypot (basic_rgb<T> v, typename basic_rgb<T>::value_type w) noexcept ;
    template <typename T> basic_rgb<T> hypot (typename basic_rgb<T>::value_type v, basic_rgb<T> w) noexcept ;

    // -- error and gamma --------------------------------------------------------------------------
    template <typename T> basic_rgb<T> erf    (basic_rgb<T> v) noexcept ;
    template <typename T> basic_rgb<T> erfc   (basic_rgb<T> v) noexcept ;
    template <typename T> basic_rgb<T> lgamma (basic_rgb<T> v) noexcept ;
    template <typename T> basic_rgb<T> tgamma (basic_rgb<T> v) noexcept ;

    // -- rounding and remainder -------------------------------------------------------------------
    template <typename T> basic_rgb<T>         ceil      (basic_rgb<T> v) noexcept ;
    template <typename T> basic_rgb<T>         floor     (basic_rgb<T> v) noexcept ;
    template <typename T> basic_rgb<T>         fmod      (basic_rgb<T> num, basic_rgb<T> den) noexcept ;
    template <typename T> basic_rgb<T>         trunc     (basic_rgb<T> v) noexcept ;
    template <typename T> basic_rgb<T>         round     (basic_rgb<T> v) noexcept ;
    template <typename T> basic_rgb<long>      lround    (basic_rgb<T> v) noexcept ;
    template <typename T> basic_rgb<long long> llround   (basic_rgb<T> v) noexcept ;
    template <typename T> basic_rgb<T>         rint      (basic_rgb<T> v) noexcept ;
    template <typename T> basic_rgb<long>      lrint     (basic_rgb<T> v) noexcept ;
    template <typename T> basic_rgb<long long> llrint    (basic_rgb<T> v) noexcept ;
    template <typename T> basic_rgb<T>         nearbyint (basic_rgb<T> v) noexcept ;
    template <typename T> basic_rgb<T>         remainder (basic_rgb<T> num, basic_rgb<T> denom) noexcept ;
    template <typename T> basic_rgb<T> remquo (basic_rgb<T> num, basic_rgb<T> den, basic_rgb<int> *quot) noexcept ;

    // -- floating point manipulation --------------------------------------------------------------
    template <typename T> basic_rgb<T> copysign  (basic_rgb<T> x, basic_rgb<T> y) noexcept ;
    template <typename T> basic_rgb<T> nextafter (basic_rgb<T> x, basic_rgb<T> y) noexcept ;
    template <typename T> basic_rgb<T> nexttoward(basic_rgb<T> x, basic_rgb<long double> y) noexcept ;
    // NAN macro constant not implemented, because we would need to be able to overload macros.

    // -- min, max, difference ---------------------------------------------------------------------
    template <typename T> basic_rgb<T> fmin(basic_rgb<T> x, basic_rgb<T> y) noexcept ;
    template <typename T> basic_rgb<T> fmax(basic_rgb<T> x, basic_rgb<T> y) noexcept ;
    template <typename T> basic_rgb<T> fdim(basic_rgb<T> x, basic_rgb<T> y) noexcept ;

    // -- other ------------------------------------------------------------------------------------
    template <typename T> basic_rgb<T> fabs(basic_rgb<T> v) noexcept ;
    template <typename T> basic_rgb<T> abs (basic_rgb<T> v) noexcept;
    template <typename T> basic_rgb<T> fma (basic_rgb<T> x, basic_rgb<T> y, basic_rgb<T> z) noexcept ;

    // -- classification functions -----------------------------------------------------------------

    // -- comparison functions ---------------------------------------------------------------------

}




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
}


namespace gaudy {
    // -- <cmath> ---------------------------------------------------------------------------------
    // DONE: replace all std-qualifcations by a using
    // TODO: for some functions, add permutations of RGB, Scalar operands
    //-- -- -- -- --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  -- --
    // Info: While glibcxx defines some (many? (all?)) cmath functions as constexpr, this is not
    //       sanctioned  by  the  C++11  standard,  therefore we are not making the  promise  of
    //       constexpr, as such code is non-portable.
    //-- -- -- -- --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  -- --

    // trigonometric
    template <typename T>
    inline basic_rgb<T> cos(basic_rgb<T> v) noexcept {
        using std::cos;
        return basic_rgb<T>(cos(v.r), cos(v.g), cos(v.b));
    }

    template <typename T>
    inline basic_rgb<T> sin(basic_rgb<T> v) noexcept {
        using std::sin;
        return basic_rgb<T>(sin(v.r), sin(v.g), sin(v.b));
    }

    template <typename T>
    inline basic_rgb<T> tan(basic_rgb<T> v) noexcept {
        using std::tan;
        return basic_rgb<T>(tan(v.r), tan(v.g), tan(v.b));
    }

    template <typename T>
    inline basic_rgb<T> acos(basic_rgb<T> v) noexcept {
        using std::acos;
        return basic_rgb<T>(acos(v.r), acos(v.g), acos(v.b));
    }

    template <typename T>
    inline basic_rgb<T> asin(basic_rgb<T> v) noexcept {
        using std::asin;
        return basic_rgb<T>(asin(v.r), asin(v.g), asin(v.b));
    }

    template <typename T>
    inline basic_rgb<T> atan(basic_rgb<T> v) noexcept {
        using std::atan;
        return basic_rgb<T>(atan(v.r), atan(v.g), atan(v.b));
    }

    template <typename T>
    inline basic_rgb<T> atan2(basic_rgb<T> v, basic_rgb<T> w) noexcept {
        using std::atan2;
        return basic_rgb<T>(atan2(v.r,w.r), atan2(v.g,w.g), atan2(v.b,w.b));
    }
    template <typename T>
    inline basic_rgb<T> atan2(basic_rgb<T> v, typename basic_rgb<T>::value_type w) noexcept {
        using std::atan2;
        return basic_rgb<T>(atan2(v.r,w), atan2(v.g,w), atan2(v.b,w));
    }
    template <typename T>
    inline basic_rgb<T> atan2(typename basic_rgb<T>::value_type v, basic_rgb<T> w) noexcept {
        using std::atan2;
        return basic_rgb<T>(atan2(v,w.r), atan2(v,w.g), atan2(v,w.b));
    }

    // hyperbolic
    template <typename T>
    inline basic_rgb<T> cosh(basic_rgb<T> v) noexcept {
        using std::cosh;
        return basic_rgb<T>(cosh(v.r), cosh(v.g), cosh(v.b));
    }

    template <typename T>
    inline basic_rgb<T> sinh(basic_rgb<T> v) noexcept {
        using std::sinh;
        return basic_rgb<T>(sinh(v.r), sinh(v.g), sinh(v.b));
    }

    template <typename T>
    inline basic_rgb<T> tanh(basic_rgb<T> v) noexcept {
        using std::tanh;
        return basic_rgb<T>(tanh(v.r), tanh(v.g), tanh(v.b));
    }

    template <typename T>
    inline basic_rgb<T> acosh(basic_rgb<T> v) noexcept {
        using std::acosh;
        return basic_rgb<T>(acosh(v.r), acosh(v.g), acosh(v.b));
    }

    template <typename T>
    inline basic_rgb<T> asinh(basic_rgb<T> v) noexcept {
        using std::asinh;
        return basic_rgb<T>(asinh(v.r), asinh(v.g), asinh(v.b));
    }

    template <typename T>
    inline basic_rgb<T> atanh(basic_rgb<T> v) noexcept {
        using std::atanh;
        return basic_rgb<T>(atanh(v.r), atanh(v.g), atanh(v.b));
    }

    // exponential and logarithmic
    template <typename T>
    inline basic_rgb<T> exp(basic_rgb<T> v) noexcept {
        using std::exp;
        return {exp(v.r), exp(v.g), exp(v.b)};
}

    template <typename T>
    inline basic_rgb<T> frexp(basic_rgb<T> v, basic_rgb<int> *exp) noexcept {
        using std::frexp;
        return basic_rgb<T>(frexp(v.r, &exp->r),
                            frexp(v.g, &exp->g),
                            frexp(v.b, &exp->b));
    }

    template <typename T>
    inline basic_rgb<T> ldexp(basic_rgb<T> sig, basic_rgb<int> exp) noexcept {
        using std::ldexp;
        return {ldexp(sig.r, exp.r),
                ldexp(sig.g, exp.g),
                ldexp(sig.b, exp.b)};
    }

    template <typename T>
    inline basic_rgb<T> log(basic_rgb<T> v) noexcept {
        using std::log;
        return {log(v.r), log(v.g), log(v.b)};
    }

    template <typename T>
    inline basic_rgb<T> log10(basic_rgb<T> v) noexcept {
        using std::log10;
        return {log10(v.r), log10(v.g), log10(v.b)};
    }

    template <typename T>
    inline basic_rgb<T> modf(basic_rgb<T> v, basic_rgb<T> *intpart) noexcept {
        using std::modf;
        return { modf(v.r, &intpart->r),
                 modf(v.g, &intpart->g),
                 modf(v.b, &intpart->b) };
    }

    template <typename T>
    inline basic_rgb<T> exp2(basic_rgb<T> v) noexcept {
        using std::exp2;
        return {exp2(v.r), exp2(v.g), exp2(v.b)};
    }

    template <typename T>
    inline basic_rgb<T> expm1(basic_rgb<T> v) noexcept {
        using std::expm1;
        return {expm1(v.r), expm1(v.g), expm1(v.b)};
    }

    template <typename T>
    inline basic_rgb<int> ilogb(basic_rgb<T> v) noexcept {
        using std::ilogb;
        return {ilogb(v.r), ilogb(v.g), ilogb(v.b)};
    }

    template <typename T>
    inline basic_rgb<T> log1p(basic_rgb<T> v) noexcept {
        using std::log1p;
        return {log1p(v.r), log1p(v.g), log1p(v.b)};
    }

    template <typename T>
    inline basic_rgb<T> log2(basic_rgb<T> v) noexcept {
        using std::log2;
        return {log2(v.r), log2(v.g), log2(v.b)};
    }


    template <typename T>
    inline basic_rgb<T> scalbn (basic_rgb<T> v, int n) noexcept {
        using std::scalbn;
        return {scalbn(v.r,n), scalbn(v.g,n), scalbn(v.b,n)};
    }
    template <typename T>
    inline basic_rgb<T> scalbn (basic_rgb<T> v, basic_rgb<int> n) noexcept {
        using std::scalbn;
        return {scalbn(v.r, n.r), scalbn(v.g, n.g), scalbn(v.b, n.b)};
    }


    template <typename T>
    inline basic_rgb<T> scalbln (basic_rgb<T> v, long n) noexcept {
        using std::scalbln;
        return {scalbln(v.r,n), scalbln(v.g,n), scalbln(v.b,n)};
    }
    template <typename T>
    inline basic_rgb<T> scalbln (basic_rgb<T> v, basic_rgb<long> n) noexcept {
        using std::scalbln;
        return {scalbln(v.r, n.r), scalbln(v.g, n.g), scalbln(v.b, n.b)};
    }


    // power
    template <typename T>
    inline basic_rgb<T> pow(basic_rgb<T> v, basic_rgb<T> w) noexcept {
        using std::pow;
        return {pow(v.r,w.r), pow(v.g,w.g), pow(v.b,w.b)};
    }

    template <typename T>
    inline basic_rgb<T> pow(basic_rgb<T> v, typename basic_rgb<T>::value_type w) noexcept {
        using std::pow;
        return {pow(v.r,w), pow(v.g,w), pow(v.b,w)};
    }

    template <typename T>
    inline basic_rgb<T> pow(typename basic_rgb<T>::value_type v, basic_rgb<T> w) noexcept {
        using std::pow;
        return {pow(v,w.r), pow(v,w.g), pow(v,w.b)};
    }

    template <typename T>
    inline basic_rgb<T> sqrt(basic_rgb<T> v) noexcept {
        using std::sqrt;
        return {sqrt(v.r), sqrt(v.g), sqrt(v.b)};
    }

    template <typename T>
    inline basic_rgb<T> cbrt(basic_rgb<T> v) noexcept {
        using std::cbrt;
        return {cbrt(v.r), cbrt(v.g), cbrt(v.b)};
    }

    template <typename T>
    inline basic_rgb<T> hypot(basic_rgb<T> v, basic_rgb<T> w) noexcept {
        using std::hypot;
        return {hypot(v.r,w.r), hypot(v.g,w.g), hypot(v.b,w.b)};
    }

    template <typename T>
    inline basic_rgb<T> hypot(basic_rgb<T> v, typename basic_rgb<T>::value_type w) noexcept {
        using std::hypot;
        return {hypot(v.r,w), hypot(v.g,w), hypot(v.b,w)};
    }

    template <typename T>
    inline basic_rgb<T> hypot(typename basic_rgb<T>::value_type v, basic_rgb<T> w) noexcept {
        using std::hypot;
        return {hypot(v,w.r), hypot(v,w.g), hypot(v,w.b)};
    }

    // error and gamma
    template <typename T>
    inline basic_rgb<T> erf (basic_rgb<T> v) noexcept {
        using std::erf;
        return {erf(v.r),  erf(v.g),  erf(v.b)};
    }
    template <typename T>
    inline basic_rgb<T> erfc(basic_rgb<T> v) noexcept {
        using std::erfc;
        return {erfc(v.r), erfc(v.g), erfc(v.b)};
    }
    template <typename T>
    inline basic_rgb<T> lgamma(basic_rgb<T> v) noexcept {
        using std::lgamma;
        return {lgamma(v.r),lgamma(v.g),lgamma(v.b)};
    }
    template <typename T>
    inline basic_rgb<T> tgamma(basic_rgb<T> v) noexcept {
        using std::tgamma;
        return {tgamma(v.r),tgamma(v.g),tgamma(v.b)};
    }


    // rounding and remainder
    template <typename T>
    inline basic_rgb<T> ceil (basic_rgb<T> v) noexcept {
        using std::ceil;
        return {ceil(v.r), ceil(v.g), ceil(v.b)};
    }

    template <typename T>
    inline basic_rgb<T> floor(basic_rgb<T> v) noexcept {
        using std::floor;
        return {floor(v.r),floor(v.g),floor(v.b)};
    }

    template <typename T>
    inline basic_rgb<T> fmod(basic_rgb<T> num, basic_rgb<T> denom) noexcept {
        using std::fmod;
        return{ fmod(num.r, denom.r), fmod(num.g, denom.g), fmod(num.b, denom.b) };
    }

    template <typename T>
    inline basic_rgb<T> trunc(basic_rgb<T> v) noexcept {
        using std::trunc;
        return {trunc(v.r),trunc(v.g),trunc(v.b)};
    }

    template <typename T>
    inline basic_rgb<T> round(basic_rgb<T> v) noexcept {
        using std::round;
        return {round(v.r),round(v.g),round(v.b)};
    }

    template <typename T>
    inline basic_rgb<long> lround(basic_rgb<T> v) noexcept{
        using std::lround;
        return {lround(v.r), lround(v.g), lround(v.b)};
    }
    template <typename T>
    inline basic_rgb<long long> llround(basic_rgb<T> v) noexcept{
        using std::llround;
        return {llround(v.r), llround(v.g), llround(v.b)};
    }

    template <typename T>
    inline basic_rgb<T> rint (basic_rgb<T> v) noexcept {
        using std::rint;
        return {rint(v.r), rint(v.g), rint(v.b)};
    }

    template <typename T>
    inline basic_rgb<long> lrint(basic_rgb<T> v) noexcept{
        using std::lrint;
        return {lrint(v.r), lrint(v.g), lrint(v.b)};
    }
    template <typename T>
    inline basic_rgb<long long> llrint(basic_rgb<T> v)noexcept{
        using std::llrint;
        return {llrint(v.r), llrint(v.g), llrint(v.b)};
    }

    template <typename T>
    inline basic_rgb<T> nearbyint(basic_rgb<T> v) noexcept {
        using std::nearbyint;
        return {nearbyint(v.r), nearbyint(v.g), nearbyint(v.b)};
    }

    template <typename T>
    inline basic_rgb<T> remainder (basic_rgb<T> num, basic_rgb<T> denom) noexcept {
        using std::remainder;
        return { remainder(num.r, denom.r),
                 remainder(num.g, denom.g),
                 remainder(num.b, denom.b) };
    }

    template <typename T>
    inline basic_rgb<T> remquo (basic_rgb<T> num, basic_rgb<T> denom, basic_rgb<int> *quot) noexcept {
        using std::remquo;
        return { remquo(num.r, denom.r, &quot->r),
                 remquo(num.g, denom.g, &quot->g),
                 remquo(num.b, denom.b, &quot->b) };
    }

    // floating point manipulation
    template <typename T>
    inline basic_rgb<T> copysign(basic_rgb<T> x, basic_rgb<T> y) noexcept {
        using std::copysign;
        return { copysign(x.r, y.r),
                 copysign(x.g, y.g),
                 copysign(x.b, y.b) };
    }

    template <typename T>
    inline basic_rgb<T> nextafter(basic_rgb<T> x, basic_rgb<T> y) noexcept {
        using std::nextafter;
        return { nextafter(x.r, y.r),
                 nextafter(x.g, y.g),
                 nextafter(x.b, y.b) };
    }

    template <typename T>
    inline basic_rgb<T> nexttoward(basic_rgb<T> x, basic_rgb<long double> y) noexcept {
        using std::nexttoward;
        return { nexttoward(x.r, y.r),
                 nexttoward(x.g, y.g),
                 nexttoward(x.b, y.b) };
    }

    // Not implementing the NAN macro constant, because we would need to be able to overload macros.

    // min, max, difference
    template <typename T>
    inline basic_rgb<T> fmin(basic_rgb<T> x, basic_rgb<T> y) noexcept {
        using std::fmin;
        return { fmin(x.r, y.r),
                 fmin(x.g, y.g),
                 fmin(x.b, y.b) };
    }

    template <typename T>
    inline basic_rgb<T> fmax(basic_rgb<T> x, basic_rgb<T> y) noexcept {
        using std::fmax;
        return { fmax(x.r, y.r),
                 fmax(x.g, y.g),
                 fmax(x.b, y.b) };
    }

    template <typename T>
    inline basic_rgb<T> fdim(basic_rgb<T> x, basic_rgb<T> y) noexcept {
        using std::fdim;
        return { fdim(x.r, y.r),
                 fdim(x.g, y.g),
                 fdim(x.b, y.b) };
    }

    // other
    template <typename T>
    inline basic_rgb<T> fabs(basic_rgb<T> v) noexcept {
        using std::fabs;
        return {fabs(v.r),fabs(v.g),fabs(v.b)};
    }

    template <typename T>
    inline basic_rgb<T> abs(basic_rgb<T> v) noexcept {
        using std::abs;
        return {abs(v.r),abs(v.g),abs(v.b)};
    }

    template <typename T>
    inline basic_rgb<T> fma(basic_rgb<T> x, basic_rgb<T> y, basic_rgb<T> z) noexcept {
        using std::fma;
        return { fma(x.r, y.r, z.r),
                 fma(x.g, y.g, z.g),
                 fma(x.b, y.b, z.b) };
    }

    // classification functions

    // comparison functions

}

#endif // RGB_HH_INCLUDED_20131017

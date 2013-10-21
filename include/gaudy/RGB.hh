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

        float r=0, g=0, b=0;

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

    // -- <cmath> ---------------------------------------------------------------------------------

    // TODO: replace all std-qualifcations by a using

    //-- -- -- -- --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  -- --
    // Info: While glibcxx defines some (many? (all?)) cmath functions as constexpr, this is not
    //       sanctioned  by  the  C++11  standard,  therefore we are not making the  promise  of
    //       constexpr, as such code is non-portable.
    //-- -- -- -- --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  -- --


    // trigonometric
    template <typename T>
    inline basic_rgb<T> cos(basic_rgb<T> v) noexcept { using std::cos;
                                                       return basic_rgb<T>(cos(v.r), cos(v.g), cos(v.b)); }

    template <typename T>
    inline basic_rgb<T> sin(basic_rgb<T> v) noexcept { using std::sin;
                                                       return basic_rgb<T>(sin(v.r), sin(v.g), sin(v.b)); }

    template <typename T>
    inline basic_rgb<T> tan(basic_rgb<T> v) noexcept { using std::tan;
                                                       return basic_rgb<T>(tan(v.r), tan(v.g), tan(v.b)); }

    template <typename T>
    inline basic_rgb<T> acos(basic_rgb<T> v) noexcept { using std::acos;
                                                        return basic_rgb<T>(acos(v.r), acos(v.g), acos(v.b)); }

    template <typename T>
    inline basic_rgb<T> asin(basic_rgb<T> v) noexcept { using std::asin;
                                                        return basic_rgb<T>(asin(v.r), asin(v.g), asin(v.b)); }

    template <typename T>
    inline basic_rgb<T> atan(basic_rgb<T> v) noexcept { using std::atan;
                                                        return basic_rgb<T>(atan(v.r), atan(v.g), atan(v.b)); }

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
    inline RGB exp(RGB v) noexcept { return RGB{std::exp(v.r), std::exp(v.g), std::exp(v.b)}; }

    // TODO: the second parameter should be RGB<int>, once RGB is generified
    inline RGB frexp(RGB v, RGB *exp) noexcept {
        using std::frexp;
        int exp_r, exp_g, exp_b;
        RGB sig {frexp(v.r, &exp_r),
                 frexp(v.g, &exp_g),
                 frexp(v.b, &exp_b)};
        *exp = RGB(exp_r, exp_g, exp_b);
        return sig;
    }

    // TODO: the second parameter should be RGB<int>, once RGB is generified
    inline RGB frexp(RGB sig, RGB exp) noexcept {
        using std::ldexp;
        return {ldexp(sig.r, exp.r),
                ldexp(sig.g, exp.g),
                ldexp(sig.b, exp.b)};
    }

    inline RGB log(RGB v) noexcept { return {std::log(v.r), std::log(v.g), std::log(v.b)}; }
    inline RGB log10(RGB v)noexcept{return {std::log10(v.r), std::log10(v.g), std::log10(v.b)};}

    inline RGB modf(RGB v, RGB *intpart) noexcept {
        using std::modf;
        return { modf(v.r, &intpart->r),
                 modf(v.g, &intpart->g),
                 modf(v.b, &intpart->b) };
    }

    inline RGB exp2(RGB v)noexcept{return {std::exp2(v.r), std::exp2(v.g), std::exp2(v.b)};}
    inline RGB expm1(RGB v)noexcept{return {std::expm1(v.r), std::expm1(v.g), std::expm1(v.b)};}

    // TODO: the return type should be RGB<int>, once RGB is generified
    inline RGB ilogb(RGB v)noexcept{using std::ilogb; return RGB(ilogb(v.r),ilogb(v.g),ilogb(v.b));}

    inline RGB log1p(RGB v) noexcept{ using std::log1p; return {log1p(v.r),log1p(v.g),log1p(v.b)}; }
    inline RGB log2 (RGB v) noexcept{ using std::log2;  return {log2(v.r),log2(v.g),log2(v.b)}; }

    inline RGB scalbn (RGB v, int n) noexcept {
        using std::scalbn;  return {scalbn(v.r,n), scalbn(v.g,n), scalbn(v.b,n)};
    }
    inline RGB scalbn (RGB v, RGB n) noexcept { // TODO: RGB<int> as rhs
        using std::scalbn;
        return {scalbn(v.r,(int)n.r), scalbn(v.g,(int)n.g), scalbn(v.b,(int)n.b)};
    }

    inline RGB scalbln (RGB v, long n) noexcept {
        using std::scalbln;
        return {scalbln(v.r,n), scalbln(v.g,n), scalbln(v.b,n)};
    }
    inline RGB scalbln (RGB v, RGB n) noexcept { // TODO: RGB<long> as rhs
        using std::scalbln;
        return {scalbln(v.r,(long)n.r), scalbln(v.g,(long)n.g), scalbln(v.b,(long)n.b)};
    }


    // power
    inline RGB pow(RGB v, RGB w) noexcept { return RGB{std::pow(v.r,w.r),
                                                       std::pow(v.g,w.g),
                                                       std::pow(v.b,w.b)}; }
    inline RGB pow(RGB v, float w) noexcept { return RGB{std::pow(v.r,w),
                                                         std::pow(v.g,w),
                                                         std::pow(v.b,w)}; }
    inline RGB pow(float v, RGB w) noexcept { return RGB{std::pow(v,w.r),
                                                         std::pow(v,w.g),
                                                         std::pow(v,w.b)}; }

    inline RGB sqrt(RGB v) noexcept { return RGB{std::sqrt(v.r), std::sqrt(v.g), std::sqrt(v.b)}; }
    inline RGB cbrt(RGB v) noexcept { return RGB{std::cbrt(v.r), std::cbrt(v.g), std::cbrt(v.b)}; }


    inline RGB hypot(RGB v, RGB w) noexcept { return RGB{std::hypot(v.r,w.r),
                                                         std::hypot(v.g,w.g),
                                                         std::hypot(v.b,w.b)}; }
    inline RGB hypot(RGB v, float w) noexcept { return RGB{std::hypot(v.r,w),
                                                           std::hypot(v.g,w),
                                                           std::hypot(v.b,w)}; }
    inline RGB hypot(float v, RGB w) noexcept { return RGB{std::hypot(v,w.r),
                                                           std::hypot(v,w.g),
                                                           std::hypot(v,w.b)}; }

    // error and gamma
    inline RGB erf (RGB v) noexcept { using std::erf;  return {erf(v.r),  erf(v.g),  erf(v.b)};  }
    inline RGB erfc(RGB v) noexcept { using std::erfc; return {erfc(v.r), erfc(v.g), erfc(v.b)}; }
    inline RGB lgamma(RGB v)noexcept{using std::lgamma;return{lgamma(v.r),lgamma(v.g),lgamma(v.b)};}
    inline RGB tgamma(RGB v)noexcept{using std::tgamma;return{tgamma(v.r),tgamma(v.g),tgamma(v.b)};}


    // rounding and remainder
    inline RGB ceil (RGB v) noexcept { using std::ceil;  return {ceil(v.r), ceil(v.g), ceil(v.b)}; }
    inline RGB floor(RGB v) noexcept { using std::floor; return {floor(v.r),floor(v.g),floor(v.b)};}
    inline RGB fmod(RGB num, RGB denom) noexcept {
        using std::fmod;
        return{ fmod(num.r, denom.r), fmod(num.g, denom.g), fmod(num.b, denom.b) };
    }
    inline RGB trunc(RGB v) noexcept { using std::trunc; return {trunc(v.r),trunc(v.g),trunc(v.b)};}
    inline RGB round(RGB v) noexcept { using std::round; return {round(v.r),round(v.g),round(v.b)};}

    // TODO: use RGB<int> and RGB<long long>
    inline RGB lround(RGB v) noexcept{
        using std::lround;
        return RGB(lround(v.r), lround(v.g), lround(v.b));
    }
    inline RGB llround(RGB v)noexcept{
        using std::llround;
        return RGB(llround(v.r), llround(v.g), llround(v.b));
    }

    inline RGB rint (RGB v) noexcept { using std::rint; return {rint(v.r), rint(v.g), rint(v.b)}; }

    // TODO: use RGB<int> and RGB<long long>
    inline RGB lrint(RGB v) noexcept{
        using std::lrint;
        return RGB(lrint(v.r), lrint(v.g), lrint(v.b));
    }
    inline RGB llrint(RGB v)noexcept{
        using std::llrint;
        return RGB(llrint(v.r), llrint(v.g), llrint(v.b));
    }

    inline RGB nearbyint(RGB v) noexcept {
        using std::nearbyint;
        return {nearbyint(v.r), nearbyint(v.g), nearbyint(v.b)};
    }

    inline RGB remainder (RGB num, RGB denom) noexcept {
        using std::remainder;
        return { remainder(num.r, denom.r),
                 remainder(num.g, denom.g),
                 remainder(num.b, denom.b) };
    }

    inline RGB remquo (RGB num, RGB denom, RGB *quot) noexcept {
        using std::remquo;
        int quot_r, quot_g, quot_b;
        RGB ret { remquo(num.r, denom.r, &quot_r),
                  remquo(num.g, denom.g, &quot_g),
                  remquo(num.b, denom.b, &quot_b)};
        quot->r = quot_r;
        quot->g = quot_g;
        quot->b = quot_b;
        return ret;
    }

    // floating point manipulation

    // min, max, difference

    // other

    // classification functions

    // comparison functions


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

#endif // RGB_HH_INCLUDED_20131017

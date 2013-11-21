// (C) 2013 Sebastian Mach (1983), this file is published under the terms of the
// GNU General Public License, Version 3 (a.k.a. GPLv3).
// See COPYING in the root-folder of the excygen project folder.
#ifndef CMATH_HH_INCLUDED_20131102
#define CMATH_HH_INCLUDED_20131102

#include <cmath>
#include <utility>
#include "RGB.hh" // TODO: remove once generified

namespace gaudy {

    //----------------------------------------------------------------------------------------------
    // Note that some definitions look wilder than they are. For example cos may look like:
    //
    //   template <typename V, typename ...R, template <typename...> class T>
    //   inline auto cos(T<V,R...> v) noexcept -> T<cmath_or_adl::cos_type<V>, R...> {
    //      return apply(v, [](typename T<V,R...>::value_type f){using std::cos; return cos(f);});
    //   }
    //
    // The reason for template templates and variadic template arguments is that some math function
    // return a different type than they take, for example ilogb.
    //
    // With C++14, this could be immediately stripped down to ...
    //
    //   template <typename T>
    //   inline auto cos(T v) noexcept {
    //      return apply(v, [](typename T::value_type f) {using std::cos; return cos(f);});
    //   }
    //
    // ... because the apply-function does already the proper type conversions for us.
    //
    // Reading advice: All functions really mainly differ in the body of the used lambda:
    //
    //      return apply(v, [](typename T::value_type f) {using std::cos; return cos(f);});
    //                                                    ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
    //
    // And because that pattern is used everywhere, the really mainly differ in just their name:
    //
    //      ....... cos(...) .....
    //
    // Which is the same as in cmath. Looks all worse than it is :).
    //----------------------------------------------------------------------------------------------

    namespace cmath_or_adl {
      using std::ilogb; template <typename T> using ilogb_type = decltype(ilogb(std::declval<T>()));
    }
    // -- <cmath> ---------------------------------------------------------------------------------
    // DONE: replace all std-qualifcations by a using
    // TODO: for some functions, add permutations of RGB, Scalar operands
    //-- -- -- -- --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  -- --
    // Info: While glibcxx defines some (many? (all?)) cmath functions as constexpr, this is not
    //       sanctioned  by  the  C++11  standard,  therefore we are not making the  promise  of
    //       constexpr, as such code is non-portable.
    //-- -- -- -- --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  -- --

    template <typename>   struct has_apply_interface               : std::false_type {};
    template <typename T> struct has_apply_interface<basic_rgb<T>> : std::true_type  {};

    // This is a type alias which is only defined if for T, there exists an apply interface.
    // Used for SFINAE.
    // The idea of using EnableIf in the template argument list is by R. Martinho Fernandez,
    // (http://flamingdangerzone.com/cxx11/2012/06/01/almost-static-if.html)
    namespace detail {
        enum class enabler {};
    }
    template <typename T> using HasConceptApply = typename std::enable_if<has_apply_interface<T>::value, detail::enabler>::type;

    template <typename Cond, typename ...Rest>
    struct all { enum { value = Cond::value && all<Rest...>::value }; };
    template <typename Cond>
    struct all<Cond> { enum { value = Cond::value }; };

    template <typename ...Condition> using EnableIf =
                typename std::enable_if<all<Condition...>::value, detail::enabler>::type;

    // TODO: introduce some template "rebind_value_type"



    // -- trigonometric ----------------------------------------------------------------------------
    template <typename T, EnableIf<has_apply_interface<T>>...> T cos (T v) noexcept ;
    template <typename T, EnableIf<has_apply_interface<T>>...> T sin (T v) noexcept ;
    template <typename T, EnableIf<has_apply_interface<T>>...> T tan (T v) noexcept ;
    template <typename T, EnableIf<has_apply_interface<T>>...> T acos(T v) noexcept ;
    template <typename T, EnableIf<has_apply_interface<T>>...> T asin(T v) noexcept ;
    template <typename T, EnableIf<has_apply_interface<T>>...> T atan(T v) noexcept ;

    template <typename T, EnableIf<has_apply_interface<T>>...> T atan2(T v, T w) noexcept ;
    template <typename T, EnableIf<has_apply_interface<T>>...> T atan2(T v, typename T::value_type w) noexcept ;
    template <typename T, EnableIf<has_apply_interface<T>>...> T atan2(typename T::value_type v, T w) noexcept ;

    // -- hyperbolic -------------------------------------------------------------------------------
    template <typename T, EnableIf<has_apply_interface<T>>...> T cosh(T v) noexcept ;
    template <typename T, EnableIf<has_apply_interface<T>>...> T sinh(T v) noexcept ;
    template <typename T, EnableIf<has_apply_interface<T>>...> T tanh(T v) noexcept ;
    template <typename T, EnableIf<has_apply_interface<T>>...> T acosh(T v) noexcept ;
    template <typename T, EnableIf<has_apply_interface<T>>...> T asinh(T v) noexcept ;
    template <typename T, EnableIf<has_apply_interface<T>>...> T atanh(T v) noexcept ;

    // -- exponential and logarithmic --------------------------------------------------------------
    template <typename T, EnableIf<has_apply_interface<T>>...> T exp(T v) noexcept ;
    template <typename T, typename ...RHS_ARGS, template <typename...> class RHS,
              EnableIf<has_apply_interface<T>>...>
        T frexp(T v, RHS<int, RHS_ARGS...> *exp) noexcept ;
    template <typename T, typename ...RHS_ARGS, template <typename...> class RHS,
              EnableIf<has_apply_interface<T>>...>
        T ldexp(T sig, RHS<int, RHS_ARGS...> exp) noexcept ;
    template <typename T, EnableIf<has_apply_interface<T>>...> T log(T v) noexcept ;
    template <typename T, EnableIf<has_apply_interface<T>>...> T log10(T v) noexcept ;
    template <typename T, EnableIf<has_apply_interface<T>>...> T modf(T v, T *intpart) noexcept ;
    template <typename T, EnableIf<has_apply_interface<T>>...> T exp2(T v) noexcept ;
    template <typename T, EnableIf<has_apply_interface<T>>...> T expm1(T v) noexcept ;
    template <typename V, typename ...R, template <typename...> class T,
              EnableIf<has_apply_interface<T<V,R...>>>...>
        auto ilogb(T<V,R...> v) noexcept -> T<cmath_or_adl::ilogb_type<V>, R...> ;
    template <typename T, EnableIf<has_apply_interface<T>>...> T log1p(T v) noexcept ;
    template <typename T, EnableIf<has_apply_interface<T>>...> T log2 (T v) noexcept ;

    template <typename T, EnableIf<has_apply_interface<T>>...>
        T scalbn (T v, int n) noexcept ;
    template <typename T, typename ...RHS_ARGS, template <typename...> class RHS,
              EnableIf<has_apply_interface<T>>...>
        T scalbn(T v, RHS<int, RHS_ARGS...> n) noexcept ;

    template <typename T, EnableIf<has_apply_interface<T>>...>
        T scalbln (T v, long n) noexcept ;
    template <typename T, typename ...RHS_ARGS, template <typename...> class RHS,
              EnableIf<has_apply_interface<T>>...>
        T scalbln(T v, RHS<long, RHS_ARGS...> n) noexcept ;


    // -- power ------------------------------------------------------------------------------------
    template <typename T, EnableIf<has_apply_interface<T>>...> T pow(T v, T w) noexcept ;
    template <typename T, EnableIf<has_apply_interface<T>>...> T pow(T v, typename T::value_type w) noexcept ;
    template <typename T, EnableIf<has_apply_interface<T>>...> T pow(typename T::value_type v, T w) noexcept ;
    template <typename T, EnableIf<has_apply_interface<T>>...> T sqrt(T v) noexcept ;
    template <typename T, EnableIf<has_apply_interface<T>>...> T cbrt(T v) noexcept ;
    template <typename T, EnableIf<has_apply_interface<T>>...> T hypot(T v, T w) noexcept ;
    template <typename T, EnableIf<has_apply_interface<T>>...> T hypot(T v, typename T::value_type w) noexcept ;
    template <typename T, EnableIf<has_apply_interface<T>>...> T hypot(typename T::value_type v, T w) noexcept ;

    // -- error and gamma --------------------------------------------------------------------------
    template <typename T, EnableIf<has_apply_interface<T>>...> T erf (T v) noexcept ;
    template <typename T, EnableIf<has_apply_interface<T>>...> T erfc(T v) noexcept ;
    template <typename T, EnableIf<has_apply_interface<T>>...> T lgamma(T v) noexcept ;
    template <typename T, EnableIf<has_apply_interface<T>>...> T tgamma(T v) noexcept ;

    // -- rounding and remainder -------------------------------------------------------------------
    template <typename T, EnableIf<has_apply_interface<T>>...> T ceil (T v) noexcept ;
    template <typename T, EnableIf<has_apply_interface<T>>...> T floor(T v) noexcept ;
    template <typename T, EnableIf<has_apply_interface<T>>...> T fmod(T num, T denom) noexcept ;
    template <typename T, EnableIf<has_apply_interface<T>>...> T fmod(T num, typename T::value_type denom) noexcept ;
    template <typename T, EnableIf<has_apply_interface<T>>...> T fmod(typename T::value_type num, T denom) noexcept ;
    template <typename T, EnableIf<has_apply_interface<T>>...> T trunc(T v) noexcept ;
    template <typename T, EnableIf<has_apply_interface<T>>...> T round(T v) noexcept ;
    template <typename V, typename ...R, template <typename...> class T, EnableIf<has_apply_interface<T<V,R...>>>...>
        T<long,R...> lround(T<V,R...> v) noexcept ;
    template <typename V, typename ...R, template <typename...> class T, EnableIf<has_apply_interface<T<V,R...>>>...>
        T<long long,R...> llround(T<V,R...> v) noexcept ;

    template <typename T, EnableIf<has_apply_interface<T>>...> T rint (T v) noexcept ;
    template <typename V, typename ...R, template <typename...> class T, EnableIf<has_apply_interface<T<V,R...>>>...>
        T<long,R...> lrint(T<V,R...> v) noexcept ;
    template <typename V, typename ...R, template <typename...> class T, EnableIf<has_apply_interface<T<V,R...>>>...>
        T<long long,R...> llrint(T<V,R...> v) noexcept ;

    template <typename T, EnableIf<has_apply_interface<T>>...> T nearbyint(T v) noexcept ;
    template <typename T, EnableIf<has_apply_interface<T>>...> T remainder (T num, T denom) noexcept ;
    template <typename T, EnableIf<has_apply_interface<T>>...> T remainder (T num, typename T::value_type denom) noexcept ;
    template <typename T, EnableIf<has_apply_interface<T>>...> T remainder (typename T::value_type num, T denom) noexcept ;

    template <typename V, typename ...R, template <typename...> class T,
              EnableIf<has_apply_interface<T<V,R...>>>...>
           T<V,R...> remquo (T<V,R...> num, T<V,R...> denom, T<int,R...> *quot) noexcept ;
    template <typename V, typename ...R, template <typename...> class T,
              EnableIf<has_apply_interface<T<V,R...>>>...>
           T<V,R...> remquo (T<V,R...> num, typename T<V,R...>::value_type denom, T<int,R...> *quot) noexcept ;
    template <typename V, typename ...R, template <typename...> class T,
              EnableIf<has_apply_interface<T<V,R...>>>...>
           T<V,R...> remquo (typename T<V,R...>::value_type num, T<V,R...> denom, T<int,R...> *quot) noexcept ;

    // -- floating point manipulation --------------------------------------------------------------
    template <typename T, EnableIf<has_apply_interface<T>>...> T copysign(T x, T y) noexcept ;
    template <typename T, EnableIf<has_apply_interface<T>>...> T copysign(T x, typename T::value_type y) noexcept ;
    template <typename T, EnableIf<has_apply_interface<T>>...> T copysign(typename T::value_type x, T y) noexcept ;
    template <typename T, EnableIf<has_apply_interface<T>>...> T nextafter(T x, T y) noexcept ;
    template <typename T, EnableIf<has_apply_interface<T>>...> T nextafter(T x, typename T::value_type y) noexcept ;
    template <typename T, EnableIf<has_apply_interface<T>>...> T nextafter(typename T::value_type x, T y) noexcept ;

    template <typename V, typename ...R, template <typename...> class T,
              EnableIf<has_apply_interface<T<V,R...>>>...>
            T<V,R...> nexttoward(T<V,R...> x, T<long double,R...> y) noexcept ;

    template <typename T, EnableIf<has_apply_interface<T>>...>
            T nexttoward(T x, long double y) noexcept ;

    template <typename V, typename ...R, template <typename...> class T,
              EnableIf<has_apply_interface<T<V,R...>>>...>
            T<V,R...> nexttoward(V x, T<long double,R...> y) noexcept ;
    // NAN macro constant not implemented, because we would need to be able to overload macros.

    // -- min, max, difference ---------------------------------------------------------------------
    template <typename T, EnableIf<has_apply_interface<T>>...> T fmin(T x, T y) noexcept ;
    template <typename T, EnableIf<has_apply_interface<T>>...> T fmax(T x, T y) noexcept ;
    template <typename T, EnableIf<has_apply_interface<T>>...> T fdim(T x, T y) noexcept ;
    template <typename T, EnableIf<has_apply_interface<T>>...> T fmin(T x, typename T::value_type y) noexcept ;
    template <typename T, EnableIf<has_apply_interface<T>>...> T fmax(T x, typename T::value_type y) noexcept ;
    template <typename T, EnableIf<has_apply_interface<T>>...> T fdim(T x, typename T::value_type y) noexcept ;
    template <typename T, EnableIf<has_apply_interface<T>>...> T fmin(typename T::value_type x, T y) noexcept ;
    template <typename T, EnableIf<has_apply_interface<T>>...> T fmax(typename T::value_type x, T y) noexcept ;
    template <typename T, EnableIf<has_apply_interface<T>>...> T fdim(typename T::value_type x, T y) noexcept ;

    // -- other ------------------------------------------------------------------------------------
    template <typename T, EnableIf<has_apply_interface<T>>...> T fabs(T v) noexcept ;
    template <typename T, EnableIf<has_apply_interface<T>>...> T abs(T v) noexcept ;

    // fma comes in many overloads:
    //   fma (RGB,    RGB,    RGB   )
    //   fma (RGB,    RGB,    Scalar)
    //   fma (RGB,    Scalar, RGB   )
    //   fma (RGB,    Scalar, Scalar)
    //   fma (Scalar, RGB,    RGB   )
    //   fma (Scalar, RGB,    Scalar)
    //   fma (Scalar, Scalar, RGB   )
    //   fma (Scalar, Scalar, Scalar) <-- this is given by cmath
    template <typename T, EnableIf<has_apply_interface<T>>...> T fma(T x, T y, T z) noexcept ;
    template <typename T, EnableIf<has_apply_interface<T>>...> T fma(T x, T y, typename T::value_type z) noexcept ;
    template <typename T, EnableIf<has_apply_interface<T>>...> T fma(T x, typename T::value_type y, T z) noexcept ;
    template <typename T, EnableIf<has_apply_interface<T>>...> T fma(T x, typename T::value_type y, typename T::value_type z) noexcept ;
    template <typename T, EnableIf<has_apply_interface<T>>...> T fma(typename T::value_type x, T y, T z) noexcept ;
    template <typename T, EnableIf<has_apply_interface<T>>...> T fma(typename T::value_type x, T y, typename T::value_type z) noexcept ;
    template <typename T, EnableIf<has_apply_interface<T>>...> T fma(typename T::value_type x, typename T::value_type y, T z) noexcept ;

    // -- classification functions -----------------------------------------------------------------

    // -- comparison functions ---------------------------------------------------------------------

}



namespace gaudy {    
    // trigonometric
    template <typename T,
              EnableIf<has_apply_interface<T>>...>
    inline T cos(T v) noexcept
    {
        using V = typename T::value_type;
        return apply(v, [](V f){using std::cos; return cos(f);});
    }

    template <typename T,
              EnableIf<has_apply_interface<T>>...>
    inline T sin(T v) noexcept {
        using V = typename T::value_type;
        return apply(v, [](V f){using std::sin; return sin(f);});
    }

    template <typename T,
              EnableIf<has_apply_interface<T>>...>
    inline T tan(T v) noexcept {
        using V = typename T::value_type;
        return apply(v, [](V f){using std::tan; return tan(f);});
    }

    template <typename T,
              EnableIf<has_apply_interface<T>>...>
    inline T acos(T v) noexcept {
        using V = typename T::value_type;
        return apply(v, [](V f){using std::acos; return acos(f);});
    }

    template <typename T,
              EnableIf<has_apply_interface<T>>...>
    inline T asin(T v) noexcept {
        using V = typename T::value_type;
        return apply(v, [](V f){using std::asin; return asin(f);});
    }

    template <typename T,
              EnableIf<has_apply_interface<T>>...>
    inline T atan(T v) noexcept  {
        using V = typename T::value_type;
        return apply(v, [](V f){using std::atan; return atan(f);});
    }

    template <typename T,
              EnableIf<has_apply_interface<T>>...>
    inline T atan2(T v, T w) noexcept {
        using V = typename T::value_type;
        return apply(v, w, [](V f, V g){using std::atan2; return atan2(f, g);});
    }
    template <typename T,
              EnableIf<has_apply_interface<T>>...>
    inline T atan2(T v, typename T::value_type w) noexcept {
        using V = typename T::value_type;
        return apply(v, w, [](V f, V g){using std::atan2; return atan2(f, g);});
    }
    template <typename T,
              EnableIf<has_apply_interface<T>>...>
    inline T atan2(typename T::value_type v, T w) noexcept {
        using V = typename T::value_type;
        return apply(v, w, [](V f, V g){using std::atan2; return atan2(f, g);});
    }

    // hyperbolic
    template <typename T,
              EnableIf<has_apply_interface<T>>...>
    inline T cosh(T v) noexcept {
        using V = typename T::value_type;
        return apply(v, [](V f){using std::cosh; return cosh(f);});
    }

    template <typename T,
              EnableIf<has_apply_interface<T>>...>
    inline T sinh(T v) noexcept {
        using V = typename T::value_type;
        return apply(v, [](V f){using std::sinh; return sinh(f);});
    }

    template <typename T,
              EnableIf<has_apply_interface<T>>...>
    inline T tanh(T v) noexcept {
        using V = typename T::value_type;
        return apply(v, [](V f){using std::tanh; return tanh(f);});
    }

    template <typename T,
              EnableIf<has_apply_interface<T>>...>
    inline T acosh(T v) noexcept {
        using V = typename T::value_type;
        return apply(v, [](V f){using std::acosh; return acosh(f);});
    }

    template <typename T,
              EnableIf<has_apply_interface<T>>...>
    inline T asinh(T v) noexcept {
        using V = typename T::value_type;
        return apply(v, [](V f){using std::asinh; return asinh(f);});
    }

    template <typename T,
              EnableIf<has_apply_interface<T>>...>
    inline T atanh(T v) noexcept {
        using V = typename T::value_type;
        return apply(v, [](V f){using std::atanh; return atanh(f);});
    }

    // exponential and logarithmic
    template <typename T,
              EnableIf<has_apply_interface<T>>...>
    inline T exp(T v) noexcept {
        using V = typename T::value_type;
        return apply(v, [](V f){using std::exp; return exp(f);});
    }

    template <typename T, typename ...RHS_ARGS, template <typename...> class RHS,
              EnableIf<has_apply_interface<T>>...>
    inline T frexp(T v, RHS<int, RHS_ARGS...> *exp) noexcept {
        using V = typename T::value_type;
        return apply(v, exp, [](V f, int *e){using std::frexp; return frexp(f, e);});
    }

    template <typename T, typename ...RHS_ARGS, template <typename...> class RHS,
              EnableIf<has_apply_interface<T>>...>
    inline T ldexp(T sig, RHS<int, RHS_ARGS...> exp) noexcept {
        using V = typename T::value_type;
        return apply(sig, exp, [](V f, int e){using std::ldexp; return ldexp(f, e);});
    }

    template <typename T,
              EnableIf<has_apply_interface<T>>...>
    inline T log(T v) noexcept {
        using V = typename T::value_type;
        return apply(v, [](V f){using std::log; return log(f);});
    }

    template <typename T,
              EnableIf<has_apply_interface<T>>...>
    inline T log10(T v) noexcept {
        using V = typename T::value_type;
        return apply(v, [](V f){using std::log10; return log10(f);});
    }

    template <typename T,
              EnableIf<has_apply_interface<T>>...>
    inline T modf(T v, T *intpart) noexcept {
        using V = typename T::value_type;
        return apply(v, intpart, [](V f, V *e){using std::modf; return modf(f, e);});
    }

    template <typename T,
              EnableIf<has_apply_interface<T>>...>
    inline T exp2(T v) noexcept {
        using V = typename T::value_type;
        return apply(v, [](V f){using std::exp2; return exp2(f);});
    }

    template <typename T,
              EnableIf<has_apply_interface<T>>...>
    inline T expm1(T v) noexcept {
        using V = typename T::value_type;
        return apply(v, [](V f){using std::expm1; return expm1(f);});
    }

    template <typename V, typename ...R, template <typename...> class T,
              EnableIf<has_apply_interface<T<V,R...>>>...>
    inline auto ilogb(T<V,R...> v) noexcept -> T<cmath_or_adl::ilogb_type<V>, R...> {
        return apply(v, [](typename T<V,R...>::value_type f){using std::ilogb; return ilogb(f);});
    }

    template <typename T,
              EnableIf<has_apply_interface<T>>...>
    inline T log1p(T v) noexcept {
        using V = typename T::value_type;
        return apply(v, [](V f){using std::log1p; return log1p(f);});
    }

    template <typename T,
              EnableIf<has_apply_interface<T>>...>
    inline T log2(T v) noexcept {
        using V = typename T::value_type;
        return apply(v, [](V f){using std::log2; return log2(f);});
    }


    template <typename T,
              EnableIf<has_apply_interface<T>>...>
    inline T scalbn (T v, int n) noexcept {
        using V = typename T::value_type;
        return apply(v, n, [](V f, int n){using std::scalbn; return scalbn(f, n);});
    }
    template <typename T, typename ...RHS_ARGS, template <typename...> class RHS,
              EnableIf<has_apply_interface<T>>...>
    inline T scalbn(T v, RHS<int, RHS_ARGS...> n) noexcept {
        using V = typename T::value_type;
        return apply(v, n, [](V f, int n){using std::scalbn; return scalbn(f, n);});
    }


    template <typename T,
              EnableIf<has_apply_interface<T>>...>
    inline T scalbln (T v, long n) noexcept {
        using V = typename T::value_type;
        return apply(v, n, [](V f, long n){using std::scalbln; return scalbln(f, n);});
    }
    template <typename T, typename ...RHS_ARGS, template <typename...> class RHS,
              EnableIf<has_apply_interface<T>>...>
    inline T scalbln(T v, RHS<long, RHS_ARGS...> n) noexcept {
        using V = typename T::value_type;
        return apply(v, n, [](V f, long n){using std::scalbln; return scalbln(f, n);});
    }

    // power
    template <typename T,
              EnableIf<has_apply_interface<T>>...>
    inline T pow(T v, T w) noexcept {
        using V = typename T::value_type;
        return apply(v, w, [](V f, V g){using std::pow; return pow(f, g);});
    }

    template <typename T,
              EnableIf<has_apply_interface<T>>...>
    inline T pow(T v, typename T::value_type w) noexcept {
        using V = typename T::value_type;
        return apply(v, w, [](V f, V g){using std::pow; return pow(f, g);});
    }

    template <typename T,
              EnableIf<has_apply_interface<T>>...>
    inline T pow(typename T::value_type v, T w) noexcept {
        using V = typename T::value_type;
        return apply(v, w, [](V f, V g){using std::pow; return pow(f, g);});
    }

    template <typename T,
              EnableIf<has_apply_interface<T>>...>
    inline T sqrt(T v) noexcept {
        using V = typename T::value_type;
        return apply(v, [](V f){using std::sqrt; return sqrt(f);});
    }

    template <typename T,
              EnableIf<has_apply_interface<T>>...>
    inline T cbrt(T v) noexcept {
        using V = typename T::value_type;
        return apply(v, [](V f){using std::cbrt; return cbrt(f);});
    }

    template <typename T,
              EnableIf<has_apply_interface<T>>...>
    inline T hypot(T v, T w) noexcept {
        using V = typename T::value_type;
        return apply(v, w, [](V f, V g){using std::hypot; return hypot(f, g);});
    }
    template <typename T,
              EnableIf<has_apply_interface<T>>...>
    inline T hypot(T v, typename T::value_type w) noexcept {
        using V = typename T::value_type;
        return apply(v, w, [](V f, V g){using std::hypot; return hypot(f, g);});
    }

    template <typename T,
              EnableIf<has_apply_interface<T>>...>
    inline T hypot(typename T::value_type v, T w) noexcept {
        using V = typename T::value_type;
        return apply(v, w, [](V f, V g){using std::hypot; return hypot(f, g);});
    }

    // error and gamma
    template <typename T,
              EnableIf<has_apply_interface<T>>...>
    inline T erf (T v) noexcept {
        using V = typename T::value_type;
        return apply(v, [](V f){using std::erf; return erf(f);});
    }

    template <typename T,
              EnableIf<has_apply_interface<T>>...>
    inline T erfc(T v) noexcept {
        using V = typename T::value_type;
        return apply(v, [](V f){using std::erfc; return erfc(f);});
    }

    template <typename T,
              EnableIf<has_apply_interface<T>>...>
    inline T lgamma(T v) noexcept {
        using V = typename T::value_type;
        return apply(v, [](V f){using std::lgamma; return lgamma(f);});
    }

    template <typename T,
              EnableIf<has_apply_interface<T>>...>
    inline T tgamma(T v) noexcept {
        using V = typename T::value_type;
        return apply(v, [](V f){using std::tgamma; return tgamma(f);});
    }


    // rounding and remainder
    template <typename T,
              EnableIf<has_apply_interface<T>>...>
    inline T ceil (T v) noexcept {
        using V = typename T::value_type;
        return apply(v, [](V f){using std::ceil; return ceil(f);});
    }

    template <typename T,
              EnableIf<has_apply_interface<T>>...>
    inline T floor(T v) noexcept {
        using V = typename T::value_type;
        return apply(v, [](V f){using std::floor; return floor(f);});
    }

    template <typename T,
              EnableIf<has_apply_interface<T>>...>
    inline T fmod(T num, T denom) noexcept {
        using V = typename T::value_type;
        return apply(num, denom, [](V f, V g){using std::fmod; return fmod(f, g);});
    }
    template <typename T,
              EnableIf<has_apply_interface<T>>...>
    inline T fmod(T num, typename T::value_type denom) noexcept {
        using V = typename T::value_type;
        return apply(num, denom, [](V f, V g){using std::fmod; return fmod(f, g);});
    }
    template <typename T,
              EnableIf<has_apply_interface<T>>...>
    inline T fmod(typename T::value_type num, T denom) noexcept {
        using V = typename T::value_type;
        return apply(num, denom, [](V f, V g){using std::fmod; return fmod(f, g);});
    }

    template <typename T,
              EnableIf<has_apply_interface<T>>...>
    inline T trunc(T v) noexcept {
        using V = typename T::value_type;
        return apply(v, [](V f){using std::trunc; return trunc(f);});
    }

    template <typename T,
              EnableIf<has_apply_interface<T>>...>
    inline T round(T v) noexcept {
        using V = typename T::value_type;
        return apply(v, [](V f){using std::round; return round(f);});
    }

    template <typename V, typename ...R, template <typename...> class T,
              EnableIf<has_apply_interface<T<V,R...>>>...>
    inline T<long,R...> lround(T<V,R...> v) noexcept{
        return apply(v, [](V f){using std::lround; return lround(f);});
    }
    template <typename V, typename ...R, template <typename...> class T,
              EnableIf<has_apply_interface<T<V,R...>>>...>
    inline T<long long,R...> llround(T<V,R...> v) noexcept{
        return apply(v, [](V f){using std::llround; return llround(f);});
    }

    template <typename T,
              EnableIf<has_apply_interface<T>>...>
    inline T rint (T v) noexcept {
        using V = typename T::value_type;
        return apply(v, [](V f){using std::rint; return rint(f);});
    }

    template <typename V, typename ...R, template <typename...> class T,
              EnableIf<has_apply_interface<T<V,R...>>>...>
    inline T<long,R...> lrint(T<V,R...> v) noexcept{
        return apply(v, [](V f){using std::lrint; return lrint(f);});
    }
    template <typename V, typename ...R, template <typename...> class T,
              EnableIf<has_apply_interface<T<V,R...>>>...>
    inline T<long long,R...> llrint(T<V,R...> v) noexcept{
        return apply(v, [](V f){using std::llrint; return llrint(f);});
    }

    template <typename T,
              EnableIf<has_apply_interface<T>>...>
    inline T nearbyint(T v) noexcept {
        using V = typename T::value_type;
        return apply(v, [](V f){using std::nearbyint; return nearbyint(f);});
    }

    template <typename T,
              EnableIf<has_apply_interface<T>>...>
    inline T remainder (T num, T denom) noexcept {
        using V = typename T::value_type;
        return apply(num, denom, [](V f, V g){using std::remainder; return remainder(f, g);});
    }
    template <typename T,
              EnableIf<has_apply_interface<T>>...>
    inline T remainder (T num, typename T::value_type denom) noexcept {
        using V = typename T::value_type;
        return apply(num, denom, [](V f, V g){using std::remainder; return remainder(f, g);});
    }
    template <typename T,
              EnableIf<has_apply_interface<T>>...>
    inline T remainder (typename T::value_type num, T denom) noexcept {
        using V = typename T::value_type;
        return apply(num, denom, [](V f, V g){using std::remainder; return remainder(f, g);});
    }

    template <typename V, typename ...R, template <typename...> class T,
              EnableIf<has_apply_interface<T<V,R...>>>...>
    inline T<V,R...> remquo (T<V,R...> num, T<V,R...> denom, T<int,R...> *quot) noexcept {
        return apply(num, denom, quot, [](V f, V g, int *h){using std::remquo; return remquo(f, g, h);});
    }
    template <typename V, typename ...R, template <typename...> class T,
              EnableIf<has_apply_interface<T<V,R...>>>...>
    inline T<V,R...> remquo (T<V,R...> num, typename T<V,R...>::value_type denom, T<int,R...> *quot) noexcept {
        return apply(num, denom, quot, [](V f, V g, int *h){using std::remquo; return remquo(f, g, h);});
    }
    template <typename V, typename ...R, template <typename...> class T,
              EnableIf<has_apply_interface<T<V,R...>>>...>
    inline T<V,R...> remquo (typename T<V,R...>::value_type num, T<V,R...> denom, T<int,R...> *quot) noexcept {
        return apply(num, denom, quot, [](V f, V g, int *h){using std::remquo; return remquo(f, g, h);});
    }

    // floating point manipulation
    template <typename T,
              EnableIf<has_apply_interface<T>>...>
    inline T copysign(T x, T y) noexcept {
        using V = typename T::value_type;
        return apply(x, y, [](V f, V g){using std::copysign; return copysign(f, g);});
    }
    template <typename T,
              EnableIf<has_apply_interface<T>>...>
    inline T copysign(T x, typename T::value_type y) noexcept {
        using V = typename T::value_type;
        return apply(x, y, [](V f, V g){using std::copysign; return copysign(f, g);});
    }
    template <typename T,
              EnableIf<has_apply_interface<T>>...>
    inline T copysign(typename T::value_type x, T y) noexcept {
        using V = typename T::value_type;
        return apply(x, y, [](V f, V g){using std::copysign; return copysign(f, g);});
    }

    template <typename T,
              EnableIf<has_apply_interface<T>>...>
    inline T nextafter(T x, T y) noexcept {
        using V = typename T::value_type;
        return apply(x, y, [](V f, V g){using std::nextafter; return nextafter(f, g);});
    }
    template <typename T,
              EnableIf<has_apply_interface<T>>...>
    inline T nextafter(T x, typename T::value_type y) noexcept {
        using V = typename T::value_type;
        return apply(x, y, [](V f, V g){using std::nextafter; return nextafter(f, g);});
    }
    template <typename T,
              EnableIf<has_apply_interface<T>>...>
    inline T nextafter(typename T::value_type x, T y) noexcept {
        using V = typename T::value_type;
        return apply(x, y, [](V f, V g){using std::nextafter; return nextafter(f, g);});
    }

    template <typename V, typename ...R, template <typename...> class T,
              EnableIf<has_apply_interface<T<V,R...>>>...>
    inline T<V,R...> nexttoward(T<V,R...> x, T<long double,R...> y) noexcept {
        return apply(x, y, [](V f, V g){using std::nexttoward; return nexttoward(f, g);});
    }
    template <typename T,
              EnableIf<has_apply_interface<T>>...>
    inline T nexttoward(T x, long double y) noexcept {
        using V = typename T::value_type;
        return apply(x, y, [](V f, V g){using std::nexttoward; return nexttoward(f, g);});
    }
    // Note: The following overload does not use our 'basic_rgb<T>::value_type' pattern to prevent
    //       lookup upon the scalar type, but rather uses just 'T', because otherwise lookup
    //       would not be possible.
    template <typename V, typename ...R, template <typename...> class T,
              EnableIf<has_apply_interface<T<V,R...>>>...>
    inline T<V,R...> nexttoward(V x, T<long double,R...> y) noexcept {
        return apply(x, y, [](V f, V g){using std::nexttoward; return nexttoward(f, g);});
    }

    // Not implementing the NAN macro constant, because we would need to be able to overload macros.

    // min, max, difference
    template <typename T,
              EnableIf<has_apply_interface<T>>...>
    inline T fmin(T x, T y) noexcept {
        using V = typename T::value_type;
        return apply(x, y, [](V f, V g){using std::fmin; return fmin(f, g);});
    }
    template <typename T,
              EnableIf<has_apply_interface<T>>...>
    inline T fmax(T x, T y) noexcept {
        using V = typename T::value_type;
        return apply(x, y, [](V f, V g){using std::fmax; return fmax(f, g);});
    }
    template <typename T,
              EnableIf<has_apply_interface<T>>...>
    inline T fdim(T x, T y) noexcept {
        using V = typename T::value_type;
        return apply(x, y, [](V f, V g){using std::fdim; return fdim(f, g);});
    }

    template <typename T,
              EnableIf<has_apply_interface<T>>...>
    inline T fmin(T x, typename T::value_type y) noexcept {
        using V = typename T::value_type;
        return apply(x, y, [](V f, V g){using std::fmin; return fmin(f, g);});
    }
    template <typename T,
              EnableIf<has_apply_interface<T>>...>
    inline T fmax(T x, typename T::value_type y) noexcept {
        using V = typename T::value_type;
        return apply(x, y, [](V f, V g){using std::fmax; return fmax(f, g);});
    }
    template <typename T,
              EnableIf<has_apply_interface<T>>...>
    inline T fdim(T x, typename T::value_type y) noexcept {
        using V = typename T::value_type;
        return apply(x, y, [](V f, V g){using std::fdim; return fdim(f, g);});
    }

    template <typename T,
              EnableIf<has_apply_interface<T>>...>
    inline T fmin(typename T::value_type x, T y) noexcept {
        using V = typename T::value_type;
        return apply(x, y, [](V f, V g){using std::fmin; return fmin(f, g);});
    }
    template <typename T,
              EnableIf<has_apply_interface<T>>...>
    inline T fmax(typename T::value_type x, T y) noexcept {
        using V = typename T::value_type;
        return apply(x, y, [](V f, V g){using std::fmax; return fmax(f, g);});
    }
    template <typename T,
              EnableIf<has_apply_interface<T>>...>
    inline T fdim(typename T::value_type x, T y) noexcept {
        using V = typename T::value_type;
        return apply(x, y, [](V f, V g){using std::fdim; return fdim(f, g);});
    }

    // other
    template <typename T,
              EnableIf<has_apply_interface<T>>...>
    inline T fabs(T v) noexcept {
        using V = typename T::value_type;
        return apply(v, [](V f){using std::fabs; return fabs(f);});
    }

    template <typename T,
              EnableIf<has_apply_interface<T>>...>
    inline T abs(T v) noexcept {
        using V = typename T::value_type;
        return apply(v, [](V f){using std::abs; return abs(f);});
    }

    template <typename T,
              EnableIf<has_apply_interface<T>>...>
    inline T fma(T x, T y, T z) noexcept {
        using V = typename T::value_type;
        return apply(x, y, z, [](V f, V g, V h){using std::fma; return fma(f,g,h);});
    }
    template <typename T,
              EnableIf<has_apply_interface<T>>...>
    inline T fma(T x, T y, typename T::value_type z) noexcept {
        using V = typename T::value_type;
        return apply(x, y, z, [](V f, V g, V h){using std::fma; return fma(f,g,h);});
    }
    template <typename T,
              EnableIf<has_apply_interface<T>>...>
    inline T fma(T x, typename T::value_type y, T z) noexcept {
        using V = typename T::value_type;
        return apply(x, y, z, [](V f, V g, V h){using std::fma; return fma(f,g,h);});
    }
    template <typename T,
              EnableIf<has_apply_interface<T>>...>
    inline T fma(T x, typename T::value_type y, typename T::value_type z) noexcept {
        using V = typename T::value_type;
        return apply(x, y, z, [](V f, V g, V h){using std::fma; return fma(f,g,h);});
    }

    template <typename T,
              EnableIf<has_apply_interface<T>>...>
    inline T fma(typename T::value_type x, T y, T z) noexcept {
        using V = typename T::value_type;
        return apply(x, y, z, [](V f, V g, V h){using std::fma; return fma(f,g,h);});
    }
    template <typename T,
              EnableIf<has_apply_interface<T>>...>
    inline T fma(typename T::value_type x, T y, typename T::value_type z) noexcept {
        using V = typename T::value_type;
        return apply(x, y, z, [](V f, V g, V h){using std::fma; return fma(f,g,h);});
    }
    template <typename T,
              EnableIf<has_apply_interface<T>>...>
    inline T fma(typename T::value_type x, typename T::value_type y, T z) noexcept {
        using V = typename T::value_type;
        return apply(x, y, z, [](V f, V g, V h){using std::fma; return fma(f,g,h);});
    }

    // classification functions

    // comparison functions

}


#endif // CMATH_HH_INCLUDED_20131102

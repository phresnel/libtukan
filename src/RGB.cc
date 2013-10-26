// (C) 2013 Sebastian Mach (1983), this file is published under the terms of the
// GNU General Public License, Version 3 (a.k.a. GPLv3).
// See COPYING in the root-folder of the excygen project folder.

#include "gaudy/RGB.hh"
#include "catch.hpp"


#include <iostream>
namespace gaudy {
    template <typename T>
    inline
    std::ostream& operator<< (std::ostream &os, basic_rgb<T> const &rhs) {
        return os << "rgb{" << rhs.r << ";" << rhs.g << ";" << rhs.b << "}";
    }
}


TEST_CASE("gaudy/RGB", "RGB tests")
{
    using namespace gaudy;

    SECTION("assignment and comparison") {
        REQUIRE(RGB()      == rel_equal(RGB()));
        REQUIRE(RGB(0,0,0) == rel_equal(RGB()));
        REQUIRE(RGB()      != rel_equal(RGB(1,2,3)));

        REQUIRE((RGB()+=RGB())           == rel_equal(RGB()));
        REQUIRE((RGB()+=RGB(1,2,3))      == rel_equal(RGB(1,2,3)));
        REQUIRE((RGB(1,2,3)+=RGB(5,6,7)) == rel_equal(RGB(6,8,10)));

        REQUIRE((RGB()-=RGB())           == rel_equal(RGB()));
        REQUIRE((RGB()-=RGB(1,2,3))      == rel_equal(RGB(-1,-2,-3)));
        REQUIRE((RGB(1,2,3)-=RGB(5,6,7)) == rel_equal(RGB(-4,-4,-4)));

        REQUIRE((RGB()*=RGB())           == rel_equal(RGB()));
        REQUIRE((RGB()*=RGB(1,2,3))      == rel_equal(RGB(0,0,0)));
        REQUIRE((RGB(1,2,3)*=RGB(5,6,7)) == rel_equal(RGB(5,12,21)));

        REQUIRE((RGB()/=RGB(1,2,3))      == rel_equal(RGB(0,0,0)));
        REQUIRE((RGB(3,6,9)/=RGB(3,2,1)) == rel_equal(RGB(1,3,9)));

        REQUIRE((RGB()+=1)      == rel_equal(RGB(1,1,1)));
        REQUIRE((RGB()+=-2)     == rel_equal(RGB(-2,-2,-2)));
        REQUIRE((RGB(1,2,3)+=5) == rel_equal(RGB(6,7,8)));

        REQUIRE((RGB()-=1)      == rel_equal(RGB(-1,-1,-1)));
        REQUIRE((RGB()-=-2)     == rel_equal(RGB(2,2,2)));
        REQUIRE((RGB(1,2,3)-=5) == rel_equal(RGB(-4,-3,-2)));

        REQUIRE((RGB()*=1)      == rel_equal(RGB()));
        REQUIRE((RGB()*=-2)     == rel_equal(RGB(0,0,0)));
        REQUIRE((RGB(1,2,3)*=5) == rel_equal(RGB(5,10,15)));

        REQUIRE((RGB()/=1)       == rel_equal(RGB(0,0,0)));
        REQUIRE((RGB(3,6,9)/=-2) == rel_equal(RGB(-1.5,-3,-4.5)));
    }

    SECTION("sign") {
        REQUIRE(RGB(-1,1,-1) == rel_equal(+RGB(-1, 1,-1)));
        REQUIRE(RGB(-1,1,-1) == rel_equal(-RGB( 1,-1, 1)));
        REQUIRE(RGB(-1,1,-1) == rel_equal(- + - +RGB(-1,1,-1)));
    }

    SECTION("arithmetics") {
        REQUIRE((RGB()+RGB())           == rel_equal(RGB()));
        REQUIRE((RGB()+RGB(1,2,3))      == rel_equal(RGB(1,2,3)));
        REQUIRE((RGB(1,2,3)+RGB(5,6,7)) == rel_equal(RGB(6,8,10)));

        REQUIRE((RGB()-RGB())           == rel_equal(RGB()));
        REQUIRE((RGB()-RGB(1,2,3))      == rel_equal(RGB(-1,-2,-3)));
        REQUIRE((RGB(1,2,3)-RGB(5,6,7)) == rel_equal(RGB(-4,-4,-4)));

        REQUIRE((RGB()*RGB())           == rel_equal(RGB()));
        REQUIRE((RGB()*RGB(1,2,3))      == rel_equal(RGB(0,0,0)));
        REQUIRE((RGB(1,2,3)*RGB(5,6,7)) == rel_equal(RGB(5,12,21)));

        REQUIRE((RGB()/RGB(1,2,3))      == rel_equal(RGB(0,0,0)));
        REQUIRE((RGB(3,6,9)/RGB(3,2,1)) == rel_equal(RGB(1,3,9)));

        REQUIRE((RGB()+1)      == rel_equal(RGB(1,1,1)));
        REQUIRE((RGB()+-2)     == rel_equal(RGB(-2,-2,-2)));
        REQUIRE((RGB(1,2,3)+5) == rel_equal(RGB(6,7,8)));

        REQUIRE((RGB()-1)      == rel_equal(RGB(-1,-1,-1)));
        REQUIRE((RGB()- -2)    == rel_equal(RGB(2,2,2)));
        REQUIRE((RGB(1,2,3)-5) == rel_equal(RGB(-4,-3,-2)));

        REQUIRE((RGB()*1)      == rel_equal(RGB()));
        REQUIRE((RGB()*-2)     == rel_equal(RGB(0,0,0)));
        REQUIRE((RGB(1,2,3)*5) == rel_equal(RGB(5,10,15)));

        REQUIRE((RGB()/1)       == rel_equal(RGB(0,0,0)));
        REQUIRE((RGB(3,6,9)/-2) == rel_equal(RGB(-1.5,-3,-4.5)));
    }
}

TEST_CASE("gaudy/RGB/IEEE 754 NaNs and Infinities", "IEEE 754 Conformance")
{
    if (!std::numeric_limits<float>::is_iec559 || !std::numeric_limits<double>::is_iec559)
        FAIL("float/double are not IEEE 754; IEEE 754 Tests skipped.");

    using namespace gaudy;

    // infinity
    REQUIRE((RGB(1,2,3)/=RGB())  == (RGB(1/.0f, 1/.0f, 1/.0f)));
    REQUIRE((RGB(1,2,3)/=0)      == (RGB(1/.0f, 1/.0f, 1/.0f)));

    // NaN
    REQUIRE_FALSE(RGB() == rel_equal(RGB()/=RGB()));
    REQUIRE(RGB() != rel_equal((RGB()/=RGB())));
    REQUIRE((RGB(1/.0f, 1/.0f, 1/.0f)       *= RGB(0,0,0)) != rel_equal(RGB(0,0,0)));
    REQUIRE_FALSE((RGB(1/.0f, 1/.0f, 1/.0f) *= RGB(0,0,0)) == rel_equal(RGB(0,0,0)));
    REQUIRE((RGB(0,0,0) *= RGB(1/.0f, 1/.0f, 1/.0f))       != rel_equal(RGB(0,0,0)));

    REQUIRE_FALSE(RGB() == rel_equal(RGB()/=0));
    REQUIRE(RGB() != rel_equal ((RGB()/=0)));
    REQUIRE((RGB(1/.0f, 1/.0f, 1/.0f)       *= 0) != rel_equal(RGB(0,0,0)));
    REQUIRE_FALSE((RGB(1/.0f, 1/.0f, 1/.0f) *= 0) == rel_equal(RGB(0,0,0)));
    REQUIRE((RGB(0,0,0) *= (1/.0f)              ) != rel_equal(RGB(0,0,0)));
}

TEST_CASE("gaudy/RGB/cmath", "RGB cmath tests")
{
    using namespace gaudy;
    using namespace std;
    const RGB v {0.6, 0.4, 0.8};
    const RGB w {0.9, 0.2, 0.7};
    const RGB x {1.9, 4, 8.7};
    const RGB z {100.9, -1, -0.7};
    const auto a = 2., b = 11., c = 0.5, d = -1.0/0.0, e = -99999.;

    SECTION("trigonometric") {
        REQUIRE(sin(v)     == rel_equal(RGB(sin(v.r),       sin(v.g),        sin(v.b))));
        REQUIRE(cos(v)     == rel_equal(RGB(cos(v.r),       cos(v.g),        cos(v.b))));
        REQUIRE(tan(v)     == rel_equal(RGB(tan(v.r),       tan(v.g),        tan(v.b))));
        REQUIRE(acos(v)    == rel_equal(RGB(acos(v.r),      acos(v.g),       acos(v.b))));
        REQUIRE(asin(v)    == rel_equal(RGB(asin(v.r),      asin(v.g),       asin(v.b))));
        REQUIRE(atan(v)    == rel_equal(RGB(atan(v.r),      atan(v.g),       atan(v.b))));

        REQUIRE(atan2(v,x) == rel_equal(RGB(atan2(v.r, x.r), atan2(v.g, x.g), atan2(v.b, x.b))));
        REQUIRE(atan2(a,w) == rel_equal(RGB(atan2(a, w.r),   atan2(a, w.g),   atan2(a, w.b))));
        REQUIRE(atan2(b,w) == rel_equal(RGB(atan2(b, w.r),   atan2(b, w.g),   atan2(b, w.b))));
        REQUIRE(atan2(c,w) == rel_equal(RGB(atan2(c, w.r),   atan2(c, w.g),   atan2(c, w.b))));
        REQUIRE(atan2(x,a) == rel_equal(RGB(atan2(x.r, a),   atan2(x.g, a),   atan2(x.b, a))));
        REQUIRE(atan2(x,b) == rel_equal(RGB(atan2(x.r, b),   atan2(x.g, b),   atan2(x.b, b))));
        REQUIRE(atan2(x,c) == rel_equal(RGB(atan2(x.r, c),   atan2(x.g, c),   atan2(x.b, c))));
    }

    SECTION("hyperbolic") {
        REQUIRE(cosh(v)  == rel_equal(RGB(cosh(v.r),  cosh(v.g),  cosh(v.b))));
        REQUIRE(sinh(v)  == rel_equal(RGB(sinh(v.r),  sinh(v.g),  sinh(v.b))));
        REQUIRE(tanh(v)  == rel_equal(RGB(tanh(v.r),  tanh(v.g),  tanh(v.b))));
        REQUIRE(acosh(x) == rel_equal(RGB(acosh(x.r), acosh(x.g), acosh(x.b))));
        REQUIRE(asinh(x) == rel_equal(RGB(asinh(x.r), asinh(x.g), asinh(x.b))));
        REQUIRE(atanh(v) == rel_equal(RGB(atanh(v.r), atanh(v.g), atanh(v.b))));
    }

    SECTION("exponential and logarithmic") {
        REQUIRE(exp(v) == rel_equal(RGB(exp(v.r), exp(v.g), exp(v.b))));

        RGB sig;
        basic_rgb<int> exp;
        sig = frexp(x, &exp);
        int exp_r, exp_g, exp_b;
        float sig_r = frexp(x.r, &exp_r);
        float sig_g = frexp(x.g, &exp_g);
        float sig_b = frexp(x.b, &exp_b);
        REQUIRE(exp_r == exp.r);
        REQUIRE(exp_g == exp.g);
        REQUIRE(exp_b == exp.b);
        REQUIRE(sig_r == Approx(sig.r));
        REQUIRE(sig_g == Approx(sig.g));
        REQUIRE(sig_b == Approx(sig.b));

        REQUIRE(x == rel_equal(RGB(ldexp(sig_r,exp_r), ldexp(sig_g,exp_g), ldexp(sig_b,exp_b))));

        // TODO: ldexp is missing.
        REQUIRE(ldexp(sig, exp) ==
                rel_equal(RGB(ldexp(sig.r,exp.r),ldexp(sig.g,exp.g),ldexp(sig.b,exp.b))));

        REQUIRE(log(x)   == rel_equal(RGB(log(x.r),   log(x.g),   log(x.b))));
        REQUIRE(log10(x) == rel_equal(RGB(log10(x.r), log10(x.g), log10(x.b))));

        RGB intpart, frac = modf(x, &intpart);
        float intpart_r, frac_r = modf(x.r, &intpart_r);
        float intpart_g, frac_g = modf(x.g, &intpart_g);
        float intpart_b, frac_b = modf(x.b, &intpart_b);
        REQUIRE (intpart.r == Approx(intpart_r));
        REQUIRE (intpart.g == Approx(intpart_g));
        REQUIRE (intpart.b == Approx(intpart_b));
        REQUIRE (frac.r == Approx(frac_r));
        REQUIRE (frac.g == Approx(frac_g));
        REQUIRE (frac.b == Approx(frac_b));

        REQUIRE (exp2(x)  == rel_equal(RGB(exp2(x.r),  exp2(x.g),  exp2(x.b))));
        REQUIRE (expm1(x) == rel_equal(RGB(expm1(x.r), expm1(x.g), expm1(x.b))));
        REQUIRE (ilogb(x) == (basic_rgb<int>(ilogb(x.r), ilogb(x.g), ilogb(x.b))));
        REQUIRE (log1p(x) == rel_equal(RGB(log1p(x.r), log1p(x.g), log1p(x.b))));
        REQUIRE (log2(x)  == rel_equal(RGB(log2(x.r),  log2(x.g),  log2(x.b))));

        REQUIRE (scalbn(x,2)   == rel_equal(RGB(scalbn(x.r,2),   scalbn(x.g,2),   scalbn(x.b,2))));
        REQUIRE (scalbn(x,11)  == rel_equal(RGB(scalbn(x.r,11),  scalbn(x.g,11),  scalbn(x.b,11))));
        REQUIRE (scalbn(x,-2)  == rel_equal(RGB(scalbn(x.r,-2),  scalbn(x.g,-2),  scalbn(x.b,-2))));

        REQUIRE (scalbn(w,basic_rgb<int>(2,3,11))   == rel_equal(RGB(scalbn(w.r,2),  scalbn(w.g,3),   scalbn(w.b,11))));
        REQUIRE (scalbn(w,basic_rgb<int>(7,-3,0))   == rel_equal(RGB(scalbn(w.r,7),  scalbn(w.g,-3),  scalbn(w.b,0))));
        REQUIRE (scalbn(w,basic_rgb<int>(12,17,-2)) == rel_equal(RGB(scalbn(w.r,12), scalbn(w.g,17),  scalbn(w.b,-2))));

        REQUIRE (scalbln(x,2)   == rel_equal(RGB(scalbln(x.r,2),   scalbln(x.g,2),   scalbln(x.b,2))));
        REQUIRE (scalbln(x,11)  == rel_equal(RGB(scalbln(x.r,11),  scalbln(x.g,11),  scalbln(x.b,11))));
        REQUIRE (scalbln(x,-2)  == rel_equal(RGB(scalbln(x.r,-2),  scalbln(x.g,-2),  scalbln(x.b,-2))));

        REQUIRE (scalbln(w,basic_rgb<long>(2,3,11))   == rel_equal(RGB(scalbln(w.r,2),  scalbln(w.g,3),   scalbln(w.b,11))));
        REQUIRE (scalbln(w,basic_rgb<long>(7,-3,0))   == rel_equal(RGB(scalbln(w.r,7),  scalbln(w.g,-3),  scalbln(w.b,0))));
        REQUIRE (scalbln(w,basic_rgb<long>(12,17,-2)) == rel_equal(RGB(scalbln(w.r,12), scalbln(w.g,17),  scalbln(w.b,-2))));;
    }

    SECTION("power functions") {
        REQUIRE(pow(v,x) == rel_equal(RGB(pow(v.r, x.r), pow(v.g, x.g), pow(v.b, x.b))));
        REQUIRE(pow(a,w) == rel_equal(RGB(pow(a, w.r),   pow(a, w.g),   pow(a, w.b))));
        REQUIRE(pow(b,w) == rel_equal(RGB(pow(b, w.r),   pow(b, w.g),   pow(b, w.b))));
        REQUIRE(pow(c,w) == rel_equal(RGB(pow(c, w.r),   pow(c, w.g),   pow(c, w.b))));
        REQUIRE(pow(x,a) == rel_equal(RGB(pow(x.r, a),   pow(x.g, a),   pow(x.b, a))));
        REQUIRE(pow(x,b) == rel_equal(RGB(pow(x.r, b),   pow(x.g, b),   pow(x.b, b))));
        REQUIRE(pow(x,c) == rel_equal(RGB(pow(x.r, c),   pow(x.g, c),   pow(x.b, c))));

        REQUIRE(sqrt(v) == rel_equal(RGB(sqrt(v.r), sqrt(v.g), sqrt(v.b))));
        REQUIRE(sqrt(x) == rel_equal(RGB(sqrt(x.r), sqrt(x.g), sqrt(x.b))));

        REQUIRE(cbrt(v) == rel_equal(RGB(cbrt(v.r), cbrt(v.g), cbrt(v.b))));
        REQUIRE(cbrt(x) == rel_equal(RGB(cbrt(x.r), cbrt(x.g), cbrt(x.b))));

        REQUIRE(hypot(v,x) == rel_equal(RGB(hypot(v.r, x.r), hypot(v.g, x.g), hypot(v.b, x.b))));
        REQUIRE(hypot(a,w) == rel_equal(RGB(hypot(a, w.r),   hypot(a, w.g),   hypot(a, w.b))));
        REQUIRE(hypot(b,w) == rel_equal(RGB(hypot(b, w.r),   hypot(b, w.g),   hypot(b, w.b))));
        REQUIRE(hypot(c,w) == rel_equal(RGB(hypot(c, w.r),   hypot(c, w.g),   hypot(c, w.b))));
        REQUIRE(hypot(x,a) == rel_equal(RGB(hypot(x.r, a),   hypot(x.g, a),   hypot(x.b, a))));
        REQUIRE(hypot(x,b) == rel_equal(RGB(hypot(x.r, b),   hypot(x.g, b),   hypot(x.b, b))));
        REQUIRE(hypot(x,c) == rel_equal(RGB(hypot(x.r, c),   hypot(x.g, c),   hypot(x.b, c))));
    }

    SECTION("error and gamma functions") {
        REQUIRE(erf(x)  == rel_equal(RGB(erf(x.r),  erf(x.g),  erf(x.b))));
        REQUIRE(erf(v)  == rel_equal(RGB(erf(v.r),  erf(v.g),  erf(v.b))));
        REQUIRE(erfc(x) == rel_equal(RGB(erfc(x.r), erfc(x.g), erfc(x.b))));
        REQUIRE(erfc(v) == rel_equal(RGB(erfc(v.r), erfc(v.g), erfc(v.b))));

        REQUIRE(tgamma(x) == rel_equal(RGB(tgamma(x.r), tgamma(x.g), tgamma(x.b))));
        REQUIRE(tgamma(v) == rel_equal(RGB(tgamma(v.r), tgamma(v.g), tgamma(v.b))));
        REQUIRE(lgamma(x) == rel_equal(RGB(lgamma(x.r), lgamma(x.g), lgamma(x.b))));
        REQUIRE(lgamma(v) == rel_equal(RGB(lgamma(v.r), lgamma(v.g), lgamma(v.b))));
    }

    SECTION("rounding and remainder") {
        REQUIRE(ceil(x)  == rel_equal(RGB(ceil(x.r),  ceil(x.g),  ceil(x.b))));
        REQUIRE(ceil(-x) == rel_equal(RGB(ceil(-x.r), ceil(-x.g), ceil(-x.b))));
        REQUIRE(floor(x)  == rel_equal(RGB(floor(x.r),  floor(x.g),  floor(x.b))));
        REQUIRE(floor(-x) == rel_equal(RGB(floor(-x.r), floor(-x.g), floor(-x.b))));
        REQUIRE(fmod(x, w)  == rel_equal(RGB(fmod(x.r,w.r),  fmod(x.g,w.g),  fmod(x.b,w.b))));
        REQUIRE(fmod(x, b)  == rel_equal(RGB(fmod(x.r,b),  fmod(x.g,b),  fmod(x.b,b))));
        REQUIRE(fmod(b, w)  == rel_equal(RGB(fmod(b,w.r),  fmod(b,w.g),  fmod(b,w.b))));
        REQUIRE(fmod(-x, w)  == rel_equal(RGB(fmod(-x.r,w.r),  fmod(-x.g,w.g),  fmod(-x.b,w.b))));
        REQUIRE(fmod(x, -w)  == rel_equal(RGB(fmod(x.r,-w.r),  fmod(x.g,-w.g),  fmod(x.b,-w.b))));

        REQUIRE(trunc(x)  == rel_equal(RGB(trunc(x.r),  trunc(x.g),  trunc(x.b))));
        REQUIRE(trunc(-x) == rel_equal(RGB(trunc(-x.r), trunc(-x.g), trunc(-x.b))));
        REQUIRE(round(x)  == rel_equal(RGB(round(x.r),  round(x.g),  round(x.b))));
        REQUIRE(round(-x) == rel_equal(RGB(round(-x.r), round(-x.g), round(-x.b))));
        REQUIRE(lround(x)  == (basic_rgb<long>{lround(x.r),  lround(x.g),  lround(x.b)}));
        REQUIRE(lround(-x) == (basic_rgb<long>{lround(-x.r), lround(-x.g), lround(-x.b)}));
        REQUIRE(llround(x)  == (basic_rgb<long long>{llround(x.r),  llround(x.g),  llround(x.b)}));
        REQUIRE(llround(-x) == (basic_rgb<long long>{llround(-x.r), llround(-x.g), llround(-x.b)}));

        REQUIRE(rint(x)  == rel_equal(RGB(rint(x.r),  rint(x.g),  rint(x.b))));
        REQUIRE(rint(-x) == rel_equal(RGB(rint(-x.r), rint(-x.g), rint(-x.b))));
        REQUIRE(lrint(x)  == (basic_rgb<long>{lrint(x.r),  lrint(x.g),  lrint(x.b)}));
        REQUIRE(lrint(-x) == (basic_rgb<long>{lrint(-x.r), lrint(-x.g), lrint(-x.b)}));
        REQUIRE(llrint(x)  == (basic_rgb<long long>{llrint(x.r),  llrint(x.g),  llrint(x.b)}));
        REQUIRE(llrint(-x) == (basic_rgb<long long>{llrint(-x.r), llrint(-x.g), llrint(-x.b)}));

        REQUIRE(nearbyint(x)  == rel_equal(RGB(nearbyint(x.r),  nearbyint(x.g),  nearbyint(x.b))));
        REQUIRE(nearbyint(-x) == rel_equal(RGB(nearbyint(-x.r), nearbyint(-x.g), nearbyint(-x.b))));

        REQUIRE(remainder(x, w)== rel_equal(RGB(remainder(x.r,w.r),remainder(x.g,w.g),remainder(x.b,w.b))));
        REQUIRE(remainder(-x,w)== rel_equal(RGB(remainder(-x.r,w.r),remainder(-x.g,w.g),remainder(-x.b,w.b))));
        REQUIRE(remainder(x,-w)== rel_equal(RGB(remainder(x.r,-w.r),remainder(x.g,-w.g),remainder(x.b,-w.b))));
        REQUIRE(remainder(c, w)== rel_equal(RGB(remainder(c,w.r),remainder(c,w.g),remainder(c,w.b))));
        REQUIRE(remainder(-x,c)== rel_equal(RGB(remainder(-x.r,c),remainder(-x.g,c),remainder(-x.b,c))));

        basic_rgb<int> quot_rgb;
        int quot_r, quot_g, quot_b;

        RGB remquo_rgb = remquo(x,   w,   &quot_rgb);
        float remquo_r = remquo(x.r, w.r, &quot_r);
        float remquo_g = remquo(x.g, w.g, &quot_g);
        float remquo_b = remquo(x.b, w.b, &quot_b);
        REQUIRE(remquo_rgb == rel_equal(RGB(remquo_r,remquo_g,remquo_b)));
        REQUIRE(  quot_rgb == basic_rgb<int>(quot_r, quot_g, quot_b));

        remquo_rgb = remquo(c, w,   &quot_rgb);
        remquo_r   = remquo(c, w.r, &quot_r);
        remquo_g   = remquo(c, w.g, &quot_g);
        remquo_b   = remquo(c, w.b, &quot_b);
        REQUIRE(remquo_rgb == rel_equal(RGB(remquo_r,remquo_g,remquo_b)));
        REQUIRE(  quot_rgb == basic_rgb<int>(quot_r, quot_g, quot_b));

        remquo_rgb = remquo(x,   b, &quot_rgb);
        remquo_r   = remquo(x.r, b, &quot_r);
        remquo_g   = remquo(x.g, b, &quot_g);
        remquo_b   = remquo(x.b, b, &quot_b);

        // NOTE: when chosing c=0.5 instead of b=11 for the test, it fails on at least one device.
        //       I am not sure how this is explained.
        REQUIRE(  quot_rgb == basic_rgb<int>(quot_r, quot_g, quot_b));
        REQUIRE(remquo_rgb == rel_equal(RGB(remquo_r,remquo_g,remquo_b)));
    }

    SECTION("floating point manipulation") {
        REQUIRE(copysign(x,z) == rel_equal(RGB(copysign(x.r,z.r),copysign(x.g,z.g),copysign(x.b,z.b))));
        REQUIRE(copysign(x,c) == rel_equal(RGB(copysign(x.r,c),  copysign(x.g,c),  copysign(x.b,c))));
        REQUIRE(copysign(e,z) == rel_equal(RGB(copysign(e,z.r),  copysign(e,z.g),  copysign(e,z.b))));

        REQUIRE(nextafter(x,z) == rel_equal(RGB(nextafter(x.r,z.r),nextafter(x.g,z.g),nextafter(x.b,z.b))));
        REQUIRE(nextafter(x,c) == rel_equal(RGB(nextafter(x.r,c),  nextafter(x.g,c),  nextafter(x.b,c))));
        REQUIRE(nextafter(d,z) == rel_equal(RGB(nextafter(d,z.r),  nextafter(d,z.g),  nextafter(d,z.b))));

        basic_rgb<long double> d {1.0l,-0.5l,-1.0l/0.0l};
        const long double e = -99999;
        REQUIRE(nexttoward(x,d) == rel_equal(RGB(nexttoward(x.r,d.r),nexttoward(x.g,d.g),nexttoward(x.b,d.b))));
        REQUIRE(nexttoward(x,c) == rel_equal(RGB(nexttoward(x.r,c),  nexttoward(x.g,c),  nexttoward(x.b,c))));

        // TODO: replace below code with rel_equal once rel_equal works properly for basic_rgb<T!=float>.
        const auto nt = nexttoward(e,d);
        REQUIRE(nt.r == Approx(nexttoward(e,d.r)));
        REQUIRE(nt.g == Approx(nexttoward(e,d.g)));
        REQUIRE(nt.b == Approx(nexttoward(e,d.b)));
    }

    SECTION("minimum, maximum, difference") {
        REQUIRE(fmin(x,z) == rel_equal(RGB(fmin(x.r,z.r),fmin(x.g,z.g),fmin(x.b,z.b))));
        REQUIRE(fmax(x,z) == rel_equal(RGB(fmax(x.r,z.r),fmax(x.g,z.g),fmax(x.b,z.b))));
        REQUIRE(fdim(x,z) == rel_equal(RGB(fdim(x.r,z.r),fdim(x.g,z.g),fdim(x.b,z.b))));

        REQUIRE(fmin(z,c) == rel_equal(RGB(fmin(z.r,c),fmin(z.g,c),fmin(z.b,c))));
        REQUIRE(fmax(z,c) == rel_equal(RGB(fmax(z.r,c),fmax(z.g,c),fmax(z.b,c))));
        REQUIRE(fdim(z,c) == rel_equal(RGB(fdim(z.r,c),fdim(z.g,c),fdim(z.b,c))));

        REQUIRE(fmin(c,z) == rel_equal(RGB(fmin(c,z.r),fmin(c,z.g),fmin(c,z.b))));
        REQUIRE(fmax(c,z) == rel_equal(RGB(fmax(c,z.r),fmax(c,z.g),fmax(c,z.b))));
        REQUIRE(fdim(c,z) == rel_equal(RGB(fdim(c,z.r),fdim(c,z.g),fdim(c,z.b))));


        REQUIRE(fmax(0, fmin(1, RGB(-1, 2, -1))) == rel_equal(RGB(0,1,0)));
        REQUIRE(fmax(0, fmin(1, RGB(0.1, 0.2, 0.3))) == rel_equal(RGB(0.1,0.2,0.3)));
    }

    SECTION("other") {
        REQUIRE(abs(z) == rel_equal(RGB(abs(z.r),abs(z.g),abs(z.b))));
        REQUIRE(fabs(z) == rel_equal(RGB(fabs(z.r),fabs(z.g),fabs(z.b))));

        REQUIRE(fma(x,z,w) == rel_equal(RGB(fma(x.r,z.r,w.r),fma(x.g,z.g,w.g),fma(x.b,z.b,w.b))));
        REQUIRE(fma(x,z,c) == rel_equal(RGB(fma(x.r,z.r,c),fma(x.g,z.g,c),fma(x.b,z.b,c))));
        REQUIRE(fma(x,c,w) == rel_equal(RGB(fma(x.r,c,w.r),fma(x.g,c,w.g),fma(x.b,c,w.b))));
        REQUIRE(fma(x,c,c) == rel_equal(RGB(fma(x.r,c,c),fma(x.g,c,c),fma(x.b,c,c))));
        REQUIRE(fma(c,z,w) == rel_equal(RGB(fma(c,z.r,w.r),fma(c,z.g,w.g),fma(c,z.b,w.b))));
        REQUIRE(fma(c,z,c) == rel_equal(RGB(fma(c,z.r,c),fma(c,z.g,c),fma(c,z.b,c))));
        REQUIRE(fma(c,c,w) == rel_equal(RGB(fma(c,c,w.r),fma(c,c,w.g),fma(c,c,w.b))));
    }
}

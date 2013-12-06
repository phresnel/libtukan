// (C) 2013 Sebastian Mach (1983), this file is published under the terms of the
// GNU General Public License, Version 3 (a.k.a. GPLv3).
// See COPYING in the root-folder of the excygen project folder.

#include "gaudy/XYZ.hh"
#include "catch.hpp"


#include <iostream>
namespace gaudy {
    template <typename T>
    inline
    std::ostream& operator<< (std::ostream &os, XYZ<T> const &rhs) {
        return os << "XYZ{" << rhs.X << ";" << rhs.Y << ";" << rhs.Z << "}";
    }
}

TEST_CASE("gaudy/XYZ", "XYZ tests")
{
    using namespace gaudy;

    SECTION("array interface") {
        REQUIRE(XYZ<float>(1,2,3)[0] == 1);
        REQUIRE(XYZ<float>(1,2,3)[1] == 2);
        REQUIRE(XYZ<float>(1,2,3)[2] == 3);
        REQUIRE(XYZ<float>(1,2,3).size() == 3);
        REQUIRE(3 == size(XYZ<float>()));

        REQUIRE_NOTHROW(XYZ<float>().at(0));
        REQUIRE_NOTHROW(XYZ<float>().at(1));
        REQUIRE_NOTHROW(XYZ<float>().at(2));
        REQUIRE_THROWS(XYZ<float>().at(3));
        REQUIRE_THROWS(XYZ<float>().at(4));
        REQUIRE_THROWS(XYZ<float>().at(454545456));
    }

    SECTION("assignment and comparison") {
        REQUIRE(XYZ<float>()      == rel_equal(XYZ<float>()));
        REQUIRE(XYZ<float>(0,0,0) == rel_equal(XYZ<float>()));
        REQUIRE(XYZ<float>()      != rel_equal(XYZ<float>(1,2,3)));

        REQUIRE((XYZ<float>()+=XYZ<float>())           == rel_equal(XYZ<float>()));
        REQUIRE((XYZ<float>()+=XYZ<float>(1,2,3))      == rel_equal(XYZ<float>(1,2,3)));
        REQUIRE((XYZ<float>(1,2,3)+=XYZ<float>(5,6,7)) == rel_equal(XYZ<float>(6,8,10)));

        REQUIRE((XYZ<float>()-=XYZ<float>())           == rel_equal(XYZ<float>()));
        REQUIRE((XYZ<float>()-=XYZ<float>(1,2,3))      == rel_equal(XYZ<float>(-1,-2,-3)));
        REQUIRE((XYZ<float>(1,2,3)-=XYZ<float>(5,6,7)) == rel_equal(XYZ<float>(-4,-4,-4)));

        REQUIRE((XYZ<float>()*=XYZ<float>())           == rel_equal(XYZ<float>()));
        REQUIRE((XYZ<float>()*=XYZ<float>(1,2,3))      == rel_equal(XYZ<float>(0,0,0)));
        REQUIRE((XYZ<float>(1,2,3)*=XYZ<float>(5,6,7)) == rel_equal(XYZ<float>(5,12,21)));

        REQUIRE((XYZ<float>()/=XYZ<float>(1,2,3))      == rel_equal(XYZ<float>(0,0,0)));
        REQUIRE((XYZ<float>(3,6,9)/=XYZ<float>(3,2,1)) == rel_equal(XYZ<float>(1,3,9)));

        REQUIRE((XYZ<float>()+=1)      == rel_equal(XYZ<float>(1,1,1)));
        REQUIRE((XYZ<float>()+=-2)     == rel_equal(XYZ<float>(-2,-2,-2)));
        REQUIRE((XYZ<float>(1,2,3)+=5) == rel_equal(XYZ<float>(6,7,8)));

        REQUIRE((XYZ<float>()-=1)      == rel_equal(XYZ<float>(-1,-1,-1)));
        REQUIRE((XYZ<float>()-=-2)     == rel_equal(XYZ<float>(2,2,2)));
        REQUIRE((XYZ<float>(1,2,3)-=5) == rel_equal(XYZ<float>(-4,-3,-2)));

        REQUIRE((XYZ<float>()*=1)      == rel_equal(XYZ<float>()));
        REQUIRE((XYZ<float>()*=-2)     == rel_equal(XYZ<float>(0,0,0)));
        REQUIRE((XYZ<float>(1,2,3)*=5) == rel_equal(XYZ<float>(5,10,15)));

        REQUIRE((XYZ<float>()/=1)       == rel_equal(XYZ<float>(0,0,0)));
        REQUIRE((XYZ<float>(3,6,9)/=-2) == rel_equal(XYZ<float>(-1.5,-3,-4.5)));
    }

    SECTION("sign") {
        REQUIRE(XYZ<float>(-1,1,-1) == rel_equal(+XYZ<float>(-1, 1,-1)));
        REQUIRE(XYZ<float>(-1,1,-1) == rel_equal(-XYZ<float>( 1,-1, 1)));
        REQUIRE(XYZ<float>(-1,1,-1) == rel_equal(- + - +XYZ<float>(-1,1,-1)));
    }

    SECTION("arithmetics") {
        REQUIRE((XYZ<float>()+XYZ<float>())           == rel_equal(XYZ<float>()));
        REQUIRE((XYZ<float>()+XYZ<float>(1,2,3))      == rel_equal(XYZ<float>(1,2,3)));
        REQUIRE((XYZ<float>(1,2,3)+XYZ<float>(5,6,7)) == rel_equal(XYZ<float>(6,8,10)));

        REQUIRE((XYZ<float>()-XYZ<float>())           == rel_equal(XYZ<float>()));
        REQUIRE((XYZ<float>()-XYZ<float>(1,2,3))      == rel_equal(XYZ<float>(-1,-2,-3)));
        REQUIRE((XYZ<float>(1,2,3)-XYZ<float>(5,6,7)) == rel_equal(XYZ<float>(-4,-4,-4)));

        REQUIRE((XYZ<float>()*XYZ<float>())           == rel_equal(XYZ<float>()));
        REQUIRE((XYZ<float>()*XYZ<float>(1,2,3))      == rel_equal(XYZ<float>(0,0,0)));
        REQUIRE((XYZ<float>(1,2,3)*XYZ<float>(5,6,7)) == rel_equal(XYZ<float>(5,12,21)));

        REQUIRE((XYZ<float>()/XYZ<float>(1,2,3))      == rel_equal(XYZ<float>(0,0,0)));
        REQUIRE((XYZ<float>(3,6,9)/XYZ<float>(3,2,1)) == rel_equal(XYZ<float>(1,3,9)));

        REQUIRE((XYZ<float>()+1)      == rel_equal(XYZ<float>(1,1,1)));
        REQUIRE((XYZ<float>()+-2)     == rel_equal(XYZ<float>(-2,-2,-2)));
        REQUIRE((XYZ<float>(1,2,3)+5) == rel_equal(XYZ<float>(6,7,8)));

        REQUIRE((XYZ<float>()-1)      == rel_equal(XYZ<float>(-1,-1,-1)));
        REQUIRE((XYZ<float>()- -2)    == rel_equal(XYZ<float>(2,2,2)));
        REQUIRE((XYZ<float>(1,2,3)-5) == rel_equal(XYZ<float>(-4,-3,-2)));

        REQUIRE((XYZ<float>()*1)      == rel_equal(XYZ<float>()));
        REQUIRE((XYZ<float>()*-2)     == rel_equal(XYZ<float>(0,0,0)));
        REQUIRE((XYZ<float>(1,2,3)*5) == rel_equal(XYZ<float>(5,10,15)));

        REQUIRE((XYZ<float>()/1)       == rel_equal(XYZ<float>(0,0,0)));
        REQUIRE((XYZ<float>(3,6,9)/-2) == rel_equal(XYZ<float>(-1.5,-3,-4.5)));
    }

    SECTION("algorithms") {
        REQUIRE(min(XYZ<float>(1,0,3), XYZ<float>(2,3,1)) == rel_equal(XYZ<float>(1,0,1)));
        REQUIRE(min(XYZ<float>(2,3,1), XYZ<float>(1,0,3)) == rel_equal(XYZ<float>(1,0,1)));
        REQUIRE(max(XYZ<float>(1,0,3), XYZ<float>(2,3,1)) == rel_equal(XYZ<float>(2,3,3)));
        REQUIRE(max(XYZ<float>(2,3,1), XYZ<float>(1,0,3)) == rel_equal(XYZ<float>(2,3,3)));

        REQUIRE(min(1, XYZ<float>(2,3,0)) == rel_equal(XYZ<float>(1,1,0)));
        REQUIRE(min(XYZ<float>(2,3,0), 1) == rel_equal(XYZ<float>(1,1,0)));
        REQUIRE(max(1, XYZ<float>(2,3,0)) == rel_equal(XYZ<float>(2,3,1)));
        REQUIRE(max(XYZ<float>(2,3,0), 1) == rel_equal(XYZ<float>(2,3,1)));
    }
}

TEST_CASE("gaudy/XYZ/IEEE 754 NaNs and Infinities", "IEEE 754 Conformance")
{
    if (!std::numeric_limits<float>::is_iec559 || !std::numeric_limits<double>::is_iec559)
        FAIL("float/double are not IEEE 754; IEEE 754 Tests skipped.");

    using namespace gaudy;

    // infinity
    REQUIRE((XYZ<float>(1,2,3)/=XYZ<float>())  == (XYZ<float>(1/.0f, 1/.0f, 1/.0f)));
    REQUIRE((XYZ<float>(1,2,3)/=0)      == (XYZ<float>(1/.0f, 1/.0f, 1/.0f)));

    // NaN
    REQUIRE_FALSE(XYZ<float>() == rel_equal(XYZ<float>()/=XYZ<float>()));
    REQUIRE(XYZ<float>() != rel_equal((XYZ<float>()/=XYZ<float>())));
    REQUIRE((XYZ<float>(1/.0f, 1/.0f, 1/.0f)       *= XYZ<float>(0,0,0)) != rel_equal(XYZ<float>(0,0,0)));
    REQUIRE_FALSE((XYZ<float>(1/.0f, 1/.0f, 1/.0f) *= XYZ<float>(0,0,0)) == rel_equal(XYZ<float>(0,0,0)));
    REQUIRE((XYZ<float>(0,0,0) *= XYZ<float>(1/.0f, 1/.0f, 1/.0f))       != rel_equal(XYZ<float>(0,0,0)));

    REQUIRE_FALSE(XYZ<float>() == rel_equal(XYZ<float>()/=0));
    REQUIRE(XYZ<float>() != rel_equal ((XYZ<float>()/=0)));
    REQUIRE((XYZ<float>(1/.0f, 1/.0f, 1/.0f)       *= 0) != rel_equal(XYZ<float>(0,0,0)));
    REQUIRE_FALSE((XYZ<float>(1/.0f, 1/.0f, 1/.0f) *= 0) == rel_equal(XYZ<float>(0,0,0)));
    REQUIRE((XYZ<float>(0,0,0) *= (1/.0f)              ) != rel_equal(XYZ<float>(0,0,0)));
}

TEST_CASE("gaudy/XYZ/cmath", "XYZ cmath tests")
{
    using namespace gaudy;
    using namespace std;
    const XYZ<float> v {0.6, 0.4, 0.8};
    const XYZ<float> w {0.9, 0.2, 0.7};
    const XYZ<float> x {1.9, 4, 8.7};
    const XYZ<float> z {100.9, -1, -0.7};
    const auto a = 2., b = 11., c = 0.5, d = -1.0/0.0, e = -99999.;

    SECTION("trigonometric") {
        REQUIRE(sin(v)     == rel_equal(XYZ<float>(sin(v.X),       sin(v.Y),        sin(v.Z))));
        REQUIRE(cos(v)     == rel_equal(XYZ<float>(cos(v.X),       cos(v.Y),        cos(v.Z))));
        REQUIRE(tan(v)     == rel_equal(XYZ<float>(tan(v.X),       tan(v.Y),        tan(v.Z))));
        REQUIRE(acos(v)    == rel_equal(XYZ<float>(acos(v.X),      acos(v.Y),       acos(v.Z))));
        REQUIRE(asin(v)    == rel_equal(XYZ<float>(asin(v.X),      asin(v.Y),       asin(v.Z))));
        REQUIRE(atan(v)    == rel_equal(XYZ<float>(atan(v.X),      atan(v.Y),       atan(v.Z))));

        REQUIRE(atan2(v,x) == rel_equal(XYZ<float>(atan2(v.X, x.X), atan2(v.Y, x.Y), atan2(v.Z, x.Z))));
        REQUIRE(atan2(a,w) == rel_equal(XYZ<float>(atan2(a, w.X),   atan2(a, w.Y),   atan2(a, w.Z))));
        REQUIRE(atan2(b,w) == rel_equal(XYZ<float>(atan2(b, w.X),   atan2(b, w.Y),   atan2(b, w.Z))));
        REQUIRE(atan2(c,w) == rel_equal(XYZ<float>(atan2(c, w.X),   atan2(c, w.Y),   atan2(c, w.Z))));
        REQUIRE(atan2(x,a) == rel_equal(XYZ<float>(atan2(x.X, a),   atan2(x.Y, a),   atan2(x.Z, a))));
        REQUIRE(atan2(x,b) == rel_equal(XYZ<float>(atan2(x.X, b),   atan2(x.Y, b),   atan2(x.Z, b))));
        REQUIRE(atan2(x,c) == rel_equal(XYZ<float>(atan2(x.X, c),   atan2(x.Y, c),   atan2(x.Z, c))));
    }

    SECTION("hyperbolic") {
        REQUIRE(cosh(v)  == rel_equal(XYZ<float>(cosh(v.X),  cosh(v.Y),  cosh(v.Z))));
        REQUIRE(sinh(v)  == rel_equal(XYZ<float>(sinh(v.X),  sinh(v.Y),  sinh(v.Z))));
        REQUIRE(tanh(v)  == rel_equal(XYZ<float>(tanh(v.X),  tanh(v.Y),  tanh(v.Z))));
        REQUIRE(acosh(x) == rel_equal(XYZ<float>(acosh(x.X), acosh(x.Y), acosh(x.Z))));
        REQUIRE(asinh(x) == rel_equal(XYZ<float>(asinh(x.X), asinh(x.Y), asinh(x.Z))));
        REQUIRE(atanh(v) == rel_equal(XYZ<float>(atanh(v.X), atanh(v.Y), atanh(v.Z))));
    }

    SECTION("exponential and logarithmic") {
        REQUIRE(exp(v) == rel_equal(XYZ<float>(exp(v.X), exp(v.Y), exp(v.Z))));

        XYZ<float> sig;
        XYZ<int> exp;
        sig = frexp(x, &exp);
        int exp_r, exp_g, exp_b;
        float sig_r = frexp(x.X, &exp_r);
        float sig_g = frexp(x.Y, &exp_g);
        float sig_b = frexp(x.Z, &exp_b);
        REQUIRE(exp_r == exp.X);
        REQUIRE(exp_g == exp.Y);
        REQUIRE(exp_b == exp.Z);
        REQUIRE(sig_r == Approx(sig.X));
        REQUIRE(sig_g == Approx(sig.Y));
        REQUIRE(sig_b == Approx(sig.Z));

        REQUIRE(x == rel_equal(XYZ<float>(ldexp(sig_r,exp_r), ldexp(sig_g,exp_g), ldexp(sig_b,exp_b))));

        // TODO: ldexp is missing.
        REQUIRE(ldexp(sig, exp) ==
                rel_equal(XYZ<float>(ldexp(sig.X,exp.X),ldexp(sig.Y,exp.Y),ldexp(sig.Z,exp.Z))));

        REQUIRE(log(x)   == rel_equal(XYZ<float>(log(x.X),   log(x.Y),   log(x.Z))));
        REQUIRE(log10(x) == rel_equal(XYZ<float>(log10(x.X), log10(x.Y), log10(x.Z))));

        XYZ<float> intpart, frac = modf(x, &intpart);
        float intpart_r, frac_r = modf(x.X, &intpart_r);
        float intpart_g, frac_g = modf(x.Y, &intpart_g);
        float intpart_b, frac_b = modf(x.Z, &intpart_b);
        REQUIRE (intpart.X == Approx(intpart_r));
        REQUIRE (intpart.Y == Approx(intpart_g));
        REQUIRE (intpart.Z == Approx(intpart_b));
        REQUIRE (frac.X == Approx(frac_r));
        REQUIRE (frac.Y == Approx(frac_g));
        REQUIRE (frac.Z == Approx(frac_b));

        REQUIRE (exp2(x)  == rel_equal(XYZ<float>(exp2(x.X),  exp2(x.Y),  exp2(x.Z))));
        REQUIRE (expm1(x) == rel_equal(XYZ<float>(expm1(x.X), expm1(x.Y), expm1(x.Z))));
        REQUIRE (ilogb(x) == (XYZ<int>(ilogb(x.X), ilogb(x.Y), ilogb(x.Z))));
        REQUIRE (log1p(x) == rel_equal(XYZ<float>(log1p(x.X), log1p(x.Y), log1p(x.Z))));
        REQUIRE (log2(x)  == rel_equal(XYZ<float>(log2(x.X),  log2(x.Y),  log2(x.Z))));

        REQUIRE (scalbn(x,2)   == rel_equal(XYZ<float>(scalbn(x.X,2),   scalbn(x.Y,2),   scalbn(x.Z,2))));
        REQUIRE (scalbn(x,11)  == rel_equal(XYZ<float>(scalbn(x.X,11),  scalbn(x.Y,11),  scalbn(x.Z,11))));
        REQUIRE (scalbn(x,-2)  == rel_equal(XYZ<float>(scalbn(x.X,-2),  scalbn(x.Y,-2),  scalbn(x.Z,-2))));

        REQUIRE (scalbn(w,XYZ<int>(2,3,11))   == rel_equal(XYZ<float>(scalbn(w.X,2),  scalbn(w.Y,3),   scalbn(w.Z,11))));
        REQUIRE (scalbn(w,XYZ<int>(7,-3,0))   == rel_equal(XYZ<float>(scalbn(w.X,7),  scalbn(w.Y,-3),  scalbn(w.Z,0))));
        REQUIRE (scalbn(w,XYZ<int>(12,17,-2)) == rel_equal(XYZ<float>(scalbn(w.X,12), scalbn(w.Y,17),  scalbn(w.Z,-2))));

        REQUIRE (scalbln(x,2)   == rel_equal(XYZ<float>(scalbln(x.X,2),   scalbln(x.Y,2),   scalbln(x.Z,2))));
        REQUIRE (scalbln(x,11)  == rel_equal(XYZ<float>(scalbln(x.X,11),  scalbln(x.Y,11),  scalbln(x.Z,11))));
        REQUIRE (scalbln(x,-2)  == rel_equal(XYZ<float>(scalbln(x.X,-2),  scalbln(x.Y,-2),  scalbln(x.Z,-2))));

        REQUIRE (scalbln(w,XYZ<long> (2,3,11))   == rel_equal(XYZ<float>(scalbln(w.X,2),  scalbln(w.Y,3),   scalbln(w.Z,11))));
        REQUIRE (scalbln(w,XYZ<long> (7,-3,0))   == rel_equal(XYZ<float>(scalbln(w.X,7),  scalbln(w.Y,-3),  scalbln(w.Z,0))));
        REQUIRE (scalbln(w,XYZ<long> (12,17,-2)) == rel_equal(XYZ<float>(scalbln(w.X,12), scalbln(w.Y,17),  scalbln(w.Z,-2))));;
    }

    SECTION("power functions") {
        REQUIRE(pow(v,x) == rel_equal(XYZ<float>(pow(v.X, x.X), pow(v.Y, x.Y), pow(v.Z, x.Z))));
        REQUIRE(pow(a,w) == rel_equal(XYZ<float>(pow(a, w.X),   pow(a, w.Y),   pow(a, w.Z))));
        REQUIRE(pow(b,w) == rel_equal(XYZ<float>(pow(b, w.X),   pow(b, w.Y),   pow(b, w.Z))));
        REQUIRE(pow(c,w) == rel_equal(XYZ<float>(pow(c, w.X),   pow(c, w.Y),   pow(c, w.Z))));
        REQUIRE(pow(x,a) == rel_equal(XYZ<float>(pow(x.X, a),   pow(x.Y, a),   pow(x.Z, a))));
        REQUIRE(pow(x,b) == rel_equal(XYZ<float>(pow(x.X, b),   pow(x.Y, b),   pow(x.Z, b))));
        REQUIRE(pow(x,c) == rel_equal(XYZ<float>(pow(x.X, c),   pow(x.Y, c),   pow(x.Z, c))));

        REQUIRE(sqrt(v) == rel_equal(XYZ<float>(sqrt(v.X), sqrt(v.Y), sqrt(v.Z))));
        REQUIRE(sqrt(x) == rel_equal(XYZ<float>(sqrt(x.X), sqrt(x.Y), sqrt(x.Z))));

        REQUIRE(cbrt(v) == rel_equal(XYZ<float>(cbrt(v.X), cbrt(v.Y), cbrt(v.Z))));
        REQUIRE(cbrt(x) == rel_equal(XYZ<float>(cbrt(x.X), cbrt(x.Y), cbrt(x.Z))));

        REQUIRE(hypot(v,x) == rel_equal(XYZ<float>(hypot(v.X, x.X), hypot(v.Y, x.Y), hypot(v.Z, x.Z))));
        REQUIRE(hypot(a,w) == rel_equal(XYZ<float>(hypot(a, w.X),   hypot(a, w.Y),   hypot(a, w.Z))));
        REQUIRE(hypot(b,w) == rel_equal(XYZ<float>(hypot(b, w.X),   hypot(b, w.Y),   hypot(b, w.Z))));
        REQUIRE(hypot(c,w) == rel_equal(XYZ<float>(hypot(c, w.X),   hypot(c, w.Y),   hypot(c, w.Z))));
        REQUIRE(hypot(x,a) == rel_equal(XYZ<float>(hypot(x.X, a),   hypot(x.Y, a),   hypot(x.Z, a))));
        REQUIRE(hypot(x,b) == rel_equal(XYZ<float>(hypot(x.X, b),   hypot(x.Y, b),   hypot(x.Z, b))));
        REQUIRE(hypot(x,c) == rel_equal(XYZ<float>(hypot(x.X, c),   hypot(x.Y, c),   hypot(x.Z, c))));
    }

    SECTION("error and gamma functions") {
        REQUIRE(erf(x)  == rel_equal(XYZ<float>(erf(x.X),  erf(x.Y),  erf(x.Z))));
        REQUIRE(erf(v)  == rel_equal(XYZ<float>(erf(v.X),  erf(v.Y),  erf(v.Z))));
        REQUIRE(erfc(x) == rel_equal(XYZ<float>(erfc(x.X), erfc(x.Y), erfc(x.Z))));
        REQUIRE(erfc(v) == rel_equal(XYZ<float>(erfc(v.X), erfc(v.Y), erfc(v.Z))));

        REQUIRE(tgamma(x) == rel_equal(XYZ<float>(tgamma(x.X), tgamma(x.Y), tgamma(x.Z))));
        REQUIRE(tgamma(v) == rel_equal(XYZ<float>(tgamma(v.X), tgamma(v.Y), tgamma(v.Z))));
        REQUIRE(lgamma(x) == rel_equal(XYZ<float>(lgamma(x.X), lgamma(x.Y), lgamma(x.Z))));
        REQUIRE(lgamma(v) == rel_equal(XYZ<float>(lgamma(v.X), lgamma(v.Y), lgamma(v.Z))));
    }

    SECTION("rounding and remainder") {
        REQUIRE(ceil(x)  == rel_equal(XYZ<float>(ceil(x.X),  ceil(x.Y),  ceil(x.Z))));
        REQUIRE(ceil(-x) == rel_equal(XYZ<float>(ceil(-x.X), ceil(-x.Y), ceil(-x.Z))));
        REQUIRE(floor(x)  == rel_equal(XYZ<float>(floor(x.X),  floor(x.Y),  floor(x.Z))));
        REQUIRE(floor(-x) == rel_equal(XYZ<float>(floor(-x.X), floor(-x.Y), floor(-x.Z))));
        REQUIRE(fmod(x, w)  == rel_equal(XYZ<float>(fmod(x.X,w.X),  fmod(x.Y,w.Y),  fmod(x.Z,w.Z))));
        REQUIRE(fmod(x, b)  == rel_equal(XYZ<float>(fmod(x.X,b),  fmod(x.Y,b),  fmod(x.Z,b))));
        REQUIRE(fmod(b, w)  == rel_equal(XYZ<float>(fmod(b,w.X),  fmod(b,w.Y),  fmod(b,w.Z))));
        REQUIRE(fmod(-x, w)  == rel_equal(XYZ<float>(fmod(-x.X,w.X),  fmod(-x.Y,w.Y),  fmod(-x.Z,w.Z))));
        REQUIRE(fmod(x, -w)  == rel_equal(XYZ<float>(fmod(x.X,-w.X),  fmod(x.Y,-w.Y),  fmod(x.Z,-w.Z))));

        REQUIRE(trunc(x)  == rel_equal(XYZ<float>(trunc(x.X),  trunc(x.Y),  trunc(x.Z))));
        REQUIRE(trunc(-x) == rel_equal(XYZ<float>(trunc(-x.X), trunc(-x.Y), trunc(-x.Z))));
        REQUIRE(round(x)  == rel_equal(XYZ<float>(round(x.X),  round(x.Y),  round(x.Z))));
        REQUIRE(round(-x) == rel_equal(XYZ<float>(round(-x.X), round(-x.Y), round(-x.Z))));
        REQUIRE(lround(x)  == (XYZ<long> {lround(x.X),  lround(x.Y),  lround(x.Z)}));
        REQUIRE(lround(-x) == (XYZ<long> {lround(-x.X), lround(-x.Y), lround(-x.Z)}));
        REQUIRE(llround(x)  == (XYZ<long long> {llround(x.X),  llround(x.Y),  llround(x.Z)}));
        REQUIRE(llround(-x) == (XYZ<long long> {llround(-x.X), llround(-x.Y), llround(-x.Z)}));

        REQUIRE(rint(x)  == rel_equal(XYZ<float>(rint(x.X),  rint(x.Y),  rint(x.Z))));
        REQUIRE(rint(-x) == rel_equal(XYZ<float>(rint(-x.X), rint(-x.Y), rint(-x.Z))));
        REQUIRE(lrint(x)  == (XYZ<long> {lrint(x.X),  lrint(x.Y),  lrint(x.Z)}));
        REQUIRE(lrint(-x) == (XYZ<long> {lrint(-x.X), lrint(-x.Y), lrint(-x.Z)}));
        REQUIRE(llrint(x)  == (XYZ<long long> {llrint(x.X),  llrint(x.Y),  llrint(x.Z)}));
        REQUIRE(llrint(-x) == (XYZ<long long> {llrint(-x.X), llrint(-x.Y), llrint(-x.Z)}));

        REQUIRE(nearbyint(x)  == rel_equal(XYZ<float>(nearbyint(x.X),  nearbyint(x.Y),  nearbyint(x.Z))));
        REQUIRE(nearbyint(-x) == rel_equal(XYZ<float>(nearbyint(-x.X), nearbyint(-x.Y), nearbyint(-x.Z))));

        REQUIRE(remainder(x, w)== rel_equal(XYZ<float>(remainder(x.X,w.X),remainder(x.Y,w.Y),remainder(x.Z,w.Z))));
        REQUIRE(remainder(-x,w)== rel_equal(XYZ<float>(remainder(-x.X,w.X),remainder(-x.Y,w.Y),remainder(-x.Z,w.Z))));
        REQUIRE(remainder(x,-w)== rel_equal(XYZ<float>(remainder(x.X,-w.X),remainder(x.Y,-w.Y),remainder(x.Z,-w.Z))));
        REQUIRE(remainder(c, w)== rel_equal(XYZ<float>(remainder(c,w.X),remainder(c,w.Y),remainder(c,w.Z))));
        REQUIRE(remainder(-x,c)== rel_equal(XYZ<float>(remainder(-x.X,c),remainder(-x.Y,c),remainder(-x.Z,c))));

        XYZ<int> quot_XYZ;
        int quot_X, quot_Y, quot_Z;

        XYZ<float> remquo_XYZ = remquo(x,   w,   &quot_XYZ);
        float remquo_r = remquo(x.X, w.X, &quot_X);
        float remquo_g = remquo(x.Y, w.Y, &quot_Y);
        float remquo_b = remquo(x.Z, w.Z, &quot_Z);
        REQUIRE(remquo_XYZ == rel_equal(XYZ<float>(remquo_r,remquo_g,remquo_b)));
        REQUIRE(  quot_XYZ == (XYZ<int>(quot_X, quot_Y, quot_Z)));

        remquo_XYZ = remquo(c, w,   &quot_XYZ);
        remquo_r   = remquo(c, w.X, &quot_X);
        remquo_g   = remquo(c, w.Y, &quot_Y);
        remquo_b   = remquo(c, w.Z, &quot_Z);
        REQUIRE(remquo_XYZ == rel_equal(XYZ<float>(remquo_r,remquo_g,remquo_b)));
        REQUIRE(  quot_XYZ == (XYZ<int>(quot_X, quot_Y, quot_Z)));

        remquo_XYZ = remquo(x,   b, &quot_XYZ);
        remquo_r   = remquo(x.X, b, &quot_X);
        remquo_g   = remquo(x.Y, b, &quot_Y);
        remquo_b   = remquo(x.Z, b, &quot_Z);

        // NOTE: when chosing c=0.5 instead of b=11 for the test, it fails on at least one device.
        //       I am not sure how this is explained.
        REQUIRE(  quot_XYZ == (XYZ<int>(quot_X, quot_Y, quot_Z)));
        REQUIRE(remquo_XYZ == rel_equal(XYZ<float>(remquo_r,remquo_g,remquo_b)));
    }

    SECTION("floating point manipulation") {
        REQUIRE(copysign(x,z) == rel_equal(XYZ<float>(copysign(x.X,z.X),copysign(x.Y,z.Y),copysign(x.Z,z.Z))));
        REQUIRE(copysign(x,c) == rel_equal(XYZ<float>(copysign(x.X,c),  copysign(x.Y,c),  copysign(x.Z,c))));

        REQUIRE(nextafter(x,z) == rel_equal(XYZ<float>(nextafter(x.X,z.X),nextafter(x.Y,z.Y),nextafter(x.Z,z.Z))));
        REQUIRE(nextafter(x,c) == rel_equal(XYZ<float>(nextafter(x.X,c),  nextafter(x.Y,c),  nextafter(x.Z,c))));

        XYZ<long double> d {1.0l,-0.5l,-1.0l/0.0l};
        const long double e = -99999;
        REQUIRE(nexttoward(x,d) == rel_equal(XYZ<float>(nexttoward(x.X,d.X),nexttoward(x.Y,d.Y),nexttoward(x.Z,d.Z))));
        REQUIRE(nexttoward(x,c) == rel_equal(XYZ<float>(nexttoward(x.X,c),  nexttoward(x.Y,c),  nexttoward(x.Z,c))));

        /*
        REQUIRE(nextafter(d,z) == rel_equal(XYZ<float>(nextafter(d,z.X),  nextafter(d,z.Y),  nextafter(d,z.Z))));
        REQUIRE(copysign(e,z) == rel_equal(XYZ<float>(copysign(e,z.X),  copysign(e,z.Y),  copysign(e,z.Z))));
        const auto nt = nexttoward(e,d);
        REQUIRE(nt.X == Approx(nexttoward(e,d.X)));
        REQUIRE(nt.Y == Approx(nexttoward(e,d.Y)));
        REQUIRE(nt.Z == Approx(nexttoward(e,d.Z)));
        */
    }

    SECTION("minimum, maximum, difference") {
        REQUIRE(fmin(x,z) == rel_equal(XYZ<float>(fmin(x.X,z.X),fmin(x.Y,z.Y),fmin(x.Z,z.Z))));
        REQUIRE(fmax(x,z) == rel_equal(XYZ<float>(fmax(x.X,z.X),fmax(x.Y,z.Y),fmax(x.Z,z.Z))));
        REQUIRE(fdim(x,z) == rel_equal(XYZ<float>(fdim(x.X,z.X),fdim(x.Y,z.Y),fdim(x.Z,z.Z))));

        REQUIRE(fmin(z,c) == rel_equal(XYZ<float>(fmin(z.X,c),fmin(z.Y,c),fmin(z.Z,c))));
        REQUIRE(fmax(z,c) == rel_equal(XYZ<float>(fmax(z.X,c),fmax(z.Y,c),fmax(z.Z,c))));
        REQUIRE(fdim(z,c) == rel_equal(XYZ<float>(fdim(z.X,c),fdim(z.Y,c),fdim(z.Z,c))));

        REQUIRE(fmin(c,z) == rel_equal(XYZ<float>(fmin(c,z.X),fmin(c,z.Y),fmin(c,z.Z))));
        REQUIRE(fmax(c,z) == rel_equal(XYZ<float>(fmax(c,z.X),fmax(c,z.Y),fmax(c,z.Z))));
        REQUIRE(fdim(c,z) == rel_equal(XYZ<float>(fdim(c,z.X),fdim(c,z.Y),fdim(c,z.Z))));


        REQUIRE(fmax(0, fmin(1, XYZ<float>(-1, 2, -1))) == rel_equal(XYZ<float>(0,1,0)));
        REQUIRE(fmax(0, fmin(1, XYZ<float>(0.1, 0.2, 0.3))) == rel_equal(XYZ<float>(0.1,0.2,0.3)));
    }

    SECTION("other") {
        REQUIRE(abs(z) == rel_equal(XYZ<float>(abs(z.X),abs(z.Y),abs(z.Z))));
        REQUIRE(fabs(z) == rel_equal(XYZ<float>(fabs(z.X),fabs(z.Y),fabs(z.Z))));

        REQUIRE(fma(x,z,w) == rel_equal(XYZ<float>(fma(x.X,z.X,w.X),fma(x.Y,z.Y,w.Y),fma(x.Z,z.Z,w.Z))));
        REQUIRE(fma(x,z,c) == rel_equal(XYZ<float>(fma(x.X,z.X,c),fma(x.Y,z.Y,c),fma(x.Z,z.Z,c))));
        REQUIRE(fma(x,c,w) == rel_equal(XYZ<float>(fma(x.X,c,w.X),fma(x.Y,c,w.Y),fma(x.Z,c,w.Z))));
        REQUIRE(fma(x,c,c) == rel_equal(XYZ<float>(fma(x.X,c,c),fma(x.Y,c,c),fma(x.Z,c,c))));
        REQUIRE(fma(c,z,w) == rel_equal(XYZ<float>(fma(c,z.X,w.X),fma(c,z.Y,w.Y),fma(c,z.Z,w.Z))));
        REQUIRE(fma(c,z,c) == rel_equal(XYZ<float>(fma(c,z.X,c),fma(c,z.Y,c),fma(c,z.Z,c))));
        REQUIRE(fma(c,c,w) == rel_equal(XYZ<float>(fma(c,c,w.X),fma(c,c,w.Y),fma(c,c,w.Z))));
    }

    SECTION("type tests") {
        REQUIRE((std::is_same<XYZ<int>, decltype(ilogb(XYZ<float>(1,2,3)))>::value));
    }
}

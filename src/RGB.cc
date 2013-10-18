// (C) 2013 Sebastian Mach (1983), this file is published under the terms of the
// GNU General Public License, Version 3 (a.k.a. GPLv3).
// See COPYING in the root-folder of the excygen project folder.

#include "gaudy/RGB.hh"
#include "catch.hpp"


#include <iostream>
namespace gaudy {
    inline
    std::ostream& operator<< (std::ostream &os, RGB const &rhs) {
        return os << "rgb{" << rhs.r << ";" << rhs.g << ";" << rhs.b << "}";
    }
}


TEST_CASE("gaudy/RGB", "RGB tests")
{
    using namespace gaudy;

    SECTION("assignment and comparison") {
        REQUIRE(RGB()==RGB());
        REQUIRE(RGB(0,0,0)==RGB());
        REQUIRE(RGB()!=RGB(1,2,3));

        REQUIRE((RGB()+=RGB())           == RGB());
        REQUIRE((RGB()+=RGB(1,2,3))      == RGB(1,2,3));
        REQUIRE((RGB(1,2,3)+=RGB(5,6,7)) == RGB(6,8,10));

        REQUIRE((RGB()-=RGB())           == RGB());
        REQUIRE((RGB()-=RGB(1,2,3))      == RGB(-1,-2,-3));
        REQUIRE((RGB(1,2,3)-=RGB(5,6,7)) == RGB(-4,-4,-4));

        REQUIRE((RGB()*=RGB())           == RGB());
        REQUIRE((RGB()*=RGB(1,2,3))      == RGB(0,0,0));
        REQUIRE((RGB(1,2,3)*=RGB(5,6,7)) == RGB(5,12,21));

        REQUIRE((RGB()/=RGB(1,2,3))      == RGB(0,0,0));
        REQUIRE((RGB(3,6,9)/=RGB(3,2,1)) == RGB(1,3,9));

        REQUIRE((RGB()+=1)      == RGB(1,1,1));
        REQUIRE((RGB()+=-2)     == RGB(-2,-2,-2));
        REQUIRE((RGB(1,2,3)+=5) == RGB(6,7,8));

        REQUIRE((RGB()-=1)      == RGB(-1,-1,-1));
        REQUIRE((RGB()-=-2)     == RGB(2,2,2));
        REQUIRE((RGB(1,2,3)-=5) == RGB(-4,-3,-2));

        REQUIRE((RGB()*=1)      == RGB());
        REQUIRE((RGB()*=-2)     == RGB(0,0,0));
        REQUIRE((RGB(1,2,3)*=5) == RGB(5,10,15));

        REQUIRE((RGB()/=1)       == RGB(0,0,0));
        REQUIRE((RGB(3,6,9)/=-2) == RGB(-1.5,-3,-4.5));
    }

    SECTION("arithmetics") {
        REQUIRE((RGB()+RGB())           == RGB());
        REQUIRE((RGB()+RGB(1,2,3))      == RGB(1,2,3));
        REQUIRE((RGB(1,2,3)+RGB(5,6,7)) == RGB(6,8,10));

        REQUIRE((RGB()-RGB())           == RGB());
        REQUIRE((RGB()-RGB(1,2,3))      == RGB(-1,-2,-3));
        REQUIRE((RGB(1,2,3)-RGB(5,6,7)) == RGB(-4,-4,-4));

        REQUIRE((RGB()*RGB())           == RGB());
        REQUIRE((RGB()*RGB(1,2,3))      == RGB(0,0,0));
        REQUIRE((RGB(1,2,3)*RGB(5,6,7)) == RGB(5,12,21));

        REQUIRE((RGB()/RGB(1,2,3))      == RGB(0,0,0));
        REQUIRE((RGB(3,6,9)/RGB(3,2,1)) == RGB(1,3,9));

        REQUIRE((RGB()+1)      == RGB(1,1,1));
        REQUIRE((RGB()+-2)     == RGB(-2,-2,-2));
        REQUIRE((RGB(1,2,3)+5) == RGB(6,7,8));

        REQUIRE((RGB()-1)      == RGB(-1,-1,-1));
        REQUIRE((RGB()- -2)    == RGB(2,2,2));
        REQUIRE((RGB(1,2,3)-5) == RGB(-4,-3,-2));

        REQUIRE((RGB()*1)      == RGB());
        REQUIRE((RGB()*-2)     == RGB(0,0,0));
        REQUIRE((RGB(1,2,3)*5) == RGB(5,10,15));

        REQUIRE((RGB()/1)       == RGB(0,0,0));
        REQUIRE((RGB(3,6,9)/-2) == RGB(-1.5,-3,-4.5));
    }
}

TEST_CASE("gaudy/RGB/IEEE 754 NaNs and Infinities", "IEEE 754 Conformance")
{
    if (!std::numeric_limits<float>::is_iec559 || !std::numeric_limits<double>::is_iec559)
        FAIL("float/double are not IEEE 754; IEEE 754 Tests skipped.");

    using namespace gaudy;

    // infinity
    REQUIRE((RGB(1,2,3)/=RGB())  == RGB(1/.0f, 1/.0f, 1/.0f));
    REQUIRE((RGB(1,2,3)/=0)      == RGB(1/.0f, 1/.0f, 1/.0f));

    // NaN
    REQUIRE_FALSE(RGB() == (RGB()/=RGB()));
    REQUIRE(RGB() != (RGB()/=RGB()));
    REQUIRE((RGB(1/.0f, 1/.0f, 1/.0f)       *= RGB(0,0,0)) != RGB(0,0,0));
    REQUIRE_FALSE((RGB(1/.0f, 1/.0f, 1/.0f) *= RGB(0,0,0)) == RGB(0,0,0));
    REQUIRE((RGB(0,0,0) *= RGB(1/.0f, 1/.0f, 1/.0f))       != RGB(0,0,0));

    REQUIRE_FALSE(RGB() == (RGB()/=0));
    REQUIRE(RGB() != (RGB()/=0));
    REQUIRE((RGB(1/.0f, 1/.0f, 1/.0f)       *= 0) != RGB(0,0,0));
    REQUIRE_FALSE((RGB(1/.0f, 1/.0f, 1/.0f) *= 0) == RGB(0,0,0));
    REQUIRE((RGB(0,0,0) *= (1/.0f)              ) != RGB(0,0,0));
}

TEST_CASE("gaudy/RGB/cmath", "RGB cmath tests")
{
    using namespace gaudy;
    using namespace std;
    const RGB v {0.6, 0.4, 0.8};
    const RGB w {0.9, 0.2, 0.7};
    const RGB x {1.9, 4, 8.7};
    const auto a = 2., b = 11., c = 0.5;

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

        RGB sig, exp;
        sig = frexp(x, &exp);
        int exp_r, exp_g, exp_b;
        float sig_r = frexp(x.r, &exp_r);
        float sig_g = frexp(x.g, &exp_g);
        float sig_b = frexp(x.b, &exp_b);
        REQUIRE(exp_r == rel_equal(exp.r));
        REQUIRE(exp_g == rel_equal(exp.g));
        REQUIRE(exp_b == rel_equal(exp.b));
        REQUIRE(sig_r == rel_equal(sig.r));
        REQUIRE(sig_g == rel_equal(sig.g));
        REQUIRE(sig_b == rel_equal(sig.b));

        REQUIRE(x == rel_equal(RGB(ldexp(sig_r,exp_r), ldexp(sig_g,exp_g), ldexp(sig_b,exp_b))));

        REQUIRE(log(x)   == rel_equal(RGB(log(x.r),   log(x.g),   log(x.b))));
        REQUIRE(log10(x) == rel_equal(RGB(log10(x.r), log10(x.g), log10(x.b))));

        RGB intpart, frac = modf(x, &intpart);
        float intpart_r, frac_r = modf(x.r, &intpart_r);
        float intpart_g, frac_g = modf(x.g, &intpart_g);
        float intpart_b, frac_b = modf(x.b, &intpart_b);
        REQUIRE (intpart.r == intpart_r);
        REQUIRE (intpart.g == intpart_g);
        REQUIRE (intpart.b == intpart_b);
        REQUIRE (frac.r == frac_r);
        REQUIRE (frac.g == frac_g);
        REQUIRE (frac.b == frac_b);

        REQUIRE (exp2(x)  == RGB(exp2(x.r),  exp2(x.g),  exp2(x.b)));
        REQUIRE (expm1(x) == RGB(expm1(x.r), expm1(x.g), expm1(x.b)));
        REQUIRE (ilogb(x) == RGB(ilogb(x.r), ilogb(x.g), ilogb(x.b)));
        REQUIRE (log1p(x) == RGB(log1p(x.r), log1p(x.g), log1p(x.b)));
        REQUIRE (log2(x)  == RGB(log2(x.r),  log2(x.g),  log2(x.b)));

        REQUIRE (scalbn(x,2)   == RGB(scalbn(x.r,2),   scalbn(x.g,2),   scalbn(x.b,2)));
        REQUIRE (scalbn(x,11)  == RGB(scalbn(x.r,11),  scalbn(x.g,11),  scalbn(x.b,11)));
        REQUIRE (scalbn(x,-2)  == RGB(scalbn(x.r,-2),  scalbn(x.g,-2),  scalbn(x.b,-2)));

        REQUIRE (scalbn(w,RGB(2,3,11))   == RGB(scalbn(w.r,2),  scalbn(w.g,3),   scalbn(w.b,11)));
        REQUIRE (scalbn(w,RGB(7,-3,0))   == RGB(scalbn(w.r,7),  scalbn(w.g,-3),  scalbn(w.b,0)));
        REQUIRE (scalbn(w,RGB(12,17,-2)) == RGB(scalbn(w.r,12), scalbn(w.g,17),  scalbn(w.b,-2)));

        REQUIRE (scalbln(x,2)   == RGB(scalbln(x.r,2),   scalbln(x.g,2),   scalbln(x.b,2)));
        REQUIRE (scalbln(x,11)  == RGB(scalbln(x.r,11),  scalbln(x.g,11),  scalbln(x.b,11)));
        REQUIRE (scalbln(x,-2)  == RGB(scalbln(x.r,-2),  scalbln(x.g,-2),  scalbln(x.b,-2)));

        REQUIRE (scalbln(w,RGB(2,3,11))   == RGB(scalbln(w.r,2),  scalbln(w.g,3),   scalbln(w.b,11)));
        REQUIRE (scalbln(w,RGB(7,-3,0))   == RGB(scalbln(w.r,7),  scalbln(w.g,-3),  scalbln(w.b,0)));
        REQUIRE (scalbln(w,RGB(12,17,-2)) == RGB(scalbln(w.r,12), scalbln(w.g,17),  scalbln(w.b,-2)));;
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
}

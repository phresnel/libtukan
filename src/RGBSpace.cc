// (C) 2013 Sebastian Mach (1983), this file is published under the terms of the
// GNU General Public License, Version 3 (a.k.a. GPLv3).
// See COPYING in the root-folder of the excygen project folder.
#include "gaudy/RGBSpace.hh"
#include "gaudy/Matrix33.hh"
#include "catch.hpp"

namespace gaudy {
    template <typename T>
    std::ostream& operator<< (std::ostream &os, Matrix33<T> const &m) {
        return os //<< std::fixed
                  << "{(" << m._11 << "," << m._12 << "," << m._13 << "),"
                  << "(" << m._21 << "," << m._22 << "," << m._23 << "),"
                  << "(" << m._31 << "," << m._32 << "," << m._33 << ")}";
    }

    template <typename T>
    inline
    std::ostream& operator<< (std::ostream &os, RGBSpace<T> const &rhs) {
        return os << "rgb-space{"
                  << "to-xyz{\n"
                  << rhs.rgb_to_xyz
                  << "}\n"
                  << "to-rgb{\n"
                  << rhs.xyz_to_rgb
                  << "}"
                  << "}";
    }
}


TEST_CASE("gaudy/RGBSpace", "RGBSpace tests") {
    using namespace gaudy;

    // The following matrices are from Bruce Lindblooms site. Some epsilons are smaller,
    // some are larger. We should switch to double numbers and re-eval the epsilon.
    REQUIRE(AdobeRGB<float>().rgb_to_xyz == rel_equal(Matrix33<float>
                                                  {0.5767309,  0.1855540,  0.1881852,
                                                   0.2973769,  0.6273491,  0.0752741,
                                                   0.0270343,  0.0706872,  0.9911085},
                                                   gaudy::epsilon, 0.0000025));
    REQUIRE(AdobeRGB<float>().xyz_to_rgb == rel_equal(Matrix33<float>
                                                  {2.0413690, -0.5649464, -0.3446944,
                                                  -0.9692660,  1.8760108,  0.0415560,
                                                   0.0134474, -0.1183897,  1.0154096},
                                                   gaudy::epsilon, 0.0000025));

    REQUIRE(AppleRGB<float>().rgb_to_xyz == rel_equal(Matrix33<float>
                                                  { 0.4497288,  0.3162486,  0.1844926,
                                                    0.2446525,  0.6720283,  0.0833192,
                                                    0.0251848,  0.1411824,  0.9224628},
                                                   gaudy::epsilon, 0.0000025));
    REQUIRE(AppleRGB<float>().xyz_to_rgb == rel_equal(Matrix33<float>
                                                  { 2.9515373, -1.2894116, -0.4738445,
                                                   -1.0851093,  1.9908566,  0.0372026,
                                                    0.0854934, -0.2694964,  1.0912975},
                                                   gaudy::epsilon, 0.0000025));

    REQUIRE(BestRGB<float>().rgb_to_xyz == rel_equal(Matrix33<float>
                                                  { 0.6326696, 0.2045558, 0.1269946,
                                                    0.2284569, 0.7373523, 0.0341908,
                                                    0.0000000, 0.0095142, 0.8156958},
                                                   gaudy::epsilon, 0.000005));
    REQUIRE(BestRGB<float>().xyz_to_rgb == rel_equal(Matrix33<float>
                                                  { 1.7552599,-0.4836786,-0.2530000,
                                                   -0.5441336, 1.5068789, 0.0215528,
                                                    0.0063467,-0.0175761, 1.2256959},
                                                   gaudy::epsilon, 0.0000175));

    REQUIRE(BetaRGB<float>().rgb_to_xyz == rel_equal(Matrix33<float>
                                                  { 0.6712537, 0.1745834, 0.1183829,
                                                    0.3032726, 0.6637861, 0.0329413,
                                                    0.0000000, 0.0407010, 0.7845090},
                                                   gaudy::epsilon, 0.0000025));
    REQUIRE(BetaRGB<float>().xyz_to_rgb == rel_equal(Matrix33<float>
                                                  { 1.6832270,-0.4282363,-0.2360185,
                                                   -0.7710229, 1.7065571, 0.0446900,
                                                    0.0400013,-0.0885376, 1.2723640},
                                                   gaudy::epsilon, 0.0000025));

    REQUIRE(BruceRGB<float>().rgb_to_xyz == rel_equal(Matrix33<float>
                                                  { 0.4674162, 0.2944512, 0.1886026,
                                                    0.2410115, 0.6835475, 0.0754410,
                                                    0.0219101, 0.0736128, 0.9933071},
                                                   gaudy::epsilon, 0.0000025));
    REQUIRE(BruceRGB<float>().xyz_to_rgb == rel_equal(Matrix33<float>
                                                  { 2.7454669,-1.1358136,-0.4350269,
                                                   -0.9692660, 1.8760108, 0.0415560,
                                                    0.0112723,-0.1139754, 1.0132541},
                                                   gaudy::epsilon, 0.00001));

    REQUIRE(CIERGB<float>().rgb_to_xyz == rel_equal(Matrix33<float>
                                                  {  0.4887180,  0.3106803,  0.2006017,
                                                     0.1762044,  0.8129847,  0.0108109,
                                                     0.0000000,  0.0102048,  0.9897952},
                                                   gaudy::epsilon, 0.000005));
    REQUIRE(CIERGB<float>().xyz_to_rgb == rel_equal(Matrix33<float>
                                                  {  2.3706743, -0.9000405, -0.4706338,
                                                    -0.5138850,  1.4253036,  0.0885814,
                                                     0.0052982, -0.0146949,  1.0093968},
                                                   gaudy::epsilon, 0.000005));

    REQUIRE(ColorMatchRGB<float>().rgb_to_xyz == rel_equal(Matrix33<float>
                                                  {  0.5093439,  0.3209071,  0.1339691,
                                                     0.2748840,  0.6581315,  0.0669845,
                                                     0.0242545,  0.1087821,  0.6921735},
                                                   gaudy::epsilon, 0.0000025));
    REQUIRE(ColorMatchRGB<float>().xyz_to_rgb == rel_equal(Matrix33<float>
                                                  { 2.6422874, -1.2234270, -0.3930143,
                                                    -1.1119763,  2.0590183,  0.0159614,
                                                     0.0821699, -0.2807254,  1.4559877},
                                                   gaudy::epsilon, 0.0000025));

    REQUIRE(DonRGB4<float>().rgb_to_xyz == rel_equal(Matrix33<float>
                                                  { 0.6457711,  0.1933511,  0.1250978,
                                                    0.2783496,  0.6879702,  0.0336802,
                                                    0.0037113,  0.0179861,  0.8035125},
                                                   gaudy::epsilon, 0.00001));
    REQUIRE(DonRGB4<float>().xyz_to_rgb == rel_equal(Matrix33<float>
                                                  { 1.7603902, -0.4881198, -0.2536126,
                                                    -0.7126288,  1.6527432,  0.0416715,
                                                     0.0078207, -0.0347411,  1.2447743},
                                                   gaudy::epsilon, 0.000005));

    REQUIRE(ECIRGBv2<float>().rgb_to_xyz == rel_equal(Matrix33<float>
                                                  { 0.6502043,  0.1780774,  0.1359384,
                                                    0.3202499,  0.6020711,  0.0776791,
                                                    0.0000000,  0.0678390,  0.7573710},
                                                   gaudy::epsilon, 0.0000025));
    REQUIRE(ECIRGBv2<float>().xyz_to_rgb == rel_equal(Matrix33<float>
                                                  { 1.7827618, -0.4969847, -0.2690101,
                                                    -0.9593623,  1.9477962, -0.0275807,
                                                     0.0859317, -0.1744674,  1.3228273},
                                                   gaudy::epsilon, 0.0000025));


    REQUIRE(EktaSpacePS5<float>().rgb_to_xyz == rel_equal(Matrix33<float>
                                                  { 0.5938914,  0.2729801,  0.0973485,
                                                     0.2606286,  0.7349465,  0.0044249,
                                                     0.0000000,  0.0419969,  0.7832131},
                                                   gaudy::epsilon, 0.000008));
    REQUIRE(EktaSpacePS5<float>().xyz_to_rgb == rel_equal(Matrix33<float>
                                                  { 2.0043819, -0.7304844, -0.2450052,
                                                    -0.7110285,  1.6202126,  0.0792227,
                                                     0.0381263, -0.0868780,  1.2725438},
                                                   gaudy::epsilon, 0.000002));


    REQUIRE(NTSCRGB<float>().rgb_to_xyz == rel_equal(Matrix33<float>
                                                  {0.6068909,  0.1735011,  0.2003480,
                                                     0.2989164,  0.5865990,  0.1144845,
                                                     0.0000000,  0.0660957,  1.1162243},
                                                   gaudy::epsilon, 0.000004));
    REQUIRE(NTSCRGB<float>().xyz_to_rgb == rel_equal(Matrix33<float>
                                                  { 1.9099961, -0.5324542, -0.2882091,
                                                    -0.9846663,  1.9991710, -0.0283082,
                                                     0.0583056, -0.1183781,  0.8975535},
                                                   gaudy::epsilon, 0.000004));


    REQUIRE(PALSECAMRGB<float>().rgb_to_xyz == rel_equal(Matrix33<float>
                                                  { 0.4306190,  0.3415419,  0.1783091,
                                                     0.2220379,  0.7066384,  0.0713236,
                                                     0.0201853,  0.1295504,  0.9390944},
                                                   gaudy::epsilon, 0.000002));
    REQUIRE(PALSECAMRGB<float>().xyz_to_rgb == rel_equal(Matrix33<float>
                                                  { 3.0628971, -1.3931791, -0.4757517,
                                                    -0.9692660,  1.8760108,  0.0415560,
                                                     0.0678775, -0.2288548,  1.0693490},
                                                   gaudy::epsilon, 0.000001));

    REQUIRE(ProPhotoRGB<float>().rgb_to_xyz == rel_equal(Matrix33<float>
                                                  { 0.7976749,  0.1351917,  0.0313534,
                                                     0.2880402,  0.7118741,  0.0000857,
                                                     0.0000000,  0.0000000,  0.8252100},
                                                   gaudy::epsilon, 0.0001));
    REQUIRE(ProPhotoRGB<float>().xyz_to_rgb == rel_equal(Matrix33<float>
                                                  { 1.3459433, -0.2556075, -0.0511118,
                                                    -0.5445989,  1.5081673,  0.0205351,
                                                     0.0000000,  0.0000000,  1.2118128},
                                                   gaudy::epsilon, 0.0001));


    REQUIRE(SMPTE_C<float>().rgb_to_xyz == rel_equal(Matrix33<float>
                                                  { 0.3935891,  0.3652497,  0.1916313,
                                                     0.2124132,  0.7010437,  0.0865432,
                                                     0.0187423,  0.1119313,  0.9581563},
                                                   gaudy::epsilon, 0.00001));
    REQUIRE(SMPTE_C<float>().xyz_to_rgb == rel_equal(Matrix33<float>
                                                  { 3.5053960, -1.7394894, -0.5439640,
                                                    -1.0690722,  1.9778245,  0.0351722,
                                                     0.0563200, -0.1970226,  1.0502026},
                                                   gaudy::epsilon, 0.000001));


    REQUIRE(sRGB<float>().rgb_to_xyz == rel_equal(Matrix33<float>
                                                  {0.4124564, 0.3575761, 0.1804375,
                                                   0.2126729, 0.7151522, 0.0721750,
                                                   0.0193339, 0.1191920, 0.9503041},
                                                   gaudy::epsilon, 0.000001));
    REQUIRE(sRGB<float>().xyz_to_rgb == rel_equal(Matrix33<float>
                                                  {3.2404542, -1.5371385, -0.4985314,
                                                  -0.9692660,  1.8760108,  0.0415560,
                                                   0.0556434, -0.2040259,  1.0572252},
                                                   gaudy::epsilon, 0.000001));


    REQUIRE(WideGamutRGB<float>().rgb_to_xyz == rel_equal(Matrix33<float>
                                                  {0.7161046,  0.1009296,  0.1471858,
                                                     0.2581874,  0.7249378,  0.0168748,
                                                     0.0000000,  0.0517813,  0.7734287},
                                                   gaudy::epsilon, 0.000001));
    REQUIRE(WideGamutRGB<float>().xyz_to_rgb == rel_equal(Matrix33<float>
                                                  { 1.4628067, -0.1840623, -0.2743606,
                                                    -0.5217933,  1.4472381,  0.0677227,
                                                     0.0349342, -0.0968930,  1.2884099},
                                                   gaudy::epsilon, 0.000001));
}

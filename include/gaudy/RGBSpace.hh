// (C) 2013 Sebastian Mach (1983), this file is published under the terms of the
// GNU General Public License, Version 3 (a.k.a. GPLv3).
// See COPYING in the root-folder of the excygen project folder.
#ifndef RGBSPACE_HH_20131122
#define RGBSPACE_HH_20131122

#include "XYZ.hh"
#include "Matrix33.hh"
#include "whitepoints.hh"
#include "gammas.hh"

namespace gaudy {

    template <typename T, typename Gamma>
    struct RGBSpace {
        Matrix33<T> rgb_to_xyz, xyz_to_rgb;
        Gamma gamma;

    protected:
        constexpr RGBSpace(Matrix33<T> rgb_to_xyz, Gamma gamma) :
            rgb_to_xyz(rgb_to_xyz),
            xyz_to_rgb(inverse(rgb_to_xyz)),
            gamma(gamma)
        {}

        constexpr RGBSpace (RGBSpace const &d) = default;
        constexpr RGBSpace& operator= (RGBSpace const &d) = delete;


        static constexpr
        RGBSpace FromXYTriple(T x_r, T y_r, T x_g, T y_g, T x_b, T y_b,
                              XYZ<double> whitepoint, Gamma gamma)
        noexcept
        {
            return lindbloom_method(
                 {/*X*/ x_r / y_r,              x_g / y_g,              x_b / y_b,
                  /*Y*/ 1,                      1,                      1,
                  /*Z*/ (1 - x_r - y_r) / y_r,  (1 - x_g - y_g) / y_g,  (1 - x_b - y_b) / y_b},
                  whitepoint, gamma
            );
        }

    private:

        static constexpr RGBSpace lindbloom_method (Matrix33<T> M,
                                                    XYZ<double> whitepoint, Gamma gamma) noexcept
        {
            return lindbloom_method_1(M, inverse(M), whitepoint, gamma);
        }

        static constexpr RGBSpace lindbloom_method_1(Matrix33<T> M, Matrix33<T> invM,
                                                     XYZ<double> whitepoint, Gamma gamma) noexcept
        {
            return lindbloom_method_2
                   (
                      M,
                      invM._11*whitepoint.X  +  invM._12*whitepoint.Y  +  invM._13*whitepoint.Z,
                      invM._21*whitepoint.X  +  invM._22*whitepoint.Y  +  invM._23*whitepoint.Z,
                      invM._31*whitepoint.X  +  invM._32*whitepoint.Y  +  invM._33*whitepoint.Z,
                      gamma
                   );
        }

        static constexpr RGBSpace lindbloom_method_2(Matrix33<T> M,
                                                     T S_r, T S_g, T S_b,
                                                     Gamma gamma) noexcept
        {
            return RGBSpace({S_r*M._11, S_g*M._12, S_b*M._13,
                             S_r*M._21, S_g*M._22, S_b*M._23,
                             S_r*M._31, S_g*M._32, S_b*M._33},
                             gamma);
        }
    };

}

namespace gaudy {
    // Apple RGB
    template <typename T> struct AppleRGB : RGBSpace<T, gaudy::gamma::detail::simple_gamma> {
     constexpr AppleRGB() noexcept : RGBSpace<T, gaudy::gamma::detail::simple_gamma>(
      RGBSpace<T, gaudy::gamma::detail::simple_gamma>::FromXYTriple(
       0.6250,0.3400, 0.2800,0.5950, 0.1550,0.0700, whitepoint::D65, gamma::_1_8)) {} };

    // Adobe RGB
    template <typename T> struct AdobeRGB : RGBSpace<T, gaudy::gamma::detail::simple_gamma> {
     constexpr AdobeRGB() noexcept : RGBSpace<T, gaudy::gamma::detail::simple_gamma>(
      RGBSpace<T, gaudy::gamma::detail::simple_gamma>::FromXYTriple(
       0.64,0.33,  0.21,0.71, 0.15,0.06, whitepoint::D65, gamma::_2_2)) {} };

    // Best RGB
    template <typename T> struct BestRGB : RGBSpace<T, gaudy::gamma::detail::simple_gamma> {
     constexpr BestRGB() noexcept : RGBSpace<T, gaudy::gamma::detail::simple_gamma>(
      RGBSpace<T, gaudy::gamma::detail::simple_gamma>::FromXYTriple(
       0.7347,0.2653, 0.2150,0.7750, 0.1300,0.0350, whitepoint::D50, gamma::_2_2)) {} };

    // Beta RGB
    template <typename T> struct BetaRGB : RGBSpace<T, gaudy::gamma::detail::simple_gamma> {
     constexpr BetaRGB() noexcept : RGBSpace<T, gaudy::gamma::detail::simple_gamma>(
      RGBSpace<T, gaudy::gamma::detail::simple_gamma>::FromXYTriple(
       0.6888,0.3112, 0.1986,0.7551, 0.1265,0.0352, whitepoint::D50, gamma::_2_2)) {} };

    // Bruce RGB
    template <typename T> struct BruceRGB : RGBSpace<T, gaudy::gamma::detail::simple_gamma> {
     constexpr BruceRGB() noexcept : RGBSpace<T, gaudy::gamma::detail::simple_gamma>(
      RGBSpace<T, gaudy::gamma::detail::simple_gamma>::FromXYTriple(
       0.6400,0.3300, 0.2800,0.6500, 0.1500,0.0600, whitepoint::D65, gamma::_2_2)) {} };

    // CIE RGB
    template <typename T> struct CIERGB : RGBSpace<T, gaudy::gamma::detail::simple_gamma> {
     constexpr CIERGB() noexcept : RGBSpace<T, gaudy::gamma::detail::simple_gamma>(
      RGBSpace<T, gaudy::gamma::detail::simple_gamma>::FromXYTriple(
       0.7350,0.2650, 0.2740,0.7170, 0.1670,0.0090, whitepoint::E, gamma::_2_2)) {} };

    // Color Match RGB
    template <typename T> struct ColorMatchRGB : RGBSpace<T, gaudy::gamma::detail::simple_gamma> {
     constexpr ColorMatchRGB() noexcept : RGBSpace<T, gaudy::gamma::detail::simple_gamma>(
      RGBSpace<T, gaudy::gamma::detail::simple_gamma>::FromXYTriple(
       0.6300,0.3400, 0.2950,0.6050, 0.1500,0.0750, whitepoint::D50, gamma::_1_8)) {} };

    // Don RGB 4
    template <typename T> struct DonRGB4 : RGBSpace<T, gaudy::gamma::detail::simple_gamma> {
     constexpr DonRGB4() noexcept : RGBSpace<T, gaudy::gamma::detail::simple_gamma>(
      RGBSpace<T, gaudy::gamma::detail::simple_gamma>::FromXYTriple(
       0.6960,0.3000, 0.2150,0.7650, 0.1300,0.0350, whitepoint::D50, gamma::_2_2)) {} };

    // ECI RGB v2
    template <typename T> struct ECIRGBv2: RGBSpace<T, gaudy::gamma::detail::L> {
     constexpr ECIRGBv2() noexcept : RGBSpace<T, gaudy::gamma::detail::L>(
      RGBSpace<T, gaudy::gamma::detail::L>::FromXYTriple(
       0.6700,0.3300, 0.2100,0.7100, 0.1400,0.0800, whitepoint::D50, gamma::L)) {} };

    // Ekta Space PS5
    template <typename T> struct EktaSpacePS5 : RGBSpace<T, gaudy::gamma::detail::simple_gamma> {
     constexpr EktaSpacePS5() noexcept : RGBSpace<T, gaudy::gamma::detail::simple_gamma>(
      RGBSpace<T, gaudy::gamma::detail::simple_gamma>::FromXYTriple(
       0.6950, 0.3050, 0.2600,0.7000, 0.1100, 0.0050, whitepoint::D50, gamma::_2_2)) {} };

    // NTSC RGB
    template <typename T> struct NTSCRGB : RGBSpace<T, gaudy::gamma::detail::simple_gamma> {
     constexpr NTSCRGB() noexcept : RGBSpace<T, gaudy::gamma::detail::simple_gamma>(
      RGBSpace<T, gaudy::gamma::detail::simple_gamma>::FromXYTriple(
       0.6700,0.3300, 0.2100,0.7100, 0.1400,0.0800, whitepoint::C, gamma::_2_2)) {} };

    // PAL/SECAM RGB
    template <typename T> struct PALSECAMRGB : RGBSpace<T, gaudy::gamma::detail::simple_gamma> {
     constexpr PALSECAMRGB() noexcept : RGBSpace<T, gaudy::gamma::detail::simple_gamma>(
      RGBSpace<T, gaudy::gamma::detail::simple_gamma>::FromXYTriple(
       0.6400,0.3300, 0.2900,0.6000, 0.1500,0.0600, whitepoint::D65, gamma::_2_2)) {} };

    // ProPhoto RGB
    template <typename T> struct ProPhotoRGB : RGBSpace<T, gaudy::gamma::detail::simple_gamma> {
     constexpr ProPhotoRGB() noexcept : RGBSpace<T, gaudy::gamma::detail::simple_gamma>(
      RGBSpace<T, gaudy::gamma::detail::simple_gamma>::FromXYTriple(
       0.7347,0.2653, 0.1596,0.8404, 0.0366,0.0001, whitepoint::D50, gamma::_1_8)) {} };

    // SMPTE-C RGB
    template <typename T> struct SMPTE_C : RGBSpace<T, gaudy::gamma::detail::simple_gamma> {
     constexpr SMPTE_C() noexcept : RGBSpace<T, gaudy::gamma::detail::simple_gamma>(
      RGBSpace<T, gaudy::gamma::detail::simple_gamma>::FromXYTriple(
       0.6300,0.3400, 0.3100,0.5950, 0.1550,0.0700, whitepoint::D65, gamma::_2_2)) {} };

    // sRGB
    template <typename T> struct sRGB : RGBSpace<T, gaudy::gamma::detail::sRGB> {
     constexpr sRGB() noexcept : RGBSpace<T, gaudy::gamma::detail::sRGB>(
      RGBSpace<T, gaudy::gamma::detail::sRGB>::FromXYTriple(
       0.6400,0.3300, 0.3000,0.6000, 0.1500,0.0600, whitepoint::D65, gamma::sRGB)) {} };

    // Wide Gamut RGB
    template <typename T> struct WideGamutRGB : RGBSpace<T, gaudy::gamma::detail::simple_gamma> {
     constexpr WideGamutRGB() noexcept : RGBSpace<T, gaudy::gamma::detail::simple_gamma>(
      RGBSpace<T, gaudy::gamma::detail::simple_gamma>::FromXYTriple(
       0.7350,0.2650, 0.1150,0.8260, 0.1570,0.0180, whitepoint::D50, gamma::_2_2)) {} };
}

#endif // RGBSPACE_HH_20131122

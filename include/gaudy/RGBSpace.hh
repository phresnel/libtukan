// (C) 2013 Sebastian Mach (1983), this file is published under the terms of the
// GNU General Public License, Version 3 (a.k.a. GPLv3).
// See COPYING in the root-folder of the excygen project folder.
#ifndef RGBSPACE_HH_20131122
#define RGBSPACE_HH_20131122

#include "XYZ.hh"
#include "Matrix33.hh"
#include "whitepoints.hh"

namespace gaudy {

    template <typename T>
    struct RGBSpace {
        Matrix33<T> rgb_to_xyz, xyz_to_rgb;

    protected:
        constexpr RGBSpace(Matrix33<T> rgb_to_xyz) :
            rgb_to_xyz(rgb_to_xyz),
            xyz_to_rgb(inverse(rgb_to_xyz))
        {}

        constexpr RGBSpace (RGBSpace const &d) = default;
        constexpr RGBSpace& operator= (RGBSpace const &d) = delete;


        static constexpr
        RGBSpace FromXYTriple(T x_r, T y_r, T x_g, T y_g, T x_b, T y_b, XYZ<double> whitepoint)
        noexcept
        {
            return lindbloom_method(
                 {/*X*/ x_r / y_r,              x_g / y_g,              x_b / y_b,
                  /*Y*/ 1,                      1,                      1,
                  /*Z*/ (1 - x_r - y_r) / y_r,  (1 - x_g - y_g) / y_g,  (1 - x_b - y_b) / y_b},
                  whitepoint
            );
        }

    private:

        static constexpr RGBSpace lindbloom_method (Matrix33<T> M, XYZ<double> whitepoint) noexcept
        {
            return lindbloom_method_1(M, inverse(M), whitepoint);
        }

        static constexpr RGBSpace lindbloom_method_1(Matrix33<T> M, Matrix33<T> invM,
                                                     XYZ<double> whitepoint) noexcept
        {
            return lindbloom_method_2
                   (
                      M,
                      invM._11*whitepoint.X  +  invM._12*whitepoint.Y  +  invM._13*whitepoint.Z,
                      invM._21*whitepoint.X  +  invM._22*whitepoint.Y  +  invM._23*whitepoint.Z,
                      invM._31*whitepoint.X  +  invM._32*whitepoint.Y  +  invM._33*whitepoint.Z
                   );
        }

        static constexpr RGBSpace lindbloom_method_2(Matrix33<T> M,
                                                     T S_r, T S_g, T S_b) noexcept
        {
            return RGBSpace({S_r*M._11, S_g*M._12, S_b*M._13,
                             S_r*M._21, S_g*M._22, S_b*M._23,
                             S_r*M._31, S_g*M._32, S_b*M._33});
        }
    };

}

namespace gaudy {
    // Apple RGB
    template <typename T> struct AppleRGB : RGBSpace<T> {
     constexpr AppleRGB() noexcept : RGBSpace<T>(
      RGBSpace<T>::FromXYTriple(0.6250,0.3400, 0.2800,0.5950, 0.1550,0.0700,  whitepoint::D65)) {} };

    // Adobe RGB
    template <typename T> struct AdobeRGB : RGBSpace<T> {
     constexpr AdobeRGB() noexcept : RGBSpace<T>(
      RGBSpace<T>::FromXYTriple(0.64,0.33,  0.21,0.71, 0.15,0.06,  whitepoint::D65)) {} };

    // Best RGB
    template <typename T> struct BestRGB : RGBSpace<T> {
     constexpr BestRGB() noexcept : RGBSpace<T>(
      RGBSpace<T>::FromXYTriple(0.7347,0.2653, 0.2150,0.7750, 0.1300,0.0350, whitepoint::D50)) {} };

    // Beta RGB
    template <typename T> struct BetaRGB : RGBSpace<T> {
     constexpr BetaRGB() noexcept : RGBSpace<T>(
      RGBSpace<T>::FromXYTriple(0.6888,0.3112, 0.1986,0.7551, 0.1265,0.0352,  whitepoint::D50)) {} };

    // Bruce RGB
    template <typename T> struct BruceRGB : RGBSpace<T> {
     constexpr BruceRGB() noexcept : RGBSpace<T>(
      RGBSpace<T>::FromXYTriple(0.6400,0.3300, 0.2800,0.6500, 0.1500,0.0600,  whitepoint::D65)) {} };

    // CIE RGB
    template <typename T> struct CIERGB : RGBSpace<T> {
     constexpr CIERGB() noexcept : RGBSpace<T>(
      RGBSpace<T>::FromXYTriple(0.7350,0.2650, 0.2740,0.7170, 0.1670,0.0090,  whitepoint::E)) {} };

    // Color Match RGB
    template <typename T> struct ColorMatchRGB : RGBSpace<T> {
     constexpr ColorMatchRGB() noexcept : RGBSpace<T>(
      RGBSpace<T>::FromXYTriple(0.6300,0.3400, 0.2950,0.6050, 0.1500,0.0750,  whitepoint::D50)) {} };

    // Don RGB 4
    template <typename T> struct DonRGB4 : RGBSpace<T> {
     constexpr DonRGB4() noexcept : RGBSpace<T>(
      RGBSpace<T>::FromXYTriple(0.6960,0.3000, 0.2150,0.7650, 0.1300,0.0350,  whitepoint::D50)) {} };

    // ECI RGB v2
    template <typename T> struct ECIRGBv2: RGBSpace<T> {
     constexpr ECIRGBv2() noexcept : RGBSpace<T>(
      RGBSpace<T>::FromXYTriple(0.6700,0.3300, 0.2100,0.7100, 0.1400,0.0800, whitepoint::D50)) {} };

    // Ekta Space PS5
    template <typename T> struct EktaSpacePS5 : RGBSpace<T> {
     constexpr EktaSpacePS5() noexcept : RGBSpace<T>(
      RGBSpace<T>::FromXYTriple(0.6950, 0.3050, 0.2600,0.7000, 0.1100, 0.0050, whitepoint::D50)) {} };

    // NTSC RGB
    template <typename T> struct NTSCRGB : RGBSpace<T> {
     constexpr NTSCRGB() noexcept : RGBSpace<T>(
      RGBSpace<T>::FromXYTriple(0.6700,0.3300, 0.2100,0.7100, 0.1400,0.0800, whitepoint::C)) {} };

    // PAL/SECAM RGB
    template <typename T> struct PALSECAMRGB : RGBSpace<T> {
     constexpr PALSECAMRGB() noexcept : RGBSpace<T>(
      RGBSpace<T>::FromXYTriple(0.6400,0.3300, 0.2900,0.6000, 0.1500,0.0600, whitepoint::D65)) {} };

    // ProPhoto RGB
    template <typename T> struct ProPhotoRGB : RGBSpace<T> {
     constexpr ProPhotoRGB() noexcept : RGBSpace<T>(
      RGBSpace<T>::FromXYTriple(0.7347,0.2653, 0.1596,0.8404, 0.0366,0.0001, whitepoint::D50)) {} };

    // SMPTE-C RGB
    template <typename T> struct SMPTE_C : RGBSpace<T> {
     constexpr SMPTE_C() noexcept : RGBSpace<T>(
      RGBSpace<T>::FromXYTriple(0.6300,0.3400, 0.3100,0.5950, 0.1550,0.0700, whitepoint::D65)) {} };

    // sRGB
    template <typename T> struct sRGB : RGBSpace<T> {
     constexpr sRGB() noexcept : RGBSpace<T>(
      RGBSpace<T>::FromXYTriple(0.6400,0.3300, 0.3000,0.6000, 0.1500,0.0600, whitepoint::D65)) {} };

    // Wide Gamut RGB
    template <typename T> struct WideGamutRGB : RGBSpace<T> {
     constexpr WideGamutRGB() noexcept : RGBSpace<T>(
      RGBSpace<T>::FromXYTriple(0.7350,0.2650, 0.1150,0.8260, 0.1570,0.0180, whitepoint::D50)) {} };
}

#endif // RGBSPACE_HH_20131122

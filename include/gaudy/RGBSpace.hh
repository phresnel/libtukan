// (C) 2013 Sebastian Mach (1983), this file is published under the terms of the
// GNU General Public License, Version 3 (a.k.a. GPLv3).
// See COPYING in the root-folder of the excygen project folder.
#ifndef RGBSPACE_HH_20131122
#define RGBSPACE_HH_20131122

#include "XYZ.hh"
#include "Matrix33.hh"

namespace gaudy {

    namespace whitepoint {
        // TODO: with C++14, the whitepoints should be variable templates.
        static constexpr XYZ<double> D65 {0.95047, 1.00000, 1.08883};
    }

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
    // sRGB
    template <typename T> struct sRGB : RGBSpace<T> {
     constexpr sRGB() noexcept : RGBSpace<T>(
      RGBSpace<T>::FromXYTriple(0.64,0.33,  0.3,0.6,   0.15,0.06,  whitepoint::D65)) {} };

    // Adobe RGB
    template <typename T> struct AdobeRGB : RGBSpace<T> {
     constexpr AdobeRGB() noexcept : RGBSpace<T>(
      RGBSpace<T>::FromXYTriple(0.64,0.33,  0.21,0.71, 0.15,0.06,  whitepoint::D65)) {} };

}

#endif // RGBSPACE_HH_20131122

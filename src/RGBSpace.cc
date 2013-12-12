// (C) 2013 Sebastian Mach (1983), this file is published under the terms of the
// GNU General Public License, Version 3 (a.k.a. GPLv3).
// See COPYING in the root-folder of the excygen project folder.
#include "gaudy/RGBSpace.hh"
#include "gaudy/Matrix33.hh"
#include "catch.hpp"

namespace gaudy {
    template <typename T>
    inline
    std::ostream& operator<< (std::ostream &os, RGBSpace<T> const &rhs) {
        return os << "rgb-space{"
                  << "to-xyz{\n"
                  << "{" << rhs.xr << ";" << rhs.xg << ";" << rhs.xb << "}\n"
                  << "{" << rhs.yr << ";" << rhs.yg << ";" << rhs.yb << "}\n"
                  << "{" << rhs.zr << ";" << rhs.zg << ";" << rhs.zb << "}\n"
                  << "}\n"
                  << "to-rgb{\n"
                  << "{" << rhs.rx << ";" << rhs.ry << ";" << rhs.rz << "}\n"
                  << "{" << rhs.gx << ";" << rhs.gy << ";" << rhs.gz << "}\n"
                  << "{" << rhs.bx << ";" << rhs.by << ";" << rhs.bz << "}\n"
                  << "}"
                  << "}";
    }


    template <typename T>
    std::ostream& operator<< (std::ostream &os, Matrix33<T> const &m) {
        return os //<< std::fixed
                  << "{(" << m._11 << "," << m._12 << "," << m._13 << "),"
                  << "(" << m._21 << "," << m._22 << "," << m._23 << "),"
                  << "(" << m._31 << "," << m._32 << "," << m._33 << ")}";
    }
}


double det(double a00, double a01, double a02,
          double a10, double a11, double a12,
          double a20, double a21, double a22)
{
    return +a00*(a11*a22-a21*a12)
           -a01*(a10*a22-a21*a12)
           +a02*(a10*a21-a11*a20);
}

void inv(double a00, double a01, double a02,
         double a10, double a11, double a12,
         double a20, double a21, double a22,
         double invdet,

         double &i00, double &i01, double &i02,
         double &i10, double &i11, double &i12,
         double &i20, double &i21, double &i22)
{
    i00 =  (a11*a22-a21*a12)*invdet;
    i10 = -(a01*a22-a02*a21)*invdet;
    i20 =  (a01*a12-a02*a11)*invdet;
    i01 = -(a10*a22-a12*a20)*invdet;
    i11 =  (a00*a22-a02*a20)*invdet;
    i21 = -(a00*a12-a10*a02)*invdet;
    i02 =  (a10*a21-a20*a11)*invdet;
    i12 = -(a00*a21-a20*a01)*invdet;
    i22 =  (a00*a11-a10*a01)*invdet;
}

void print(std::ostream &os,
           double a00, double a01, double a02,
           double a10, double a11, double a12,
           double a20, double a21, double a22)
{
    os << "(" << a00 << " " << a01 << " " << a02 << "\n"
       << " " << a10 << " " << a11 << " " << a12 << "\n"
       << " " << a20 << " " << a21 << " " << a22 << ")";
}

void print_rel(std::ostream &os,
           double a00, double a01, double a02,
           double a10, double a11, double a12,
           double a20, double a21, double a22,

           double b00, double b01, double b02,
           double b10, double b11, double b12,
           double b20, double b21, double b22)
{
    os << "(" << (a00/b00) << " " << (a01/b01) << " " << (a02/b02) << "\n"
       << " " << (a10/b10) << " " << (a11/b11) << " " << (a12/b12) << "\n"
       << " " << (a20/b20) << " " << (a21/b21) << " " << (a22/b22) << ")";
}

TEST_CASE("gaudy/RGBSpace", "RGBSpace tests") {

    using gaudy::Matrix33;

    /*std::cout << "sRGB\n" << gaudy::sRGB<double>() << "\n";
              << "AdobeRGB\n" << gaudy::AdobeRGB<double>() << "\n"*/;

    const double x_r = 0.64, y_r=0.33;
    const double x_g = 0.3,  y_g=0.6;
    const double x_b = 0.15, y_b=0.06;

    const double X_w = 0.95047, Y_w=1.00000, Z_w=1.08883; // pointed to by Mr Lindbloom upon email: http://www.brucelindbloom.com/index.html?Eqn_ChromAdapt.html

    const Matrix33<double> M_{
        /*X*/ x_r / y_r,              x_g / y_g,              x_b / y_b,
        /*Y*/ 1,                      1,                      1,
        /*Z*/ (1 - x_r - y_r) / y_r,  (1 - x_g - y_g) / y_g,  (1 - x_b - y_b) / y_b
    };

    const Matrix33<double> invM_ = inverse(M_);

    const double S_r = invM_._11*X_w  +  invM_._12*Y_w  +  invM_._13*Z_w;
    const double S_g = invM_._21*X_w  +  invM_._22*Y_w  +  invM_._23*Z_w;
    const double S_b = invM_._31*X_w  +  invM_._32*Y_w  +  invM_._33*Z_w;

    std::cout << "S={" << S_r << "," << S_g << "," << S_b << "}\n";
    std::cout << "W={" << X_w << "," << Y_w << "," << Z_w << "}\n";
    std::cout << "----------\n";

    print (std::cout,
           S_r*M_._11, S_g*M_._12, S_b*M_._13,
           S_r*M_._21, S_g*M_._22, S_b*M_._23,
           S_r*M_._31, S_g*M_._32, S_b*M_._33);
    std::cout << "\n-------------\nshould be:\n";
    print (std::cout,
           0.4124564,  0.3575761,  0.1804375,
           0.2126729,  0.7151522,  0.0721750,
           0.0193339,  0.1191920,  0.9503041);
    std::cout << "\n-------------\nrel bruce:\n";

    const Matrix33<double> M {
        S_r*M_._11, S_g*M_._12, S_b*M_._13,
        S_r*M_._21, S_g*M_._22, S_b*M_._23,
        S_r*M_._31, S_g*M_._32, S_b*M_._33,
    };
    const Matrix33<double> iM = inverse(M);

    print_rel (std::cout,
           M._11, M._12, M._13,
           M._21, M._22, M._23,
           M._31, M._32, M._33,
           0.4124564,  0.3575761,  0.1804375,
           0.2126729,  0.7151522,  0.0721750,
           0.0193339,  0.1191920,  0.9503041);
    std::cout << std::endl;
    print_rel (std::cout,
           iM._11, iM._12, iM._13,
           iM._21, iM._22, iM._23,
           iM._31, iM._32, iM._33,
           3.2404542, -1.5371385, -0.4985314,
           -0.9692660,  1.8760108,  0.0415560,
           0.0556434, -0.2040259,  1.0572252);
    std::cout << std::endl;
}

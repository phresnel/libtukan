// (C) 2013 Sebastian Mach (1983), this file is published under the terms of the
// GNU General Public License, Version 3 (a.k.a. GPLv3).
// See COPYING in the root-folder of the excygen project folder.
#include "gaudy/RGBSpace.hh"
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

TEST_CASE("gaudy/RGBSpace", "RGBSpace tests") {
    std::cout << "sRGB\n" << gaudy::sRGB<double>() << "\n";
              /*<< "AdobeRGB\n" << gaudy::AdobeRGB<double>() << "\n"*/;

    const double x_r = 0.64, y_r=0.33;
    const double x_g = 0.3,  y_g=0.6;
    const double x_b = 0.15, y_b=0.06;


    const double X_r = x_r / y_r;
    const double X_g = x_g / y_g;
    const double X_b = x_b / y_b;

    const double Z_r = (1 - x_r - y_r) / y_r;
    const double Z_g = (1 - x_g - y_g) / y_g;
    const double Z_b = (1 - x_b - y_b) / y_b;

    const double Y_r = 1;
    const double Y_g = 1;
    const double Y_b = 1;


    const double XYZ_det = det(X_r, X_g, X_b,
                               Y_r, Y_g, Y_b,
                               Z_r, Z_g, Z_b);
    const double XYZ_invdet = 1 / XYZ_det;


    double invX_r, invX_g, invX_b,
           invY_r, invY_g, invY_b,
           invZ_r, invZ_g, invZ_b;

    inv(X_r, X_g, X_b,
        Y_r, Y_g, Y_b,
        Z_r, Z_g, Z_b,
        XYZ_invdet,

        invX_r, invY_r, invZ_r,
        invX_g, invY_g, invZ_g,
        invX_b, invY_b, invZ_b);

    const double X_w = .950429;
    const double Y_w = 1.000;
    const double Z_w = 1.088900;

    const double S_r = invX_r*X_w  +  invX_g*Y_w  +  invX_b*Z_w;
    const double S_g = invY_r*X_w  +  invY_g*Y_w  +  invY_b*Z_w;
    const double S_b = invZ_r*X_w  +  invZ_g*Y_w  +  invZ_b*Z_w;
    /*const double S_r = invX_r*X_w  +  invY_r*Y_w  +  invZ_r*Z_w;
    const double S_g = invX_g*X_w  +  invY_g*Y_w  +  invZ_g*Z_w;
    const double S_b = invX_b*X_w  +  invY_b*Y_w  +  invZ_b*Z_w;*/

    std::cout << "S={" << S_r << "," << S_g << "," << S_b << "}\n";
    std::cout << "e={" << (0.4124564/X_r) << "," << (0.3575761/X_g) << "," << (0.1804375/X_b) << "}\n";
    //std::cout << (0.4124564/0.2126729) << "::" << (X_r/Y_r) << std::endl;
    std::cout << "----------\n";
    /*print (std::cout,
           X_r, X_g, X_b,
           Y_r, Y_g, Y_b,
           Z_r, Z_g, Z_b);
    std::cout << "\n----------\n";*/
    print (std::cout,
           S_r*X_r, S_g*X_g, S_b*X_b,
           S_r*Y_r, S_g*Y_g, S_b*Y_b,
           S_r*Z_r, S_g*Z_g, S_b*Z_b);
    std::cout << "\n-------------\n";
}

// (C) 2013 Sebastian Mach (1983), this file is published under the terms of the
// GNU General Public License, Version 3 (a.k.a. GPLv3).
// See COPYING in the root-folder of the excygen project folder.
#ifndef GAMMAS_HH_INCLUDED_20131231
#define GAMMAS_HH_INCLUDED_20131231

#include <cmath>

namespace tukan { namespace gamma { namespace detail {

    struct simple_gamma {
        double gamma;
        simple_gamma (double gamma) noexcept : gamma(gamma) {}

        double to_linear (double v) noexcept {
            using std::pow; using std::fabs;
            return (v<0?-1:1) * pow(fabs(v), gamma);
        }

        double to_nonlinear (double v) noexcept {
            using std::pow; using std::fabs;
            return (v<0?-1:1) * pow(fabs(v), 1./gamma);
        }
    };

    // see also * http://www.w3.org/Graphics/Color/sRGB.html
    //          * http://en.wikipedia.org/wiki/SRGB
    struct sRGB {

        double to_linear (double v) noexcept {
            using std::fabs;
            return (v<0?-1:1) * to_linear_impl(fabs(v));
        }

        double to_nonlinear (double v) noexcept {
            using std::fabs;
            return (v<0?-1:1) * to_nonlinear_impl(fabs(v));
        }

    private:
        double to_linear_impl (double v) noexcept {
            using std::pow;
            return (v<=0.04045) ? (v/12.92)
                                : pow((v+0.055)/1.055, 2.4);
        }

        double to_nonlinear_impl (double v) noexcept {
            using std::pow;
            return (v<=0.0031308) ? (v*12.92)
                                  : 1.055*pow(v, 1/2.4) - 0.055;
        }
    };

    // see also * http://www.brucelindbloom.com/
    struct L {

        double to_linear (double v) noexcept {
            using std::fabs;
            return (v<0?-1:1) * to_linear_impl(fabs(v));
        }

        double to_nonlinear (double v) noexcept {
            using std::fabs;
            return (v<0?-1:1) * to_nonlinear_impl(fabs(v));
        }

    private:
        double to_linear_impl (double v) noexcept {
            using std::pow;
            return (v<=0.08) ? (100*v/903.3) // using actual CIE standard
                             : pow((v+0.16)/1.16, 3.0);
        }

        double to_nonlinear_impl (double v) noexcept {
            using std::pow;
            return (v<=0.008856) ? (v*9.033)
                                 : 1.16*pow(v, 1/3.0) - 0.16;
        }
    };

} } }


namespace tukan { namespace gamma {

    static inline auto _1_0 = detail::simple_gamma(1.0);
    static inline auto _1_8 = detail::simple_gamma(1.8);
    static inline auto _2_2 = detail::simple_gamma(2.2);
    static inline auto sRGB = detail::sRGB();
    static inline auto L    = detail::L();

} }

#endif // GAMMAS_HH_INCLUDED_20131231

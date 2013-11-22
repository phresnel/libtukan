// (C) 2013 Sebastian Mach (1983), this file is published under the terms of the
// GNU General Public License, Version 3 (a.k.a. GPLv3).
// See COPYING in the root-folder of the excygen project folder.
#ifndef RGBSPACE_HH_20131122
#define RGBSPACE_HH_20131122

namespace gaudy {

    template <typename T>
    struct RGBSpace {
        T rx, ry, rz,
          gx, gy, gz,
          bx, by, bz;

        T xr, yr, zr,
          xg, yg, zg,
          xb, yb, zb;
    protected:
        constexpr RGBSpace(T rx, T ry, T rz,
                           T gx, T gy, T gz,
                           T bx, T by, T bz,

                           T xr, T xg, T xb,
                           T yr, T yg, T yb,
                           T zr, T zg, T zb) noexcept :
           rx(rx), ry(ry), rz(rz),
           gx(gx), gy(gy), gz(gz),
           bx(bx), by(by), bz(bz),

           xr(xr), yr(yr), zr(zr),
           xg(xg), yg(yg), zg(zg),
           xb(xb), yb(yb), zb(zb)
        {}

        constexpr RGBSpace (RGBSpace const &d) = default;
        constexpr RGBSpace& operator= (RGBSpace const &d) = delete;

        static constexpr
        RGBSpace from_xy_quadruple(T xr, T yr, T xg, T yg, T xb, T yb, T xw, T yw) noexcept
        {
            return description_0(xr,yr, xg,yg, xb,yb, xw,yw,
                                 1-(xr+yr), 1-(xg+yg), 1-(xb+yb), 1-(xw + yw));
        }

    private:
        static constexpr
        RGBSpace description_0(T xr, T yr, T xg, T yg, T xb, T yb, T xw, T yw,
                               T zr, T zg, T zb, T zw) noexcept
        {
            return description_1(xw, yw, zw,
                                 // xyz -> rgb matrix, before scaling to white.
                                 (yg * zb) - (yb * zg),
                                 (xb * zg) - (xg * zb),
                                 (xg * yb) - (xb * yg),
                                 (yb * zr) - (yr * zb),
                                 (xr * zb) - (xb * zr),
                                 (xb * yr) - (xr * yb),
                                 (yr * zg) - (yg * zr),
                                 (xg * zr) - (xr * zg),
                                 (xr * yg) - (xg * yr)
                                 );
        }

        static constexpr
        RGBSpace description_1 (T xw, T yw, T zw,
                                T rx, T ry, T rz,
                                T gx, T gy, T gz,
                                T bx, T by, T bz) noexcept
        {
            return description_2 (rx, ry, rz,
                                  gx, gy, gz,
                                  bx, by, bz,
                                  // White scaling factors. Dividing by yw scales the white
                                  // luminance to unity, as conventional.
                                  ((rx * xw) + (ry * yw) + (rz * zw)) / yw,
                                  ((gx * xw) + (gy * yw) + (gz * zw)) / yw,
                                  ((bx * xw) + (by * yw) + (bz * zw)) / yw);
        }

        static constexpr
        RGBSpace description_2(T rx, T ry, T rz,
                               T gx, T gy, T gz,
                               T bx, T by, T bz,
                               T rw, T gw, T bw) noexcept
        {
            // xyz -> rgb matrix, correctly scaled to white
            return description_3(rx/rw, ry/rw, rz/rw,
                                 gx/gw, gy/gw, gz/gw,
                                 bx/bw, by/bw, bz/bw);
        }

        static constexpr
        RGBSpace description_3(T rx, T ry, T rz,
                               T gx, T gy, T gz,
                               T bx, T by, T bz) noexcept
        {
            return description_4(rx, ry, rz,
                                 gx, gy, gz,
                                 bx, by, bz,
                                 // determinant to build inverse
                                 1 / (rx * (gy*bz - by*gz)
                                     -ry * (gx*bz - bx*gz)
                                     +rz * (gx*by - bx*gy)));
        }

        static constexpr
        RGBSpace description_4(T rx, T ry, T rz,
                               T gx, T gy, T gz,
                               T bx, T by, T bz,
                               T s) noexcept
        {
            return RGBSpace(rx, ry, rz,
                            gx, gy, gz,
                            bx, by, bz,
                            s*(gy*bz - gz*by), s*(rz*by - ry*bz), s*(ry*gz - rz*gy),
                            s*(gz*bx - gx*bz), s*(rx*bz - rz*bx), s*(rz*gx - rx*gz),
                            s*(gx*by - gy*bx), s*(ry*bx - rx*by), s*(rx*gy - ry*gx));
        }
    };
}

namespace gaudy {
    // sRGB
    template <typename T> struct sRGB : RGBSpace<T> {
     constexpr sRGB() noexcept : RGBSpace<T>(
      RGBSpace<T>::from_xy_quadruple(0.64,0.33,  0.3,0.6,   0.15,0.06,  0.31271,0.32902)) {} };

    // Adobe RGB
    template <typename T> struct AdobeRGB : RGBSpace<T> {
     constexpr AdobeRGB() noexcept : AdobeRGB<T>(
      RGBSpace<T>::from_xy_quadruple(0.64,0.33,  0.21,0.71, 0.15,0.06,  0.31271,0.32902)) {} };

}

#endif // RGBSPACE_HH_20131122

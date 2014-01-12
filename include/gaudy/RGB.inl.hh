// (C) 2013 Sebastian Mach (1983), this file is published under the terms of the
// GNU General Public License, Version 3 (a.k.a. GPLv3).
// See COPYING in the root-folder of the excygen project folder.
#ifndef RGB_INL_HH_20140112
#define RGB_INL_HH_20140112



// Member functions implementation.
namespace gaudy {

    template <typename T, template <typename> class RGBSpace>
    T RGB<T, RGBSpace>::* const RGB<T, RGBSpace>::offsets_[3] =
    {
        &RGB<T, RGBSpace>::r,
        &RGB<T, RGBSpace>::g,
        &RGB<T, RGBSpace>::b
    };


    template <typename T, template <typename> class RGBSpace>
    inline
    T& RGB<T, RGBSpace>::operator[] (size_t idx) noexcept
    {
        return this->*offsets_[idx];
    }


    template <typename T, template <typename> class RGBSpace>
    inline constexpr
    T RGB<T, RGBSpace>::operator[] (size_t idx) const noexcept
    {
        return this->*offsets_[idx];
    }


    template <typename T, template <typename> class RGBSpace>
    inline
    T& RGB<T, RGBSpace>::at (size_t idx)
    {
        if (idx>=size()) // TODO: check if the negative check is faster.
            throw std::out_of_range("RGB: out of range access");
        return this->*offsets_[idx];
    }


    template <typename T, template <typename> class RGBSpace>
    inline constexpr
    T RGB<T, RGBSpace>::at (size_t idx) const
    {
        if (idx>=size()) // TODO: check if the negative check is faster.
            throw std::out_of_range("RGB: out of range access");
        return this->*offsets_[idx];
    }


    template <typename T, template <typename> class RGBSpace>
    inline constexpr
    size_t RGB<T, RGBSpace>::size() const noexcept
    {
        return 3;
    }


    // TODO: refactor xyz-conversion wrt LinearRGB/RGB conversions
    namespace detail {
        template <typename T, template <typename> class RGBSpace>
        constexpr XYZ<T> to_xyz (T r, T g, T b) noexcept
        {
            return {
                r*RGBSpace<T>().rgb_to_xyz._11 + g*RGBSpace<T>().rgb_to_xyz._12 + b*RGBSpace<T>().rgb_to_xyz._13,
                r*RGBSpace<T>().rgb_to_xyz._21 + g*RGBSpace<T>().rgb_to_xyz._22 + b*RGBSpace<T>().rgb_to_xyz._23,
                r*RGBSpace<T>().rgb_to_xyz._31 + g*RGBSpace<T>().rgb_to_xyz._32 + b*RGBSpace<T>().rgb_to_xyz._33
            };
        }
    }

    template <typename T, template <typename> class RGBSpace>
    constexpr RGB<T, RGBSpace>::operator XYZ<T> () noexcept
    {
        using detail::to_xyz;
        return to_xyz<T,RGBSpace>(static_cast<T>(RGBSpace<T>().gamma.to_linear(r)),
                                  static_cast<T>(RGBSpace<T>().gamma.to_linear(g)),
                                  static_cast<T>(RGBSpace<T>().gamma.to_linear(b)));
    }


    template <typename T, template <typename> class RGBSpace>
    constexpr RGB<T, RGBSpace>::RGB (XYZ<T> xyz) noexcept
        : r(RGBSpace<T>().gamma.to_nonlinear(xyz.X*RGBSpace<T>().xyz_to_rgb._11 + xyz.Y*RGBSpace<T>().xyz_to_rgb._12 + xyz.Z*RGBSpace<T>().xyz_to_rgb._13))
        , g(RGBSpace<T>().gamma.to_nonlinear(xyz.X*RGBSpace<T>().xyz_to_rgb._21 + xyz.Y*RGBSpace<T>().xyz_to_rgb._22 + xyz.Z*RGBSpace<T>().xyz_to_rgb._23))
        , b(RGBSpace<T>().gamma.to_nonlinear(xyz.X*RGBSpace<T>().xyz_to_rgb._31 + xyz.Y*RGBSpace<T>().xyz_to_rgb._32 + xyz.Z*RGBSpace<T>().xyz_to_rgb._33))
    {
    }


    template <typename T, template <typename> class RGBSpace>
    constexpr RGB<T, RGBSpace>::operator LinearRGB<T, RGBSpace> () noexcept
    {
        return {static_cast<T>(RGBSpace<T>().gamma.to_linear(r)),
                static_cast<T>(RGBSpace<T>().gamma.to_linear(g)),
                static_cast<T>(RGBSpace<T>().gamma.to_linear(b))};
    }

    template <typename T, template <typename> class RGBSpace>
    constexpr RGB<T, RGBSpace>::RGB (LinearRGB<T, RGBSpace> linear) noexcept
        : r(static_cast<T>(RGBSpace<T>().gamma.to_nonlinear(linear.r)))
        , g(static_cast<T>(RGBSpace<T>().gamma.to_nonlinear(linear.g)))
        , b(static_cast<T>(RGBSpace<T>().gamma.to_nonlinear(linear.b)))
    {
    }
}



namespace gaudy {

    // relation
    template <typename T, template <typename> class RGBSpace>
    constexpr bool operator== (RGB<T, RGBSpace> lhs, RGB<T, RGBSpace> rhs) noexcept {
        return lhs.r==rhs.r && lhs.g==rhs.g && lhs.b==rhs.b;
    }
    template <typename T, template <typename> class RGBSpace>
    constexpr bool operator!= (RGB<T, RGBSpace> lhs, RGB<T, RGBSpace> rhs) noexcept {
        return !(lhs == rhs);
    }
    template <typename T, template <typename> class RGBSpace>
    constexpr bool rel_equal (RGB<T, RGBSpace> lhs, RGB<T, RGBSpace> rhs, T max_rel_diff) noexcept
    {
        return rel_equal (lhs.r, rhs.r, max_rel_diff)
            && rel_equal (lhs.g, rhs.g, max_rel_diff)
            && rel_equal (lhs.b, rhs.b, max_rel_diff)
        ;
    }

}

#endif // RGB_INL_HH_20140112

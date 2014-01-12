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


    template <typename T, template <typename> class RGBSpace>
    constexpr RGB<T, RGBSpace>::operator XYZ<T> () noexcept
    {
        return static_cast<XYZ<T>> (static_cast<LinearRGB<T,RGBSpace>> (*this));
    }


    template <typename T, template <typename> class RGBSpace>
    constexpr RGB<T, RGBSpace>::RGB (XYZ<T> xyz) noexcept
        : RGB(static_cast<LinearRGB<T,RGBSpace>> (xyz))
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

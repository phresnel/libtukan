// (C) 2013 Sebastian Mach (1983), this file is published under the terms of the
// GNU General Public License, Version 3 (a.k.a. GPLv3).
// See COPYING in the root-folder of the excygen project folder.
#ifndef RGB_HH_INCLUDED_20140112
#define RGB_HH_INCLUDED_20140112

#include "RGBSpace.hh"
#include "LinearRGB.hh"
#include "XYZ.hh"

namespace tukan {

    // -- structure -------------------------------------------------------------------------------
    template <typename T, template <typename> class RGBSpace>
    struct RGB {

        // Data.
        T r=0, g=0, b=0;


        // Construction.
        constexpr RGB() noexcept = default;
        constexpr RGB(T r, T g, T b) noexcept : r(r), g(g), b(b) {}
        constexpr explicit RGB(T f) noexcept  : r(f), g(f), b(f) {}


        // Conversion.
        constexpr explicit operator XYZ<T> () noexcept;
        constexpr explicit RGB (XYZ<T>) noexcept;

        constexpr explicit operator LinearRGB<T, RGBSpace> () noexcept;
        constexpr explicit RGB (LinearRGB<T, RGBSpace>) noexcept;



        // Array interface.
        constexpr T  at         (size_t idx) const ;
        constexpr T  operator[] (size_t idx) const noexcept;
        T& at         (size_t idx) ;
        T& operator[] (size_t idx) noexcept;

        constexpr size_t size() const noexcept ; // Always "3".


        // Meta.
        using value_type = T;
        template <typename N> using rebind_value_type = RGB<N, RGBSpace>;


    private:
        static T RGB::* const offsets_[3];
    };


    template <typename T, template <typename> class RGBSpace>
    constexpr size_t size(RGB<T, RGBSpace> const &v) noexcept { return v.size(); }


    // -- relation --------------------------------------------------------------------------------
    template <typename T, template <typename> class RGBSpace> constexpr bool operator== (RGB<T, RGBSpace> lhs, RGB<T, RGBSpace> rhs) noexcept;
    template <typename T, template <typename> class RGBSpace> constexpr bool operator!= (RGB<T, RGBSpace> lhs, RGB<T, RGBSpace> rhs) noexcept;
    template <typename T, template <typename> class RGBSpace> constexpr bool rel_equal (RGB<T, RGBSpace> lhs, RGB<T, RGBSpace> rhs,
                                                    T max_rel_diff=std::numeric_limits<T>::epsilon() ) noexcept;

}

#include "inl/RGB.inl.hh"

#endif // RGB_HH_INCLUDED_20140112

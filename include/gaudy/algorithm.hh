// (C) 2013 Sebastian Mach (1983), this file is published under the terms of the
// GNU General Public License, Version 3 (a.k.a. GPLv3).
// See COPYING in the root-folder of the excygen project folder.
#ifndef ALGORITHM_HH_INCLUDED_20131029
#define ALGORITHM_HH_INCLUDED_20131029

#include "Interval.hh"

//--------------------------------------------------------------------------------------------------
// Interface / Documentation
//--------------------------------------------------------------------------------------------------
namespace gaudy {

    //=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
    //
    // lerp : L -> R -> F -> (L*(1-F) + R*F)
    //
    //----------------------------------------------------------------------------------------------
    // Type Requirements:
    //   f          :  `(1-f)` must be defined
    //   a          :  `a*(1-f)` must be defined
    //   b          :  `b*f` must be defined
    //   other      :  `a*(1-f)+b*f` must be defined
    //
    // Value Requirements:
    //   None. Particularly, f is allowed to be outside [0..1], such that for f=2, lerp(0,1,f)==2.
    //
    //----------------------------------------------------------------------------------------------
    // About:
    //
    // A quite flexible lerp implementation which is templated upon the first operand a,
    // the second operand b, and its interpolant f:
    //
    //        (left op   , right op  , interpolant ) == result
    //    - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    //    lerp(RGB(0,0,0), RGB(1,2,3), 0.5         ) == RGB(0.5,1  ,1.5)
    //    lerp(RGB(0,0,0), RGB(1,2,3), RGB(0,0.5,1)) == RGB(0  ,1  ,3  )
    //    lerp(RGB(0,0,0), 1         , RGB(0,0.5,1)) == RGB(0  ,0.5,1  )
    //    lerp(0         , 1         , RGB(0,0.5,1)) == RGB(0  ,0.5,1  )
    //
    //=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
    template <typename L, typename R, typename F>
    auto lerp(L a, R b, F f) noexcept -> decltype(a*(1-f) + b*f);



    //=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
    //
    // lerp : [T..T] -> f -> (T*(1-F) + T*F)
    //
    //----------------------------------------------------------------------------------------------
    // About:
    //
    // Overload for intervals. Note that in an interval, min<=max, which is not defined for
    // for all types:
    //
    //    lerp(interval(RGB(0,0,0),RGB(1,1,1)), 0.5); // not compilable. RGB<=RGB is not defined.
    //    lerp(interval(0,1), RGB(0.0,0.5,1);         // compilable, however.
    //
    //=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
    template <typename T, typename F>
    auto lerp(Interval<T> i, F f) noexcept -> decltype(lerp(i.min, i.max, f));
}






//--------------------------------------------------------------------------------------------------
// Implementation
//--------------------------------------------------------------------------------------------------
namespace gaudy {
    template <typename L, typename R, typename F>
    inline auto lerp(L a, R b, F f) noexcept -> decltype(a*(1-f) + b*f) {
        return a*(1-f) + b*f;
    }

    template <typename T, typename F>
    inline auto lerp(Interval<T> i, F f) noexcept -> decltype(lerp(i.min, i.max, f)) {
        return lerp(i.min, i.max, f);
    }
}

#endif // ALGORITHM_HH_INCLUDED_20131029

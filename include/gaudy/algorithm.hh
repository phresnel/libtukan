// (C) 2013 Sebastian Mach (1983), this file is published under the terms of the
// GNU General Public License, Version 3 (a.k.a. GPLv3).
// See COPYING in the root-folder of the excygen project folder.
#ifndef ALGORITHM_HH_INCLUDED_20131029
#define ALGORITHM_HH_INCLUDED_20131029

#include "Interval.hh"
#include <cmath>
#include <algorithm>
#include <initializer_list>
#include <type_traits>
#include <iterator>


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



    //=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
    //
    // lerp_sat : L -> R -> F -> (L*(1-F) + R*F)
    //
    //----------------------------------------------------------------------------------------------
    // Type Requirements:
    //   The same requirements like for lerp apply, with the following addition:
    //
    //   `f = max(F(0), min(f, F(1)))` must be defined, such that if f<0, f is saturated to 0,
    //                                 and if f>1, f is saturated to 1.
    //
    //----------------------------------------------------------------------------------------------
    // About:
    //
    // Overload which does the same as lerp, but saturates f into the range [0..1]. The effect is
    // that for `lerp_sat(a,b,f)`, the result is `a` for all `f<0`, `b` for all `f>1`, and
    // `lerp(a,b,f)` for any `f in [0..1]`.
    //
    //=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
    template <typename L, typename R, typename F>
    auto lerp_sat(L a, R b, F f) noexcept -> decltype(a*(1-f) + b*f);



    //=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
    //
    // lerp_sat : [T..T] -> f -> (T*(1-F) + T*F)
    //
    //----------------------------------------------------------------------------------------------
    // About:
    //
    // Overload which does the same as lerp, but saturates f into the range [0..1]. The effect is
    // that for `lerp_sat([a,b],f)`, the result is `a` for all `f<0`, `b` for all `f>1`, and
    // `lerp([a,b],f)` for any `f in [0..1]`.
    //
    //=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
    template <typename T, typename F>
    auto lerp_sat(Interval<T> i, F f) noexcept -> decltype(lerp_sat(i.min, i.max, f));



    //=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
    //
    // lerp_sat : RandomAccessIterator -> RandomAccessIterator -> f -> lerp(*,*,f)
    //
    //----------------------------------------------------------------------------------------------
    // Type Requirements:
    //
    // * let x_n be any element in the range, then `lerp(x_n,x_(n+1), f)` must be defined
    // * `f = max(F(0), min(f, F(1))) * size_t()` must be defined
    // * `size_t(trunc(f))` must be defined, i.e. `trunc(f)` must be defined, and `f` must be
    //    convertible to `size_t` (a conversion to `int` will work).
    //
    // Value Requirements:
    //   None:
    //     * an initializer-list without elements results in an exception
    //     * `f` will be saturated onto [0..1]
    //
    //----------------------------------------------------------------------------------------------
    // About:
    //
    // This overload allows to use lerp_sat with random-access-iterators, or simply containers:
    //   std::vector<int> foo{1,2,3,5};
    //   lerp_sat(foo.begin(), foo.end(), 0.5) == 1
    //   lerp_sat(begin(foo), end(foo), 0.5) == 1.5
    //
    // Calling it with an empty container yields an exception.
    //
    // There is some additional overhead in size-checking, but optimization will probably eliminate
    // it.
    //=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
    template <typename Iter, typename F>
    auto lerp_sat(Iter begin, Iter end, F f)
     -> decltype(lerp(*Iter(), *Iter(), F()-std::size_t()));



    //=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
    //
    // lerp_sat : {x_1,x_2,..,x_n} -> f -> lerp(x_a,x_b,f)
    //
    //----------------------------------------------------------------------------------------------
    // Type Requirements:
    //
    // * let x_n be any element in the initializer-list, then `lerp(x_n,x_(n+1), f)` must be defined
    // * `f = max(F(0), min(f, F(1))) * size_t()` must be defined
    // * `size_t(trunc(f))` must be defined, i.e. `trunc(f)` must be defined, and `f` must be
    //    convertible to `size_t` (a conversion to `int` will work).
    //
    // Value Requirements:
    //   None:
    //     * an initializer-list without elements results in an exception
    //     * `f` will be saturated onto [0..1]
    //
    //----------------------------------------------------------------------------------------------
    // About:
    //
    // This overload allows to use lerp_sat like this:
    //   lerp_sat({1}, 0.5) == 1
    //   lerp_sat({1,2}, 0.5) == 1.5
    //   lerp_sat({1,2,3,4}, 0.5) == 2.5
    //
    // Note that calling it with an empty initializer-list yields an exception, therefore it is not
    // noexcept.
    //
    // There is some additional overhead in size-checking, but optimization wil probably eliminate
    // it.
    //=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
    template <typename T, typename F>
    auto lerp_sat(std::initializer_list<T> vals, F f)
      -> decltype(lerp_sat(vals.begin(), vals.end(), f));
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

    template <typename L, typename R, typename F>
    inline auto lerp_sat(L a, R b, F f) noexcept -> decltype(a*(1-f) + b*f) {
        using std::min; using std::max;
        f = max(F(0), min(f, F(1)));
        return a*(1-f) + b*f;
    }

    template <typename T, typename F>
    inline auto lerp_sat(Interval<T> i, F f) noexcept -> decltype(lerp_sat(i.min, i.max, f)) {
        return lerp_sat(i.min, i.max, f);
    }    

    template <typename Iter, typename F>
    inline auto lerp_sat(Iter begin, Iter end, F f)
     -> decltype(lerp(*Iter(), *Iter(), F()-std::size_t()))
    {
        using std::min; using std::max; using std::trunc; using std::distance; using std::next;

        const auto size = distance(begin, end);
        switch (size) {
        case 0: throw std::logic_error("called lerp_sat({...},f) with empty initializer list");
        case 1: return *begin;
        default:
            f = max(F(0), min(f, F(1))) * (size-1);
            const auto t = std::size_t(trunc(f));
            const auto x = next(begin, t);
            return lerp(*x, *next(x), f-t);
        }
    }

    template <typename T, typename F>
    inline auto lerp_sat(std::initializer_list<T> vals, F f)
     -> decltype(lerp_sat(vals.begin(), vals.end(), f))
    {
        return lerp_sat(begin(vals), end(vals), f);
    }
}

#endif // ALGORITHM_HH_INCLUDED_20131029

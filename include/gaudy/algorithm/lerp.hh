// (C) 2013 Sebastian Mach (1983), this file is published under the terms of the
// GNU General Public License, Version 3 (a.k.a. GPLv3).
// See COPYING in the root-folder of the excygen project folder.
#ifndef LERP_HH_INCLUDED_20131031
#define LERP_HH_INCLUDED_20131031



//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
//
// lerp:
//
//    'lerp' does linear interpolation of its first arguments using the last argument as the
//    interpolant.
//
//
// Definitions:
//
//    auto lerp (L a, R b     , F f) noexcept
//    auto lerp (Interval<T> i, F f) noexcept
//
//    'lerp_sat' provides additional overloads for ranges, containers and initializer lists.
//
//
// Examples:
//
//        (left op   , right op  , interpolant ) == result
//    - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
//    lerp(RGB(0,0,0), RGB(1,2,3), 0.5         ) == RGB(0.5,1  ,1.5)
//    lerp(RGB(0,0,0), RGB(1,2,3), RGB(0,0.5,1)) == RGB(0  ,1  ,3  )
//    lerp(RGB(0,0,0), 1         , RGB(0,0.5,1)) == RGB(0  ,0.5,1  )
//    lerp(0         , 1         , RGB(0,0.5,1)) == RGB(0  ,0.5,1  )
//
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
//
// lerp_sat:
//
//    'lerp_sat' does linear interpolation, too, however, it saturates the factor to [0..1].
//    It does so by means of functions 'min(F,F)' and 'max(F,F)', which means that you can still
//    use non-scalar types, like RGB, as the interpolant, for some overloads of 'lerp_sat'.
//
//    'lerp_sat' also provides additional overloads for range/container types and for
//    'initializer_list<>'.
//
//
// Overloads:
//
//    auto lerp_sat (L a, R b                     , F f) noexcept
//    auto lerp_sat (Interval<T> i                , F f) noexcept
//    auto lerp_sat (Iter begin, Iter end         , F f)
//    auto lerp_sat (std::initializer_list<T> vals, F f)
//    auto lerp_sat (Range const& range           , F f)
//
//
// Examples:
//
//    lerp_sat (0, 1.5, RGB(0,1,2)); // Note: RGB value as interpolant.
//    lerp_sat (interval(RGB(0,0,0),RGB(1,1,1)), 0.5);
//
//    std::vector<float> x {{1,2,3}};
//    lerp_sat (x.begin(), x.end(), 0.5);
//    lerp_sat (begin(x), end(x), 0.5);
//    lerp_sat (x, 0.5);
//
//    lerp({5,6,7}, 0.5);
//
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=



#include "../Interval.hh"
#include <cmath>
#include <algorithm>
#include <initializer_list>
#include <type_traits>
#include <iterator>



namespace gaudy
{

    template <typename L, typename R, typename F>
    inline auto lerp(L a, R b, F f) noexcept -> decltype(a*(1-f) + b*f)
    {
        return a*(1-f) + b*f;
    }

    template <typename T, typename F>
    inline auto lerp(Interval<T> i, F f) noexcept -> decltype(lerp(i.min, i.max, f))
    {
        return lerp(i.min, i.max, f);
    }

}



namespace gaudy
{

    template <typename L, typename R, typename F>
    inline auto lerp_sat(L a, R b, F f) noexcept -> decltype(a*(1-f) + b*f)
    {
        using std::min; using std::max;
        f = max(F(0), min(f, F(1)));
        return a*(1-f) + b*f;
    }


    template <typename T, typename F>
    inline auto lerp_sat(Interval<T> i, F f) noexcept -> decltype(lerp_sat(i.min, i.max, f))
    {
        return lerp_sat(i.min, i.max, f);
    }


    template <typename Iter, typename F>
    inline auto lerp_sat(Iter begin, Iter end, F f)
      -> decltype(lerp(*begin, *begin, f-std::size_t()))
    {
        // TODO: possibly use 'std::next' in the function signature.
        // TODO: static_assert to see if `distance(begin,end)` is defined.
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
     -> decltype(lerp_sat(std::begin(vals), std::end(vals), f))
    {
        return lerp_sat(begin(vals), end(vals), f);
    }


    template <typename Range, typename F>
    inline auto lerp_sat(Range const &range, F f)
     -> decltype(lerp_sat(std::begin(range), std::end(range), f))
    {
        return lerp_sat(std::begin(range), std::end(range), f);
    }

}

#endif // LERP_HH_INCLUDED_20131031

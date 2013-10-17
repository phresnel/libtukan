// (C) 2013 Sebastian Mach (1983), this file is published under the terms of the
// GNU General Public License, Version 3 (a.k.a. GPLv3).
// See COPYING in the root-folder of the excygen project folder.
#ifndef INTERVAL_HH_INCLUDED_20131017
#define INTERVAL_HH_INCLUDED_20131017

#include "optional.hh"
#include <algorithm>
#include <stdexcept>

namespace gaudy {

    //----------------------------------------------------------------------------------------------
    // Interval
    //----------------------------------------------------------------------------------------------
    template <typename T>
    class Interval {
    public:
        constexpr Interval(T min, T max) :
            min_(min<=max?min:throw std::out_of_range("Interval::min must be <= Interval::max")),
            max_(max)
        {}
        constexpr T min() noexcept { return min_; }
        constexpr T max() noexcept { return max_; }
    private:
        T min_, max_;
    };

    template <typename T>
    inline constexpr
    bool operator== (Interval<T> const &lhs, Interval<T> const &rhs) noexcept {
        return lhs.min()==rhs.min() && lhs.max()==rhs.max();
    }

    template <typename T>
    inline constexpr
    bool operator!= (Interval<T> const &lhs, Interval<T> const &rhs) noexcept {
        return !(lhs==rhs);
    }

    template <typename T>
    inline constexpr
    T length(Interval<T> const &i) noexcept {
        return i.max() - i.min();
    }

    template <typename T>
    inline
    optional<Interval<T>> intersection(Interval<T> const &lhs, Interval<T> const &rhs) noexcept {
        using std::min; using std::max;
        T l = max(lhs.min(), rhs.min()),
          r = min(lhs.max(), rhs.max());
        if (l>r) return optional<Interval<T>>();
        return Interval<T>(l,r);
    }

}

#endif // INTERVAL_HH_INCLUDED_20131017

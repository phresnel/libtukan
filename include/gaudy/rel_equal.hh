// (C) 2013 Sebastian Mach (1983), this file is published under the terms of the
// GNU General Public License, Version 3 (a.k.a. GPLv3).
// See COPYING in the root-folder of the excygen project folder.
#ifndef REL_EQUAL_HH_INCLUDED_20131017
#define REL_EQUAL_HH_INCLUDED_20131017

#include <cmath>
#include <limits>

namespace gaudy {

    namespace detail {
        constexpr
        bool rel_equal(float lhs, float rhs, float max_rel_diff,
                       float diff, float largest)
        {
            return diff <= largest * max_rel_diff;
        }
    }

    constexpr
    bool rel_equal (float lhs, float rhs,
                    float max_rel_diff=std::numeric_limits<float>::epsilon()
                   ) noexcept
    {
        using std::fabs;
        // http://www.cygnus-software.com/papers/comparingfloats/comparingfloats.htm
        return detail::rel_equal(fabs(lhs), fabs(rhs), max_rel_diff,
                                 fabs(lhs - rhs), (rhs > lhs) ? rhs : lhs
                                );
    }
}

#endif // REL_EQUAL_HH_INCLUDED_20131017

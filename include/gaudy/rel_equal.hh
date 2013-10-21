// (C) 2013 Sebastian Mach (1983), this file is published under the terms of the
// GNU General Public License, Version 3 (a.k.a. GPLv3).
// See COPYING in the root-folder of the excygen project folder.
#ifndef REL_EQUAL_HH_INCLUDED_20131017
#define REL_EQUAL_HH_INCLUDED_20131017

#include <cmath>
#include <limits>
#include <iosfwd>

namespace gaudy {


    namespace detail {
        constexpr
        bool rel_equal_helper(float lhs, float rhs, float max_rel_diff,
                              float diff)
        {
            return diff <= ((rhs > lhs) ? rhs : lhs) * max_rel_diff;
        }
    }

    constexpr
    bool rel_equal (float lhs, float rhs,
                    float max_rel_diff=std::numeric_limits<float>::epsilon()
                   ) noexcept
    {
        using std::fabs;
        // http://www.cygnus-software.com/papers/comparingfloats/comparingfloats.htm
        return detail::rel_equal_helper(fabs(lhs), fabs(rhs), max_rel_diff,
                                        fabs(lhs - rhs)
                                       );
    }

    namespace detail {
        template <typename T>
        struct RelEqualProxy {
            constexpr RelEqualProxy (T const & val, float max_rel_diff)
                : val(val), max_rel_diff(max_rel_diff)
            {}

            friend
            constexpr bool operator== (T const &lhs, RelEqualProxy const &rhs) noexcept
            {
                using gaudy::rel_equal;
                return rel_equal (lhs, rhs.val, rhs.max_rel_diff);
            }

            friend
            constexpr bool operator!= (T const &lhs, RelEqualProxy const &rhs) noexcept
            {
                using gaudy::rel_equal;
                return !(lhs == rhs);
            }

            friend
            std::ostream& operator<< (std::ostream &os, RelEqualProxy const &p)
            {
                return os << p.val;
            }

        private:
            T const &val;
            float max_rel_diff;
        };
    }

    template <typename T>
    constexpr
    detail::RelEqualProxy<T> rel_equal (
        T const & rhs,
        float max_rel_diff=std::numeric_limits<float>::epsilon()
    ) noexcept
    {
        return {rhs, std::numeric_limits<float>::epsilon()};//max_rel_diff};
    }
}

#endif // REL_EQUAL_HH_INCLUDED_20131017

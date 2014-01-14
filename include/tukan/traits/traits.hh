// (C) 2013 Sebastian Mach (1983), this file is published under the terms of the
// GNU General Public License, Version 3 (a.k.a. GPLv3).
// See COPYING in the root-folder of the excygen project folder.
#ifndef TRAITS_HH_INCLUDED_20131121
#define TRAITS_HH_INCLUDED_20131121

#include <utility>

namespace tukan {



    template <typename>
    struct has_apply_interface : std::false_type
    {};


    // The idea of using EnableIf in the template argument list is by R. Martinho Fernandez,
    // (http://flamingdangerzone.com/cxx11/2012/06/01/almost-static-if.html)
    namespace detail {
        enum class enabler {};
    }

    template <typename Cond, typename ...Rest>
    struct all {
        enum { value = Cond::value && all<Rest...>::value };
    };

    template <typename Cond>
    struct all<Cond> {
        enum { value = Cond::value };
    };



    template <typename ...Condition>
    using EnableIf = typename std::enable_if<all<Condition...>::value, detail::enabler>::type;

    template <typename ...Condition>
    using DisableIf = typename std::enable_if<!all<Condition...>::value, detail::enabler>::type;



    namespace detail {
        template <typename To, typename Base>
        struct rebind_value_type;

        template <typename To, template <typename...> class Base, typename V, typename ...R>
        struct rebind_value_type<To, Base<V,R...>> {
            using type = Base<To, R...>;
        };
    }

    template <typename Base, typename NewVType>
    using RebindValueType = typename detail::rebind_value_type<Base, NewVType>::type;

    template <typename T>
    using ValueTypeOf = typename T::value_type;

}

#endif // TRAITS_HH_INCLUDED_20131121

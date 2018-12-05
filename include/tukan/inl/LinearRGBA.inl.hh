// (C) 2013 Sebastian Mach (1983), this file is published under the terms of the
// GNU General Public License, Version 3 (a.k.a. GPLv3).
// See COPYING in the root-folder of the excygen project folder.
#ifndef LINEARRGBA_INL_HH_20181205
#define LINEARRGBA_INL_HH_20181205



// Member functions implementation.
namespace tukan {

    template <typename T, template <typename> class RGBSpace>
    static
    T LinearRGBA<T, RGBSpace>::* const LinearRGBA<T, RGBSpace>::offsets_[4] =
    {
        &LinearRGBA<T, RGBSpace>::r,
        &LinearRGBA<T, RGBSpace>::g,
        &LinearRGBA<T, RGBSpace>::b,
        &LinearRGBA<T, RGBSpace>::a
    };


    template <typename T, template <typename> class RGBSpace>
    inline
    T& LinearRGBA<T, RGBSpace>::operator[] (size_t idx) noexcept
    {
        return this->*offsets_[idx];
    }


    template <typename T, template <typename> class RGBSpace>
    inline constexpr
    T LinearRGBA<T, RGBSpace>::operator[] (size_t idx) const noexcept
    {
        return this->*offsets_[idx];
    }


    template <typename T, template <typename> class RGBSpace>
    inline
    T& LinearRGBA<T, RGBSpace>::at (size_t idx)
    {
        if (idx>=size()) // TODO: check if the negative check is faster.
            throw std::out_of_range("LinearRGBA: out of range access");
        return this->*offsets_[idx];
    }


    template <typename T, template <typename> class RGBSpace>
    inline constexpr
    T LinearRGBA<T, RGBSpace>::at (size_t idx) const
    {
        if (idx>=size()) // TODO: check if the negative check is faster.
            throw std::out_of_range("LinearRGBA: out of range access");
        return this->*offsets_[idx];
    }


    template <typename T, template <typename> class RGBSpace>
    inline constexpr
    size_t LinearRGBA<T, RGBSpace>::size() const noexcept
    {
        return 4;
    }
}



namespace tukan {

    //---------------------------------------------------------------------------------------------
    // implementation
    //---------------------------------------------------------------------------------------------

    // relation
    template <typename T, template <typename> class RGBSpace>
    constexpr bool operator== (LinearRGBA<T, RGBSpace> lhs, LinearRGBA<T, RGBSpace> rhs) noexcept {
        return lhs.r==rhs.r && lhs.g==rhs.g && lhs.b==rhs.b && lhs.a==rhs.a;
    }
    template <typename T, template <typename> class RGBSpace>
    constexpr bool operator!= (LinearRGBA<T, RGBSpace> lhs, LinearRGBA<T, RGBSpace> rhs) noexcept {
        return !(lhs == rhs);
    }
    template <typename T, template <typename> class RGBSpace>
    constexpr bool rel_equal (LinearRGBA<T, RGBSpace> lhs, LinearRGBA<T, RGBSpace> rhs, T max_rel_diff) noexcept
    {
        return rel_equal (lhs.r, rhs.r, max_rel_diff)
            && rel_equal (lhs.g, rhs.g, max_rel_diff)
            && rel_equal (lhs.b, rhs.b, max_rel_diff)
            && rel_equal (lhs.a, rhs.a, max_rel_diff)
        ;
    }


    // arithmetics

    //------------------------------------------------------------------------------------------------------------------
    // Note: There is no single clear definition on how to perform arithmetics on RGBA.
    //
    // The following is a common variant of RGBA+RGBA:
    //
    //   template <typename T, template <typename> class RGBSpace>
    //   constexpr LinearRGBA<T, RGBSpace> operator+ (LinearRGBA<T, RGBSpace> lhs, LinearRGBA<T, RGBSpace> rhs) noexcept
    //   {
    //       return {
    //           lhs.r*lhs.a + rhs.r*rhs.a*(T(1)-lhs.a),
    //           lhs.g*lhs.a + rhs.g*rhs.a*(T(1)-lhs.a),
    //           lhs.b*lhs.a + rhs.b*rhs.a*(T(1)-lhs.a),
    //                 lhs.a +       rhs.a*(T(1)-lhs.a),
    //       };
    //   }
    //
    // TODO: Implement combination operations, but it's probably best to not do so as arithmetics overloads.
    //------------------------------------------------------------------------------------------------------------------

    // algorithms
    template <typename T, template <typename> class RGBSpace>
    inline LinearRGBA<T, RGBSpace> min(LinearRGBA<T, RGBSpace> x, LinearRGBA<T, RGBSpace> y) noexcept {
        using std::min;
        return { min(x.r, y.r),
                 min(x.g, y.g),
                 min(x.b, y.b),
                 min(x.a, y.a), };
    }
    template <typename T, template <typename> class RGBSpace>
    inline LinearRGBA<T, RGBSpace> max(LinearRGBA<T, RGBSpace> x, LinearRGBA<T, RGBSpace> y) noexcept {
        using std::max;
        return { max(x.r, y.r),
                 max(x.g, y.g),
                 max(x.b, y.b),
                 max(x.a, y.a), };
    }

    template <typename T, template <typename> class RGBSpace>
    inline LinearRGBA<T, RGBSpace> min(LinearRGBA<T, RGBSpace> x, typename LinearRGBA<T, RGBSpace>::value_type y) noexcept {
        using std::min;
        return { min(x.r, y),
                 min(x.g, y),
                 min(x.b, y),
                 min(x.a, y), };
    }
    template <typename T, template <typename> class RGBSpace>
    inline LinearRGBA<T, RGBSpace> max(LinearRGBA<T, RGBSpace> x, typename LinearRGBA<T, RGBSpace>::value_type y) noexcept {
        using std::max;
        return { max(x.r, y),
                 max(x.g, y),
                 max(x.b, y),
                 max(x.a, y), };
    }

    template <typename T, template <typename> class RGBSpace>
    inline LinearRGBA<T, RGBSpace> min(typename LinearRGBA<T, RGBSpace>::value_type x, LinearRGBA<T, RGBSpace> y) noexcept {
        using std::min;
        return { min(x, y.r),
                 min(x, y.g),
                 min(x, y.b),
                 min(x, y.a), };
    }
    template <typename T, template <typename> class RGBSpace>
    inline LinearRGBA<T, RGBSpace> max(typename LinearRGBA<T, RGBSpace>::value_type x, LinearRGBA<T, RGBSpace> y) noexcept {
        using std::max;
        return { max(x, y.r),
                 max(x, y.g),
                 max(x, y.b),
                 max(x, y.a), };
    }
}



// "apply"-concept implementation.
namespace tukan {
    namespace detail {
        // We have to overload the rebind_value_type-template because the general version does not
        // like template template arguments.
        template <typename To, typename From, template <typename> class RGBSpace>
        struct rebind_value_type<To, LinearRGBA<From, RGBSpace>> {
            using type = LinearRGBA<To, RGBSpace>;
        };
    }

    template <typename T, template <typename> class RGBSpace>
    struct has_apply_interface<LinearRGBA<T, RGBSpace>> : std::true_type
    {};

    // Unary
    template <typename T, template <typename> class RGBSpace, typename Fun>
    constexpr auto apply (LinearRGBA<T, RGBSpace> operand, Fun fun)
      -> LinearRGBA<decltype (fun(operand.r)), RGBSpace>
    {
        return {fun(operand.r),
                fun(operand.g),
                fun(operand.b),
                fun(operand.a),};
    }

    // Binary
    template <typename T, typename U, template <typename> class RGBSpace, typename Fun>
    constexpr auto apply (
            LinearRGBA<T, RGBSpace> lhs,
            LinearRGBA<U, RGBSpace> rhs,
            Fun fun
    ) -> LinearRGBA<decltype (fun(lhs.r, rhs.r)), RGBSpace>
    {
        return {fun(lhs.r, rhs.r),
                fun(lhs.g, rhs.g),
                fun(lhs.b, rhs.b),
                fun(lhs.a, rhs.a),};
    }

    template <typename T, typename U, template <typename> class RGBSpace, typename Fun>
    constexpr auto apply (LinearRGBA<T, RGBSpace> lhs, U rhs, Fun fun)
      -> LinearRGBA<decltype (fun(lhs.r, rhs)), RGBSpace>
    {
        return {fun(lhs.r, rhs),
                fun(lhs.g, rhs),
                fun(lhs.b, rhs),
                fun(lhs.a, rhs),};
    }

    template <typename T, typename U, template <typename> class RGBSpace, typename Fun>
    constexpr auto apply (T lhs, LinearRGBA<U, RGBSpace> rhs, Fun fun)
      -> LinearRGBA<decltype (fun(lhs, rhs.r)), RGBSpace>
    {
        return {fun(lhs, rhs.r),
                fun(lhs, rhs.g),
                fun(lhs, rhs.b),
                fun(lhs, rhs.a),};
    }


    template <typename T, typename U, template <typename> class RGBSpace, typename Fun>
    constexpr auto apply (LinearRGBA<T, RGBSpace> lhs, LinearRGBA<U, RGBSpace> *rhs, Fun fun)
      -> LinearRGBA<decltype (fun(lhs.r, &rhs->r)), RGBSpace>
    {
        return {fun(lhs.r, &rhs->r),
                fun(lhs.g, &rhs->g),
                fun(lhs.b, &rhs->b),
                fun(lhs.a, &rhs->a),};
    }

    template <typename T, typename U, template <typename> class RGBSpace, typename Fun>
    constexpr auto apply (T lhs, LinearRGBA<U, RGBSpace> *rhs, Fun fun)
      -> LinearRGBA<decltype (fun(lhs, &rhs->r)), RGBSpace>
    {
        return {fun(lhs, &rhs->r),
                fun(lhs, &rhs->g),
                fun(lhs, &rhs->b),
                fun(lhs, &rhs->a),};
    }


    // Ternary
    template <typename T, typename U, typename V, template <typename> class RGBSpace, typename Fun>
    constexpr auto apply (LinearRGBA<T, RGBSpace> a, LinearRGBA<U, RGBSpace> b, LinearRGBA<V, RGBSpace> c, Fun fun)
      -> LinearRGBA<decltype (fun(a.r, b.r, c.r)), RGBSpace>
    {
        return {fun(a.r, b.r, c.r),
                fun(a.g, b.g, c.g),
                fun(a.b, b.b, c.b),
                fun(a.a, b.a, c.a),};
    }

    template <typename T, typename U, typename V, template <typename> class RGBSpace, typename Fun>
    constexpr auto apply (LinearRGBA<T, RGBSpace> a, LinearRGBA<U, RGBSpace> b, V c, Fun fun)
      -> LinearRGBA<decltype (fun(a.r, b.r, c)), RGBSpace>
    {
        return {fun(a.r, b.r, c),
                fun(a.g, b.g, c),
                fun(a.b, b.b, c),
                fun(a.a, b.a, c),};
    }

    template <typename T, typename U, typename V, template <typename> class RGBSpace, typename Fun>
    constexpr auto apply (LinearRGBA<T, RGBSpace> a, U b, LinearRGBA<V, RGBSpace> c, Fun fun)
      -> LinearRGBA<decltype (fun(a.r, b, c.r)), RGBSpace>
    {
        return {fun(a.r, b, c.r),
                fun(a.g, b, c.g),
                fun(a.b, b, c.b),
                fun(a.a, b, c.a),};
    }

    template <typename T, typename U, typename V, template <typename> class RGBSpace, typename Fun>
    constexpr auto apply (LinearRGBA<T, RGBSpace> a, U b, V c, Fun fun)
      -> LinearRGBA<decltype (fun(a.r, b, c)), RGBSpace>
    {
        return {fun(a.r, b, c),
                fun(a.g, b, c),
                fun(a.b, b, c),
                fun(a.a, b, c),};
    }

    template <typename T, typename U, typename V, template <typename> class RGBSpace, typename Fun>
    constexpr auto apply (T a, LinearRGBA<U, RGBSpace> b, LinearRGBA<V, RGBSpace> c, Fun fun)
      -> LinearRGBA<decltype (fun(a, b.r, c.r)), RGBSpace>
    {
        return {fun(a, b.r, c.r),
                fun(a, b.g, c.g),
                fun(a, b.b, c.b),
                fun(a, b.a, c.a),};
    }

    template <typename T, typename U, typename V, template <typename> class RGBSpace, typename Fun>
    constexpr auto apply (T a, LinearRGBA<U, RGBSpace> b, V c, Fun fun)
      -> LinearRGBA<decltype (fun(a, b.r, c)), RGBSpace>
    {
        return {fun(a, b.r, c),
                fun(a, b.g, c),
                fun(a, b.b, c),
                fun(a, b.a, c),};
    }

    template <typename T, typename U, typename V, template <typename> class RGBSpace, typename Fun>
    constexpr auto apply (T a, U b, LinearRGBA<V, RGBSpace> c, Fun fun)
      -> LinearRGBA<decltype (fun(a, b, c.r)), RGBSpace>
    {
        return {fun(a, b, c.r),
                fun(a, b, c.g),
                fun(a, b, c.b),
                fun(a, b, c.a),};
    }

    template <typename T, typename U, typename V, template <typename> class RGBSpace, typename Fun>
    constexpr auto apply (LinearRGBA<T, RGBSpace> a, LinearRGBA<U, RGBSpace> b, LinearRGBA<V, RGBSpace> *c, Fun fun)
      -> LinearRGBA<decltype (fun(a.r, b.r, &c->r)), RGBSpace>
    {
        return {fun(a.r, b.r, &c->r),
                fun(a.g, b.g, &c->g),
                fun(a.b, b.b, &c->b),
                fun(a.a, b.a, &c->a),};
    }

    template <typename T, typename U, typename V, template <typename> class RGBSpace, typename Fun>
    constexpr auto apply (LinearRGBA<T, RGBSpace> a, U b, LinearRGBA<V, RGBSpace> *c, Fun fun)
      -> LinearRGBA<decltype (fun(a.r, b, &c->r)), RGBSpace>
    {
        return {fun(a.r, b, &c->r),
                fun(a.g, b, &c->g),
                fun(a.b, b, &c->b),
                fun(a.a, b, &c->a),};
    }

    template <typename T, typename U, typename V, template <typename> class RGBSpace, typename Fun>
    constexpr auto apply (T a, LinearRGBA<U, RGBSpace> b, LinearRGBA<V, RGBSpace> *c, Fun fun)
      -> LinearRGBA<decltype (fun(a, b.r, &c->r)), RGBSpace>
    {
        return {fun(a, b.r, &c->r),
                fun(a, b.g, &c->g),
                fun(a, b.b, &c->b),
                fun(a, b.a, &c->a),};
    }

    //Implementation notes:
    // Some operator overloads use LinearRGBA<T, RGBSpace>::value_type instead of just plain T. This is because
    // with plain T, the operators are deduced on both the lhs AND rhs, leading to ambiguities when
    // using e.g. 'LinearRGBA<float> foo; foo += 1;', where there is an int added to a float-RGB.
    // Using LinearRGBA::value_type prevents type deduction on the scalar argument.
}

#endif // LINEARRGBA_INL_HH_20181205

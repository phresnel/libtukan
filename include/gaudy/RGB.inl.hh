// (C) 2013 Sebastian Mach (1983), this file is published under the terms of the
// GNU General Public License, Version 3 (a.k.a. GPLv3).
// See COPYING in the root-folder of the excygen project folder.
#ifndef RGB_INL_HH_20131122
#define RGB_INL_HH_20131122



// Member functions implementation.
namespace gaudy {

    template <typename T, template <typename> class RGBSpace>
    T basic_rgb<T, RGBSpace>::* const basic_rgb<T, RGBSpace>::offsets_[3] =
    {
        &basic_rgb<T, RGBSpace>::r,
        &basic_rgb<T, RGBSpace>::g,
        &basic_rgb<T, RGBSpace>::b
    };


    template <typename T, template <typename> class RGBSpace>
    inline
    T& basic_rgb<T, RGBSpace>::operator[] (size_t idx) noexcept
    {
        return this->*offsets_[idx];
    }


    template <typename T, template <typename> class RGBSpace>
    inline constexpr
    T basic_rgb<T, RGBSpace>::operator[] (size_t idx) const noexcept
    {
        return this->*offsets_[idx];
    }


    template <typename T, template <typename> class RGBSpace>
    inline
    T& basic_rgb<T, RGBSpace>::at (size_t idx)
    {
        if (idx>=size()) // TODO: check if the negative check is faster.
            throw std::out_of_range("basic_rgb: out of range access");
        return this->*offsets_[idx];
    }


    template <typename T, template <typename> class RGBSpace>
    inline constexpr
    T basic_rgb<T, RGBSpace>::at (size_t idx) const
    {
        if (idx>=size()) // TODO: check if the negative check is faster.
            throw std::out_of_range("basic_rgb: out of range access");
        return this->*offsets_[idx];
    }


    template <typename T, template <typename> class RGBSpace>
    inline constexpr
    size_t basic_rgb<T, RGBSpace>::size() const noexcept
    {
        return 3;
    }
}



namespace gaudy {

    //---------------------------------------------------------------------------------------------
    // implementation
    //---------------------------------------------------------------------------------------------
    template <typename T, template <typename> class RGBSpace>
    inline basic_rgb<T, RGBSpace>& basic_rgb<T, RGBSpace>::operator+= (basic_rgb<T, RGBSpace> rhs) noexcept {
        r += rhs.r;
        g += rhs.g;
        b += rhs.b;
        return *this;
    }

    template <typename T, template <typename> class RGBSpace>
    inline basic_rgb<T, RGBSpace>& basic_rgb<T, RGBSpace>::operator-= (basic_rgb<T, RGBSpace> rhs) noexcept {
        r -= rhs.r;
        g -= rhs.g;
        b -= rhs.b;
        return *this;
    }

    template <typename T, template <typename> class RGBSpace>
    inline basic_rgb<T, RGBSpace>& basic_rgb<T, RGBSpace>::operator*= (basic_rgb<T, RGBSpace> rhs) noexcept {
        r *= rhs.r;
        g *= rhs.g;
        b *= rhs.b;
        return *this;
    }

    template <typename T, template <typename> class RGBSpace>
    inline basic_rgb<T, RGBSpace>& basic_rgb<T, RGBSpace>::operator/= (basic_rgb<T, RGBSpace> rhs) noexcept {
        r /= rhs.r;
        g /= rhs.g;
        b /= rhs.b;
        return *this;
    }

    template <typename T, template <typename> class RGBSpace>
    inline basic_rgb<T, RGBSpace>& basic_rgb<T, RGBSpace>::operator+= (T rhs) noexcept {
        r += rhs;
        g += rhs;
        b += rhs;
        return *this;
    }

    template <typename T, template <typename> class RGBSpace>
    inline basic_rgb<T, RGBSpace>& basic_rgb<T, RGBSpace>::operator-= (T rhs) noexcept {
        r -= rhs;
        g -= rhs;
        b -= rhs;
        return *this;
    }

    template <typename T, template <typename> class RGBSpace>
    inline basic_rgb<T, RGBSpace>& basic_rgb<T, RGBSpace>::operator*= (T rhs) noexcept {
        r *= rhs;
        g *= rhs;
        b *= rhs;
        return *this;
    }

    template <typename T, template <typename> class RGBSpace>
    inline basic_rgb<T, RGBSpace>& basic_rgb<T, RGBSpace>::operator/= (T rhs) noexcept {
        r /= rhs;
        g /= rhs;
        b /= rhs;
        return *this;
    }


    // relation
    template <typename T, template <typename> class RGBSpace>
    constexpr bool operator== (basic_rgb<T, RGBSpace> lhs, basic_rgb<T, RGBSpace> rhs) noexcept {
        return lhs.r==rhs.r && lhs.g==rhs.g && lhs.b==rhs.b;
    }
    template <typename T, template <typename> class RGBSpace>
    constexpr bool operator!= (basic_rgb<T, RGBSpace> lhs, basic_rgb<T, RGBSpace> rhs) noexcept {
        return !(lhs == rhs);
    }
    template <typename T, template <typename> class RGBSpace>
    constexpr bool rel_equal (basic_rgb<T, RGBSpace> lhs, basic_rgb<T, RGBSpace> rhs, T max_rel_diff) noexcept
    {
        return rel_equal (lhs.r, rhs.r, max_rel_diff)
            && rel_equal (lhs.g, rhs.g, max_rel_diff)
            && rel_equal (lhs.b, rhs.b, max_rel_diff)
        ;
    }


    // arithmetics
    template <typename T, template <typename> class RGBSpace>
    constexpr basic_rgb<T, RGBSpace> operator+ (basic_rgb<T, RGBSpace> lhs, basic_rgb<T, RGBSpace> rhs) noexcept {
        return {lhs.r+rhs.r, lhs.g+rhs.g, lhs.b+rhs.b};
    }
    template <typename T, template <typename> class RGBSpace>
    constexpr basic_rgb<T, RGBSpace> operator- (basic_rgb<T, RGBSpace> lhs, basic_rgb<T, RGBSpace> rhs) noexcept {
        return {lhs.r-rhs.r, lhs.g-rhs.g, lhs.b-rhs.b};
    }
    template <typename T, template <typename> class RGBSpace>
    constexpr basic_rgb<T, RGBSpace> operator* (basic_rgb<T, RGBSpace> lhs, basic_rgb<T, RGBSpace> rhs) noexcept {
        return {lhs.r*rhs.r, lhs.g*rhs.g, lhs.b*rhs.b};
    }
    template <typename T, template <typename> class RGBSpace>
    constexpr basic_rgb<T, RGBSpace> operator/ (basic_rgb<T, RGBSpace> lhs, basic_rgb<T, RGBSpace> rhs) noexcept {
        return {lhs.r/rhs.r, lhs.g/rhs.g, lhs.b/rhs.b};
    }

    template <typename T, template <typename> class RGBSpace>
    constexpr basic_rgb<T, RGBSpace> operator+ (basic_rgb<T, RGBSpace> lhs, typename basic_rgb<T, RGBSpace>::value_type rhs) noexcept {
        return {lhs.r+rhs, lhs.g+rhs, lhs.b+rhs};
    }
    template <typename T, template <typename> class RGBSpace>
    constexpr basic_rgb<T, RGBSpace> operator- (basic_rgb<T, RGBSpace> lhs, typename basic_rgb<T, RGBSpace>::value_type rhs) noexcept {
        return {lhs.r-rhs, lhs.g-rhs, lhs.b-rhs};
    }
    template <typename T, template <typename> class RGBSpace>
    constexpr basic_rgb<T, RGBSpace> operator* (basic_rgb<T, RGBSpace> lhs, typename basic_rgb<T, RGBSpace>::value_type rhs) noexcept {
        return {lhs.r*rhs, lhs.g*rhs, lhs.b*rhs};
    }
    template <typename T, template <typename> class RGBSpace>
    constexpr basic_rgb<T, RGBSpace> operator/ (basic_rgb<T, RGBSpace> lhs, typename basic_rgb<T, RGBSpace>::value_type rhs) noexcept {
        return {lhs.r/rhs, lhs.g/rhs, lhs.b/rhs};
    }

    template <typename T, template <typename> class RGBSpace>
    constexpr basic_rgb<T, RGBSpace> operator+ (typename basic_rgb<T, RGBSpace>::value_type lhs, basic_rgb<T, RGBSpace> rhs) noexcept {
        return {lhs+rhs.r, lhs+rhs.g, lhs+rhs.b};
    }
    template <typename T, template <typename> class RGBSpace>
    constexpr basic_rgb<T, RGBSpace> operator- (typename basic_rgb<T, RGBSpace>::value_type lhs, basic_rgb<T, RGBSpace> rhs) noexcept {
        return {lhs-rhs.r, lhs-rhs.g, lhs-rhs.b};
    }
    template <typename T, template <typename> class RGBSpace>
    constexpr basic_rgb<T, RGBSpace> operator* (typename basic_rgb<T, RGBSpace>::value_type lhs, basic_rgb<T, RGBSpace> rhs) noexcept {
        return {lhs*rhs.r, lhs*rhs.g, lhs*rhs.b};
    }
    template <typename T, template <typename> class RGBSpace>
    constexpr basic_rgb<T, RGBSpace> operator/ (typename basic_rgb<T, RGBSpace>::value_type lhs, basic_rgb<T, RGBSpace> rhs) noexcept {
        return {lhs/rhs.r, lhs/rhs.g, lhs/rhs.b};
    }


    // algorithms
    template <typename T, template <typename> class RGBSpace>
    inline basic_rgb<T, RGBSpace> min(basic_rgb<T, RGBSpace> x, basic_rgb<T, RGBSpace> y) noexcept {
        using std::min;
        return { min(x.r, y.r),
                 min(x.g, y.g),
                 min(x.b, y.b) };
    }
    template <typename T, template <typename> class RGBSpace>
    inline basic_rgb<T, RGBSpace> max(basic_rgb<T, RGBSpace> x, basic_rgb<T, RGBSpace> y) noexcept {
        using std::max;
        return { max(x.r, y.r),
                 max(x.g, y.g),
                 max(x.b, y.b) };
    }

    template <typename T, template <typename> class RGBSpace>
    inline basic_rgb<T, RGBSpace> min(basic_rgb<T, RGBSpace> x, typename basic_rgb<T, RGBSpace>::value_type y) noexcept {
        using std::min;
        return { min(x.r, y),
                 min(x.g, y),
                 min(x.b, y) };
    }
    template <typename T, template <typename> class RGBSpace>
    inline basic_rgb<T, RGBSpace> max(basic_rgb<T, RGBSpace> x, typename basic_rgb<T, RGBSpace>::value_type y) noexcept {
        using std::max;
        return { max(x.r, y),
                 max(x.g, y),
                 max(x.b, y) };
    }

    template <typename T, template <typename> class RGBSpace>
    inline basic_rgb<T, RGBSpace> min(typename basic_rgb<T, RGBSpace>::value_type x, basic_rgb<T, RGBSpace> y) noexcept {
        using std::min;
        return { min(x, y.r),
                 min(x, y.g),
                 min(x, y.b) };
    }
    template <typename T, template <typename> class RGBSpace>
    inline basic_rgb<T, RGBSpace> max(typename basic_rgb<T, RGBSpace>::value_type x, basic_rgb<T, RGBSpace> y) noexcept {
        using std::max;
        return { max(x, y.r),
                 max(x, y.g),
                 max(x, y.b) };
    }
}



// "apply"-concept implementation.
namespace gaudy {
    namespace detail {
        // We have to overload the rebind_value_type-template because the general version does not
        // like template template arguments.
        template <typename To, typename From, template <typename> class RGBSpace>
        struct rebind_value_type<To, basic_rgb<From, RGBSpace>> {
            using type = basic_rgb<To, RGBSpace>;
        };
    }

    template <typename T, template <typename> class RGBSpace>
    struct has_apply_interface<basic_rgb<T, RGBSpace>> : std::true_type
    {};

    // Unary
    template <typename T, template <typename> class RGBSpace, typename Fun>
    constexpr auto apply (basic_rgb<T, RGBSpace> operand, Fun fun)
      -> basic_rgb<decltype (fun(operand.r)), RGBSpace>
    {
        return {fun(operand.r), fun(operand.g), fun(operand.b)};
    }

    // Binary
    template <typename T, typename U, template <typename> class RGBSpace, typename Fun>
    constexpr auto apply (basic_rgb<T, RGBSpace> lhs, basic_rgb<U, RGBSpace> rhs, Fun fun)
      -> basic_rgb<decltype (fun(lhs.r, rhs.r)), RGBSpace>
    {
        return {fun(lhs.r, rhs.r), fun(lhs.g, rhs.g), fun(lhs.b, rhs.b)};
    }

    template <typename T, typename U, template <typename> class RGBSpace, typename Fun>
    constexpr auto apply (basic_rgb<T, RGBSpace> lhs, U rhs, Fun fun)
      -> basic_rgb<decltype (fun(lhs.r, rhs)), RGBSpace>
    {
        return {fun(lhs.r, rhs), fun(lhs.g, rhs), fun(lhs.b, rhs)};
    }

    template <typename T, typename U, template <typename> class RGBSpace, typename Fun>
    constexpr auto apply (T lhs, basic_rgb<U, RGBSpace> rhs, Fun fun)
      -> basic_rgb<decltype (fun(lhs, rhs.r)), RGBSpace>
    {
        return {fun(lhs, rhs.r), fun(lhs, rhs.g), fun(lhs, rhs.b)};
    }


    template <typename T, typename U, template <typename> class RGBSpace, typename Fun>
    constexpr auto apply (basic_rgb<T, RGBSpace> lhs, basic_rgb<U, RGBSpace> *rhs, Fun fun)
      -> basic_rgb<decltype (fun(lhs.r, &rhs->r)), RGBSpace>
    {
        return {fun(lhs.r, &rhs->r), fun(lhs.g, &rhs->g), fun(lhs.b, &rhs->b)};
    }

    template <typename T, typename U, template <typename> class RGBSpace, typename Fun>
    constexpr auto apply (T lhs, basic_rgb<U, RGBSpace> *rhs, Fun fun)
      -> basic_rgb<decltype (fun(lhs, &rhs->r)), RGBSpace>
    {
        return {fun(lhs, &rhs->r), fun(lhs, &rhs->g), fun(lhs, &rhs->b)};
    }


    // Ternary
    template <typename T, typename U, typename V, template <typename> class RGBSpace, typename Fun>
    constexpr auto apply (basic_rgb<T, RGBSpace> a, basic_rgb<U, RGBSpace> b, basic_rgb<V, RGBSpace> c, Fun fun)
      -> basic_rgb<decltype (fun(a.r, b.r, c.r)), RGBSpace>
    {
        return {fun(a.r, b.r, c.r), fun(a.g, b.g, c.g), fun(a.b, b.b, c.b)};
    }

    template <typename T, typename U, typename V, template <typename> class RGBSpace, typename Fun>
    constexpr auto apply (basic_rgb<T, RGBSpace> a, basic_rgb<U, RGBSpace> b, V c, Fun fun)
      -> basic_rgb<decltype (fun(a.r, b.r, c)), RGBSpace>
    {
        return {fun(a.r, b.r, c), fun(a.g, b.g, c), fun(a.b, b.b, c)};
    }

    template <typename T, typename U, typename V, template <typename> class RGBSpace, typename Fun>
    constexpr auto apply (basic_rgb<T, RGBSpace> a, U b, basic_rgb<V, RGBSpace> c, Fun fun)
      -> basic_rgb<decltype (fun(a.r, b, c.r)), RGBSpace>
    {
        return {fun(a.r, b, c.r), fun(a.g, b, c.g), fun(a.b, b, c.b)};
    }

    template <typename T, typename U, typename V, template <typename> class RGBSpace, typename Fun>
    constexpr auto apply (basic_rgb<T, RGBSpace> a, U b, V c, Fun fun)
      -> basic_rgb<decltype (fun(a.r, b, c)), RGBSpace>
    {
        return {fun(a.r, b, c), fun(a.g, b, c), fun(a.b, b, c)};
    }

    template <typename T, typename U, typename V, template <typename> class RGBSpace, typename Fun>
    constexpr auto apply (T a, basic_rgb<U, RGBSpace> b, basic_rgb<V, RGBSpace> c, Fun fun)
      -> basic_rgb<decltype (fun(a, b.r, c.r)), RGBSpace>
    {
        return {fun(a, b.r, c.r), fun(a, b.g, c.g), fun(a, b.b, c.b)};
    }

    template <typename T, typename U, typename V, template <typename> class RGBSpace, typename Fun>
    constexpr auto apply (T a, basic_rgb<U, RGBSpace> b, V c, Fun fun)
      -> basic_rgb<decltype (fun(a, b.r, c)), RGBSpace>
    {
        return {fun(a, b.r, c), fun(a, b.g, c), fun(a, b.b, c)};
    }

    template <typename T, typename U, typename V, template <typename> class RGBSpace, typename Fun>
    constexpr auto apply (T a, U b, basic_rgb<V, RGBSpace> c, Fun fun)
      -> basic_rgb<decltype (fun(a, b, c.r)), RGBSpace>
    {
        return {fun(a, b, c.r), fun(a, b, c.g), fun(a, b, c.b)};
    }

    template <typename T, typename U, typename V, template <typename> class RGBSpace, typename Fun>
    constexpr auto apply (basic_rgb<T, RGBSpace> a, basic_rgb<U, RGBSpace> b, basic_rgb<V, RGBSpace> *c, Fun fun)
      -> basic_rgb<decltype (fun(a.r, b.r, &c->r)), RGBSpace>
    {
        return {fun(a.r, b.r, &c->r), fun(a.g, b.g, &c->g), fun(a.b, b.b, &c->b)};
    }

    template <typename T, typename U, typename V, template <typename> class RGBSpace, typename Fun>
    constexpr auto apply (basic_rgb<T, RGBSpace> a, U b, basic_rgb<V, RGBSpace> *c, Fun fun)
      -> basic_rgb<decltype (fun(a.r, b, &c->r)), RGBSpace>
    {
        return {fun(a.r, b, &c->r), fun(a.g, b, &c->g), fun(a.b, b, &c->b)};
    }

    template <typename T, typename U, typename V, template <typename> class RGBSpace, typename Fun>
    constexpr auto apply (T a, basic_rgb<U, RGBSpace> b, basic_rgb<V, RGBSpace> *c, Fun fun)
      -> basic_rgb<decltype (fun(a, b.r, &c->r)), RGBSpace>
    {
        return {fun(a, b.r, &c->r), fun(a, b.g, &c->g), fun(a, b.b, &c->b)};
    }

    //Implementation notes:
    // Some operator overloads use basic_rgb<T, RGBSpace>::value_type instead of just plain T. This is because
    // with plain T, the operators are deduced on both the lhs AND rhs, leading to ambiguities when
    // using e.g. 'basic_rgb<float> foo; foo += 1;', where there is an int added to a float-RGB.
    // Using basic_rgb::value_type prevents type deduction on the scalar argument.
}

#endif // RGB_INL_HH_20131122

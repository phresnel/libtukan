// (C) 2013 Sebastian Mach (1983), this file is published under the terms of the
// GNU General Public License, Version 3 (a.k.a. GPLv3).
// See COPYING in the root-folder of the excygen project folder.
#ifndef LINEARRGB_INL_HH_20131122
#define LINEARRGB_INL_HH_20131122



// Member functions implementation.
namespace tukan {

    template <typename T, template <typename> class RGBSpace>
    T LinearRGB<T, RGBSpace>::* const LinearRGB<T, RGBSpace>::offsets_[3] =
    {
        &LinearRGB<T, RGBSpace>::r,
        &LinearRGB<T, RGBSpace>::g,
        &LinearRGB<T, RGBSpace>::b
    };


    template <typename T, template <typename> class RGBSpace>
    inline
    T& LinearRGB<T, RGBSpace>::operator[] (size_t idx) noexcept
    {
        return this->*offsets_[idx];
    }


    template <typename T, template <typename> class RGBSpace>
    inline constexpr
    T LinearRGB<T, RGBSpace>::operator[] (size_t idx) const noexcept
    {
        return this->*offsets_[idx];
    }


    template <typename T, template <typename> class RGBSpace>
    inline
    T& LinearRGB<T, RGBSpace>::at (size_t idx)
    {
        if (idx>=size()) // TODO: check if the negative check is faster.
            throw std::out_of_range("LinearRGB: out of range access");
        return this->*offsets_[idx];
    }


    template <typename T, template <typename> class RGBSpace>
    inline constexpr
    T LinearRGB<T, RGBSpace>::at (size_t idx) const
    {
        if (idx>=size()) // TODO: check if the negative check is faster.
            throw std::out_of_range("LinearRGB: out of range access");
        return this->*offsets_[idx];
    }


    template <typename T, template <typename> class RGBSpace>
    inline constexpr
    size_t LinearRGB<T, RGBSpace>::size() const noexcept
    {
        return 3;
    }


    template <typename T, template <typename> class RGBSpace>
    constexpr LinearRGB<T, RGBSpace>::operator XYZ<T> () noexcept
    {
        return {
            r*RGBSpace<T>().rgb_to_xyz._11 + g*RGBSpace<T>().rgb_to_xyz._12 + b*RGBSpace<T>().rgb_to_xyz._13,
            r*RGBSpace<T>().rgb_to_xyz._21 + g*RGBSpace<T>().rgb_to_xyz._22 + b*RGBSpace<T>().rgb_to_xyz._23,
            r*RGBSpace<T>().rgb_to_xyz._31 + g*RGBSpace<T>().rgb_to_xyz._32 + b*RGBSpace<T>().rgb_to_xyz._33
        };
    }


    template <typename T, template <typename> class RGBSpace>
    constexpr LinearRGB<T, RGBSpace>::LinearRGB (XYZ<T> xyz) noexcept
        : r(xyz.X*RGBSpace<T>().xyz_to_rgb._11 + xyz.Y*RGBSpace<T>().xyz_to_rgb._12 + xyz.Z*RGBSpace<T>().xyz_to_rgb._13)
        , g(xyz.X*RGBSpace<T>().xyz_to_rgb._21 + xyz.Y*RGBSpace<T>().xyz_to_rgb._22 + xyz.Z*RGBSpace<T>().xyz_to_rgb._23)
        , b(xyz.X*RGBSpace<T>().xyz_to_rgb._31 + xyz.Y*RGBSpace<T>().xyz_to_rgb._32 + xyz.Z*RGBSpace<T>().xyz_to_rgb._33)
    {
    }
}



namespace tukan {

    //---------------------------------------------------------------------------------------------
    // implementation
    //---------------------------------------------------------------------------------------------
    template <typename T, template <typename> class RGBSpace>
    inline LinearRGB<T, RGBSpace>& LinearRGB<T, RGBSpace>::operator+= (LinearRGB<T, RGBSpace> rhs) noexcept {
        r += rhs.r;
        g += rhs.g;
        b += rhs.b;
        return *this;
    }

    template <typename T, template <typename> class RGBSpace>
    inline LinearRGB<T, RGBSpace>& LinearRGB<T, RGBSpace>::operator-= (LinearRGB<T, RGBSpace> rhs) noexcept {
        r -= rhs.r;
        g -= rhs.g;
        b -= rhs.b;
        return *this;
    }

    template <typename T, template <typename> class RGBSpace>
    inline LinearRGB<T, RGBSpace>& LinearRGB<T, RGBSpace>::operator*= (LinearRGB<T, RGBSpace> rhs) noexcept {
        r *= rhs.r;
        g *= rhs.g;
        b *= rhs.b;
        return *this;
    }

    template <typename T, template <typename> class RGBSpace>
    inline LinearRGB<T, RGBSpace>& LinearRGB<T, RGBSpace>::operator/= (LinearRGB<T, RGBSpace> rhs) noexcept {
        r /= rhs.r;
        g /= rhs.g;
        b /= rhs.b;
        return *this;
    }

    template <typename T, template <typename> class RGBSpace>
    inline LinearRGB<T, RGBSpace>& LinearRGB<T, RGBSpace>::operator+= (T rhs) noexcept {
        r += rhs;
        g += rhs;
        b += rhs;
        return *this;
    }

    template <typename T, template <typename> class RGBSpace>
    inline LinearRGB<T, RGBSpace>& LinearRGB<T, RGBSpace>::operator-= (T rhs) noexcept {
        r -= rhs;
        g -= rhs;
        b -= rhs;
        return *this;
    }

    template <typename T, template <typename> class RGBSpace>
    inline LinearRGB<T, RGBSpace>& LinearRGB<T, RGBSpace>::operator*= (T rhs) noexcept {
        r *= rhs;
        g *= rhs;
        b *= rhs;
        return *this;
    }

    template <typename T, template <typename> class RGBSpace>
    inline LinearRGB<T, RGBSpace>& LinearRGB<T, RGBSpace>::operator/= (T rhs) noexcept {
        r /= rhs;
        g /= rhs;
        b /= rhs;
        return *this;
    }


    // relation
    template <typename T, template <typename> class RGBSpace>
    constexpr bool operator== (LinearRGB<T, RGBSpace> lhs, LinearRGB<T, RGBSpace> rhs) noexcept {
        return lhs.r==rhs.r && lhs.g==rhs.g && lhs.b==rhs.b;
    }
    template <typename T, template <typename> class RGBSpace>
    constexpr bool operator!= (LinearRGB<T, RGBSpace> lhs, LinearRGB<T, RGBSpace> rhs) noexcept {
        return !(lhs == rhs);
    }
    template <typename T, template <typename> class RGBSpace>
    constexpr bool rel_equal (LinearRGB<T, RGBSpace> lhs, LinearRGB<T, RGBSpace> rhs, T max_rel_diff) noexcept
    {
        return rel_equal (lhs.r, rhs.r, max_rel_diff)
            && rel_equal (lhs.g, rhs.g, max_rel_diff)
            && rel_equal (lhs.b, rhs.b, max_rel_diff)
        ;
    }


    // arithmetics
    template <typename T, template <typename> class RGBSpace>
    constexpr LinearRGB<T, RGBSpace> operator+ (LinearRGB<T, RGBSpace> lhs, LinearRGB<T, RGBSpace> rhs) noexcept {
        return {lhs.r+rhs.r, lhs.g+rhs.g, lhs.b+rhs.b};
    }
    template <typename T, template <typename> class RGBSpace>
    constexpr LinearRGB<T, RGBSpace> operator- (LinearRGB<T, RGBSpace> lhs, LinearRGB<T, RGBSpace> rhs) noexcept {
        return {lhs.r-rhs.r, lhs.g-rhs.g, lhs.b-rhs.b};
    }
    template <typename T, template <typename> class RGBSpace>
    constexpr LinearRGB<T, RGBSpace> operator* (LinearRGB<T, RGBSpace> lhs, LinearRGB<T, RGBSpace> rhs) noexcept {
        return {lhs.r*rhs.r, lhs.g*rhs.g, lhs.b*rhs.b};
    }
    template <typename T, template <typename> class RGBSpace>
    constexpr LinearRGB<T, RGBSpace> operator/ (LinearRGB<T, RGBSpace> lhs, LinearRGB<T, RGBSpace> rhs) noexcept {
        return {lhs.r/rhs.r, lhs.g/rhs.g, lhs.b/rhs.b};
    }

    template <typename T, template <typename> class RGBSpace>
    constexpr LinearRGB<T, RGBSpace> operator+ (LinearRGB<T, RGBSpace> lhs, typename LinearRGB<T, RGBSpace>::value_type rhs) noexcept {
        return {lhs.r+rhs, lhs.g+rhs, lhs.b+rhs};
    }
    template <typename T, template <typename> class RGBSpace>
    constexpr LinearRGB<T, RGBSpace> operator- (LinearRGB<T, RGBSpace> lhs, typename LinearRGB<T, RGBSpace>::value_type rhs) noexcept {
        return {lhs.r-rhs, lhs.g-rhs, lhs.b-rhs};
    }
    template <typename T, template <typename> class RGBSpace>
    constexpr LinearRGB<T, RGBSpace> operator* (LinearRGB<T, RGBSpace> lhs, typename LinearRGB<T, RGBSpace>::value_type rhs) noexcept {
        return {lhs.r*rhs, lhs.g*rhs, lhs.b*rhs};
    }
    template <typename T, template <typename> class RGBSpace>
    constexpr LinearRGB<T, RGBSpace> operator/ (LinearRGB<T, RGBSpace> lhs, typename LinearRGB<T, RGBSpace>::value_type rhs) noexcept {
        return {lhs.r/rhs, lhs.g/rhs, lhs.b/rhs};
    }

    template <typename T, template <typename> class RGBSpace>
    constexpr LinearRGB<T, RGBSpace> operator+ (typename LinearRGB<T, RGBSpace>::value_type lhs, LinearRGB<T, RGBSpace> rhs) noexcept {
        return {lhs+rhs.r, lhs+rhs.g, lhs+rhs.b};
    }
    template <typename T, template <typename> class RGBSpace>
    constexpr LinearRGB<T, RGBSpace> operator- (typename LinearRGB<T, RGBSpace>::value_type lhs, LinearRGB<T, RGBSpace> rhs) noexcept {
        return {lhs-rhs.r, lhs-rhs.g, lhs-rhs.b};
    }
    template <typename T, template <typename> class RGBSpace>
    constexpr LinearRGB<T, RGBSpace> operator* (typename LinearRGB<T, RGBSpace>::value_type lhs, LinearRGB<T, RGBSpace> rhs) noexcept {
        return {lhs*rhs.r, lhs*rhs.g, lhs*rhs.b};
    }
    template <typename T, template <typename> class RGBSpace>
    constexpr LinearRGB<T, RGBSpace> operator/ (typename LinearRGB<T, RGBSpace>::value_type lhs, LinearRGB<T, RGBSpace> rhs) noexcept {
        return {lhs/rhs.r, lhs/rhs.g, lhs/rhs.b};
    }


    // algorithms
    template <typename T, template <typename> class RGBSpace>
    inline LinearRGB<T, RGBSpace> min(LinearRGB<T, RGBSpace> x, LinearRGB<T, RGBSpace> y) noexcept {
        using std::min;
        return { min(x.r, y.r),
                 min(x.g, y.g),
                 min(x.b, y.b) };
    }
    template <typename T, template <typename> class RGBSpace>
    inline LinearRGB<T, RGBSpace> max(LinearRGB<T, RGBSpace> x, LinearRGB<T, RGBSpace> y) noexcept {
        using std::max;
        return { max(x.r, y.r),
                 max(x.g, y.g),
                 max(x.b, y.b) };
    }

    template <typename T, template <typename> class RGBSpace>
    inline LinearRGB<T, RGBSpace> min(LinearRGB<T, RGBSpace> x, typename LinearRGB<T, RGBSpace>::value_type y) noexcept {
        using std::min;
        return { min(x.r, y),
                 min(x.g, y),
                 min(x.b, y) };
    }
    template <typename T, template <typename> class RGBSpace>
    inline LinearRGB<T, RGBSpace> max(LinearRGB<T, RGBSpace> x, typename LinearRGB<T, RGBSpace>::value_type y) noexcept {
        using std::max;
        return { max(x.r, y),
                 max(x.g, y),
                 max(x.b, y) };
    }

    template <typename T, template <typename> class RGBSpace>
    inline LinearRGB<T, RGBSpace> min(typename LinearRGB<T, RGBSpace>::value_type x, LinearRGB<T, RGBSpace> y) noexcept {
        using std::min;
        return { min(x, y.r),
                 min(x, y.g),
                 min(x, y.b) };
    }
    template <typename T, template <typename> class RGBSpace>
    inline LinearRGB<T, RGBSpace> max(typename LinearRGB<T, RGBSpace>::value_type x, LinearRGB<T, RGBSpace> y) noexcept {
        using std::max;
        return { max(x, y.r),
                 max(x, y.g),
                 max(x, y.b) };
    }
}



// "apply"-concept implementation.
namespace tukan {
    namespace detail {
        // We have to overload the rebind_value_type-template because the general version does not
        // like template template arguments.
        template <typename To, typename From, template <typename> class RGBSpace>
        struct rebind_value_type<To, LinearRGB<From, RGBSpace>> {
            using type = LinearRGB<To, RGBSpace>;
        };
    }

    template <typename T, template <typename> class RGBSpace>
    struct has_apply_interface<LinearRGB<T, RGBSpace>> : std::true_type
    {};

    // Unary
    template <typename T, template <typename> class RGBSpace, typename Fun>
    constexpr auto apply (LinearRGB<T, RGBSpace> operand, Fun fun)
      -> LinearRGB<decltype (fun(operand.r)), RGBSpace>
    {
        return {fun(operand.r), fun(operand.g), fun(operand.b)};
    }

    // Binary
    template <typename T, typename U, template <typename> class RGBSpace, typename Fun>
    constexpr auto apply (LinearRGB<T, RGBSpace> lhs, LinearRGB<U, RGBSpace> rhs, Fun fun)
      -> LinearRGB<decltype (fun(lhs.r, rhs.r)), RGBSpace>
    {
        return {fun(lhs.r, rhs.r), fun(lhs.g, rhs.g), fun(lhs.b, rhs.b)};
    }

    template <typename T, typename U, template <typename> class RGBSpace, typename Fun>
    constexpr auto apply (LinearRGB<T, RGBSpace> lhs, U rhs, Fun fun)
      -> LinearRGB<decltype (fun(lhs.r, rhs)), RGBSpace>
    {
        return {fun(lhs.r, rhs), fun(lhs.g, rhs), fun(lhs.b, rhs)};
    }

    template <typename T, typename U, template <typename> class RGBSpace, typename Fun>
    constexpr auto apply (T lhs, LinearRGB<U, RGBSpace> rhs, Fun fun)
      -> LinearRGB<decltype (fun(lhs, rhs.r)), RGBSpace>
    {
        return {fun(lhs, rhs.r), fun(lhs, rhs.g), fun(lhs, rhs.b)};
    }


    template <typename T, typename U, template <typename> class RGBSpace, typename Fun>
    constexpr auto apply (LinearRGB<T, RGBSpace> lhs, LinearRGB<U, RGBSpace> *rhs, Fun fun)
      -> LinearRGB<decltype (fun(lhs.r, &rhs->r)), RGBSpace>
    {
        return {fun(lhs.r, &rhs->r), fun(lhs.g, &rhs->g), fun(lhs.b, &rhs->b)};
    }

    template <typename T, typename U, template <typename> class RGBSpace, typename Fun>
    constexpr auto apply (T lhs, LinearRGB<U, RGBSpace> *rhs, Fun fun)
      -> LinearRGB<decltype (fun(lhs, &rhs->r)), RGBSpace>
    {
        return {fun(lhs, &rhs->r), fun(lhs, &rhs->g), fun(lhs, &rhs->b)};
    }


    // Ternary
    template <typename T, typename U, typename V, template <typename> class RGBSpace, typename Fun>
    constexpr auto apply (LinearRGB<T, RGBSpace> a, LinearRGB<U, RGBSpace> b, LinearRGB<V, RGBSpace> c, Fun fun)
      -> LinearRGB<decltype (fun(a.r, b.r, c.r)), RGBSpace>
    {
        return {fun(a.r, b.r, c.r), fun(a.g, b.g, c.g), fun(a.b, b.b, c.b)};
    }

    template <typename T, typename U, typename V, template <typename> class RGBSpace, typename Fun>
    constexpr auto apply (LinearRGB<T, RGBSpace> a, LinearRGB<U, RGBSpace> b, V c, Fun fun)
      -> LinearRGB<decltype (fun(a.r, b.r, c)), RGBSpace>
    {
        return {fun(a.r, b.r, c), fun(a.g, b.g, c), fun(a.b, b.b, c)};
    }

    template <typename T, typename U, typename V, template <typename> class RGBSpace, typename Fun>
    constexpr auto apply (LinearRGB<T, RGBSpace> a, U b, LinearRGB<V, RGBSpace> c, Fun fun)
      -> LinearRGB<decltype (fun(a.r, b, c.r)), RGBSpace>
    {
        return {fun(a.r, b, c.r), fun(a.g, b, c.g), fun(a.b, b, c.b)};
    }

    template <typename T, typename U, typename V, template <typename> class RGBSpace, typename Fun>
    constexpr auto apply (LinearRGB<T, RGBSpace> a, U b, V c, Fun fun)
      -> LinearRGB<decltype (fun(a.r, b, c)), RGBSpace>
    {
        return {fun(a.r, b, c), fun(a.g, b, c), fun(a.b, b, c)};
    }

    template <typename T, typename U, typename V, template <typename> class RGBSpace, typename Fun>
    constexpr auto apply (T a, LinearRGB<U, RGBSpace> b, LinearRGB<V, RGBSpace> c, Fun fun)
      -> LinearRGB<decltype (fun(a, b.r, c.r)), RGBSpace>
    {
        return {fun(a, b.r, c.r), fun(a, b.g, c.g), fun(a, b.b, c.b)};
    }

    template <typename T, typename U, typename V, template <typename> class RGBSpace, typename Fun>
    constexpr auto apply (T a, LinearRGB<U, RGBSpace> b, V c, Fun fun)
      -> LinearRGB<decltype (fun(a, b.r, c)), RGBSpace>
    {
        return {fun(a, b.r, c), fun(a, b.g, c), fun(a, b.b, c)};
    }

    template <typename T, typename U, typename V, template <typename> class RGBSpace, typename Fun>
    constexpr auto apply (T a, U b, LinearRGB<V, RGBSpace> c, Fun fun)
      -> LinearRGB<decltype (fun(a, b, c.r)), RGBSpace>
    {
        return {fun(a, b, c.r), fun(a, b, c.g), fun(a, b, c.b)};
    }

    template <typename T, typename U, typename V, template <typename> class RGBSpace, typename Fun>
    constexpr auto apply (LinearRGB<T, RGBSpace> a, LinearRGB<U, RGBSpace> b, LinearRGB<V, RGBSpace> *c, Fun fun)
      -> LinearRGB<decltype (fun(a.r, b.r, &c->r)), RGBSpace>
    {
        return {fun(a.r, b.r, &c->r), fun(a.g, b.g, &c->g), fun(a.b, b.b, &c->b)};
    }

    template <typename T, typename U, typename V, template <typename> class RGBSpace, typename Fun>
    constexpr auto apply (LinearRGB<T, RGBSpace> a, U b, LinearRGB<V, RGBSpace> *c, Fun fun)
      -> LinearRGB<decltype (fun(a.r, b, &c->r)), RGBSpace>
    {
        return {fun(a.r, b, &c->r), fun(a.g, b, &c->g), fun(a.b, b, &c->b)};
    }

    template <typename T, typename U, typename V, template <typename> class RGBSpace, typename Fun>
    constexpr auto apply (T a, LinearRGB<U, RGBSpace> b, LinearRGB<V, RGBSpace> *c, Fun fun)
      -> LinearRGB<decltype (fun(a, b.r, &c->r)), RGBSpace>
    {
        return {fun(a, b.r, &c->r), fun(a, b.g, &c->g), fun(a, b.b, &c->b)};
    }

    //Implementation notes:
    // Some operator overloads use LinearRGB<T, RGBSpace>::value_type instead of just plain T. This is because
    // with plain T, the operators are deduced on both the lhs AND rhs, leading to ambiguities when
    // using e.g. 'LinearRGB<float> foo; foo += 1;', where there is an int added to a float-RGB.
    // Using LinearRGB::value_type prevents type deduction on the scalar argument.
}

#endif // LINEARRGB_INL_HH_20131122

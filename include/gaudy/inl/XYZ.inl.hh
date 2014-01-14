// (C) 2013 Sebastian Mach (1983), this file is published under the terms of the
// GNU General Public License, Version 3 (a.k.a. GPLv3).
// See COPYING in the root-folder of the excygen project folder.
#ifndef XYZ_INL_HH_20131206
#define XYZ_INL_HH_20131206



// Member functions implementation.
namespace gaudy {

    template <typename T>
    T XYZ<T>::* const XYZ<T>::offsets_[3] =
    {
        &XYZ<T>::X,
        &XYZ<T>::Y,
        &XYZ<T>::Z
    };


    template <typename T>
    inline
    T& XYZ<T>::operator[] (size_t idx) noexcept
    {
        return this->*offsets_[idx];
    }


    template <typename T>
    inline constexpr
    T XYZ<T>::operator[] (size_t idx) const noexcept
    {
        return this->*offsets_[idx];
    }


    template <typename T>
    inline
    T& XYZ<T>::at (size_t idx)
    {
        if (idx>=size()) // TODO: check if the negative check is faster.
            throw std::out_of_range("XYZ: out of range access");
        return this->*offsets_[idx];
    }


    template <typename T>
    inline constexpr
    T XYZ<T>::at (size_t idx) const
    {
        if (idx>=size()) // TODO: check if the negative check is faster.
            throw std::out_of_range("XYZ: out of range access");
        return this->*offsets_[idx];
    }


    template <typename T>
    inline constexpr
    size_t XYZ<T>::size() const noexcept
    {
        return 3;
    }
}



namespace gaudy {

    //---------------------------------------------------------------------------------------------
    // implementation
    //---------------------------------------------------------------------------------------------
    template <typename T>
    inline XYZ<T>& XYZ<T>::operator+= (XYZ<T> rhs) noexcept {
        X += rhs.X;
        Y += rhs.Y;
        Z += rhs.Z;
        return *this;
    }

    template <typename T>
    inline XYZ<T>& XYZ<T>::operator-= (XYZ<T> rhs) noexcept {
        X -= rhs.X;
        Y -= rhs.Y;
        Z -= rhs.Z;
        return *this;
    }

    template <typename T>
    inline XYZ<T>& XYZ<T>::operator*= (XYZ<T> rhs) noexcept {
        X *= rhs.X;
        Y *= rhs.Y;
        Z *= rhs.Z;
        return *this;
    }

    template <typename T>
    inline XYZ<T>& XYZ<T>::operator/= (XYZ<T> rhs) noexcept {
        X /= rhs.X;
        Y /= rhs.Y;
        Z /= rhs.Z;
        return *this;
    }

    template <typename T>
    inline XYZ<T>& XYZ<T>::operator+= (T rhs) noexcept {
        X += rhs;
        Y += rhs;
        Z += rhs;
        return *this;
    }

    template <typename T>
    inline XYZ<T>& XYZ<T>::operator-= (T rhs) noexcept {
        X -= rhs;
        Y -= rhs;
        Z -= rhs;
        return *this;
    }

    template <typename T>
    inline XYZ<T>& XYZ<T>::operator*= (T rhs) noexcept {
        X *= rhs;
        Y *= rhs;
        Z *= rhs;
        return *this;
    }

    template <typename T>
    inline XYZ<T>& XYZ<T>::operator/= (T rhs) noexcept {
        X /= rhs;
        Y /= rhs;
        Z /= rhs;
        return *this;
    }


    // relation
    template <typename T>
    constexpr bool operator== (XYZ<T> lhs, XYZ<T> rhs) noexcept {
        return lhs.X==rhs.X && lhs.Y==rhs.Y && lhs.Z==rhs.Z;
    }
    template <typename T>
    constexpr bool operator!= (XYZ<T> lhs, XYZ<T> rhs) noexcept {
        return !(lhs == rhs);
    }
    template <typename T>
    constexpr bool rel_equal (XYZ<T> lhs, XYZ<T> rhs, T max_rel_diff) noexcept
    {
        return rel_equal (lhs.X, rhs.X, max_rel_diff)
            && rel_equal (lhs.Y, rhs.Y, max_rel_diff)
            && rel_equal (lhs.Z, rhs.Z, max_rel_diff)
        ;
    }


    // arithmetics
    template <typename T>
    constexpr XYZ<T> operator+ (XYZ<T> lhs, XYZ<T> rhs) noexcept {
        return {lhs.X+rhs.X, lhs.Y+rhs.Y, lhs.Z+rhs.Z};
    }
    template <typename T>
    constexpr XYZ<T> operator- (XYZ<T> lhs, XYZ<T> rhs) noexcept {
        return {lhs.X-rhs.X, lhs.Y-rhs.Y, lhs.Z-rhs.Z};
    }
    template <typename T>
    constexpr XYZ<T> operator* (XYZ<T> lhs, XYZ<T> rhs) noexcept {
        return {lhs.X*rhs.X, lhs.Y*rhs.Y, lhs.Z*rhs.Z};
    }
    template <typename T>
    constexpr XYZ<T> operator/ (XYZ<T> lhs, XYZ<T> rhs) noexcept {
        return {lhs.X/rhs.X, lhs.Y/rhs.Y, lhs.Z/rhs.Z};
    }

    template <typename T>
    constexpr XYZ<T> operator+ (XYZ<T> lhs, typename XYZ<T>::value_type rhs) noexcept {
        return {lhs.X+rhs, lhs.Y+rhs, lhs.Z+rhs};
    }
    template <typename T>
    constexpr XYZ<T> operator- (XYZ<T> lhs, typename XYZ<T>::value_type rhs) noexcept {
        return {lhs.X-rhs, lhs.Y-rhs, lhs.Z-rhs};
    }
    template <typename T>
    constexpr XYZ<T> operator* (XYZ<T> lhs, typename XYZ<T>::value_type rhs) noexcept {
        return {lhs.X*rhs, lhs.Y*rhs, lhs.Z*rhs};
    }
    template <typename T>
    constexpr XYZ<T> operator/ (XYZ<T> lhs, typename XYZ<T>::value_type rhs) noexcept {
        return {lhs.X/rhs, lhs.Y/rhs, lhs.Z/rhs};
    }

    template <typename T>
    constexpr XYZ<T> operator+ (typename XYZ<T>::value_type lhs, XYZ<T> rhs) noexcept {
        return {lhs+rhs.X, lhs+rhs.Y, lhs+rhs.Z};
    }
    template <typename T>
    constexpr XYZ<T> operator- (typename XYZ<T>::value_type lhs, XYZ<T> rhs) noexcept {
        return {lhs-rhs.X, lhs-rhs.Y, lhs-rhs.Z};
    }
    template <typename T>
    constexpr XYZ<T> operator* (typename XYZ<T>::value_type lhs, XYZ<T> rhs) noexcept {
        return {lhs*rhs.X, lhs*rhs.Y, lhs*rhs.Z};
    }
    template <typename T>
    constexpr XYZ<T> operator/ (typename XYZ<T>::value_type lhs, XYZ<T> rhs) noexcept {
        return {lhs/rhs.X, lhs/rhs.Y, lhs/rhs.Z};
    }


    // algorithms
    template <typename T>
    inline XYZ<T> min(XYZ<T> x, XYZ<T> y) noexcept {
        using std::min;
        return { min(x.X, y.X),
                 min(x.Y, y.Y),
                 min(x.Z, y.Z) };
    }
    template <typename T>
    inline XYZ<T> max(XYZ<T> x, XYZ<T> y) noexcept {
        using std::max;
        return { max(x.X, y.X),
                 max(x.Y, y.Y),
                 max(x.Z, y.Z) };
    }

    template <typename T>
    inline XYZ<T> min(XYZ<T> x, typename XYZ<T>::value_type y) noexcept {
        using std::min;
        return { min(x.X, y),
                 min(x.Y, y),
                 min(x.Z, y) };
    }
    template <typename T>
    inline XYZ<T> max(XYZ<T> x, typename XYZ<T>::value_type y) noexcept {
        using std::max;
        return { max(x.X, y),
                 max(x.Y, y),
                 max(x.Z, y) };
    }

    template <typename T>
    inline XYZ<T> min(typename XYZ<T>::value_type x, XYZ<T> y) noexcept {
        using std::min;
        return { min(x, y.X),
                 min(x, y.Y),
                 min(x, y.Z) };
    }
    template <typename T>
    inline XYZ<T> max(typename XYZ<T>::value_type x, XYZ<T> y) noexcept {
        using std::max;
        return { max(x, y.X),
                 max(x, y.Y),
                 max(x, y.Z) };
    }
}



// "apply"-concept implementation.
namespace gaudy {
    namespace detail {
        // We have to overload the rebind_value_type-template because the general version does not
        // like template template arguments.
        template <typename To, typename From>
        struct rebind_value_type<To, XYZ<From>> {
            using type = XYZ<To>;
        };
    }

    template <typename T>
    struct has_apply_interface<XYZ<T>> : std::true_type
    {};

    // Unary
    template <typename T, typename Fun>
    constexpr auto apply (XYZ<T> operand, Fun fun)
      -> XYZ<decltype (fun(operand.X))>
    {
        return {fun(operand.X), fun(operand.Y), fun(operand.Z)};
    }

    // Binary
    template <typename T, typename U, typename Fun>
    constexpr auto apply (XYZ<T> lhs, XYZ<U> rhs, Fun fun)
      -> XYZ<decltype (fun(lhs.X, rhs.X))>
    {
        return {fun(lhs.X, rhs.X), fun(lhs.Y, rhs.Y), fun(lhs.Z, rhs.Z)};
    }

    template <typename T, typename U, typename Fun>
    constexpr auto apply (XYZ<T> lhs, U rhs, Fun fun)
      -> XYZ<decltype (fun(lhs.X, rhs))>
    {
        return {fun(lhs.X, rhs), fun(lhs.Y, rhs), fun(lhs.Z, rhs)};
    }

    template <typename T, typename U, typename Fun>
    constexpr auto apply (T lhs, XYZ<U> rhs, Fun fun)
      -> XYZ<decltype (fun(lhs, rhs.X))>
    {
        return {fun(lhs, rhs.X), fun(lhs, rhs.Y), fun(lhs, rhs.Z)};
    }


    template <typename T, typename U, typename Fun>
    constexpr auto apply (XYZ<T> lhs, XYZ<U> *rhs, Fun fun)
      -> XYZ<decltype (fun(lhs.X, &rhs->X))>
    {
        return {fun(lhs.X, &rhs->X), fun(lhs.Y, &rhs->Y), fun(lhs.Z, &rhs->Z)};
    }

    template <typename T, typename U, typename Fun>
    constexpr auto apply (T lhs, XYZ<U> *rhs, Fun fun)
      -> XYZ<decltype (fun(lhs, &rhs->X))>
    {
        return {fun(lhs, &rhs->X), fun(lhs, &rhs->Y), fun(lhs, &rhs->Z)};
    }


    // Ternary
    template <typename T, typename U, typename V, typename Fun>
    constexpr auto apply (XYZ<T> a, XYZ<U> b, XYZ<V> c, Fun fun)
      -> XYZ<decltype (fun(a.X, b.X, c.X))>
    {
        return {fun(a.X, b.X, c.X), fun(a.Y, b.Y, c.Y), fun(a.Z, b.Z, c.Z)};
    }

    template <typename T, typename U, typename V, typename Fun>
    constexpr auto apply (XYZ<T> a, XYZ<U> b, V c, Fun fun)
      -> XYZ<decltype (fun(a.X, b.X, c))>
    {
        return {fun(a.X, b.X, c), fun(a.Y, b.Y, c), fun(a.Z, b.Z, c)};
    }

    template <typename T, typename U, typename V, typename Fun>
    constexpr auto apply (XYZ<T> a, U b, XYZ<V> c, Fun fun)
      -> XYZ<decltype (fun(a.X, b, c.X))>
    {
        return {fun(a.X, b, c.X), fun(a.Y, b, c.Y), fun(a.Z, b, c.Z)};
    }

    template <typename T, typename U, typename V, typename Fun>
    constexpr auto apply (XYZ<T> a, U b, V c, Fun fun)
      -> XYZ<decltype (fun(a.X, b, c))>
    {
        return {fun(a.X, b, c), fun(a.Y, b, c), fun(a.Z, b, c)};
    }

    template <typename T, typename U, typename V, typename Fun>
    constexpr auto apply (T a, XYZ<U> b, XYZ<V> c, Fun fun)
      -> XYZ<decltype (fun(a, b.X, c.X))>
    {
        return {fun(a, b.X, c.X), fun(a, b.Y, c.Y), fun(a, b.Z, c.Z)};
    }

    template <typename T, typename U, typename V, typename Fun>
    constexpr auto apply (T a, XYZ<U> b, V c, Fun fun)
      -> XYZ<decltype (fun(a, b.X, c))>
    {
        return {fun(a, b.X, c), fun(a, b.Y, c), fun(a, b.Z, c)};
    }

    template <typename T, typename U, typename V, typename Fun>
    constexpr auto apply (T a, U b, XYZ<V> c, Fun fun)
      -> XYZ<decltype (fun(a, b, c.X))>
    {
        return {fun(a, b, c.X), fun(a, b, c.Y), fun(a, b, c.Z)};
    }

    template <typename T, typename U, typename V, typename Fun>
    constexpr auto apply (XYZ<T> a, XYZ<U> b, XYZ<V> *c, Fun fun)
      -> XYZ<decltype (fun(a.X, b.X, &c->X))>
    {
        return {fun(a.X, b.X, &c->X), fun(a.Y, b.Y, &c->Y), fun(a.Z, b.Z, &c->Z)};
    }

    template <typename T, typename U, typename V, typename Fun>
    constexpr auto apply (XYZ<T> a, U b, XYZ<V> *c, Fun fun)
      -> XYZ<decltype (fun(a.X, b, &c->X))>
    {
        return {fun(a.X, b, &c->X), fun(a.Y, b, &c->Y), fun(a.Z, b, &c->Z)};
    }

    template <typename T, typename U, typename V, typename Fun>
    constexpr auto apply (T a, XYZ<U> b, XYZ<V> *c, Fun fun)
      -> XYZ<decltype (fun(a, b.X, &c->X))>
    {
        return {fun(a, b.X, &c->X), fun(a, b.Y, &c->Y), fun(a, b.Z, &c->Z)};
    }

    //Implementation notes:
    // Some operator overloads use XYZ<T>::value_type instead of just plain T. This is because
    // with plain T, the operators are deduced on both the lhs AND rhs, leading to ambiguities when
    // using e.Y. 'XYZ<float> foo; foo += 1;', where there is an int added to a float-RGB.
    // Using XYZ::value_type prevents type deduction on the scalar argument.
}

#endif // XYZ_INL_HH_20131206

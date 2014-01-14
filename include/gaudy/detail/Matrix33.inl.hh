// (C) 2013 Sebastian Mach (1983), this file is published under the terms of the
// GNU General Public License, Version 3 (a.k.a. GPLv3).
// See COPYING in the root-folder of the excygen project folder.


namespace gaudy { namespace detail {
    template <typename T>
    constexpr bool rel_equal (detail::Matrix33<T> const &m,
                              detail::Matrix33<T> const &n,
                              T e) noexcept
    {
        using gaudy::rel_equal;
        return rel_equal(m._11,n._11,e) && rel_equal(m._12,n._12,e) && rel_equal(m._13,n._13,e)
            && rel_equal(m._21,n._21,e) && rel_equal(m._22,n._22,e) && rel_equal(m._23,n._23,e)
            && rel_equal(m._31,n._31,e) && rel_equal(m._32,n._32,e) && rel_equal(m._33,n._33,e);
    }
} }


namespace gaudy {  namespace detail {
    template <typename T>
    constexpr bool operator== (Matrix33<T> const &m, Matrix33<T> const &n) noexcept
    {
        return (m._11==n._11) && (m._12==n._12) && (m._13==n._13)
            && (m._21==n._21) && (m._22==n._22) && (m._23==n._23)
            && (m._31==n._31) && (m._32==n._32) && (m._33==n._33);
    }

    template <typename T>
    constexpr bool operator!= (Matrix33<T> const &m, Matrix33<T> const &n) noexcept
    {
        return !(m==n);
    }

    template <typename T>
    constexpr T determinant(Matrix33<T> const &m) noexcept
    {
        return + m._11*m._22*m._33
               + m._12*m._23*m._31
               + m._13*m._21*m._32
               - m._12*m._21*m._33
               - m._13*m._22*m._31
               - m._11*m._23*m._32;
    }

    template <typename T>
    constexpr Matrix33<T> operator* (Matrix33<T> const &m, T f) noexcept
    {
        return {m._11*f, m._12*f, m._13*f,
                m._21*f, m._22*f, m._23*f,
                m._31*f, m._32*f, m._33*f};
    }

    template <typename T>
    constexpr Matrix33<T> operator* (T f, Matrix33<T> const &m) noexcept
    {
        return {f*m._11, f*m._12, f*m._13,
                f*m._21, f*m._22, f*m._23,
                f*m._31, f*m._32, f*m._33};
    }

    template <typename T>
    constexpr Matrix33<T> operator* (Matrix33<T> const &m, Matrix33<T> const &n) noexcept
    {
        return { m._11*n._11 + m._12*n._21 + m._13*n._31,
                 m._11*n._12 + m._12*n._22 + m._13*n._32,
                 m._11*n._13 + m._12*n._23 + m._13*n._33,

                 m._21*n._11 + m._22*n._21 + m._23*n._31,
                 m._21*n._12 + m._22*n._22 + m._23*n._32,
                 m._21*n._13 + m._22*n._23 + m._23*n._33,

                 m._31*n._11 + m._32*n._21 + m._33*n._31,
                 m._31*n._12 + m._32*n._22 + m._33*n._32,
                 m._31*n._13 + m._32*n._23 + m._33*n._33,
               };
    }

    template <typename T>
    constexpr Matrix33<T> inverse (Matrix33<T> const &m) noexcept
    {
        return (1 / determinant(m))
             * Matrix33<T>{
                     +m._22*m._33-m._23*m._32,  -m._12*m._33+m._13*m._32,  +m._12*m._23-m._13*m._22,
                     -m._21*m._33+m._23*m._31,  +m._11*m._33-m._13*m._31,  -m._11*m._23+m._13*m._21,
                     +m._21*m._32-m._22*m._31,  -m._11*m._32+m._12*m._31,  +m._11*m._22-m._12*m._21,
                    };
    }

    template <typename T>
    constexpr Matrix33<T> transpose (Matrix33<T> const &m) noexcept
    {
        return {m._11, m._21, m._31,
                m._12, m._22, m._32,
                m._13, m._23, m._33};
    }
} }


/*******************************************************************************
 * Copyright (c) 2023.
 * This file is part of The WhiteGear Studio software property.
 * If you get unexpected access to this file, or part ot whole codebase, you should
 * report this source code leak and delete all copies of source code from all your machines.
 ******************************************************************************/

#ifndef WHITEGEAR_MAT4_HPP
#define WHITEGEAR_MAT4_HPP

#include <math/matrix_base.hpp>

namespace wg {
    template<>
    struct mat<4, 4> {
        using column_type = vec<4>;
        using row_type = vec<4>;

        inline mat() = default;
        inline ~mat() = default;

        inline mat(const mat&) = default;
        inline mat& operator=(const mat&) = default;
        inline mat(mat&&) noexcept = default;
        inline mat& operator=(mat&&) noexcept = default;

        inline explicit mat(scalar v) : value{
            column_type(v, 0, 0, 0),
            column_type(0, v, 0, 0),
            column_type(0, 0, v, 0),
            column_type(0, 0, 0, v) }
        {}

        inline mat(scalar x0, scalar y0, scalar z0, scalar w0,
                   scalar x1, scalar y1, scalar z1, scalar w1,
                   scalar x2, scalar y2, scalar z2, scalar w2,
                   scalar x3, scalar y3, scalar z3, scalar w3) : value {
            column_type(x0, y0, z0, w0),
            column_type(x1, y1, z1, w1),
            column_type(x2, y2, z2, w2),
            column_type(x3, y3, z3, w3) }
        {}

        inline mat(const column_type& c0, const column_type& c1, const column_type& c2, const column_type& c3)
            : value{ c0, c1, c2, c3 }
        {}

        // TODO: complete conversion mat3->mat4
        inline mat(const mat<3, 3>& m)
        {}

        template<class T>
        inline mat& operator+=(T s) {
            value[0] += s;
            value[1] += s;
            value[2] += s;
            value[3] += s;
            return *this;
        }
        inline mat& operator+=(const mat& m) {
            value[0] += m[0];
            value[1] += m[1];
            value[2] += m[2];
            value[3] += m[3];
            return *this;
        }
        template<class T>
        inline mat& operator-=(T s) {
            value[0] -= s;
            value[1] -= s;
            value[2] -= s;
            value[3] -= s;
            return *this;
        }
        inline mat& operator-=(const mat& m) {
            value[0] -= m[0];
            value[1] -= m[1];
            value[2] -= m[2];
            value[3] -= m[3];
            return *this;
        }
        template<class T>
        inline mat& operator*=(T s) {
            value[0] *= s;
            value[1] *= s;
            value[2] *= s;
            value[3] *= s;
            return *this;
        }
        inline mat& operator*=(const mat& m) {
            value[0] *= m[0];
            value[1] *= m[1];
            value[2] *= m[2];
            value[3] *= m[3];
            return *this;
        }
        template<class T>
        inline mat& operator/=(T s) {
            value[0] /= s;
            value[1] /= s;
            value[2] /= s;
            value[3] /= s;
            return *this;
        }
        inline mat& operator/=(const mat& m) {
            value[0] /= m[0];
            value[1] /= m[1];
            value[2] /= m[2];
            value[3] /= m[3];
            return *this;
        }

        inline mat& operator++() {
            ++value[0];
            ++value[1];
            ++value[2];
            ++value[3];
            return *this;
        }
        inline mat& operator--() {
            --value[0];
            --value[1];
            --value[2];
            --value[3];
            return *this;
        }
        inline mat operator++(int) {
            mat t(*this);
            ++*this;
            return t;
        }
        inline mat operator--(int) {
            mat t(*this);
            --*this;
            return t;
        }

        inline column_type& operator[](int i) { return (value)[i]; }
        inline const column_type & operator[](int i) const { return (value)[i]; }

        column_type value[4];
    };

    inline mat4 operator+(const mat4& m) {
        return m;
    }
    inline mat4 operator-(const mat4& m) {
        return {
            -m[0],
            -m[1],
            -m[2],
            -m[3]
        };
    }

    template<class T>
    inline mat4 operator+(const mat4& m, T s) {
        return {
            m[0] + s,
            m[1] + s,
            m[2] + s,
            m[3] + s
        };
    }
    inline mat4 operator+(const mat4& m0, const mat4& m1) {
        return {
            m0[0] + m1[0],
            m0[1] + m1[1],
            m0[2] + m1[2],
            m0[3] + m1[3]
        };
    }
    template<class T>
    inline mat4 operator-(const mat4& m, T s) {
        return {
            m[0] - s,
            m[1] - s,
            m[2] - s,
            m[3] - s
        };
    }
    inline mat4 operator-(const mat4& m0, const mat4& m1) {
        return {
            m0[0] - m1[0],
            m0[1] - m1[1],
            m0[2] - m1[2],
            m0[3] - m1[3]
        };
    }
    template<class T>
    inline mat4 operator*(const mat4& m, T s) {
        return {
            m[0] * s,
            m[1] * s,
            m[2] * s,
            m[3] * s
        };
    }
    inline typename mat4::column_type operator*(const mat4& m, const typename mat4::row_type&  v) {
        const auto Mov0(v[0]);
        const auto Mov1(v[1]);
        const auto Mul0 = m[0] * Mov0;
        const auto Mul1 = m[1] * Mov1;
        const auto Add0 = Mul0 + Mul1;
        const auto Mov2(v[2]);
        const auto Mov3(v[3]);
        const auto Mul2 = m[2] * Mov2;
        const auto Mul3 = m[3] * Mov3;
        const auto Add1 = Mul2 + Mul3;
        const auto Add2 = Add0 + Add1;
        return Add2;
    }

    inline typename mat4::row_type operator*(const typename mat4::column_type& v, const mat4& m) {
        return {
            m[0][0] * v[0] + m[0][1] * v[1] + m[0][2] * v[2] + m[0][3] * v[3],
            m[1][0] * v[0] + m[1][1] * v[1] + m[1][2] * v[2] + m[1][3] * v[3],
            m[2][0] * v[0] + m[2][1] * v[1] + m[2][2] * v[2] + m[2][3] * v[3],
            m[3][0] * v[0] + m[3][1] * v[1] + m[3][2] * v[2] + m[3][3] * v[3]
        };
    }

    inline mat4 operator*(const mat4& m1, const mat4& m2) {
        const auto SrcA0 = m1[0];
        const auto SrcA1 = m1[1];
        const auto SrcA2 = m1[2];
        const auto SrcA3 = m1[3];

        const auto SrcB0 = m2[0];
        const auto SrcB1 = m2[1];
        const auto SrcB2 = m2[2];
        const auto SrcB3 = m2[3];

        mat4 Result;
        Result[0] = SrcA0 * SrcB0[0] + SrcA1 * SrcB0[1] + SrcA2 * SrcB0[2] + SrcA3 * SrcB0[3];
        Result[1] = SrcA0 * SrcB1[0] + SrcA1 * SrcB1[1] + SrcA2 * SrcB1[2] + SrcA3 * SrcB1[3];
        Result[2] = SrcA0 * SrcB2[0] + SrcA1 * SrcB2[1] + SrcA2 * SrcB2[2] + SrcA3 * SrcB2[3];
        Result[3] = SrcA0 * SrcB3[0] + SrcA1 * SrcB3[1] + SrcA2 * SrcB3[2] + SrcA3 * SrcB3[3];
        return Result;
    }
    template<class T>
    inline mat4 operator/(const mat4& m, T s) {
        return {
            m[0] / s,
            m[1] / s,
            m[2] / s,
            m[3] / s
        };
    }

    inline typename mat4::column_type operator/(const mat4& m, const typename mat4::row_type& v) {
        return inverse(m) * v;
    }
    inline typename mat4::row_type operator/(const typename mat4::column_type & v, const mat4& m) {
        return v * inverse(m);
    }

    inline mat4 operator/(const mat4& m1, const mat4& m2) {
        auto cpy(m1);
        return cpy /= m2;
    }

    inline bool operator==(const mat4& a, const mat4& b) {
        return ((a[0] == b[0]) && (a[1] == b[1]) && (a[2] == b[2]) && (a[3] == b[3]));
    }
    inline bool operator!=(const mat4& a, const mat4& b) {
        return !((a[0] == b[0]) && (a[1] == b[1]) && (a[2] == b[2]) && (a[3] == b[3]));
    }
}

#endif //WHITEGEAR_MAT4_HPP

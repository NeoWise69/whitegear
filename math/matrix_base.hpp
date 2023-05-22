
/*******************************************************************************
 * Copyright (c) 2023.
 * This file is part of The WhiteGear Studio software property.
 * If you get unexpected access to this file, or part ot whole codebase, you should
 * report this source code leak and delete all copies of source code from all your machines.
 ******************************************************************************/

#ifndef WHITEGEAR_MATRIX_BASE_HPP
#define WHITEGEAR_MATRIX_BASE_HPP

#include <math/scalar_base.hpp>
#include <math/vec4.hpp>

namespace wg {
    /**
    * Forward matrix type declarations.
    */
    template<uint C, uint R> struct mat;

    using mat4  = mat<4, 4>;
    using mat3  = mat<3, 3>;
    using mat43 = mat<4, 3>;
    using mat34 = mat<3, 4>;

    template<uint C, uint R>
    inline mat<C, R> inverse(const mat<C, R>& m) {
        const auto Coef00 = m[2][2] * m[3][3] - m[3][2] * m[2][3];
        const auto Coef02 = m[1][2] * m[3][3] - m[3][2] * m[1][3];
        const auto Coef03 = m[1][2] * m[2][3] - m[2][2] * m[1][3];

        const auto Coef04 = m[2][1] * m[3][3] - m[3][1] * m[2][3];
        const auto Coef06 = m[1][1] * m[3][3] - m[3][1] * m[1][3];
        const auto Coef07 = m[1][1] * m[2][3] - m[2][1] * m[1][3];

        const auto Coef08 = m[2][1] * m[3][2] - m[3][1] * m[2][2];
        const auto Coef10 = m[1][1] * m[3][2] - m[3][1] * m[1][2];
        const auto Coef11 = m[1][1] * m[2][2] - m[2][1] * m[1][2];

        const auto Coef12 = m[2][0] * m[3][3] - m[3][0] * m[2][3];
        const auto Coef14 = m[1][0] * m[3][3] - m[3][0] * m[1][3];
        const auto Coef15 = m[1][0] * m[2][3] - m[2][0] * m[1][3];

        const auto Coef16 = m[2][0] * m[3][2] - m[3][0] * m[2][2];
        const auto Coef18 = m[1][0] * m[3][2] - m[3][0] * m[1][2];
        const auto Coef19 = m[1][0] * m[2][2] - m[2][0] * m[1][2];

        const auto Coef20 = m[2][0] * m[3][1] - m[3][0] * m[2][1];
        const auto Coef22 = m[1][0] * m[3][1] - m[3][0] * m[1][1];
        const auto Coef23 = m[1][0] * m[2][1] - m[2][0] * m[1][1];

        const vec<C> Fac0(Coef00, Coef00, Coef02, Coef03);
        const vec<C> Fac1(Coef04, Coef04, Coef06, Coef07);
        const vec<C> Fac2(Coef08, Coef08, Coef10, Coef11);
        const vec<C> Fac3(Coef12, Coef12, Coef14, Coef15);
        const vec<C> Fac4(Coef16, Coef16, Coef18, Coef19);
        const vec<C> Fac5(Coef20, Coef20, Coef22, Coef23);

        const vec<C> Vec0(m[1][0], m[0][0], m[0][0], m[0][0]);
        const vec<C> Vec1(m[1][1], m[0][1], m[0][1], m[0][1]);
        const vec<C> Vec2(m[1][2], m[0][2], m[0][2], m[0][2]);
        const vec<C> Vec3(m[1][3], m[0][3], m[0][3], m[0][3]);

        const vec<C> Inv0(Vec1 * Fac0 - Vec2 * Fac1 + Vec3 * Fac2);
        const vec<C> Inv1(Vec0 * Fac0 - Vec2 * Fac3 + Vec3 * Fac4);
        const vec<C> Inv2(Vec0 * Fac1 - Vec1 * Fac3 + Vec3 * Fac5);
        const vec<C> Inv3(Vec0 * Fac2 - Vec1 * Fac4 + Vec2 * Fac5);

        const vec<C> SignA(+1, -1, +1, -1);
        const vec<C> SignB(-1, +1, -1, +1);
        const mat<C, R> Inverse(Inv0 * SignA, Inv1 * SignB, Inv2 * SignA, Inv3 * SignB);

        const vec<C> Row0(Inverse[0][0], Inverse[1][0], Inverse[2][0], Inverse[3][0]);

        const vec<C> Dot0(m[0] * Row0);
        const auto Dot1 = (Dot0.x + Dot0.y) + (Dot0.z + Dot0.w);

        const auto OneOverDeterminant = scalar(1) / Dot1;

        return Inverse * OneOverDeterminant;
    }
}

#endif //WHITEGEAR_MATRIX_BASE_HPP

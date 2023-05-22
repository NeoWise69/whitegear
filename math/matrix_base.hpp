
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
    /**
     * Computes inverse matrix based on input one.
     */
    template<uint C, uint R>
    inline mat<C, R> inverse(const mat<C, R>& m) {
        const auto c_00 = m[2][2] * m[3][3] - m[3][2] * m[2][3];
        const auto c_02 = m[1][2] * m[3][3] - m[3][2] * m[1][3];
        const auto c_03 = m[1][2] * m[2][3] - m[2][2] * m[1][3];

        const auto c_04 = m[2][1] * m[3][3] - m[3][1] * m[2][3];
        const auto c_06 = m[1][1] * m[3][3] - m[3][1] * m[1][3];
        const auto c_07 = m[1][1] * m[2][3] - m[2][1] * m[1][3];

        const auto c_08 = m[2][1] * m[3][2] - m[3][1] * m[2][2];
        const auto c_10 = m[1][1] * m[3][2] - m[3][1] * m[1][2];
        const auto c_11 = m[1][1] * m[2][2] - m[2][1] * m[1][2];

        const auto c_12 = m[2][0] * m[3][3] - m[3][0] * m[2][3];
        const auto c_14 = m[1][0] * m[3][3] - m[3][0] * m[1][3];
        const auto c_15 = m[1][0] * m[2][3] - m[2][0] * m[1][3];

        const auto c_16 = m[2][0] * m[3][2] - m[3][0] * m[2][2];
        const auto c_18 = m[1][0] * m[3][2] - m[3][0] * m[1][2];
        const auto c_19 = m[1][0] * m[2][2] - m[2][0] * m[1][2];

        const auto c_20 = m[2][0] * m[3][1] - m[3][0] * m[2][1];
        const auto c_22 = m[1][0] * m[3][1] - m[3][0] * m[1][1];
        const auto c_23 = m[1][0] * m[2][1] - m[2][0] * m[1][1];

        const vec<C> f_0(c_00, c_00, c_02, c_03);
        const vec<C> f_1(c_04, c_04, c_06, c_07);
        const vec<C> f_2(c_08, c_08, c_10, c_11);
        const vec<C> f_3(c_12, c_12, c_14, c_15);
        const vec<C> f_4(c_16, c_16, c_18, c_19);
        const vec<C> f_5(c_20, c_20, c_22, c_23);

        const vec<C> v_0(m[1][0], m[0][0], m[0][0], m[0][0]);
        const vec<C> v_1(m[1][1], m[0][1], m[0][1], m[0][1]);
        const vec<C> v_2(m[1][2], m[0][2], m[0][2], m[0][2]);
        const vec<C> v_3(m[1][3], m[0][3], m[0][3], m[0][3]);

        const auto i_0(v_1 * f_0 - v_2 * f_1 + v_3 * f_2);
        const auto i_1(v_0 * f_0 - v_2 * f_3 + v_3 * f_4);
        const auto i_2(v_0 * f_1 - v_1 * f_3 + v_3 * f_5);
        const auto i_3(v_0 * f_2 - v_1 * f_4 + v_2 * f_5);

        const vec<C> SignA(+1, -1, +1, -1);
        const vec<C> SignB(-1, +1, -1, +1);
        const mat<C, R> i_last(i_0 * SignA, i_1 * SignB, i_2 * SignA, i_3 * SignB);

        const vec<C> r0(i_last[0][0], i_last[1][0], i_last[2][0], i_last[3][0]);

        const auto d0(m[0] * r0);
        const auto Dot1 = (d0.x + d0.y) + (d0.z + d0.w);

        const auto OneOverDeterminant = scalar(1) / Dot1;

        return i_last * OneOverDeterminant;
    }
}

#endif //WHITEGEAR_MATRIX_BASE_HPP

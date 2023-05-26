
/*******************************************************************************
 * Copyright (c) 2023.
 * This file is part of The WhiteGear Studio software property.
 * If you get unexpected access to this file, or part ot whole codebase, you should
 * report this source code leak and delete all copies of source code from all your machines.
 ******************************************************************************/

#ifndef WHITEGEAR_VEC4_HPP
#define WHITEGEAR_VEC4_HPP

#include "vector_base.hpp"
#include "vec3.hpp"

#define __vec4_declare_operator_2(sign)     \
inline vec operator sign(scalar v)const {        \
    return vec(*this) sign##= v;            \
}                                           \
inline vec operator sign(const vec& v)const {    \
    return vec(*this) sign##= v;            \
}                                           \
inline vec operator sign(const vec<2>& v)const { \
    return vec(*this) sign##= v;            \
}                                           \
inline vec operator sign(const vec<3>& v) const{ \
    return vec(*this) sign##= v;            \
}                                           \

namespace wg {
    template<>
    struct vec<4> {
        inline vec() = default;
        inline ~vec() = default;

        inline vec(const vec&) = default;
        inline vec& operator=(const vec&) = default;
        inline vec(vec&&) noexcept = default;
        inline vec& operator=(vec&&) noexcept = default;

        inline explicit vec(scalar _x) : data(_mm_set1_ps(_x)) {}
        inline vec(scalar _x, scalar _y, scalar _z, scalar _w) : data(_mm_set_ps(_w, _z, _y, _x)) {}
        inline vec(const vec<2>& _xy, scalar _z, scalar _w) : data(_mm_set_ps(_w, _z, _xy.y, _xy.x)) {}
        inline vec(const vec<3>& _xyz, scalar _w) : data(_mm_set_ps(_w, _xyz.z, _xyz.y, _xyz.x)) {}
        inline vec(scalar _x, const vec<2>& _yz, scalar _w) : data(_mm_set_ps(_w, _yz.y, _yz.x, _x)) {}
        inline vec(scalar _x, scalar _y, const vec<2>& _zw) : data(_mm_set_ps(_zw.y, _zw.x, _y, _x)) {}
        inline vec(scalar _x, const vec<3>& _yzw) : data(_mm_set_ps(_yzw.z, _yzw.y, _yzw.x, _x)) {}

        inline scalar& operator[](int i) { return (&x)[i]; }
        inline const scalar& operator[](int i) const { return (&x)[i]; }

        inline vec& operator+=(scalar v) {
            data = _mm_add_ps(data, _mm_set_ps(v, v, v, v));
            return *this;
        }
        inline vec& operator+=(const vec& v) {
            data = _mm_add_ps(data, v.data);
            return *this;
        }
        inline vec& operator+=(const vec<2>& v) {
            // this is even more efficient (for vec2)
            // because of load time to __m128 with only 2
            // usable values and the rest with Zeros.
            x += v.x;
            y += v.y;
            return *this;
        }
        inline vec& operator+=(const vec<3>& v) {
            x += v.x;
            y += v.y;
            z += v.z;
            return *this;
        }
        inline vec& operator-=(scalar v) {
            data = _mm_sub_ps(data, _mm_set_ps(v, v, v, v));
            return *this;
        }
        inline vec& operator-=(const vec& v) {
            data = _mm_sub_ps(data, v.data);
            return *this;
        }
        inline vec& operator-=(const vec<2>& v) {
            x -= v.x;
            y -= v.y;
            return *this;
        }
        inline vec& operator-=(const vec<3>& v) {
            x -= v.x;
            y -= v.y;
            z -= v.z;
            return *this;
        }
        inline vec& operator*=(scalar v) {
            data = _mm_mul_ps(data, _mm_set_ps(v, v, v, v));
            return *this;
        }
        inline vec& operator*=(const vec& v) {
            data = _mm_mul_ps(data, v.data);
            return *this;
        }
        inline vec& operator*=(const vec<2>& v) {
            x *= v.x;
            y *= v.y;
            return *this;
        }
        inline vec& operator*=(const vec<3>& v) {
            x *= v.x;
            y *= v.y;
            z *= v.z;
            return *this;
        }
        inline vec& operator/=(scalar v) {
            data = _mm_div_ps(data, _mm_set_ps(v, v, v, v));
            return *this;
        }
        inline vec& operator/=(const vec& v) {
            data = _mm_div_ps(data, v.data);
            return *this;
        }
        inline vec& operator/=(const vec<2>& v) {
            x /= v.x;
            y /= v.y;
            return *this;
        }
        inline vec& operator/=(const vec<3>& v) {
            x /= v.x;
            y /= v.y;
            z /= v.z;
            return *this;
        }

        __vec4_declare_operator_2(+)
        __vec4_declare_operator_2(-)
        __vec4_declare_operator_2(*)
        __vec4_declare_operator_2(/)

        inline vec& operator++() {
            ++x;
            ++y;
            ++z;
            ++w;
            return *this;
        }
        inline vec& operator--() {
            --x;
            --y;
            --z;
            --w;
            return *this;
        }
        inline vec operator++(int) {
            const vec t(*this);
            ++*this;
            return t;
        }
        inline vec operator--(int) {
            const vec t(*this);
            ++*this;
            return t;
        }
        inline vec operator+() const {
            return *this;
        }
        inline vec operator-() const {
            return { -x, -y, -z, -w };
        }

        inline bool operator==(const vec& other) const {
            return  _mm_movemask_ps(_mm_cmpeq_ps(data, other.data)) != 0;
        }
        inline bool operator!=(const vec& other) const {
            return  _mm_movemask_ps(_mm_cmpneq_ps(data, other.data)) != 0;
        }

        union {
            contiguous_data<4> data = {};
            struct {
                scalar x, y, z, w;
            };
            struct {
                scalar r, g, b, a;
            };
            struct {
                scalar u, v, s, t;
            };
        };
    };
}

#endif //WHITEGEAR_VEC4_HPP


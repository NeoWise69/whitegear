
/*******************************************************************************
 * Copyright (c) 2023.
 * This file is part of The WhiteGear Studio software property.
 * If you get unexpected access to this file, or part ot whole codebase, you should
 * report this source code leak and delete all copies of source code from all your machines.
 ******************************************************************************/

#ifndef WHITEGEAR_VEC3_HPP
#define WHITEGEAR_VEC3_HPP

#include "vector_base.hpp"
#include "vec2.hpp"

#define __vec3_declare_operator(sign)       \
inline vec& operator sign(scalar v) {       \
    this->x sign v;                         \
    this->y sign v;                         \
    this->z sign v;                         \
    return *this;                           \
}                                           \
inline vec& operator sign(const vec& b) {   \
    this->x sign b.x;                       \
    this->y sign b.y;                       \
    this->z sign b.y;                       \
    return *this;                           \
}                                           \
inline vec& operator sign(const vec<2>& b) {\
    this->x sign b.x;                       \
    this->y sign b.y;                       \
    return *this;                           \
}

#define __vec3_declare_operator_2(sign)     \
inline vec operator sign(scalar v) const {        \
    return vec(*this) sign##= v;            \
}                                           \
inline vec operator sign(const vec& v) const {    \
    return vec(*this) sign##= v;            \
}                                           \
inline vec operator sign(const vec<2>& v) const { \
    return vec(*this) sign##= v;            \
}                                           \

namespace wg {
    template<>
    struct vec<3> {
        inline vec() = default;
        inline ~vec() = default;

        inline vec(const vec&) = default;
        inline vec& operator=(const vec&) = default;
        inline vec(vec&&) noexcept = default;
        inline vec& operator=(vec&&) noexcept = default;

        inline constexpr explicit vec(scalar _x) : x(_x), y(_x), z(_x) {}
        inline constexpr vec(scalar _x, scalar _y, scalar _z) : x(_x), y(_y), z(_z) {}
        inline constexpr vec(const vec<2>& _xy, scalar _z) : x(_xy.x), y(_xy.y), z(_z) {}
        inline constexpr vec(scalar _x, const vec<2>& _yz) : x(_x), y(_yz.x), z(_yz.y) {}

        inline scalar& operator[](int i) { return (&x)[i]; }
        inline const scalar& operator[](int i) const { return (&x)[i]; }

        __vec3_declare_operator(+=)
        __vec3_declare_operator(-=)
        __vec3_declare_operator(*=)
        __vec3_declare_operator(/=)

        __vec3_declare_operator_2(+)
        __vec3_declare_operator_2(-)
        __vec3_declare_operator_2(*)
        __vec3_declare_operator_2(/)

        inline vec& operator++() {
            ++x;
            ++y;
            ++z;
            return *this;
        }
        inline vec& operator--() {
            --x;
            --y;
            --z;
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
        inline constexpr vec operator+() const {
            return *this;
        }
        inline constexpr vec operator-() const {
            return { -x, -y, -z };
        }

        inline bool operator==(const vec& other) const {
            return  equal(x, other.x)
                    &&      equal(y, other.y)
                    &&      equal(z, other.z);
        }
        inline bool operator!=(const vec& other) const {
            return  nequal(x, other.x)
                    ||      nequal(y, other.y)
                    ||      nequal(z, other.z);
        }

        inline constexpr vec<2> xy() const { return {x, y}; }
        inline constexpr vec<2> yz() const { return {y, z}; }

        union {
            contiguous_data<3> data = {};
            struct {
                scalar x, y, z;
            };
            struct {
                scalar r, g, b;
            };
            struct {
                scalar u, v, s;
            };
        };
    };
}

#endif //WHITEGEAR_VEC3_HPP

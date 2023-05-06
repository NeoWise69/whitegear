
/*******************************************************************************
 * Copyright (c) 2023.
 * This file is part of The WhiteGear Studio software property.
 * If you get unexpected access to this file, or part ot whole codebase, you should
 * report this source code leak and delete all copies of source code from all your machines.
 ******************************************************************************/

#ifndef WHITEGEAR_VEC2_HPP
#define WHITEGEAR_VEC2_HPP

#include "vector_base.hpp"

#define __vec2_declare_operator(sign)       \
inline vec& operator sign(scalar v) {       \
    this->x sign v;                         \
    this->y sign v;                         \
    return *this;                           \
}                                           \
inline vec& operator sign(const vec& b) {   \
    this->x sign b.x;                       \
    this->y sign b.y;                       \
    return *this;                           \
}

#define __vec2_declare_operator_2(sign)     \
inline vec operator sign(scalar v) const {        \
    return vec(*this) sign##= v;              \
}                                           \
inline vec operator sign(const vec& v) const {    \
    return vec(*this) sign##= v;              \
}                                           \

namespace wg {
    template<>
    struct vec<2> {
        inline vec() = default;
        inline ~vec() = default;

        inline vec(const vec&) = default;
        inline vec& operator=(const vec&) = default;
        inline vec(vec&&) noexcept = default;
        inline vec& operator=(vec&&) noexcept = default;

        inline constexpr explicit vec(scalar _x) : x(_x), y(_x) {}
        inline constexpr vec(scalar _x, scalar _y) : x(_x), y(_y) {}

        inline scalar& operator[](int i) { return (&x)[i]; }
        inline const scalar& operator[](int i) const { return (&x)[i]; }

        __vec2_declare_operator(+=)
        __vec2_declare_operator(-=)
        __vec2_declare_operator(*=)
        __vec2_declare_operator(/=)

        __vec2_declare_operator_2(+)
        __vec2_declare_operator_2(-)
        __vec2_declare_operator_2(*)
        __vec2_declare_operator_2(/)

        inline vec& operator++() {
            ++x;
            ++y;
            return *this;
        }
        inline vec& operator--() {
            --x;
            --y;
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
            return { -x, -y };
        }

        inline bool operator==(const vec& other) const {
            return  equal(x, other.x)
            &&      equal(y, other.y);
        }
        inline bool operator!=(const vec& other) const {
            return  nequal(x, other.x)
            ||      nequal(y, other.y);
        }

        union {
            contiguous_data<2> data = {};
            struct {
                scalar x, y;
            };
            struct {
                scalar r, g;
            };
            struct {
                scalar u, v;
            };
        };
    };
}

#endif //WHITEGEAR_VEC2_HPP


/*******************************************************************************
 * Copyright (c) 2023.
 * This file is part of The WhiteGear Studio software property.
 * If you get unexpected access to this file, or part ot whole codebase, you should
 * report this source code leak and delete all copies of source code from all your machines.
 ******************************************************************************/

#ifndef WHITEGEAR_VEC_HPP
#define WHITEGEAR_VEC_HPP

#include "scalar_base.hpp"
#include "vec2.hpp"
#include "vec3.hpp"
#include "vec4.hpp"

namespace wg {

    namespace details {
        template<template<size_t N> class vec, size_t N>
        struct caller1 {};
        template<template<size_t N> class vec, size_t N>
        struct caller2 {};
        template<template<size_t N> class vec, size_t N>
        struct caller3 {};

        template<template<size_t N> class vec>
        struct caller1<vec, 2> {
            static inline vec<2> call(scalar(*Fn)(scalar x), const vec<2>& v) {
                return { Fn(v.x), Fn(v.y) };
            }
        };
        template<template<size_t N> class vec>
        struct caller1<vec, 3> {
            static inline vec<3> call(scalar(*Fn)(scalar x), const vec<3>& v) {
                return { Fn(v.x), Fn(v.y), Fn(v.z) };
            }
        };
        template<template<size_t N> class vec>
        struct caller1<vec, 4> {
            static inline vec<4> call(scalar(*Fn)(scalar x), const vec<4>& v) {
                return { Fn(v.x), Fn(v.y), Fn(v.z), Fn(v.w) };
            }
        };

        template<template<size_t N> class vec>
        struct caller2<vec, 2> {
            static inline vec<2> call(scalar(*Fn)(scalar x, scalar y), const vec<2>& a, const vec<2>& b) {
                return { Fn(a.x, b.x), Fn(a.y, b.y) };
            }
        };
        template<template<size_t N> class vec>
        struct caller2<vec, 3> {
            static inline vec<3> call(scalar(*Fn)(scalar x, scalar y), const vec<3>& a, const vec<3>& b) {
                return { Fn(a.x, b.x), Fn(a.y, b.y), Fn(a.z, b.z) };
            }
        };
        template<template<size_t N> class vec>
        struct caller2<vec, 4> {
            static inline vec<4> call(scalar(*Fn)(scalar x, scalar y), const vec<4>& a, const vec<4>& b) {
                return { Fn(a.x, b.x), Fn(a.y, b.y), Fn(a.z, b.z), Fn(a.w, b.w) };
            }
        };

        template<template<size_t N> class vec>
        struct caller3<vec, 2> {
            static inline vec<2> call(scalar(*Fn)(scalar x, scalar y, scalar z), const vec<2>& a, const vec<2>& b, const vec<2>& c) {
                return { Fn(a.x, b.x, c.x), Fn(a.y, b.y, c.y) };
            }
        };
        template<template<size_t N> class vec>
        struct caller3<vec, 3> {
            static inline vec<3> call(scalar(*Fn)(scalar x, scalar y, scalar z), const vec<3>& a, const vec<3>& b, const vec<3>& c) {
                return { Fn(a.x, b.x, c.x), Fn(a.y, b.y, c.y), Fn(a.z, b.z, c.z) };
            }
        };
        template<template<size_t N> class vec>
        struct caller3<vec, 4> {
            static inline vec<4> call(scalar(*Fn)(scalar x, scalar y, scalar z), const vec<4>& a, const vec<4>& b, const vec<4>& c) {
                return { Fn(a.x, b.x, c.x), Fn(a.y, b.y, c.y), Fn(a.z, b.z, c.z), Fn(a.w, b.w, c.w) };
            }
        };
    }

    inline vec2 floor(const vec2& v) { return details::caller1<vec, 2>::call(std::floor, v); }
    inline vec3 floor(const vec3& v) { return details::caller1<vec, 3>::call(std::floor, v); }
    inline vec4 floor(const vec4& v) { return details::caller1<vec, 4>::call(std::floor, v); }
    inline vec2 sin(const vec2& v) { return details::caller1<vec, 2>::call(std::sin, v); }
    inline vec3 sin(const vec3& v) { return details::caller1<vec, 3>::call(std::sin, v); }
    inline vec4 sin(const vec4& v) { return details::caller1<vec, 4>::call(std::sin, v); }
    inline vec2 asin(const vec2& v) { return details::caller1<vec, 2>::call(std::asin, v); }
    inline vec3 asin(const vec3& v) { return details::caller1<vec, 3>::call(std::asin, v); }
    inline vec4 asin(const vec4& v) { return details::caller1<vec, 4>::call(std::asin, v); }
    inline vec2 sinh(const vec2& v) { return details::caller1<vec, 2>::call(std::sinh, v); }
    inline vec3 sinh(const vec3& v) { return details::caller1<vec, 3>::call(std::sinh, v); }
    inline vec4 sinh(const vec4& v) { return details::caller1<vec, 4>::call(std::sinh, v); }
    inline vec2 asinh(const vec2& v) { return details::caller1<vec, 2>::call(std::asinh, v); }
    inline vec3 asinh(const vec3& v) { return details::caller1<vec, 3>::call(std::asinh, v); }
    inline vec4 asinh(const vec4& v) { return details::caller1<vec, 4>::call(std::asinh, v); }
    inline vec2 cos(const vec2& v) { return details::caller1<vec, 2>::call(std::cos, v); }
    inline vec3 cos(const vec3& v) { return details::caller1<vec, 3>::call(std::cos, v); }
    inline vec4 cos(const vec4& v) { return details::caller1<vec, 4>::call(std::cos, v); }
    inline vec2 acos(const vec2& v) { return details::caller1<vec, 2>::call(std::acos, v); }
    inline vec3 acos(const vec3& v) { return details::caller1<vec, 3>::call(std::acos, v); }
    inline vec4 acos(const vec4& v) { return details::caller1<vec, 4>::call(std::acos, v); }
    inline vec2 cosh(const vec2& v) { return details::caller1<vec, 2>::call(std::cosh, v); }
    inline vec3 cosh(const vec3& v) { return details::caller1<vec, 3>::call(std::cosh, v); }
    inline vec4 cosh(const vec4& v) { return details::caller1<vec, 4>::call(std::cosh, v); }
    inline vec2 acosh(const vec2& v) { return details::caller1<vec, 2>::call(std::acosh, v); }
    inline vec3 acosh(const vec3& v) { return details::caller1<vec, 3>::call(std::acosh, v); }
    inline vec4 acosh(const vec4& v) { return details::caller1<vec, 4>::call(std::acosh, v); }
    inline vec2 tan(const vec2& v) { return details::caller1<vec, 2>::call(std::tan, v); }
    inline vec3 tan(const vec3& v) { return details::caller1<vec, 3>::call(std::tan, v); }
    inline vec4 tan(const vec4& v) { return details::caller1<vec, 4>::call(std::tan, v); }
    inline vec2 atan(const vec2& v) { return details::caller1<vec, 2>::call(std::atan, v); }
    inline vec3 atan(const vec3& v) { return details::caller1<vec, 3>::call(std::atan, v); }
    inline vec4 atan(const vec4& v) { return details::caller1<vec, 4>::call(std::atan, v); }
    inline vec2 tanh(const vec2& v) { return details::caller1<vec, 2>::call(std::tanh, v); }
    inline vec3 tanh(const vec3& v) { return details::caller1<vec, 3>::call(std::tanh, v); }
    inline vec4 tanh(const vec4& v) { return details::caller1<vec, 4>::call(std::tanh, v); }
    inline vec2 atanh(const vec2& v) { return details::caller1<vec, 2>::call(std::atanh, v); }
    inline vec3 atanh(const vec3& v) { return details::caller1<vec, 3>::call(std::atanh, v); }
    inline vec4 atanh(const vec4& v) { return details::caller1<vec, 4>::call(std::atanh, v); }
    inline vec2 ceil(const vec2& v) { return details::caller1<vec, 2>::call(std::ceil, v); }
    inline vec3 ceil(const vec3& v) { return details::caller1<vec, 3>::call(std::ceil, v); }
    inline vec4 ceil(const vec4& v) { return details::caller1<vec, 4>::call(std::ceil, v); }
    inline vec2 abs(const vec2& v) { return details::caller1<vec, 2>::call(std::abs, v); }
    inline vec3 abs(const vec3& v) { return details::caller1<vec, 3>::call(std::abs, v); }
    inline vec4 abs(const vec4& v) { return details::caller1<vec, 4>::call(std::abs, v); }
    inline vec2 sqrt(const vec2& v) { return details::caller1<vec, 2>::call(wg::sqrt, v); }
    inline vec3 sqrt(const vec3& v) { return details::caller1<vec, 3>::call(wg::sqrt, v); }
    inline vec4 sqrt(const vec4& v) { return details::caller1<vec, 4>::call(wg::sqrt, v); }
    inline vec2 fract(const vec2& v) { return details::caller1<vec, 2>::call(wg::fract, v); }
    inline vec3 fract(const vec3& v) { return details::caller1<vec, 3>::call(wg::fract, v); }
    inline vec4 fract(const vec4& v) { return details::caller1<vec, 4>::call(wg::fract, v); }
    inline vec2 fmod(const vec2& x, const vec2& y) { return details::caller2<vec, 2>::call(std::fmod, x, y); }
    inline vec3 fmod(const vec3& x, const vec3& y) { return details::caller2<vec, 3>::call(std::fmod, x, y); }
    inline vec4 fmod(const vec4& x, const vec4& y) { return details::caller2<vec, 4>::call(std::fmod, x, y); }
    inline vec2 fmin(const vec2& x, const vec2& y) { return details::caller2<vec, 2>::call(wg::fmin, x, y); }
    inline vec3 fmin(const vec3& x, const vec3& y) { return details::caller2<vec, 3>::call(wg::fmin, x, y); }
    inline vec4 fmin(const vec4& x, const vec4& y) { return details::caller2<vec, 4>::call(wg::fmin, x, y); }
    inline vec2 max(const vec2& x, const vec2& y) { return details::caller2<vec, 2>::call(wg::max, x, y); }
    inline vec3 max(const vec3& x, const vec3& y) { return details::caller2<vec, 3>::call(wg::max, x, y); }
    inline vec4 max(const vec4& x, const vec4& y) { return details::caller2<vec, 4>::call(wg::max, x, y); }
    inline vec2 clamp(const vec2& x, const vec2& _min, const vec2& _max) { return details::caller3<vec, 2>::call(wg::clamp, x, _min, _max); }
    inline vec3 clamp(const vec3& x, const vec3& _min, const vec3& _max) { return details::caller3<vec, 3>::call(wg::clamp, x, _min, _max); }
    inline vec4 clamp(const vec4& x, const vec4& _min, const vec4& _max) { return details::caller3<vec, 4>::call(wg::clamp, x, _min, _max); }
    inline vec2 mix(const vec2& x, const vec2& y, const vec2& a) { return details::caller3<vec, 2>::call(wg::mix, x, y, a); }
    inline vec3 mix(const vec3& x, const vec3& y, const vec3& a) { return details::caller3<vec, 3>::call(wg::mix, x, y, a); }
    inline vec4 mix(const vec4& x, const vec4& y, const vec4& a) { return details::caller3<vec, 4>::call(wg::mix, x, y, a); }
    inline vec2 lerp(const vec2& x, const vec2& y, const vec2& a) { return details::caller3<vec, 2>::call(wg::lerp, x, y, a); }
    inline vec3 lerp(const vec3& x, const vec3& y, const vec3& a) { return details::caller3<vec, 3>::call(wg::lerp, x, y, a); }
    inline vec4 lerp(const vec4& x, const vec4& y, const vec4& a) { return details::caller3<vec, 4>::call(wg::lerp, x, y, a); }
    inline vec2 slerp(const vec2& x, const vec2& y, const vec2& a) { return details::caller3<vec, 2>::call(wg::slerp, x, y, a); }
    inline vec3 slerp(const vec3& x, const vec3& y, const vec3& a) { return details::caller3<vec, 3>::call(wg::slerp, x, y, a); }
    inline vec4 slerp(const vec4& x, const vec4& y, const vec4& a) { return details::caller3<vec, 4>::call(wg::slerp, x, y, a); }
    inline scalar dot(const vec2& a, const vec2& b) { const auto t(a * b); return t.x + t.y; }
    inline scalar dot(const vec3& a, const vec3& b) { const auto t(a * b); return t.x + t.y + t.z; }
    inline scalar dot(const vec4& a, const vec4& b) { const auto t(a * b); return t.x + t.y + t.z + t.w; }
    inline vec3 cross(const vec3& x, const vec3& y) { return {x.y * y.z - y.y * x.z,x.z * y.x - y.z * x.x,x.x * y.y - y.x * x.y}; }

    template<size_t N>
    inline scalar length(const vec<N>& v) { return sqrt(dot(v, v)); }
    template<size_t N>
    inline scalar distance(const vec<N>& a, const vec<N>& b) { return length(b - a); }
    template<size_t N>
    inline vec<N> rsqrt(const vec<N>& x) { return details::caller1<vec, N>::call(wg::rsqrt, x); }
}

#endif //WHITEGEAR_VEC_HPP

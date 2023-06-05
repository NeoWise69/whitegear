
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
        template<template<uint N> class vec, uint N>
        struct caller1 {};
        template<template<uint N> class vec, uint N>
        struct caller2 {};
        template<template<uint N> class vec, uint N>
        struct caller3 {};

        template<template<uint N> class vec>
        struct caller1<vec, 2> {
            static inline vec<2> call(scalar(*Fn)(scalar x), const vec<2>& v) {
                return { Fn(v.x), Fn(v.y) };
            }
        };
        template<template<uint N> class vec>
        struct caller1<vec, 3> {
            static inline vec<3> call(scalar(*Fn)(scalar x), const vec<3>& v) {
                return { Fn(v.x), Fn(v.y), Fn(v.z) };
            }
        };
        template<template<uint N> class vec>
        struct caller1<vec, 4> {
            static inline vec<4> call(scalar(*Fn)(scalar x), const vec<4>& v) {
                return { Fn(v.x), Fn(v.y), Fn(v.z), Fn(v.w) };
            }
        };

        template<template<uint N> class vec>
        struct caller2<vec, 2> {
            static inline vec<2> call(scalar(*Fn)(scalar x, scalar y), const vec<2>& a, const vec<2>& b) {
                return { Fn(a.x, b.x), Fn(a.y, b.y) };
            }
        };
        template<template<uint N> class vec>
        struct caller2<vec, 3> {
            static inline vec<3> call(scalar(*Fn)(scalar x, scalar y), const vec<3>& a, const vec<3>& b) {
                return { Fn(a.x, b.x), Fn(a.y, b.y), Fn(a.z, b.z) };
            }
        };
        template<template<uint N> class vec>
        struct caller2<vec, 4> {
            static inline vec<4> call(scalar(*Fn)(scalar x, scalar y), const vec<4>& a, const vec<4>& b) {
                return { Fn(a.x, b.x), Fn(a.y, b.y), Fn(a.z, b.z), Fn(a.w, b.w) };
            }
        };

        template<template<uint N> class vec>
        struct caller3<vec, 2> {
            static inline vec<2> call(scalar(*Fn)(scalar x, scalar y, scalar z), const vec<2>& a, const vec<2>& b, const vec<2>& c) {
                return { Fn(a.x, b.x, c.x), Fn(a.y, b.y, c.y) };
            }
        };
        template<template<uint N> class vec>
        struct caller3<vec, 3> {
            static inline vec<3> call(scalar(*Fn)(scalar x, scalar y, scalar z), const vec<3>& a, const vec<3>& b, const vec<3>& c) {
                return { Fn(a.x, b.x, c.x), Fn(a.y, b.y, c.y), Fn(a.z, b.z, c.z) };
            }
        };
        template<template<uint N> class vec>
        struct caller3<vec, 4> {
            static inline vec<4> call(scalar(*Fn)(scalar x, scalar y, scalar z), const vec<4>& a, const vec<4>& b, const vec<4>& c) {
                return { Fn(a.x, b.x, c.x), Fn(a.y, b.y, c.y), Fn(a.z, b.z, c.z), Fn(a.w, b.w, c.w) };
            }
        };
    }
    /**
     * Find the nearest integer less than or equal to the parameter.
     */
    inline vec2 floor(const vec2& v) { return details::caller1<vec, 2>::call(std::floor, v); }
    /**
     * Find the nearest integer less than or equal to the parameter.
     */
    inline vec3 floor(const vec3& v) { return details::caller1<vec, 3>::call(std::floor, v); }
    /**
     * Find the nearest integer less than or equal to the parameter.
     */
    inline vec4 floor(const vec4& v) { return details::caller1<vec, 4>::call(std::floor, v); }
    /**
     * Return the sine function of vector.
     */
    inline vec2 sin(const vec2& v) { return details::caller1<vec, 2>::call(std::sin, v); }
    /**
     * Return the sine function of vector.
     */
    inline vec3 sin(const vec3& v) { return details::caller1<vec, 3>::call(std::sin, v); }
    /**
     * Return the sine function of vector.
     */
    inline vec4 sin(const vec4& v) { return details::caller1<vec, 4>::call(std::sin, v); }
    /**
     * Return the arcsine function of vector.
     */
    inline vec2 asin(const vec2& v) { return details::caller1<vec, 2>::call(std::asin, v); }
    /**
     * Return the arcsine function of vector.
     */
    inline vec3 asin(const vec3& v) { return details::caller1<vec, 3>::call(std::asin, v); }
    /**
     * Return the arcsine function of vector.
     */
    inline vec4 asin(const vec4& v) { return details::caller1<vec, 4>::call(std::asin, v); }
    /**
     * Return the hyperbolic sine function of vector.
     */
    inline vec2 sinh(const vec2& v) { return details::caller1<vec, 2>::call(std::sinh, v); }
    /**
     * Return the hyperbolic sine function of vector.
     */
    inline vec3 sinh(const vec3& v) { return details::caller1<vec, 3>::call(std::sinh, v); }
    /**
     * Return the hyperbolic sine function of vector.
     */
    inline vec4 sinh(const vec4& v) { return details::caller1<vec, 4>::call(std::sinh, v); }
    /**
     * Return the arc hyperbolic sine function of vector.
     */
    inline vec2 asinh(const vec2& v) { return details::caller1<vec, 2>::call(std::asinh, v); }
    /**
     * Return the arc hyperbolic sine function of vector.
     */
    inline vec3 asinh(const vec3& v) { return details::caller1<vec, 3>::call(std::asinh, v); }
    /**
     * Return the arc hyperbolic sine function of vector.
     */
    inline vec4 asinh(const vec4& v) { return details::caller1<vec, 4>::call(std::asinh, v); }
    /**
     * Return the cosine function of vector.
     */
    inline vec2 cos(const vec2& v) { return details::caller1<vec, 2>::call(std::cos, v); }
    /**
     * Return the cosine function of vector.
     */
    inline vec3 cos(const vec3& v) { return details::caller1<vec, 3>::call(std::cos, v); }
    /**
     * Return the cosine function of vector.
     */
    inline vec4 cos(const vec4& v) { return details::caller1<vec, 4>::call(std::cos, v); }
    /**
     * Return the arc cosine function of vector.
     */
    inline vec2 acos(const vec2& v) { return details::caller1<vec, 2>::call(std::acos, v); }
    /**
     * Return the arc cosine function of vector.
     */
    inline vec3 acos(const vec3& v) { return details::caller1<vec, 3>::call(std::acos, v); }
    /**
     * Return the arc cosine function of vector.
     */
    inline vec4 acos(const vec4& v) { return details::caller1<vec, 4>::call(std::acos, v); }
    /**
     * Return the hyperbolic cosine function of vector.
     */
    inline vec2 cosh(const vec2& v) { return details::caller1<vec, 2>::call(std::cosh, v); }
    /**
     * Return the hyperbolic cosine function of vector.
     */
    inline vec3 cosh(const vec3& v) { return details::caller1<vec, 3>::call(std::cosh, v); }
    /**
     * Return the hyperbolic cosine function of vector.
     */
    inline vec4 cosh(const vec4& v) { return details::caller1<vec, 4>::call(std::cosh, v); }
    /**
     * Return the arc hyperbolic cosine function of vector.
     */
    inline vec2 acosh(const vec2& v) { return details::caller1<vec, 2>::call(std::acosh, v); }
    /**
     * Return the arc hyperbolic cosine function of vector.
     */
    inline vec3 acosh(const vec3& v) { return details::caller1<vec, 3>::call(std::acosh, v); }
    /**
     * Return the arc hyperbolic cosine function of vector.
     */
    inline vec4 acosh(const vec4& v) { return details::caller1<vec, 4>::call(std::acosh, v); }
    /**
     * Return the tangent function of vector.
     */
    inline vec2 tan(const vec2& v) { return details::caller1<vec, 2>::call(std::tan, v); }
    /**
     * Return the tangent function of vector.
     */
    inline vec3 tan(const vec3& v) { return details::caller1<vec, 3>::call(std::tan, v); }
    /**
     * Return the tangent function of vector.
     */
    inline vec4 tan(const vec4& v) { return details::caller1<vec, 4>::call(std::tan, v); }
    /**
     * Return the arc tangent function of vector.
     */
    inline vec2 atan(const vec2& v) { return details::caller1<vec, 2>::call(std::atan, v); }
    /**
     * Return the arc tangent function of vector.
     */
    inline vec3 atan(const vec3& v) { return details::caller1<vec, 3>::call(std::atan, v); }
    /**
     * Return the arc tangent function of vector.
     */
    inline vec4 atan(const vec4& v) { return details::caller1<vec, 4>::call(std::atan, v); }
    /**
     * Return the hyperbolic tangent function of vector.
     */
    inline vec2 tanh(const vec2& v) { return details::caller1<vec, 2>::call(std::tanh, v); }
    /**
     * Return the hyperbolic tangent function of vector.
     */
    inline vec3 tanh(const vec3& v) { return details::caller1<vec, 3>::call(std::tanh, v); }
    /**
     * Return the hyperbolic tangent function of vector.
     */
    inline vec4 tanh(const vec4& v) { return details::caller1<vec, 4>::call(std::tanh, v); }
    /**
     * Return the arc hyperbolic tangent function of vector.
     */
    inline vec2 atanh(const vec2& v) { return details::caller1<vec, 2>::call(std::atanh, v); }
    /**
     * Return the arc hyperbolic tangent function of vector.
     */
    inline vec3 atanh(const vec3& v) { return details::caller1<vec, 3>::call(std::atanh, v); }
    /**
     * Return the arc hyperbolic tangent function of vector.
     */
    inline vec4 atanh(const vec4& v) { return details::caller1<vec, 4>::call(std::atanh, v); }
    /**
     * Find the nearest integer that is greater than or equal to the vector.
     */
    inline vec2 ceil(const vec2& v) { return details::caller1<vec, 2>::call(std::ceil, v); }
    /**
     * Find the nearest integer that is greater than or equal to the vector.
     */
    inline vec3 ceil(const vec3& v) { return details::caller1<vec, 3>::call(std::ceil, v); }
    /**
     * Find the nearest integer that is greater than or equal to the vector.
     */
    inline vec4 ceil(const vec4& v) { return details::caller1<vec, 4>::call(std::ceil, v); }
    /**
     * Returns the absolute value of a vector.
     */
    inline vec2 abs(const vec2& v) { return details::caller1<vec, 2>::call(std::abs, v); }
    /**
     * Returns the absolute value of a vector.
     */
    inline vec3 abs(const vec3& v) { return details::caller1<vec, 3>::call(std::abs, v); }
    /**
     * Returns the absolute value of a vector.
     */
    inline vec4 abs(const vec4& v) { return details::caller1<vec, 4>::call(std::abs, v); }
    /**
     * Returns the square root of the vector.
     */
    inline vec2 sqrt(const vec2& v) { return details::caller1<vec, 2>::call(wg::sqrt, v); }
    /**
     * Returns the square root of the vector.
     */
    inline vec3 sqrt(const vec3& v) { return details::caller1<vec, 3>::call(wg::sqrt, v); }
    /**
     * Returns the square root of the vector.
     */
    inline vec4 sqrt(const vec4& v) { return details::caller1<vec, 4>::call(wg::sqrt, v); }
    /**
     * Compute the frictional part of the vector.
     */
    inline vec2 fract(const vec2& v) { return details::caller1<vec, 2>::call(wg::fract, v); }
    /**
     * Compute the frictional part of the vector.
     */
    inline vec3 fract(const vec3& v) { return details::caller1<vec, 3>::call(wg::fract, v); }
    /**
     * Compute the frictional part of the vector.
     */
    inline vec4 fract(const vec4& v) { return details::caller1<vec, 4>::call(wg::fract, v); }
    /**
     *
     */
    inline vec2 fmod(const vec2& x, const vec2& y) { return details::caller2<vec, 2>::call(std::fmod, x, y); }
    /**
     *
     */
    inline vec3 fmod(const vec3& x, const vec3& y) { return details::caller2<vec, 3>::call(std::fmod, x, y); }
    /**
     *
     */
    inline vec4 fmod(const vec4& x, const vec4& y) { return details::caller2<vec, 4>::call(std::fmod, x, y); }
    /**
     * Returns minimal value from between two further vectors.
     */
    inline vec2 fmin(const vec2& x, const vec2& y) { return details::caller2<vec, 2>::call(wg::fmin, x, y); }
    /**
     * Returns minimal value from between two further vectors.
     */
    inline vec3 fmin(const vec3& x, const vec3& y) { return details::caller2<vec, 3>::call(wg::fmin, x, y); }
    /**
     * Returns minimal value from between two further vectors.
     */
    inline vec4 fmin(const vec4& x, const vec4& y) { return details::caller2<vec, 4>::call(wg::fmin, x, y); }
    /**
     * Returns maximum value from between two further vectors.
     */
    inline vec2 fmax(const vec2& x, const vec2& y) { return details::caller2<vec, 2>::call(wg::fmax, x, y); }
    /**
     * Returns maximum value from between two further vectors.
     */
    inline vec3 fmax(const vec3& x, const vec3& y) { return details::caller2<vec, 3>::call(wg::fmax, x, y); }
    /**
     * Returns maximum value from between two further vectors.
     */
    inline vec4 fmax(const vec4& x, const vec4& y) { return details::caller2<vec, 4>::call(wg::fmax, x, y); }
    /**
     * Constrain a value to lie between two further.
     */
    inline vec2 clamp(const vec2& x, const vec2& _min, const vec2& _max) { return details::caller3<vec, 2>::call(wg::clamp, x, _min, _max); }
    /**
     * Constrain a value to lie between two further.
     */
    inline vec3 clamp(const vec3& x, const vec3& _min, const vec3& _max) { return details::caller3<vec, 3>::call(wg::clamp, x, _min, _max); }
    /**
     * Constrain a value to lie between two further.
     */
    inline vec4 clamp(const vec4& x, const vec4& _min, const vec4& _max) { return details::caller3<vec, 4>::call(wg::clamp, x, _min, _max); }
    /**
     * Linearly interpolate between two vectors.
     */
    inline vec2 mix(const vec2& x, const vec2& y, const vec2& a) { return details::caller3<vec, 2>::call(wg::mix, x, y, a); }
    /**
     * Linearly interpolate between two vectors.
     */
    inline vec3 mix(const vec3& x, const vec3& y, const vec3& a) { return details::caller3<vec, 3>::call(wg::mix, x, y, a); }
    /**
     * Linearly interpolate between two vectors.
     */
    inline vec4 mix(const vec4& x, const vec4& y, const vec4& a) { return details::caller3<vec, 4>::call(wg::mix, x, y, a); }
    /**
     * Linearly interpolate between two vectors.
     */
    inline vec2 lerp(const vec2& x, const vec2& y, const vec2& a) { return details::caller3<vec, 2>::call(wg::lerp, x, y, a); }
    /**
     * Linearly interpolate between two vectors.
     */
    inline vec3 lerp(const vec3& x, const vec3& y, const vec3& a) { return details::caller3<vec, 3>::call(wg::lerp, x, y, a); }
    /**
     * Linearly interpolate between two vectors.
     */
    inline vec4 lerp(const vec4& x, const vec4& y, const vec4& a) { return details::caller3<vec, 4>::call(wg::lerp, x, y, a); }
    /**
     * Calculate the dot product of two vectors.
     */
    inline scalar dot(const vec2& a, const vec2& b) { const auto t(a * b); return t.x + t.y; }
    /**
     * Calculate the dot product of two vectors.
     */
    inline scalar dot(const vec3& a, const vec3& b) { const auto t(a * b); return t.x + t.y + t.z; }
    /**
     * Calculate the dot product of two vectors.
     */
    inline scalar dot(const vec4& a, const vec4& b) { const auto t(a * b); return t.x + t.y + t.z + t.w; }
    /**
     * Calculate the cross product of two vectors.
     */
    inline vec3 cross(const vec3& x, const vec3& y) { return {x.y * y.z - y.y * x.z,x.z * y.x - y.z * x.x,x.x * y.y - y.x * x.y}; }
    /**
     * Spherically interpolate between two vectors.
     */
    inline vec2 slerp(const vec2& x, const vec2& y, const vec2& a) { return details::caller3<vec, 2>::call(wg::slerp, x, y, a); }
    /**
     * Spherically interpolate between two vectors.
     */
    inline vec3 slerp(const vec3& x, const vec3& y, const vec3& a) {
        const auto CosAlpha = dot(x, y);
        const auto Alpha = acos(CosAlpha);
        const auto SinAlpha = sin(Alpha);
        const auto t1 = sin((vec3(1) - a) * Alpha) / SinAlpha;
        const auto t2 = sin(a * Alpha) / SinAlpha;
        return x * t1 + y * t2;
    }
    /**
     * Spherically interpolate between two vectors.
     */
    inline vec4 slerp(const vec4& x, const vec4& y, const vec4& a) { return details::caller3<vec, 4>::call(wg::slerp, x, y, a); }
    /**
     * Rotate a three dimensional vector around the X axis.
     */
    inline vec3 rotate_x(const vec3& v, scalar a) {
        vec3 Result(v);
        const auto Cos(cos(a));
        const auto Sin(sin(a));
        Result.y = v.y * Cos - v.z * Sin;
        Result.z = v.y * Sin + v.z * Cos;
        return Result;
    }
    /**
    * Rotate a three dimensional vector around the Y axis.
    */
    inline vec3 rotate_y(const vec3& v, scalar a) {
        vec3 Result(v);
        const auto Cos(cos(a));
        const auto Sin(sin(a));
        Result.x =  v.x * Cos + v.z * Sin;
        Result.z = -v.x * Sin + v.z * Cos;
        return Result;
    }
    /**
    * Rotate a three dimensional vector around the Z axis.
    */
    inline vec3 rotate_z(const vec3& v, scalar a) {
        vec3 Result(v);
        const auto Cos(cos(a));
        const auto Sin(sin(a));
        Result.x = v.x * Cos - v.y * Sin;
        Result.y = v.x * Sin + v.y * Cos;
        return Result;
    }
    /**
    * Rotate a four dimensional vector around the X axis.
    */
    inline vec4 rotate_x(const vec4& v, scalar a) {
        vec4 Result(v);
        const auto Cos(cos(a));
        const auto Sin(sin(a));
        Result.y = v.y * Cos - v.z * Sin;
        Result.z = v.y * Sin + v.z * Cos;
        return Result;
    }
    /**
    * Rotate a four dimensional vector around the Y axis.
    */
    inline vec4 rotate_y(const vec4& v, scalar a) {
        vec4 Result(v);
        const auto Cos(cos(a));
        const auto Sin(sin(a));
        Result.x =  v.x * Cos + v.z * Sin;
        Result.z = -v.x * Sin + v.z * Cos;
        return Result;
    }
    /**
    * Rotate a four dimensional vector around the Z axis.
    */
    inline vec4 rotate_z(const vec4& v, scalar a) {
        vec4 Result(v);
        const auto Cos(cos(a));
        const auto Sin(sin(a));
        Result.x = v.x * Cos - v.y * Sin;
        Result.y = v.x * Sin + v.y * Cos;
        return Result;
    }
    /**
     * Calculate the length of a vector.
     */
    template<uint N>
    inline scalar length(const vec<N>& v) { return sqrt(dot(v, v)); }
    /**
     * Calculate the distance between two points.
     */
    template<uint N>
    inline scalar distance(const vec<N>& a, const vec<N>& b) { return length(b - a); }
    /**
     * Return the inverse of the square root of the vector.
     */
    template<uint N>
    inline vec<N> rsqrt(const vec<N>& x) { return details::caller1<vec, N>::call(wg::rsqrt, x); }
    /**
     * Calculate normalized vector.
     */
    template<uint N>
    inline vec<N> normalize(const vec<N>& x) { return x * rsqrt(dot(x, x)); }
    /**
     * Calculate normalized vector.
     */
    template<uint N>
    inline void normalize(vec<N>* x) { *x *= rsqrt(dot(*x, *x)); }
    /**
     * Checks if vector is zero, and doesn't require any computation.
     */
    template<uint N>
    inline bool is_zero(const vec<N>& x) { return x == vec<N>::zero; }

    template<uint N>
    inline vec<N> degrees(const vec<N>& x) { return details::caller1<vec, N>::call(wg::degrees, x); }

    template<uint N>
    inline vec<N> radians(const vec<N>& x) { return details::caller1<vec, N>::call(wg::radians, x); }
}

#endif //WHITEGEAR_VEC_HPP

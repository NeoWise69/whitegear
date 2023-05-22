
/*******************************************************************************
 * Copyright (c) 2023.
 * This file is part of The WhiteGear Studio software property.
 * If you get unexpected access to this file, or part ot whole codebase, you should
 * report this source code leak and delete all copies of source code from all your machines.
 ******************************************************************************/

#ifndef WHITEGEAR_MAT_HPP
#define WHITEGEAR_MAT_HPP

#include <math/matrix_base.hpp>
#include <math/mat4.hpp>
#include <math/vec.hpp>

namespace wg {
    inline mat4 mix(const mat4& x, const mat4& y, scalar a) {
        return x * (scalar(1) - a) + y * a;
    }
    inline mat4 orthographic(scalar left, scalar right, scalar bottom, scalar top) {
        mat4 res(scalar(1));
        res[0][0] = scalar(2) / (right - left);
        res[1][1] = scalar(2) / (top - bottom);
        res[2][2] = - scalar(1);
        res[3][0] = - (right + left) / (right - left);
        res[3][1] = - (top + bottom) / (top - bottom);
        return res;
    }
    inline mat4 orghographic(scalar left, scalar right, scalar bottom, scalar top, scalar zNear, scalar zFar) {
        mat4 res(scalar(1));
        res[0][0] = scalar(2) / (right - left);
        res[1][1] = scalar(2) / (top - bottom);
        res[2][2] = - scalar(2) / (zFar - zNear);
        res[3][0] = - (right + left) / (right - left);
        res[3][1] = - (top + bottom) / (top - bottom);
        res[3][2] = - (zFar + zNear) / (zFar - zNear);
        return res;
    }
    inline mat4 mat4_frustum(scalar left, scalar right, scalar bottom, scalar top, scalar nearVal, scalar farVal) {
        mat4 res(0);
        res[0][0] = (scalar(2) * nearVal) / (right - left);
        res[1][1] = (scalar(2) * nearVal) / (top - bottom);
        res[2][0] = (right + left) / (right - left);
        res[2][1] = (top + bottom) / (top - bottom);
        res[2][2] = - (farVal + nearVal) / (farVal - nearVal);
        res[2][3] = scalar(-1);
        res[3][2] = - (scalar(2) * farVal * nearVal) / (farVal - nearVal);
        return res;
    }
    inline mat4 perspective(scalar fovy, scalar aspect, scalar zNear, scalar zFar) {
        const auto tanHalfFovy = tan(fovy / scalar(2));

        mat4 res(scalar(0));
        res[0][0] = scalar(1) / (aspect * tanHalfFovy);
        res[1][1] = scalar(1) / (tanHalfFovy);
        res[2][2] = - (zFar + zNear) / (zFar - zNear);
        res[2][3] = - scalar(1);
        res[3][2] = - (scalar(2) * zFar * zNear) / (zFar - zNear);
        return res;
    }
    inline mat4 perspective_fov(scalar fov, scalar width, scalar height, scalar zNear, scalar zFar) {
        const auto rad = fov;
        const auto h = cos(scalar(0.5) * rad) / sin(scalar(0.5) * rad);
        const auto w = h * height / width;

        mat4 res(scalar(0));
        res[0][0] = w;
        res[1][1] = h;
        res[2][2] = - (zFar + zNear) / (zFar - zNear);
        res[2][3] = - scalar(1);
        res[3][2] = - (scalar(2) * zFar * zNear) / (zFar - zNear);
        return res;
    }
    inline mat4 perspective_inf(scalar fovy, scalar aspect, scalar zNear) {
        const auto range = tan(fovy / scalar(2)) * zNear;
        const auto left = -range * aspect;
        const auto right = range * aspect;
        const auto bottom = -range;
        const auto top = range;

        mat4 res(0);
        res[0][0] = (scalar(2) * zNear) / (right - left);
        res[1][1] = (scalar(2) * zNear) / (top - bottom);
        res[2][2] = - scalar(1);
        res[2][3] = - scalar(1);
        res[3][2] = - scalar(2) * zNear;
        return res;
    }
    inline mat4 perspective_inf_v2(scalar fovy, scalar aspect, scalar zNear, scalar eps = constants<scalar>::epsilon) {
        const auto range = tan(fovy / scalar(2)) * zNear;
        const auto left = -range * aspect;
        const auto right = range * aspect;
        const auto bottom = -range;
        const auto top = range;

        mat4 res(0);
        res[0][0] = (scalar(2) * zNear) / (right - left);
        res[1][1] = (scalar(2) * zNear) / (top - bottom);
        res[2][2] = eps - scalar(1);
        res[2][3] = scalar(-1);
        res[3][2] = (eps - scalar(2)) * zNear;
        return res;
    }
    inline mat4 translate(const mat4& m, const vec3& v) {
        mat4 r(m);
        r[3] = m[0] * v[0] + m[1] * v[1] + m[2] * v[2] + m[3];
        return r;
    }
    inline mat4 rotate(const mat4& m, scalar angle, const vec3& v) {
        const auto a = angle;
        const auto c = cos(a);
        const auto s = sin(a);

        const vec3 axis(normalize(v));
        const vec3 temp((vec3(1) - c) * axis);

        mat4 rot;
        rot[0][0] = c + temp[0] * axis[0];
        rot[0][1] = temp[0] * axis[1] + s * axis[2];
        rot[0][2] = temp[0] * axis[2] - s * axis[1];

        rot[1][0] = temp[1] * axis[0] - s * axis[2];
        rot[1][1] = c + temp[1] * axis[1];
        rot[1][2] = temp[1] * axis[2] + s * axis[0];

        rot[2][0] = temp[2] * axis[0] + s * axis[1];
        rot[2][1] = temp[2] * axis[1] - s * axis[0];
        rot[2][2] = c + temp[2] * axis[2];

        mat4 r;
        r[0] = m[0] * rot[0][0] + m[1] * rot[0][1] + m[2] * rot[0][2];
        r[1] = m[0] * rot[1][0] + m[1] * rot[1][1] + m[2] * rot[1][2];
        r[2] = m[0] * rot[2][0] + m[1] * rot[2][1] + m[2] * rot[2][2];
        r[3] = m[3];
        return r;
    }
    inline mat4 scale(const mat4& m, scalar angle, const vec3& v) {
        mat4 r;
        r[0] = m[0] * v[0];
        r[1] = m[1] * v[1];
        r[2] = m[2] * v[2];
        r[3] = m[3];
        return r;
    }
    inline mat4 look_at(const vec3& eye, const vec3& center, const vec3& up) {
        const auto f(normalize(center - eye));
        const auto s(normalize(cross(f, up)));
        const auto u(cross(s, f));
        mat4 res(1);
        res[0][0] = s.x;
        res[1][0] = s.y;
        res[2][0] = s.z;
        res[0][1] = u.x;
        res[1][1] = u.y;
        res[2][1] = u.z;
        res[0][2] =-f.x;
        res[1][2] =-f.y;
        res[2][2] =-f.z;
        res[3][0] =-dot(s, eye);
        res[3][1] =-dot(u, eye);
        res[3][2] = dot(f, eye);
        return res;
    }
}

#endif //WHITEGEAR_MAT_HPP

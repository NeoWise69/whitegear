
/*******************************************************************************
 * Copyright (c) 2023.
 * This file is part of The WhiteGear Studio software property.
 * If you get unexpected access to this file, or part ot whole codebase, you should
 * report this source code leak and delete all copies of source code from all your machines.
 ******************************************************************************/

#ifndef WHITEGEAR_QUATERNION_HPP
#define WHITEGEAR_QUATERNION_HPP

#include <math/scalar_base.hpp>
#include <math/mat4.hpp>
#include <math/vec4.hpp>
#include <math/vec.hpp>

#include <smmintrin.h> // _mm_dp_ps

namespace wg {
    struct quat {

        inline quat() = default;
        inline ~quat() = default;

        inline quat(const quat&) = default;
        inline quat& operator=(const quat&) = default;
        inline quat(quat&&) noexcept = default;
        inline quat& operator=(quat&&) noexcept = default;

        inline quat(scalar s, const vec3& v) : data(_mm_set_ps(v.x, v.y, v.z, s)) {}
        inline quat(scalar _w, scalar _x, scalar _y, scalar _z) : data(_mm_set_ps(_x, _y, _z, _w)) {}
        inline quat(const vec3& eulerAngle) {
            const auto c = cos(eulerAngle * scalar(0.5));
            const auto s = sin(eulerAngle * scalar(0.5));
            w = c.x * c.y * c.z + s.x * s.y * s.z;
            x = s.x * c.y * c.z - c.x * s.y * s.z;
            y = c.x * s.y * c.z + s.x * c.y * s.z;
            z = c.x * c.y * s.z - s.x * s.y * c.z;
        }

        inline quat& operator+=(const quat& q) {
            data.data = _mm_add_ps(data, q.data);
            return *this;
        }
        inline quat& operator-=(const quat& q) {
            data.data = _mm_sub_ps(data, q.data);
            return *this;
        }
        inline quat& operator*=(const quat& r) {
            const quat p(*this);
            const quat q(r);
            w = p.w * q.w - p.x * q.x - p.y * q.y - p.z * q.z;
            x = p.w * q.x + p.x * q.w + p.y * q.z - p.z * q.y;
            y = p.w * q.y + p.y * q.w + p.z * q.x - p.x * q.z;
            z = p.w * q.z + p.z * q.w + p.x * q.y - p.y * q.x;
            return *this;
        }
        inline quat& operator*=(scalar s) {
            data.data = _mm_mul_ps(data, vec4(s).data);
            return *this;
        }
        inline quat& operator/=(scalar s) {
            data.data = _mm_div_ps(data, vec4(s).data);
            return *this;
        }

        inline scalar& operator[](int i) { return (&x)[i]; }
        inline const scalar& operator[](int i) const { return (&x)[i]; }

        union {
            struct {
                scalar w, z, y, x;
            };
            contiguous_data<4> data = {};
        };
    };

    inline quat operator+(const quat& q) {
        return q;
    }
    inline quat operator-(const quat& q) {
        return { -q.w, -q.x, -q.y, -q.z };
    }

    inline quat operator+(const quat& a, const quat& b) {
        return quat(a) += b;
    }
    inline quat operator-(const quat& a, const quat& b) {
        return quat(a) -= b;
    }
    inline quat operator*(const quat& a, const quat& b) {
        return quat(a) *= b;
    }
    inline quat operator*(const quat& q, scalar s) {
        return { q.w * s, q.x * s, q.y * s, q.z * s };
    }
    inline vec3 operator*(const quat& q, const vec3& v) {
        const vec3 qvec(q.x, q.y, q.z);
        const auto uv(cross(qvec, v));
        const auto uuv(cross(qvec, uv));
        return v + ((uv * q.w) + uuv) * scalar(2);
    }
    inline quat operator/(const quat& q, scalar s) {
        return { q.w / s, q.x / s, q.y / s, q.z / s };
    }

    inline bool operator==(const quat& a, const quat& b) {
        return a.x == b.x && a.y == b.y && a.z == b.z && a.w == b.w;
    }
    inline bool operator!=(const quat& a, const quat& b) {
        return !(a.x == b.x && a.y == b.y && a.z == b.z && a.w == b.w);
    }

    /**
     * Returns dot product of two quaternions.
     */
    inline scalar dot(const quat& x, const quat& y) { return _mm_cvtss_f32(_mm_dp_ps(x.data, y.data, 0xff)); }
    /**
     * Returns the norm of a quaternions.
     */
    inline scalar length(const quat& q) { return sqrt(dot(q, q)); }
    /**
     * Returns the normalized quaternion.
     */
    inline quat normalize(const quat& q) {
        const auto len = length(q);
        if(len <= scalar(0)) {
            return {scalar(1), scalar(0), scalar(0), scalar(0)};
        }
        const auto one_over_len = scalar(1) / len;
        return { q.w * one_over_len, q.x * one_over_len, q.y * one_over_len, q.z * one_over_len };
    }
    /**
     * Compute a cross product.
     */
    inline quat cross(const quat& q1, const quat& q2) {
        return {
            q1.w * q2.w - q1.x * q2.x - q1.y * q2.y - q1.z * q2.z,
            q1.w * q2.x + q1.x * q2.w + q1.y * q2.z - q1.z * q2.y,
            q1.w * q2.y + q1.y * q2.w + q1.z * q2.x - q1.x * q2.z,
            q1.w * q2.z + q1.z * q2.w + q1.x * q2.y - q1.y * q2.x
        };
    }
    /**
     * Rotates a quaternion from a vector of 3 components axis and an angle.
     */
    inline quat rotate(const quat& q, scalar angle, const vec3& axis) {
        auto t = axis;

        // Axis of rotation must be normalised
        const auto len = length(t);
        if(abs(len - scalar(1)) > scalar(0.001))
        {
            const auto oneOverLen = scalar(1) / len;
            t.x *= oneOverLen;
            t.y *= oneOverLen;
            t.z *= oneOverLen;
        }

        const auto rad(angle);
        const auto _sin = sin(rad * scalar(0.5));

        return q * quat(cos(rad * scalar(0.5)), t.x * _sin, t.y * _sin, t.z * _sin);
    }
    /**
     * Returns the quaternion rotation angle.
     */
    inline scalar angle(const quat& q) {
        if (abs(q.w) > constants<scalar>::cos_half) {
            return asin(sqrt(q.x * q.x + q.y * q.y + q.z * q.z)) * scalar(2);
        }
        return acos(q.w) * scalar(2);
    }
    /**
     * Returns the q rotation axis.
     */
    inline vec3 axis(const quat& q) {
        const auto tmp1 = scalar(1) - q.w * q.w;
        if(tmp1 <= scalar(0)) {
            return {0, 0, 1};
        }
        const auto tmp2 = scalar(1) / sqrt(tmp1);
        return { q.x * tmp2, q.y * tmp2, q.z * tmp2 };
    }
    /**
     * Build a quaternion from an angle and a normalized axis.
     */
    inline quat angle_axis(scalar angle, const vec3& axis) {
        const auto a(angle);
        const auto s = sin(a * scalar(0.5));

        return { cos(a * scalar(0.5)), axis * s };
    }
}

#endif //WHITEGEAR_QUATERNION_HPP

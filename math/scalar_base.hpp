
/*******************************************************************************
 * Copyright (c) 2023.
 * This file is part of The WhiteGear Studio software property.
 * If you get unexpected access to this file, or part ot whole codebase, you should
 * report this source code leak and delete all copies of source code from all your machines.
 ******************************************************************************/

#ifndef WHITEGEAR_SCALAR_BASE_HPP
#define WHITEGEAR_SCALAR_BASE_HPP

#include <core/typedefs.hpp>

#include <cmath>

namespace wg {
    using std::floor;
    using std::sin;
    using std::asin;
    using std::sinh;
    using std::asinh;
    using std::cos;
    using std::acos;
    using std::cosh;
    using std::acosh;
    using std::tan;
    using std::atan;
    using std::tanh;
    using std::atanh;
    using std::ceil;
    using std::fmod;
    using std::abs;
    using std::sqrt;
    /**
     * Universal scalar data type for math functions.
     */
    using scalar = real;
    /**
     * Constants for defined scalar data type.
     */
    template<class T>
    struct constants {
        /**
         * Truncated PI value.
         */
        static constexpr T pi       = T(3.14159265358979);
        /**
         * PI * 2
         */
        static constexpr T two_pi   = T(6.28318530717958);
        /**
         * PI * 3
         */
        static constexpr T three_pi = T(9.42477796076938);
        /**
         * Minimal meaningful value
         */
        static constexpr T epsilon = T(1.192092896e-07);
        /**
         * Pretty self explained.
         */
        static constexpr T cos_half = T(0.87758256189037);
    };
    /**
     * Returns minimal from given parameters.
     */
    scalar fmin(scalar a, scalar b);
    /**
     * Returns minimal from given parameters.
     */
    scalar fmin(scalar a, scalar b, scalar c);
    /**
     * Returns minimal from given parameters.
     */
    scalar fmin(scalar a, scalar b, scalar c, scalar d);
    /**
     * Returns maximal from given parameters.
     */
    scalar fmax(scalar a, scalar b);
    /**
     * Returns maximal from given parameters.
     */
    scalar fmax(scalar a, scalar b, scalar c);
    /**
     * Returns maximal from given parameters.
     */
    scalar fmax(scalar a, scalar b, scalar c, scalar d);
    /**
     * Truncates scalar value to _min _max bounds.
     */
    scalar clamp(scalar x, scalar _min, scalar _max);
    /**
     * X - FLOOR
     */
    scalar fract(scalar x);
    /**
     * Computes interpolated value between X and Y.
     * @param a Interpolator
     */
    scalar mix(scalar x, scalar y, scalar a);
    /**
     * Computes interpolated value between X and Y.
     * @param a Interpolator
     */
    scalar lerp(scalar x, scalar y, scalar a);
    /**
     * Computes spherical interpolated value between X and Y.
     * @param a Interpolator
     */
    scalar slerp(scalar x, scalar y, scalar a);
    /**
     * Computes good-old evil inverse square root.
     */
    scalar rsqrt(scalar x);
    /**
     * Fast FP comparison.
     */
    bool equal(scalar a, scalar b, scalar eps = constants<scalar>::epsilon);
    /**
     * Fast FP comparison.
     */
    bool nequal(scalar a, scalar b, scalar eps = constants<scalar>::epsilon);
    /**
     * Converts degrees to radians.
     */
    inline scalar radians(scalar deg) {
        return deg * scalar(0.01745329251994329576923690768489);
    }
    /**
     * Converts radians to degrees.
     */
    inline scalar degrees(scalar rad) {
        return rad * scalar(57.295779513082320876798154814105);
    }
}

#endif //WHITEGEAR_SCALAR_BASE_HPP

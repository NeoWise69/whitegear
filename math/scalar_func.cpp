
/*******************************************************************************
 * Copyright (c) 2023.
 * This file is part of The WhiteGear Studio software property.
 * If you get unexpected access to this file, or part ot whole codebase, you should
 * report this source code leak and delete all copies of source code from all your machines.
 ******************************************************************************/

#include <math/scalar_base.hpp>

namespace wg {
    scalar fmin(scalar a, scalar b) {
        return a < b ? a : b;
    }

    scalar fmin(scalar a, scalar b, scalar c) {
        return fmin(fmin(a, b), c);
    }

    scalar fmin(scalar a, scalar b, scalar c, scalar d) {
        return fmin(fmin(a, b), fmin(c, d));
    }

    scalar fmax(scalar a, scalar b) {
        return a > b ? a : b;
    }

    scalar fmax(scalar a, scalar b, scalar c) {
        return fmax(fmax(a, b), c);
    }

    scalar fmax(scalar a, scalar b, scalar c, scalar d) {
        return fmax(fmax(a, b), fmax(c, d));
    }

    scalar clamp(scalar x, scalar _min, scalar _max) {
        return fmin(fmax(x, _min), _max);
    }

    scalar fract(scalar x) {
        return x - floor(x);
    }

    scalar mix(scalar x, scalar y, scalar a) {
        return (x * (1 - a)) + y * a;
    }

    scalar lerp(scalar x, scalar y, scalar a) {
        return (x * (1 - a)) + y * a;
    }

    scalar slerp(scalar x, scalar y, scalar a) {
        scalar d = y - x;
        d = fmod(d, constants<scalar>::two_pi);
        d = fmod(d + constants<scalar>::three_pi, constants<scalar>::two_pi) - constants<scalar>::pi;
        return x + a * d;
    }

    scalar rsqrt(scalar x) {
        scalar t(x);
        const scalar xhalf(t * scalar(0.5));
        const uint* p = reinterpret_cast<uint*>(const_cast<scalar*>(&x));
        const uint i = uint(0x5f375a86) - (*p >> uint(1));
        const auto* t2 = reinterpret_cast<const scalar*>(&i);
        t = *t2;
        return t * (scalar(1.5) - xhalf * t * t);
    }

    bool equal(scalar a, scalar b, scalar eps) {
        return abs(a - b) <= eps;
    }

    bool nequal(scalar a, scalar b, scalar eps) {
        return abs(a - b) > eps;
    }

}

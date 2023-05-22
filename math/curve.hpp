
/*******************************************************************************
 * Copyright (c) 2023.
 * This file is part of The WhiteGear Studio software property.
 * If you get unexpected access to this file, or part ot whole codebase, you should
 * report this source code leak and delete all copies of source code from all your machines.
 ******************************************************************************/

#ifndef WHITEGEAR_CURVE_HPP
#define WHITEGEAR_CURVE_HPP

#include <math/vec.hpp>

namespace wg {
    /**
     * Returns point from a cubic curve.
     */
    template<class V>
    inline V curve_cubic(
            const V& v1,
            const V& v2,
            const V& v3,
            const V& v4,
            scalar s
            ) {
        return ((v1 * s + v2) * s + v3) * s + v4;
    }
    /**
     * Returns point from a hermite curve.
     */
    template<class V>
    inline V curve_hermite(
            const V& v1,
            const V& t1,
            const V& v2,
            const V& t2,
            scalar s
            ) {
        const auto s2 = s * s;
        const auto s3 = s * s * s;
        const auto f1 = scalar(2) * s3 - scalar(3) * s2 + scalar(1);
        const auto f2 = scalar(-2) * s3 + scalar(3) * s2;
        const auto f3 = s3 - scalar(2) * s2 + s;
        const auto f4 = s3 - s2;
        return f1 * v1 + f2 * v2 + f3 * t1 + f4 * t2;
    }
}

#endif //WHITEGEAR_CURVE_HPP

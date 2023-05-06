
/*******************************************************************************
 * Copyright (c) 2023.
 * This file is part of The WhiteGear Studio software property.
 * If you get unexpected access to this file, or part ot whole codebase, you should
 * report this source code leak and delete all copies of source code from all your machines.
 ******************************************************************************/

#ifndef WHITEGEAR_VECTOR_BASE_HPP
#define WHITEGEAR_VECTOR_BASE_HPP

#include "scalar_base.hpp"

#include <xmmintrin.h>

namespace wg {
    /**
     * Structure for defining a simple and usable interface for
     * access to vector's data as contiguous array(even if it is simd type).
     * @tparam N
     */
    template<size_t N>
    struct contiguous_data {
        scalar data[N] = {};

        inline scalar& operator[](int i) { return data[i]; }
        inline constexpr size_t size() const { return N; }
    };

    template<>
    struct contiguous_data<4> {
        __m128 data = {};

        inline operator __m128() const { return data; }
        inline contiguous_data(__m128 d) : data(d) {}
        inline contiguous_data() = default;
        inline constexpr size_t size() const { return 4; }
    };
    /**
     * Forward vector type declarations.
     */
     template<size_t N> struct vec;

     using vec2 = vec<2u>;
     using vec3 = vec<3u>;
     using vec4 = vec<4u>;
}

#endif //WHITEGEAR_VECTOR_BASE_HPP

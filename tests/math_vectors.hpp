
/*******************************************************************************
 * Copyright (c) 2023.
 * This file is part of The WhiteGear Studio software property.
 * If you get unexpected access to this file, or part ot whole codebase, you should
 * report this source code leak and delete all copies of source code from all your machines.
 ******************************************************************************/

#ifndef WHITEGEAR_MATH_VECTORS_HPP
#define WHITEGEAR_MATH_VECTORS_HPP

#include <math/vec.hpp>

auto math_vectors_test() -> bool {
    using namespace wg;

    // vec2 test:
    {
        vec2 a = {1, 2};
        vec2 a1 = {1.0001f, 2};
        if (a == a1)
            return false;

        const auto b = a;
        if (a != b)
            return false;
    }

    // vec3 test:
    {
        vec3 a = {22, 12, 2};
        vec2 a0 = {22, 12};
        vec3 b = {a0, 2};

        const auto rs = rsqrt(a);

        if (a != b)
            return false;
    }

    // vec4 test:
    {
        vec4 a = { 22, 12, 2, 0.1f };
        const auto b = a;
        if (a != b)
            return false;
    }

    return true;
}

#endif //WHITEGEAR_MATH_VECTORS_HPP

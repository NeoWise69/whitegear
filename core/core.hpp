
/*******************************************************************************
 * Copyright (c) 2023.
 * This file is part of The WhiteGear Studio software property.
 * If you get unexpected access to this file, or part ot whole codebase, you should
 * report this source code leak and delete all copies of source code from all your machines.
 ******************************************************************************/

#ifndef WHITEGEAR_CORE_HPP
#define WHITEGEAR_CORE_HPP

// basic things
#include "typedefs.hpp"
#include "arch_info.hpp"
#include "logger.hpp"

// containers
#include "containers/array_view.hpp"
#include "containers/string_view.hpp"

// algorithms
template<class A>
inline constexpr A min(A x) {
    return x;
}

template<class A, class B>
inline constexpr A min(A x, B y) {
    return (x < B(y)) ? x : B(y);
}

template<class A, class B, class C>
inline constexpr A min(A x, B y, C z) {
    return min(min(x, y), z);
}

template<class A, class B, class C, class D>
inline constexpr A min(A x, B y, C z, D w) {
    return min(min(x, y), min(z, w));
}

#endif //WHITEGEAR_CORE_HPP

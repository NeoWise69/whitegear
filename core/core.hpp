
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
#include "ret.hpp"

// containers
#include "containers/array_view.hpp"
#include "containers/string_view.hpp"
#include "containers/string.hpp"
#include "containers/bounded_array.hpp"
#include "containers/hashmap.hpp"

/**
 * Returns lower between parameters
 */
template<class A>
inline constexpr A min(A x) {
    return x;
}
/**
 * Returns lower between parameters
 */
template<class A, class B>
inline constexpr A min(A x, B y) {
    return (x < B(y)) ? x : B(y);
}
/**
 * Returns lower between parameters
 */
template<class A, class B, class C>
inline constexpr A min(A x, B y, C z) {
    return min(min(x, y), z);
}
/**
 * Returns lower between parameters
 */
template<class A, class B, class C, class D>
inline constexpr A min(A x, B y, C z, D w) {
    return min(min(x, y), min(z, w));
}

/**
 * Returns higher between parameters
 */
template<class A>
inline constexpr A max(A x) {
    return x;
}
/**
 * Returns higher between parameters
 */
template<class A, class B>
inline constexpr A max(A x, B y) {
    return (x > B(y)) ? x : B(y);
}
/**
 * Returns higher between parameters
 */
template<class A, class B, class C>
inline constexpr A max(A x, B y, C z) {
    return max(max(x, y), z);
}
/**
 * Returns higher between parameters
 */
template<class A, class B, class C, class D>
inline constexpr A max(A x, B y, C z, D w) {
    return max(max(x, y), max(z, w));
}

#endif //WHITEGEAR_CORE_HPP

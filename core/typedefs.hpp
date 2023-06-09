
/*******************************************************************************
 * Copyright (c) 2023.
 * This file is part of The WhiteGear Studio software property.
 * If you get unexpected access to this file, or part ot whole codebase, you should
 * report this source code leak and delete all copies of source code from all your machines.
 ******************************************************************************/

#ifndef WHITEGEAR_TYPEDEFS_HPP
#define WHITEGEAR_TYPEDEFS_HPP

#include <core/macros.hpp>

namespace wg {
    typedef char i8;
    typedef unsigned char u8;
    typedef short i16;
    typedef unsigned short u16;
    typedef int i32;
    typedef unsigned int u32;
    typedef unsigned int uint;
    typedef long long i64;
    typedef unsigned long long u64;
    typedef float real;
    /**
     * IObject is a non-typed pointer to
     * Internal Object, that client code
     * doesn't know about.
     */
    typedef void* i_object;
}

static_assert((sizeof(wg::i8) == 1) && (sizeof(wg::u8) == 1), "incompatible type sizes and layouts!");
static_assert((sizeof(wg::i16) == 2) && (sizeof(wg::u16) == 2), "incompatible type sizes and layouts!");
static_assert((sizeof(wg::i32) == 4) && (sizeof(wg::u32) == 4), "incompatible type sizes and layouts!");
static_assert((sizeof(wg::i64) == 8) && (sizeof(wg::u64) == 8), "incompatible type sizes and layouts!");

#endif //WHITEGEAR_TYPEDEFS_HPP

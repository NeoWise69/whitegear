
/*******************************************************************************
 * Copyright (c) 2023.
 * This file is part of The WhiteGear Studio software property.
 * If you get unexpected access to this file, or part ot whole codebase, you should
 * report this source code leak and delete all copies of source code from all your machines.
 ******************************************************************************/

#include <core/hash.hpp>

namespace wg {
    static constexpr auto OFFSET = 0xcbf29ce484222325;
    static constexpr auto PRIME = 0x00000100000001B3;

    u64 hash_string(const string& s) {
        u64 h = OFFSET;
        for (const char c : s) {
            h ^= (u64)(u8)c;
            h *= PRIME;
        }
        return h;
    }
    u64 hash_string_view(const string_view& s) {
        u64 h = OFFSET;
        for (const char c : s) {
            h ^= (u64)(u8)c;
            h *= PRIME;
        }
        return h;
    }
}

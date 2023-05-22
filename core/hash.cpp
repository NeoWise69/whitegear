
/*******************************************************************************
 * Copyright (c) 2023.
 * This file is part of The WhiteGear Studio software property.
 * If you get unexpected access to this file, or part ot whole codebase, you should
 * report this source code leak and delete all copies of source code from all your machines.
 ******************************************************************************/

#include <core/hash.hpp>

namespace wg {
    i64 hash_string(const string& s) {
        constexpr int p = 31;
        constexpr int m = 1e9 + 9;
        long long hash_value = 0;
        long long p_pow = 1;
        for (const char& c : s) {
            hash_value = (hash_value + (c - 'a' + 1) * p_pow) % m;
            p_pow = (p_pow * p) % m;
        }
        return hash_value;
    }
    i64 hash_string_view(const string_view& s) {
        constexpr int p = 31;
        constexpr int m = 1e9 + 9;
        long long hash_value = 0;
        long long p_pow = 1;
        for (const char& c : s) {
            hash_value = (hash_value + (c - 'a' + 1) * p_pow) % m;
            p_pow = (p_pow * p) % m;
        }
        return hash_value;
    }
}

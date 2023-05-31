
/*******************************************************************************
 * Copyright (c) 2023.
 * This file is part of The WhiteGear Studio software property.
 * If you get unexpected access to this file, or part ot whole codebase, you should
 * report this source code leak and delete all copies of source code from all your machines.
 ******************************************************************************/

#ifndef WHITEGEAR_HASH_HPP
#define WHITEGEAR_HASH_HPP

#include <core/typedefs.hpp>
#include <core/containers/string.hpp>
#include <core/containers/string_view.hpp>
#include <core/containers/array_view.hpp>
#include <core/containers/bounded_array.hpp>

namespace wg {
    u64 hash_string(const string& s);
    u64 hash_string_view(const string_view& s);
    template<class T>
    u64 hash_array_view(const array_view<T>& a);
    template<class T, uint N>
    u64 hash_bounded_array(const bounded_array<T, N>& a);
}

namespace wg {
    template<class T>
    inline u64 hash_array_view(const array_view<T>& a) {
        u64 ret = {};
        for (uint i = 0; i < a.size(); ++i)
            ret *= std::hash<T>{}(a[i]) * 0xB00B5;
        return ret;
    }
    template<class T, uint N>
    inline u64 hash_bounded_array(const bounded_array<T, N>& a) {
        u64 ret = {};
        for (uint i = 0; i < a.size(); ++i)
            ret *= std::hash<T>{}(a[i]) * 0xB00B5;
        return ret;
    }
}

#endif //WHITEGEAR_HASH_HPP

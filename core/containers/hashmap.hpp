
/*******************************************************************************
 * Copyright (c) 2023.
 * This file is part of The WhiteGear Studio software property.
 * If you get unexpected access to this file, or part ot whole codebase, you should
 * report this source code leak and delete all copies of source code from all your machines.
 ******************************************************************************/

#ifndef WHITEGEAR_HASHMAP_HPP
#define WHITEGEAR_HASHMAP_HPP

#include <unordered_map>
#include "string.hpp"
#include "string_view.hpp"
#include "bounded_array.hpp"
#include "array_view.hpp"

#include <core/hash.hpp>

namespace wg {
    template<class KeyType, class ValueType>
    using hashmap = std::unordered_map<KeyType, ValueType>;
}

namespace std {
    template<>
    struct hash<wg::string> {
        inline size_t operator()(const wg::string& s) const noexcept {
#if WG_WINDOWS
            return std::_Hash_array_representation(s.c_str(), s.size());
#elif WG_UNIX
            return wg::hash_string(s);
#endif
        }
    };
    template<>
    struct hash<wg::string_view> {
        inline size_t operator()(const wg::string_view& s) const noexcept {
#if WG_WINDOWS
            return std::_Hash_array_representation(s.c_str(), s.size());
#elif WG_UNIX
            return wg::hash_string_view(s);
#endif
        }
    };
    template<class T, size_t N>
    struct hash<wg::bounded_array<T, N>> {
        inline size_t operator()(const wg::bounded_array<T, N>& a) const noexcept {
#if WG_WINDOWS
            return std::_Hash_array_representation(a.data(), a.size());
#elif WG_UNIX
            return wg::hash_bounded_array<T, N>(a);
#endif
        }
    };
    template<class T>
    struct hash<wg::array_view<T>> {
        inline size_t operator()(const wg::array_view<T>& a) const noexcept {
#if WG_WINDOWS
            return std::_Hash_array_representation(a.data(), a.size());
#elif WG_UNIX
            return wg::hash_array_view<T>(a);
#endif
        }
    };
}

#endif //WHITEGEAR_HASHMAP_HPP

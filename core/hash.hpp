
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
    namespace fnv {
        template<uint N>
        struct hash;
        inline u64 seed = 14695981039346656037ull;
        inline constexpr static u64 prime = 1099511628211ull;

        template<>
        struct hash<sizeof(i8)> {
            inline auto operator()(i8 v, u64 h = seed) {
                return (v ^ h) * prime;
            }

            inline auto operator()(u8 v, u64 h = seed) {
                return (v ^ h) * prime;
            }
        };

        template<>
        struct hash<sizeof(i16)> {
            inline auto operator()(i16 v, u64 h = seed) {
                const i8 *p = (const i8 *) &v;
                h = hash<1>()(*p++, h);
                return hash<1>()(*p, h);
            }

            inline auto operator()(u16 v, u64 h = seed) {
                const u8 *p = (const u8 *) &v;
                h = hash<1>()(*p++, h);
                return hash<1>()(*p, h);
            }
        };

        template<>
        struct hash<sizeof(i32)> {
            inline auto operator()(i32 v, u64 h = seed) {
                const i8 *p = (const i8 *) &v;
                h = hash<1>()(*p++, h);
                h = hash<1>()(*p++, h);
                h = hash<1>()(*p++, h);
                return hash<1>()(*p, h);
            }

            inline auto operator()(u32 v, u64 h = seed) {
                const u8 *p = (const u8 *) &v;
                h = hash<1>()(*p++, h);
                h = hash<1>()(*p++, h);
                h = hash<1>()(*p++, h);
                return hash<1>()(*p, h);
            }

            inline auto operator()(float f, u64 h = seed) {
                const i8 *p = (const i8 *) &f;
                h = hash<1>()(*p++, h);
                h = hash<1>()(*p++, h);
                h = hash<1>()(*p++, h);
                return hash<1>()(*p, h);
            }
        };

        template<>
        struct hash<sizeof(i64)> {
            inline auto operator()(i64 v, u64 h = seed) {
                const i8 *p = (const i8 *) &v;
                h = hash<1>()(*p++, h);
                h = hash<1>()(*p++, h);
                h = hash<1>()(*p++, h);
                h = hash<1>()(*p++, h);
                h = hash<1>()(*p++, h);
                h = hash<1>()(*p++, h);
                h = hash<1>()(*p++, h);
                return hash<1>()(*p, h);
            }

            inline auto operator()(u64 v, u64 h = seed) {
                const u8 *p = (const u8 *) &v;
                h = hash<1>()(*p++, h);
                h = hash<1>()(*p++, h);
                h = hash<1>()(*p++, h);
                h = hash<1>()(*p++, h);
                h = hash<1>()(*p++, h);
                h = hash<1>()(*p++, h);
                h = hash<1>()(*p++, h);
                return hash<1>()(*p, h);
            }

            inline auto operator()(double v, u64 h = seed) {
                const i8 *p = (const i8 *) &v;
                h = hash<1>()(*p++, h);
                h = hash<1>()(*p++, h);
                h = hash<1>()(*p++, h);
                h = hash<1>()(*p++, h);
                h = hash<1>()(*p++, h);
                h = hash<1>()(*p++, h);
                h = hash<1>()(*p++, h);
                return hash<1>()(*p, h);
            }

            inline auto operator()(const char *s, u64 h = seed) {
                if (!s) return 0ull;
                while (*s) {
                    h = hash<1>()(*s++, h);
                }
                return h;
            }

            inline auto operator()(const char *s, uint len, u64 h = seed) {
                if (!s) return 0ull;
                for (uint i = 0; i < len && s[i] != 0; ++i) {
                    h = hash<1>()(s[i], h);
                }
                return h;
            }
        };
    }

    template<class T>
    inline auto make_hash(T* v) {
        return ((u64)(v) / sizeof(T));
    }
    template<class T>
    inline auto make_hash(const T* v) {
        return ((u64)(v) / sizeof(T));
    }
    template<class T>
    inline auto make_hash(const T& v) {
        return fnv::hash<sizeof(v)>()(v);
    }
    /* make_hash variants for POD types */
    template<>
    inline auto make_hash(void* p) {
        return fnv::hash<sizeof(p)>()((u64)p);
    }
    template<>
    inline auto make_hash(const void* p) {
        return fnv::hash<sizeof(p)>()((u64)p);
    }
    template<>
    inline auto make_hash(const i64& v) {
        return fnv::hash<sizeof(v)>()(v);
    }
    template<>
    inline auto make_hash(const u64& v) {
        return fnv::hash<sizeof(v)>()(v);
    }
    template<>
    inline auto make_hash(const i32& v) {
        return fnv::hash<sizeof(v)>()(v);
    }
    template<>
    inline auto make_hash(const u32& v) {
        return fnv::hash<sizeof(v)>()(v);
    }
    template<>
    inline auto make_hash(const i16& v) {
        return fnv::hash<sizeof(v)>()(v);
    }
    template<>
    inline auto make_hash(const u16& v) {
        return fnv::hash<sizeof(v)>()(v);
    }
    template<>
    inline auto make_hash(const i8& v) {
        return fnv::hash<sizeof(v)>()(v);
    }
    template<>
    inline auto make_hash(const u8& v) {
        return fnv::hash<sizeof(v)>()(v);
    }
    template<>
    inline auto make_hash(const float& v) {
        return fnv::hash<sizeof(v)>()(v);
    }
    template<>
    inline auto make_hash(const double& v) {
        return fnv::hash<sizeof(v)>()(v);
    }
    template<>
    inline auto make_hash(const string& v) {
        return fnv::hash<8>()(v.c_str(), v.size());
    }
    template<>
    inline auto make_hash(const string_view& v) {
        return fnv::hash<8>()(v.c_str(), v.size());
    }
    template<class T>
    inline auto make_hash(const array_view<T>& v) {
        u64 ret = {};
        for (uint i = 0; i < v.size(); ++i)
            ret += fnv::hash<sizeof(T)>()(v[i]);
        return ret;
    }
    template<class T, uint N>
    inline auto make_hash(const bounded_array<T, N>& v) {
        u64 ret = {};
        for (uint i = 0; i < v.size(); ++i)
            ret += fnv::hash<sizeof(T)>()(v[i]);
        return ret;
    }
}

#endif //WHITEGEAR_HASH_HPP


/*******************************************************************************
 * Copyright (c) 2023.
 * This file is part of The WhiteGear Studio software property.
 * If you get unexpected access to this file, or part ot whole codebase, you should
 * report this source code leak and delete all copies of source code from all your machines.
 ******************************************************************************/

#ifndef WHITEGEAR_BASE_HPP
#define WHITEGEAR_BASE_HPP

#include <core/typedefs.hpp>
#include <core/containers/string.hpp>
#include <core/smart_ptr.hpp>
#include <core/hash.hpp>
#include <core/containers/string_view.hpp>

namespace wg::resource {
    class name_t {
    public:
        inline name_t() = default;
        inline ~name_t() = default;
        name_t(const char* p_name);
        name_t(const string_view& sv);
        name_t(const string& str);

        inline auto get_hash() const {
            return mHash;
        }
        inline auto get_length() const {
            return mName.size();
        }
        inline auto get_size() const {
            return get_length();
        }
        inline operator string() const {
            return mName;
        }
        inline operator string_view() const {
            return mName.c_str();
        }
        inline explicit operator u64() const {
            return mHash;
        }
    private:
        u64 mHash = {};
        string mName = {};
    };
    bool operator==(const name_t& a, const name_t& b);
    bool operator!=(const name_t& a, const name_t& b);

    template<class T>
    using handle = shared_ptr<T>;

    template<class T, class...Args>
    inline constexpr handle<T> make_handle(Args&&...args) {
        return make_shared<T>(std::forward<Args>(args)...);
    }

    template<class T>
    class cache;

    template<class T, class...Args>
    class loader {
    public:
        friend class cache<T>;
        virtual handle<T> load(const name_t& name_id, Args&&...args) const = 0;
    };
}

namespace wg::fnv {
    template<>
    struct hash<sizeof(wg::resource::name_t)> {
        inline auto operator()(const wg::resource::name_t& name) const {
            return name.get_hash();
        }
    };
}

#endif //WHITEGEAR_BASE_HPP

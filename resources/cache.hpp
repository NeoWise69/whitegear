
/*******************************************************************************
 * Copyright (c) 2023.
 * This file is part of The WhiteGear Studio software property.
 * If you get unexpected access to this file, or part ot whole codebase, you should
 * report this source code leak and delete all copies of source code from all your machines.
 ******************************************************************************/

#ifndef WHITEGEAR_CACHE_HPP
#define WHITEGEAR_CACHE_HPP

#include "base.hpp"
#include <core/containers/hashmap.hpp>
#include <core/io.hpp>

namespace wg::resource {
    template<class T>
    class cache {
    public:
        typedef handle<T> handle_type;

        template<class loader_class, class...Args>
        inline handle_type set(loader_class& loader_instance, const name_t& name_id, Args&&...args) {
            const auto it = mCache.find(name_id);
            if (it != mCache.end())
                return it->second;
            else
                return handle_type((mCache.insert(name_id, std::move(loader_instance.load(name_id, std::forward<Args>(args)...))).first)->second);
        }
        template<class loader_class, class...Args>
        inline handle_type set(const loader_class& loader_instance, const name_t& name_id, Args&&...args) {
            const auto it = mCache.find(name_id);
            if (it != mCache.end())
                return it->second;
            else
                return handle_type((mCache.emplace(name_id, std::move(loader_instance.load(name_id, std::forward<Args>(args)...))).first)->second);
        }
        inline void reset(const name_t& name_id) { mCache.erase(name_id); }
        inline void reset() { mCache.clear(); }

        inline handle_type get_handle(const name_t& name_id) {
            const auto it = mCache.find(name_id);
            if (it != mCache.end())
                return handle_type(it->second);
            return {};
        }
        inline auto get_size() const {
            return mCache.size();
        }

        virtual bool save_to_file(const string_view& filename) const = 0;
        virtual bool load_from_file(const string_view& filename) = 0;
    protected:
        hashmap<name_t, handle_type> mCache = {};
    };
}

#endif //WHITEGEAR_CACHE_HPP

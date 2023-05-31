
/*******************************************************************************
 * Copyright (c) 2023.
 * This file is part of The WhiteGear Studio software property.
 * If you get unexpected access to this file, or part ot whole codebase, you should
 * report this source code leak and delete all copies of source code from all your machines.
 ******************************************************************************/

#include "text_resource.hpp"
#include <core/core.hpp>

namespace wg::resource {
    struct text_resource_info {
        u64 num_strings;
    };
    struct text_packed_pair_info {
        uint name_size;
        uint text_size;
    };

    bool text_cache::save_to_file(const string_view& filename) const {
        file f(filename, "wb");

        if (!f.is_opened()) return false;

        text_resource_info resource_info = {
            get_size()
        };
        f.write(&resource_info, sizeof(resource_info));

        for (const auto&[name, text] : mCache) {
            text_packed_pair_info pair_info = {
                    uint(name.get_size()),
                    uint(text->size())
            };
            f.write(&pair_info, sizeof(pair_info));
            f.write(((string)name).c_str(), pair_info.name_size);
            f.write(text->c_str(), pair_info.text_size);
        }

        f.close();
        return true;
    }

    bool text_cache::load_from_file(const string_view& filename) {
        file f(filename, "rb");

        if (!f.is_opened()) return false;

        text_resource_info resource_info = {};
        f.read(&resource_info, sizeof(resource_info));

        string buffer = {};

        for (u64 i = 0; i < resource_info.num_strings; ++i) {
            text_packed_pair_info pair_info = {};
            f.read(&pair_info, sizeof(pair_info));
            if (buffer.size() < pair_info.name_size)
                buffer.append('\0', max(pair_info.name_size, pair_info.text_size));
            f.read(buffer.data(), pair_info.name_size);
            auto& text = mCache[buffer.c_str()];
            text = make_handle<string>();
            text->append('\0', pair_info.text_size);
            f.read(text->data(), pair_info.text_size);
        }

        f.close();
        return true;
    }

    text_cache& get_text_cache(name_t&& name) {
        static hashmap<name_t, text_cache> caches = {};
        return caches[name];
    }
}

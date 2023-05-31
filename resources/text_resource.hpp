
/*******************************************************************************
 * Copyright (c) 2023.
 * This file is part of The WhiteGear Studio software property.
 * If you get unexpected access to this file, or part ot whole codebase, you should
 * report this source code leak and delete all copies of source code from all your machines.
 ******************************************************************************/

#ifndef WHITEGEAR_TEXT_RESOURCE_HPP
#define WHITEGEAR_TEXT_RESOURCE_HPP

#include <resources/cache.hpp>

namespace wg::resource {
    class text_cache : public cache<string> {
    public:
        bool save_to_file(const string_view& filename) const override;
        bool load_from_file(const string_view& filename) override;
    };

    class text_loader : public loader<string, string_view> {
    public:
        handle<string> load(const name_t& name_id, string_view&& sv) const override;
    };

    text_cache& get_text_cache(name_t&& name = "global");
}

#endif //WHITEGEAR_TEXT_RESOURCE_HPP

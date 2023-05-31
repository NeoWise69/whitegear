
/*******************************************************************************
 * Copyright (c) 2023.
 * This file is part of The WhiteGear Studio software property.
 * If you get unexpected access to this file, or part ot whole codebase, you should
 * report this source code leak and delete all copies of source code from all your machines.
 ******************************************************************************/

#include "base.hpp"
#include <core/hash.hpp>

namespace wg::resource {
    name_t::name_t(const char *p_name) : mName(p_name), mHash(hash_string(p_name)) {}
    name_t::name_t(const string_view &sv) : mName(sv), mHash(hash_string_view(sv)) {}
    name_t::name_t(const string &str) : mName(str), mHash(hash_string(str)) {}
    bool operator==(const name_t& a, const name_t& b) {
        return a.get_hash() == b.get_hash();
    }
    bool operator!=(const name_t& a, const name_t& b) {
        return a.get_hash() != b.get_hash();
    }
}

/*******************************************************************************
 * Copyright (c) 2023.
 * This file is part of The WhiteGear Studio software property.
 * If you get unexpected access to this file, or part ot whole codebase, you should
 * report this source code leak and delete all copies of source code from all your machines.
 ******************************************************************************/

#include "text_resource.hpp"

namespace wg::resource {
    handle<string> text_loader::load(const wg::resource::name_t &name_id, wg::string_view &&sv) const {
        return make_handle<string>(sv);
    }
}


/*******************************************************************************
 * Copyright (c) 2023.
 * This file is part of The WhiteGear Studio software property.
 * If you get unexpected access to this file, or part ot whole codebase, you should
 * report this source code leak and delete all copies of source code from all your machines.
 ******************************************************************************/

#ifndef WHITEGEAR_CONTAINERS_ARRAY_VIEW_HPP
#define WHITEGEAR_CONTAINERS_ARRAY_VIEW_HPP

#include <core/containers/array_view.hpp>

auto containers_array_view_test() -> bool {

    wg::array_view<const char* const> av = {
        "hello",
        "world!"
    };

    if (av.size() != 2)
        return false;

    for (auto s : av) {
        if (!strcmp(s, "hello"))
            break;
    }

    return true;
}

#endif //WHITEGEAR_CONTAINERS_ARRAY_VIEW_HPP


/*******************************************************************************
 * Copyright (c) 2023.
 * This file is part of The WhiteGear Studio software property.
 * If you get unexpected access to this file, or part ot whole codebase, you should
 * report this source code leak and delete all copies of source code from all your machines.
 ******************************************************************************/

#ifndef WHITEGEAR_CONTAINERS_STRING_VIEW_HPP
#define WHITEGEAR_CONTAINERS_STRING_VIEW_HPP

#include <core/containers/string_view.hpp>

auto containers_string_view_test() -> bool {

    wg::string_view sv = {"Hello, World!"};
    if (sv.compare("hello, world!"))
        return false;
    if (!sv.compare("Hello, World!"))
        return false;

    return true;
}

#endif //WHITEGEAR_CONTAINERS_STRING_VIEW_HPP

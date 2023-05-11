
/*******************************************************************************
 * Copyright (c) 2023.
 * This file is part of The WhiteGear Studio software property.
 * If you get unexpected access to this file, or part ot whole codebase, you should
 * report this source code leak and delete all copies of source code from all your machines.
 ******************************************************************************/

#ifndef WHITEGEAR_CONTAINERS_STRING_HPP
#define WHITEGEAR_CONTAINERS_STRING_HPP

#include <core/containers/string.hpp>

auto containers_string_test() -> bool {

    wg::string s;
    auto s1 = s;

    s[0] = 's';

    return true;
}

#endif //WHITEGEAR_CONTAINERS_STRING_HPP

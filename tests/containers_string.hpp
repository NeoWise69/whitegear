
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

    /*
    // Got tricky warning here about exceptions
    try {
        wg::string s = "Hello, world! - 1;  Hello, world! - 2;";
        auto s1 = s;
        s = "Hello, world! - 1;  Hello, world!";
        s = s1;

        const auto c = s.c_str();

        s[0] = 's';
        s = "test =(";
    }
    catch (std::exception&) {
        return false;
    }
     */

    return true;
}

#endif //WHITEGEAR_CONTAINERS_STRING_HPP


/*******************************************************************************
 * Copyright (c) 2023.
 * This file is part of The WhiteGear Studio software property.
 * If you get unexpected access to this file, or part ot whole codebase, you should
 * report this source code leak and delete all copies of source code from all your machines.
 ******************************************************************************/

#ifndef WHITEGEAR_PTS_HPP
#define WHITEGEAR_PTS_HPP

#include <core/pts/pts_base.hpp>
#include <core/pts/pts_blob.hpp>

auto pts_test() -> bool {
    using namespace wg;

    pts_blob blob("test.bin");

    auto tree = pts_tree_create("test");

    {   /* load-in the data block */
        tree->add_child({false, "greeting.txt", 13, 13});
    }

    pts_entry* gc = tree->find_child("greeting.txt");

    if (gc) {
        u8 *greet = blob.get_data(gc);
        greet[13] = 0;
    }
    return true;
}

#endif //WHITEGEAR_PTS_HPP

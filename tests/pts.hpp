
/*******************************************************************************
 * Copyright (c) 2023.
 * This file is part of The WhiteGear Studio software property.
 * If you get unexpected access to this file, or part ot whole codebase, you should
 * report this source code leak and delete all copies of source code from all your machines.
 ******************************************************************************/

#ifndef WHITEGEAR_PTS_HPP
#define WHITEGEAR_PTS_HPP

#include <core/pts/base.hpp>
#include <core/pts/blob.hpp>
#include <core/pts/io.hpp>

auto pts_test() -> bool {
    using namespace wg;

    pts_blob blob("test.bin");

    auto tree = new pts_entry();
    {/*
        const auto text = string_view("Hello, world!");
        blob.write((u8*)text.c_str(), text.size());
        tree->add_child(pts_entry(false, "gmsg.txt", 0, text.size()));
    */}

    if (!pts_entry_load_from_file(tree, "test.pts")) {
        return false;
    }

    pts_entry* gc = tree->find_child("gmsg.txt");

    if (gc) {
        u8 *greet = blob.get_data(gc);
        greet[gc->get_size()] = 0;
    }
    return true;
}

#endif //WHITEGEAR_PTS_HPP

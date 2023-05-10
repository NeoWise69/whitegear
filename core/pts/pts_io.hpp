
/*******************************************************************************
 * Copyright (c) 2023.
 * This file is part of The WhiteGear Studio software property.
 * If you get unexpected access to this file, or part ot whole codebase, you should
 * report this source code leak and delete all copies of source code from all your machines.
 ******************************************************************************/

#ifndef WHITEGEAR_PTS_IO_HPP
#define WHITEGEAR_PTS_IO_HPP

#include <core/pts/pts_base.hpp>

namespace wg {
    /**
     * Simple serialization routine for saving pts tree structure to file.
     * @param e Pointer to a valid pts entry.
     * @param filename Path to not-readonly location on disk.
     * @return true on success, otherwise false.
     */
    bool pts_entry_write_to_file(const pts_entry* e, const string_view& filename);
    /**
     * Simple deserialization routine for loading pts tree structure from disk.
     * @param e A valid pointer to pts entry tree root.
     * @return true on success, otherwise false.
     */
    bool pts_entry_load_from_file(pts_entry* e, const string_view& filename);
}

#endif //WHITEGEAR_PTS_IO_HPP

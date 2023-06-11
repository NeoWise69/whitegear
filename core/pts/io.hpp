
/*******************************************************************************
 * Copyright (c) 2023.
 * This file is part of The WhiteGear Studio software property.
 * If you get unexpected access to this file, or part ot whole codebase, you should
 * report this source code leak and delete all copies of source code from all your machines.
 ******************************************************************************/

#ifndef WHITEGEAR_PTS_IO_HPP
#define WHITEGEAR_PTS_IO_HPP

#include <core/pts/base.hpp>

namespace wg::pts {
    /**
     * Simple serialization routine for saving pts tree structure to file.
     * @param e Pointer to a valid pts entry.
     * @param filename Path to not-readonly location on disk.
     * @return true on success, otherwise false.
     */
    bool write_entry_to_file(const entry* e, const string_view& filename);
    /**
     * Simple deserialization routine for loading pts tree structure from disk.
     * @param e A valid pointer to pts entry tree root.
     * @return true on success, otherwise false.
     */
    bool load_entry_from_file(entry* e, const string_view& filename);
}

#endif //WHITEGEAR_IO_HPP

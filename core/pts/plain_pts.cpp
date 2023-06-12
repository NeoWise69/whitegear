
/*******************************************************************************
 * Copyright (c) 2023.
 * This file is part of The WhiteGear Studio software property.
 * If you get unexpected access to this file, or part ot whole codebase, you should
 * report this source code leak and delete all copies of source code from all your machines.
 ******************************************************************************/

#include <core/pts/plain_pts.hpp>
#include <core/pts/io.hpp>

namespace wg {
    void plain_text::set(const wg::string_view &name, const wg::string &value) {
        const auto pos = blob.write((u8*)value.c_str(), uint(value.size()));
        tree.add_child(pts::entry(false, name.c_str(), pos, uint(value.size())));
    }

    bool plain_text::get(const wg::string_view &name, wg::string &value) const {
        const auto child = tree.find_child(name.c_str());
        if (child) {
            const u8* data = blob.get_data(child);
            const auto size = child->get_size();
            value = { (const char*)data, size };
            return true;
        }
        return false;
    }

    void plain_text::save() const {
        pts::write_entry_to_file(&tree, "TXTSRC.tbl");

    }

    void plain_text::load() {
        pts::load_entry_from_file(&tree, "TXTSRC.tbl");
    }

    bool plain_text::is_initialized() const {
        return tree.is_dir();
    }

}

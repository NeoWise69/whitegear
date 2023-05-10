
/*******************************************************************************
 * Copyright (c) 2023.
 * This file is part of The WhiteGear Studio software property.
 * If you get unexpected access to this file, or part ot whole codebase, you should
 * report this source code leak and delete all copies of source code from all your machines.
 ******************************************************************************/

#include <core/pts/pts_blob.hpp>
#include "pts_base.hpp"
#include <fstream>

namespace wg {

    pts_blob::pts_blob(const wg::string_view &filename) : mFile() {
        reopen(filename);
    }

    void pts_blob::release() {
        if (mFile.is_opened()) {
            mFile.close();
        }
    }

    bool pts_blob::reopen(const wg::string_view &filename) {
        file t(filename, "ab+");
        if (!t.is_opened()) return false;
        release();
        mFile.swap(std::move(t));
        return true;
    }

    u8* pts_blob::get_data(uint start, uint size) const {
        if (!mFile.is_opened()) return nullptr;
        mFile.seek(start);
        u8* data = new u8[size]();
        mFile.read(data, size);
        return data;
    }

    u8 *pts_blob::get_data(const pts_entry *e) const {
        return e ? get_data(e->get_address(), e->get_size()) : nullptr;
    }

    uint pts_blob::write(const u8 *data, uint size) {
        if (!mFile.is_opened()) return uint(-1);
        mFile.seek(0, SEEK_DIR_END);
        const uint pos = mFile.pos();
        mFile.write(data, size);
        return pos;
    }
}

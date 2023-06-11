
/*******************************************************************************
 * Copyright (c) 2023.
 * This file is part of The WhiteGear Studio software property.
 * If you get unexpected access to this file, or part ot whole codebase, you should
 * report this source code leak and delete all copies of source code from all your machines.
 ******************************************************************************/

#include <core/pts/blob.hpp>
#include "base.hpp"

namespace wg::pts {

    blob::blob(const wg::string_view &filename) : mFile() {
        reopen(filename);
    }

    void blob::release() {
        if (mFile.is_opened()) {
            mFile.close();
        }
    }

    bool blob::reopen(const wg::string_view &filename) {
        file t(filename, "ab+");
        if (!t.is_opened()) return false;
        release();
        mFile.swap(std::move(t));
        return true;
    }

    u8* blob::get_data(uint start, uint size) const {
        if (!mFile.is_opened()) return nullptr;
        mFile.seek(start);
        u8* data = new u8[size]();
        mFile.read(data, size);
        return data;
    }

    u8 *blob::get_data(const pts::entry *e) const {
        return e ? get_data(e->get_address(), e->get_size()) : nullptr;
    }

    uint blob::write(const u8 *data, uint size) {
        if (!mFile.is_opened()) return uint(-1);
        mFile.seek(0, SEEK_DIR_END);
        const uint pos = mFile.pos();
        mFile.write(data, size);
        return pos;
    }
}

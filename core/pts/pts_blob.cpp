
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
    namespace {
        void fopen_(FILE** pp, const char* filename, const char* args) {
#if defined(_WIN32) || defined(_MSC_VER)
            fopen_s(pp, filename, args);
#elif defined(__APPLE__)
            *pp = fopen(filename, args);
#endif
        }
    }

    pts_blob::pts_blob(const wg::string_view &filename) : mFile() {
        reopen(filename);
    }

    void pts_blob::release() {
        if (mFile) {
            fclose(mFile);
            mFile = nullptr;
        }
    }

    bool pts_blob::reopen(const wg::string_view &filename) {
        FILE* tf;
        fopen_(&tf, filename.c_str(), "ab+");
        if (!tf) return false;
        release();
        mFile = tf;
        return true;
    }

    u8* pts_blob::get_data(uint start, uint size) const {
        if (!mFile) return nullptr;
        fseek(mFile, long(start), SEEK_SET);
        u8* data = new u8[size]();
        fread(data, sizeof(u8), size, mFile);
        return data;
    }

    u8 *pts_blob::get_data(const pts_entry *e) const {
        return e ? get_data(e->get_address(), e->get_size()) : nullptr;
    }

    uint pts_blob::write(const u8 *data, uint size) {
        if (!mFile) return uint(-1);
        fseek(mFile, 0, SEEK_END);
        const uint pos = uint(ftell(mFile));
        fwrite(data, 1, size, mFile);
        return pos;
    }
}

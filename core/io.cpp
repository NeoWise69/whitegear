
/*******************************************************************************
 * Copyright (c) 2023.
 * This file is part of The WhiteGear Studio software property.
 * If you get unexpected access to this file, or part ot whole codebase, you should
 * report this source code leak and delete all copies of source code from all your machines.
 ******************************************************************************/

#include <core/io.hpp>
#include <cstdio>

#define F(x) (FILE*)(x)
#define F2(x) (FILE**)(x)
#define P(x) (void*)(x)

namespace wg {
    namespace {
        int SEEKDIR(file_seek_direction d) {
            switch (d) {
                case SEEK_DIR_START: return SEEK_SET;
                case SEEK_DIR_END: return SEEK_END;
            }
            return SEEK_SET;
        }
    }

    file::file() : mInternal() {}
    file::~file() { mInternal = nullptr; }

    void file::swap(wg::file &&o) noexcept {
        mInternal = o.mInternal;
    }

    file::file(const wg::string_view &filename, const char *attr) : file() {
        (void)open(filename, attr);
    }

    file_error file::open(const wg::string_view &filename, const char *attr) {
#if WG_WINDOWS
        const auto err = fopen_s(F2(&mInternal), filename.c_str(), attr);
        if (err == ENOENT)
            return FILE_ERROR_NOT_FOUND;
        else if (err == EACCES)
            return FILE_ERROR_TWIN_OPEN;
        return FILE_ERROR_OK;
#elif WG_UNIX
        mInternal = P(fopen(filename.c_str(), attr));
        if (mInternal)
            return FILE_ERROR_OK;
        else
            return FILE_ERROR_NOT_FOUND;
#endif
    }

    void file::close() {
        fclose(F(mInternal));
        mInternal = nullptr;
    }

    bool file::is_opened() const {
        return F(mInternal) != nullptr;
    }

    int file::seek(wg::i64 offset, wg::file_seek_direction dir) const {
        return fseek(F(mInternal), long(offset), SEEKDIR(dir));
    }

    uint file::pos() const {
        return uint(ftell(F(mInternal)));
    }

    size_t file::read(void *data, size_t size) const {
        return fread(data, size, 1, F(mInternal));
    }

    size_t file::write(const void *data, size_t size) const {
        return fwrite(data, size, 1, F(mInternal));
    }

    bool file::exists(const string_view &filename) {
        file tmp = {};
        file_error e = tmp.open(filename);
        if (tmp.is_opened()) {
            tmp.close();
        }
        return e != FILE_ERROR_NOT_FOUND;
    }

}

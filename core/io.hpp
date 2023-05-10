
/*******************************************************************************
 * Copyright (c) 2023.
 * This file is part of The WhiteGear Studio software property.
 * If you get unexpected access to this file, or part ot whole codebase, you should
 * report this source code leak and delete all copies of source code from all your machines.
 ******************************************************************************/

#ifndef WHITEGEAR_IO_HPP
#define WHITEGEAR_IO_HPP

#include <core/typedefs.hpp>
#include <core/containers/string_view.hpp>

namespace wg {
    /**
     * Enumeration for error handling while working with files.
     * Contains self-describable values.
     */
    enum file_error {
        FILE_ERROR_OK,
        FILE_ERROR_NOT_FOUND,
    };
    /**
     * Enumeration for definition of seek direction,
     * i.e from START or from END.
     */
    enum file_seek_direction {
        SEEK_DIR_START,
        SEEK_DIR_END,
    };
    /**
     * Simple and thin abstraction for similar and simple
     * usage of file-io across compilers and OS's.
     */
    class file {
    public:
        file();
        /**
         * File handles can't be copied or moved like POD structures.
         * This is because of several states:
         * 1 - Accidentally you'll try to get access to the same file handle
         *     from several places, which is NOT GOOD AT ALL.
         *
         * 2 - When you're filehandle #2 is closed, filehandle #1 which is
         *     a parent of #2's, doesn't know about this, and the next time
         *     #1 will try to get access to a file, the program will crash
         *     due to this weird situation.
         */
        file(const file&) = delete;
        file& operator=(const file&) = delete;
        file(file&&) noexcept = delete;
        file& operator=(file&&) noexcept = delete;
        virtual ~file();

        void swap(file&& o) noexcept;

        file(const string_view& filename, const char* attr = "rb+");

        file_error open(const string_view& filename, const char* attr = "rb+");
        bool is_opened() const;
        void close();

        int seek(i64 offset, file_seek_direction dir = SEEK_DIR_START) const;
        uint pos() const;

        size_t read(void* data, size_t size) const;
        size_t write(const void* data, size_t size) const;
    private:
        void* mInternal;
    };
}

#endif //WHITEGEAR_IO_HPP

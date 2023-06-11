
/*******************************************************************************
 * Copyright (c) 2023.
 * This file is part of The WhiteGear Studio software property.
 * If you get unexpected access to this file, or part ot whole codebase, you should
 * report this source code leak and delete all copies of source code from all your machines.
 ******************************************************************************/

#ifndef WHITEGEAR_PTS_BLOB_HPP
#define WHITEGEAR_PTS_BLOB_HPP

#include <core/typedefs.hpp>
#include <core/containers/string_view.hpp>
#include <core/io.hpp>

namespace wg::pts {
    class entry;
    /**
     * BLOB is a simple data handler class
     * that helps with managing data inside blob file.
     */
    class blob {
    public:
        explicit blob(const string_view& filename);
        inline blob() noexcept = default;
        ~blob() = default;

        /**
         * Get pointer to the data block, starting from 'start'
         * !!![WARNING] DONT FORGET TO DELETE[] DATA!!!
         */
        inline u8* get_data(uint start, uint size) const;
        /**
         * Get pointer to the data block, based on 'entry'
         * !!![WARNING] DONT FORGET TO DELETE[] DATA!!!
         */
        u8* get_data(const pts::entry* e) const;

        bool reopen(const string_view& filename);
        /**
         * Writes data at the end of data handle.
         * @return Start position of written data block.
         */
        uint write(const u8* data, uint size);

        void release();

    private:
        file mFile;
    };
}

#endif //WHITEGEAR_BLOB_HPP

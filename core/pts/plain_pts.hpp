
/*******************************************************************************
 * Copyright (c) 2023.
 * This file is part of The WhiteGear Studio software property.
 * If you get unexpected access to this file, or part ot whole codebase, you should
 * report this source code leak and delete all copies of source code from all your machines.
 ******************************************************************************/

#ifndef WHITEGEAR_PLAIN_PTS_HPP
#define WHITEGEAR_PLAIN_PTS_HPP

#include <core/pts/base.hpp>
#include <core/pts/blob.hpp>

namespace wg {
    class plain_text {
    public:
        inline static plain_text& instance() {
            static plain_text inst = {};
            inst.blob.reopen("TXTSRC.bin");
            if (!file::exists("TXTSRC.tbl")) {
                inst.save();
            }
            inst.load();
            return inst;
        }

        void set(const string_view& name, const string& value);
        bool get(const string_view& name, string& value) const;

        void save() const;
        void load();

        bool is_initialized() const;
    private:

        pts::entry tree = {};
        pts::blob blob = {};
    };
}

#endif //WHITEGEAR_PLAIN_PTS_HPP

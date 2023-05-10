
/*******************************************************************************
 * Copyright (c) 2023.
 * This file is part of The WhiteGear Studio software property.
 * If you get unexpected access to this file, or part ot whole codebase, you should
 * report this source code leak and delete all copies of source code from all your machines.
 ******************************************************************************/

#include <core/pts/pts_io.hpp>
#include <core/io.hpp>

namespace wg {
    void write_entry(file* fp, const pts_entry* e) {
        const auto name = e->get_name();
        union {
            uint solid = {};
            struct {
                bool b0;
                bool b1;
                u8 u0;
            };
        } glue = {
            .b0 = e->is_dir(),
            .b1 = e->is_compressed(),
            .u0 = (u8)name.size()
        };

        uint entry_plain[5] = {
            e->get_address(),
            e->get_size(),
            e->get_children_count(),
            e->get_meta_size(),
            glue.solid
        };

        fp->write(entry_plain, sizeof(uint) * 5);
        fp->write(name.c_str(), name.size());
        if (e->get_meta_size() > 0) {
            fp->write(e->get_meta_data(), e->get_meta_size());
        }

        for (uint i = 0; i < e->get_children_count(); ++i) {
            auto* child = e->get_child(i);
            write_entry(fp, child);
        }
    }

    void read_entry(file* fp, pts_entry* e) {

        union {
            uint solid = {};
            struct {
                bool b0;
                bool b1;
                u8 u0;
            };
        } glue = {};
        uint plain_entry[5] = {};

        fp->read(plain_entry, sizeof(uint) * 5);

        glue.solid = plain_entry[4];
        const u8 name_len = glue.u0;

        fp->read(e->mName, name_len);

        e->mStartPos = plain_entry[0];
        e->mNameLen = name_len;
        e->mBlobSize = plain_entry[1];
        const auto num_children = plain_entry[2];
        e->mMetaSize = plain_entry[3];
        e->mIsDirectory = glue.b0;
        e->mIsCompressed = glue.b1;

        if (e->get_meta_size()) {
            char* data = new char[e->get_meta_size()]{};
            fp->read(data, e->get_meta_size());
            e->mMetaData = data;
        }

        for (uint i = 0; i < num_children; ++i) {
            pts_entry child = {};
            read_entry(fp, &child);
            e->add_child(child);
        }

    }

    bool pts_entry_write_to_file(const pts_entry* e, const string_view& filename) {
        if (e && !filename.empty()) {

            file f(filename, "wb");
            // start recursive write routine
            write_entry(&f, e);

            f.close();
            return true;
        }
        return false;
    }

    bool pts_entry_load_from_file(pts_entry* e, const string_view& filename) {
        if (e && !filename.empty()) {

            file f(filename, "rb");
            read_entry(&f, e);
            f.close();
            return true;
        }
        return false;
    }
}

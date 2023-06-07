
/*******************************************************************************
 * Copyright (c) 2023.
 * This file is part of The WhiteGear Studio software property.
 * If you get unexpected access to this file, or part ot whole codebase, you should
 * report this source code leak and delete all copies of source code from all your machines.
 ******************************************************************************/

/**
 * File: pts_base.hpp
 *
 * PTS (stands for Packed Tree Structure) file is a simple but powerful
 * file format for store any kind of data, with required meta information.
 */

#ifndef WHITEGEAR_PTS_BASE_HPP
#define WHITEGEAR_PTS_BASE_HPP

#include <core/core.hpp>
#include <iterator>

namespace wg {
    inline constexpr const uint MAX_NAME = 64u;
    inline constexpr const uint MAX_CHILDREN = 128u;
    /**
     * Entry is a simple unit that describes one point in a tree structure
     * of PTS 'filesystem'. BTW, this is linked list-like structure that
     * can have a single parent and multiple children at the same time.
     * Just like usual filesystem :)
     */
    class pts_entry {
    public:
        inline pts_entry() noexcept : mIsDirectory(), mName(), mNameLen(), mIsCompressed(),
                            mMetaSize(), mMetaData(), mStartPos(), mBlobSize(),
                            pParent(), ppChildren(), mNumChildren()
        {}
        inline virtual ~pts_entry() noexcept {}

        inline pts_entry(const pts_entry& o) noexcept {
            mIsDirectory = o.mIsDirectory;
            mNameLen = o.mNameLen;
            mIsCompressed = o.mIsCompressed;
            mMetaSize = o.mMetaSize;
            mStartPos = o.mStartPos;
            mBlobSize = o.mBlobSize;
            mNumChildren = o.mNumChildren;
            pParent = o.pParent;
            // copy name
            memcpy(mName, o.mName, MAX_NAME);
            // !copy name
            // copy meta
            if (o.mMetaSize > 0 && o.mMetaData) {
                mMetaData = new char[mMetaSize]{};
                memcpy(mMetaData, o.mMetaData, mMetaSize);
            }
            else {
                mMetaData = nullptr;
            }
            // !copy meta
            // copy children
            if (mNumChildren > 0) {
                memcpy(ppChildren, o.ppChildren, MAX_CHILDREN * 8);
            }
            else {
                memset(ppChildren, 0, MAX_CHILDREN * 8);
            }
            // !copy children
        }

        inline pts_entry(bool is_dir, const char* name, uint start, uint size) noexcept :
            mIsDirectory(is_dir), mIsCompressed(), mMetaSize(), mMetaData(), mStartPos(start), mBlobSize(size),
            mNumChildren(), pParent(), ppChildren()
        {
            memset(ppChildren, 0, sizeof(ppChildren));
            const auto nm = wg::string_view(name);
            mNameLen = u8(min(nm.size(), 255u));
            for (int i = 0; i < MAX_NAME && i < mNameLen; ++i)
                mName[i] = nm[i];
            mName[mNameLen] = 0;
        }

        /**
         * This method releases resources for all children, and deletes itself.
         * (NO EFFECTS TO BLOB)
         */
        inline void release() noexcept {
            /**
             * Firstly-first, recursive go down till last child, and release it
             * with 'down->top' model.
             */
            for (uint i = 0; i < MAX_CHILDREN && i < mNumChildren; ++i) {
                pts_entry* child = ppChildren[i];
                child->release();
            }

            delete[] mMetaData;
            *this = {};
        }

        inline void rename(const string_view& name) noexcept {
            memcpy(mName, name.c_str(), min(name.size(), MAX_NAME));
        }

        /**
         * Addicts a new child object to children list, but if there is no
         * empty space for new ones, it reserves single entry for a new
         * directory entry, in order to not to stuck with 'filled space'
         * PTS structure that can't grow.
         * @return pointer to created child inside this entry, otherwise NULL.
         */
        inline pts_entry* add_child(const pts_entry& child) noexcept {
            if (((mNumChildren + 1) >= MAX_CHILDREN) && !child.mIsDirectory) return nullptr;

            const auto id = mNumChildren++;
            ppChildren[id] = new pts_entry(child);
            ppChildren[id]->pParent = this;
            return ppChildren[id];
        }

        /**
         * Address of data inside associated blob object.
         */
        inline uint get_address() const noexcept { return mStartPos; }
        /**
         * Size(in bytes) of data which is pointed by entry.
         */
        inline uint get_size() const noexcept { return mBlobSize; }
        inline uint get_children_count() const noexcept { return mNumChildren; }
        inline uint get_meta_size() const noexcept { return mMetaSize; }

        inline string_view get_name() const noexcept { return { mName, mNameLen }; }

        inline pts_entry* get_child(uint i) const noexcept { return ppChildren[i]; }
        inline pts_entry* get_parent() const noexcept { return pParent; }

        inline bool is_root() const noexcept { return pParent == nullptr; }
        inline bool is_dir() const noexcept { return mIsDirectory; }
        inline bool is_compressed() const noexcept { return mIsCompressed; }

        inline char* get_meta_data() const noexcept {
            return mMetaData;
        }

        template<class T>
        inline void set_meta(T obj) noexcept {
            mMetaSize = sizeof(obj);
            mMetaData = new char[mMetaSize]{};
            memcpy(mMetaData, &obj, sizeof(obj));
        }

        /**
         * Search for a child with name, and returns its pointer, otherwise nullptr.
         */
        inline pts_entry* find_child(const char* name) noexcept {
            for (uint i = 0; i < MAX_CHILDREN && i < mNumChildren; ++i) {
                if (ppChildren[i] && ppChildren[i]->get_name() == name)
                    return ppChildren[i];
            }
            return nullptr;
        }

    private:
        bool mIsDirectory;      // whether is this entry a directory or a file.
        char mName[MAX_NAME];  // store name of an entry.
        u8 mNameLen;            // META, not stored at all.
        bool mIsCompressed;     // whether is this file compressed or not.
        uint mMetaSize;         // size of additional meta info structure.
        char* mMetaData;        // meta structure raw data.
        uint mStartPos;    // start position of a data blob.
        uint mBlobSize;         // size (in bytes) of a data blob.

        pts_entry* pParent;     // pointer to the parent entry (NULL in root)
        pts_entry* ppChildren[MAX_CHILDREN]; // array of pointers to the children entries.
        uint mNumChildren;      // number of children

        friend void read_entry(class file* fp, pts_entry* e);
    };

    inline pts_entry* pts_entry_create_dir(const char* name) noexcept {
        return new pts_entry(true, name, 0, 0);
    }
}

#endif //WHITEGEAR_PTS_BASE_HPP

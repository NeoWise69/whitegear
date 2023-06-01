
/*******************************************************************************
 * Copyright (c) 2023.
 * This file is part of The WhiteGear Studio software property.
 * If you get unexpected access to this file, or part ot whole codebase, you should
 * report this source code leak and delete all copies of source code from all your machines.
 ******************************************************************************/

#include "hash_base.hpp"

namespace wg::experimental {
    void hash_iterator_base::next_node() {
        if (mPtr)
            mPtr = mPtr->mNext;
    }
    void hash_iterator_base::prev_node() {
        if (mPtr)
            mPtr = mPtr->mPrev;
    }
    bool operator==(const hash_iterator_base &a, const hash_iterator_base &b) {
        return a.mPtr == b.mPtr;
    }
    bool operator!=(const hash_iterator_base &a, const hash_iterator_base &b) {
        return a.mPtr != b.mPtr;
    }

    uint hash_base::size() const {
        return mPtrs ? ((uint*)(mPtrs))[0] : 0u;
    }
    uint hash_base::get_num_buckets() const {
        return mPtrs ? ((uint*)(mPtrs))[1] : 0u;
    }
    bool hash_base::empty() const {
        return size() == 0;
    }
    void hash_base::_allocate_buckets(uint size, uint num_buckets) {
        delete[] mPtrs;

        auto** ptrs = new hash_node_base*[num_buckets + 2];
        auto* data = (uint*)(ptrs);
        data[0] = size;
        data[1] = num_buckets;
        mPtrs = ptrs;

        _reset_ptrs();
    }
    void hash_base::_reset_ptrs() {
        if (!mPtrs) return;

        const auto num_buckets = get_num_buckets();
        auto** ptrs = _get_ptrs();
        for (uint i = 0; i < num_buckets; ++i) {
            ptrs[i] = nullptr;
        }
    }
}

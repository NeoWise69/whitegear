
/*******************************************************************************
 * Copyright (c) 2023.
 * This file is part of The WhiteGear Studio software property.
 * If you get unexpected access to this file, or part ot whole codebase, you should
 * report this source code leak and delete all copies of source code from all your machines.
 ******************************************************************************/

#ifndef WHITEGEAR_HASH_BASE_HPP
#define WHITEGEAR_HASH_BASE_HPP

#include "core/hash.hpp"
#include "core/utils.hpp"
#include "blocked_allocator.hpp"

namespace wg {
    /**
     * Node base class.
     */
    struct hash_node_base {
        inline hash_node_base() = default;
        /**
         * Next node in a bucket.
         */
        hash_node_base* mDown = nullptr;

        hash_node_base* mPrev = nullptr;
        hash_node_base* mNext = nullptr;
    };
    /**
     * Node iterator class base.
     */
    struct hash_iterator_base {
        inline hash_iterator_base() = default;
        /**
         * Explicit load constructor.
         */
        inline explicit hash_iterator_base(hash_node_base* p) : mPtr(p)
        {}
        /**
         * Go to next node, if exists.
         */
        void next_node();
        /**
         * Back to previous node.
         */
        void prev_node();

        hash_node_base* mPtr = nullptr;
    };
    /**
     * Test for equality between hash_iterators.
     */
    bool operator==(const hash_iterator_base& a, const hash_iterator_base& b);
    /**
     * Test for equality between hash_iterators.
     */
    bool operator!=(const hash_iterator_base& a, const hash_iterator_base& b);

    class hash_base {
    public:
        inline static constexpr auto MIN_BUCKETS = 8ull;
        inline static constexpr auto MAX_LOAD_FACTOR = 4ull;

        inline hash_base() = default;

        uint size() const;
        uint get_num_buckets() const;
        bool empty() const;
    protected:
        inline void _set_size(uint n) {
            if (mPtrs) {
                ((uint*)(mPtrs))[0] = n;
            }
        }
        inline hash_node_base** _get_ptrs() const {
            return mPtrs ? (hash_node_base**)(mPtrs + 2) : (hash_node_base**)nullptr;
        }
        void _reset_ptrs();
        void _allocate_buckets(uint size, uint num_buckets);

        hash_node_base* mHead = nullptr;
        hash_node_base* mTail = nullptr;
        hash_node_base** mPtrs = nullptr;
        allocator_block* mAllocator = nullptr;

        friend void wg::swap(hash_base&, hash_base&);
    };
}
namespace wg {
    template<>
    inline void swap(hash_base& a, hash_base& b) {
        swap(a.mHead, b.mHead);
        swap(a.mTail, b.mTail);
        swap(a.mPtrs, b.mPtrs);
        swap(a.mAllocator, b.mAllocator);
    }
}

#endif //WHITEGEAR_HASH_BASE_HPP

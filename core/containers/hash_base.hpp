
/*******************************************************************************
 * Copyright (c) 2023.
 * This file is part of The WhiteGear Studio software property.
 * If you get unexpected access to this file, or part ot whole codebase, you should
 * report this source code leak and delete all copies of source code from all your machines.
 ******************************************************************************/

#ifndef WHITEGEAR_HASH_BASE_HPP
#define WHITEGEAR_HASH_BASE_HPP

#include <core/hash.hpp>
#include <core/utils.hpp>
#include "blocked_allocator.hpp"

namespace wg {
    /**
     * Node base class.
     */
    struct hash_node_base {
        inline hash_node_base() noexcept = default;
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
        inline hash_iterator_base() noexcept = default;
        /**
         * Explicit load constructor.
         */
        inline explicit hash_iterator_base(hash_node_base* p) noexcept : mPtr(p)
        {}
        /**
         * Go to next node, if exists.
         */
        void next_node() noexcept;
        /**
         * Back to previous node.
         */
        void prev_node() noexcept;

        hash_node_base* mPtr = nullptr;
    };
    /**
     * Test for equality between hash_iterators.
     */
    bool operator==(const hash_iterator_base& a, const hash_iterator_base& b) noexcept;
    /**
     * Test for equality between hash_iterators.
     */
    bool operator!=(const hash_iterator_base& a, const hash_iterator_base& b) noexcept;

    class hash_base {
    public:
        inline static constexpr auto MIN_BUCKETS = 8ull;
        inline static constexpr auto MAX_LOAD_FACTOR = 4ull;

        inline hash_base() noexcept = default;

        uint size() const noexcept;
        uint get_num_buckets() const noexcept;
        bool empty() const noexcept;

        inline void swap(hash_base& b) {
            wg::swap(mHead, b.mHead);
            wg::swap(mTail, b.mTail);
            wg::swap(mPtrs, b.mPtrs);
            wg::swap(mAllocator, b.mAllocator);
        }
    protected:
        inline void _set_size(uint n) noexcept {
            if (mPtrs) {
                ((uint*)(mPtrs))[0] = n;
            }
        }
        inline hash_node_base** _get_ptrs() const noexcept {
            return mPtrs ? (hash_node_base**)(mPtrs + 2) : (hash_node_base**)nullptr;
        }
        void _reset_ptrs() noexcept;
        void _allocate_buckets(uint size, uint num_buckets) noexcept;

        hash_node_base* mHead = nullptr;
        hash_node_base* mTail = nullptr;
        hash_node_base** mPtrs = nullptr;
        allocator_block* mAllocator = nullptr;

    };
}
namespace wg {
    template<>
    inline void swap(hash_base& a, hash_base& b) noexcept {
        a.swap(b);
    }
}

#endif //WHITEGEAR_HASH_BASE_HPP

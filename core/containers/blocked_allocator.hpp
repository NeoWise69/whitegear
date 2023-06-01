
/*******************************************************************************
 * Copyright (c) 2023.
 * This file is part of The WhiteGear Studio software property.
 * If you get unexpected access to this file, or part ot whole codebase, you should
 * report this source code leak and delete all copies of source code from all your machines.
 ******************************************************************************/

#ifndef WHITEGEAR_BLOCKED_ALLOCATOR_HPP
#define WHITEGEAR_BLOCKED_ALLOCATOR_HPP

#include <core/typedefs.hpp>

#include <utility> // std::forward

namespace wg {
    struct allocator_node {
        /**
         * Next free node.
         */
        allocator_node* next;
    };
    /**
     * Allocator block of memory.
     */
    struct allocator_block {
        uint node_size;
        /**
         * Maximum amount of nodes in this block.
         */
        uint capacity;
        /**
         * First free node.
         */
        allocator_node* free;
        /**
         * Next allocator block.
         */
        allocator_block* next;
    };
    /**
     * Creates new allocator for fixed size elements, with initial capacity.
     */
    allocator_block* allocator_create(uint node_size, uint i_capacity = 1);
    /**
     * Destroys an p_allocator and frees all blocks in the chain.
     */
    void allocator_destroy(allocator_block* p_allocator);
    /**
     * Allocates new memory from blocks chain, and creates new once, if necessary.
     */
    void* allocator_alloc(allocator_block* p_allocator);
    /**
     * Free the node. Doesn't free any blocks.
     */
    void allocator_free(allocator_block* p_allocator, void* p);

    /**
     * Fixed allocator for object type.
     */
    template<class T>
    class blocked_allocator {
    public:
        inline blocked_allocator() = default;
        inline blocked_allocator(uint initial_capacity) {
            if (initial_capacity) {
                mAllocator = allocator_create(sizeof(T), initial_capacity);
            }
        }
        inline ~blocked_allocator() {
            if (mAllocator) // maybe we're not initialized allocator properly, like in a default constructor.
                allocator_destroy(mAllocator);
        }
        /**
         * Allocate a new object with arguments.
         */
        template<class...Args>
        T* allocate(Args&&...args) {
            if (!mAllocator) {
                mAllocator = allocator_create(sizeof(T));
            }
            T* p = (T*)(allocator_alloc(mAllocator));
            new(p) T(std::forward<Args>(args)...);
            return p;
        }
        void free(T* p) {
            (p)->~T();
            allocator_free(mAllocator, p);
        }
    private:
        blocked_allocator(const blocked_allocator&);
        blocked_allocator& operator=(const blocked_allocator&);

        allocator_block* mAllocator = nullptr;
    };
}

#endif //WHITEGEAR_BLOCKED_ALLOCATOR_HPP

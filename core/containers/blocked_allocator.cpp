
/*******************************************************************************
 * Copyright (c) 2023.
 * This file is part of The WhiteGear Studio software property.
 * If you get unexpected access to this file, or part ot whole codebase, you should
 * report this source code leak and delete all copies of source code from all your machines.
 ******************************************************************************/

#include "blocked_allocator.hpp"

namespace wg {
    namespace {
        allocator_block* allocator_reserve_block(allocator_block* allocator, uint node_size, uint capacity) {
            if (!capacity) capacity = 1u;
            u8* p_block = new u8[sizeof(allocator_block) + capacity * (sizeof(allocator_node) + node_size)]{};
            auto* p_allocator = (allocator_block*)p_block;
            p_allocator->node_size = node_size;
            p_allocator->capacity = capacity;
            p_allocator->free = nullptr;
            p_allocator->next = nullptr;

            if (!allocator) {
                allocator = p_allocator;
            }
            else {
                p_allocator->next = allocator->next;
                allocator->next = p_allocator;
            }

            u8* p_node = p_block + sizeof(allocator_block);
            auto* first_node = (allocator_node*)p_node;

            const auto n = sizeof(allocator_node) + node_size;
            for (uint i = 0; i < capacity - 1; ++i) {
                auto* new_node = (allocator_node*)p_node;
                new_node->next = (allocator_node*)(p_node + n);
                p_node += n;
            }
            {
                auto* new_node = (allocator_node*)p_node;
                new_node->next = nullptr;
            }
            allocator->free = first_node;
            return p_allocator;
        }
    }

    allocator_block* allocator_create(uint node_size, uint i_capacity) {
        return allocator_reserve_block(nullptr, node_size, i_capacity);
    }
    void allocator_destroy(allocator_block* p_allocator) {
        while (p_allocator) {
            auto* p_next = p_allocator->next;
            delete[] (u8*)(p_allocator);
            p_allocator = p_next;
        }
    }
    void* allocator_alloc(allocator_block* p_allocator) {
        if (!p_allocator) return nullptr;
        if (!p_allocator->free) {
            uint new_capacity = (p_allocator->capacity + 1) << 1;
            allocator_reserve_block(p_allocator, p_allocator->node_size, new_capacity);
            p_allocator->capacity = new_capacity;
        }
        auto* free_node = p_allocator->free;
        void* p = (void*)(((u8*)(free_node)) + sizeof(allocator_node));
        p_allocator->free = free_node->next;
        free_node->next = nullptr;
        return p;
    }
    void allocator_free(allocator_block* p_allocator, void* p) {
        if (p_allocator && p) {
            auto* p_data = (u8*)p;
            auto* p_node = (allocator_node*)(p_data - sizeof(allocator_node));
            p_node->next = p_allocator->free;
            p_allocator->free = p_node;
        }
    }
}

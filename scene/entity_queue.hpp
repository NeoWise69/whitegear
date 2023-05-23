
/*******************************************************************************
 * Copyright (c) 2023.
 * This file is part of The WhiteGear Studio software property.
 * If you get unexpected access to this file, or part ot whole codebase, you should
 * report this source code leak and delete all copies of source code from all your machines.
 ******************************************************************************/

#ifndef WHITEGEAR_ENTITY_QUEUE_HPP
#define WHITEGEAR_ENTITY_QUEUE_HPP

#include <scene/entity.hpp>

namespace wg {
    class entity_queue {
    public:
        entity_queue();
        inline ~entity_queue() = default;

        entity_t dequeue();
        void enqueue(entity_t entt);
        entity_t peek() const;
        entity_t front() const;
        entity_t back() const;
        i64 size() const;
        bool empty() const;
        bool full() const;

    private:
        entity_t mEntities[MAX_ENTITIES];
        i64 mFront;
        i64 mRear;
        i64 mCount;
    };
}

#endif //WHITEGEAR_ENTITY_QUEUE_HPP

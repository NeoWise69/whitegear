
/*******************************************************************************
 * Copyright (c) 2023.
 * This file is part of The WhiteGear Studio software property.
 * If you get unexpected access to this file, or part ot whole codebase, you should
 * report this source code leak and delete all copies of source code from all your machines.
 ******************************************************************************/

#include <scene/entity_queue.hpp>
#include "core/logger.hpp"

namespace wg {
    entity_queue::entity_queue() : mEntities(), mFront(), mRear(), mCount() {}

    entity_t entity_queue::dequeue() {
        if (empty()) {
            out
            .error("Failed to dequeue entity id! entity_queue is EMPTY. UNDERFLOW!");
            return -1;
        }

        const auto e = mEntities[mFront];
        mFront = (mFront + 1) % MAX_ENTITIES;
        --mCount;

        return e;
    }

    void entity_queue::enqueue(entity_t entt) {
        if (full()) {
            out
            .error("Failed to enqueue entity id! entity_queue is FULL. OVERFLOW!");
            return;
        }

        mRear = (mRear + 1) % MAX_ENTITIES;
        mEntities[mRear] = entt;
        ++mCount;
    }

    entity_t entity_queue::peek() const {
        if (empty()) {
            out
                    .error("Failed to peek entity id! entity_queue is EMPTY. UNDERFLOW!");
            return -1;
        }
        return mEntities[mFront];
    }

    i64 entity_queue::size() const {
        return mCount;
    }

    bool entity_queue::empty() const {
        return !mCount;
    }

    bool entity_queue::full() const {
        return mCount == MAX_ENTITIES;
    }

    entity_t entity_queue::front() const {
        return mEntities[mFront];
    }

    entity_t entity_queue::back() const {
        return mEntities[mRear];
    }
}

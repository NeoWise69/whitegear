
/*******************************************************************************
 * Copyright (c) 2023.
 * This file is part of The WhiteGear Studio software property.
 * If you get unexpected access to this file, or part ot whole codebase, you should
 * report this source code leak and delete all copies of source code from all your machines.
 ******************************************************************************/

#ifndef WHITEGEAR_COMPONENT_ARRAY_HPP
#define WHITEGEAR_COMPONENT_ARRAY_HPP

#include <scene/component.hpp>
#include <scene/entity.hpp>
#include <core/containers/hashmap.hpp>

namespace wg {
    class component_array_base {
    public:
        virtual ~component_array_base() = default;
        virtual void on_entity_destroyed(entity_t) = 0;
    };
    template<class T>
    class component_array : public component_array_base {
    public:
        inline component_array() : mComponentArray(), mSize() {}
        inline ~component_array() override = default;

        inline void insert_data(entity_t entt, const T& component_data) {
            assert(mToIndex.find(entt) == mToIndex.end() && "Component added to same entity more than once.");

            const auto id = mSize;
            mToIndex[entt] = id;
            mToEntity[id] = entt;
            mComponentArray[id] = component_data;
            ++mSize;
        }

        inline void remove_data(entity_t entt) {
            assert(mToIndex.find(entt) != mToIndex.end() && "Removing non-existent component.");

            const auto id_to_remove = mToIndex[entt];
            const auto id_last = mSize - 1;
            mComponentArray[id_to_remove] = mComponentArray[id_last];

            const auto entt_last = mToEntity[id_last];
            mToIndex[entt_last] = id_to_remove;
            mToEntity[id_to_remove] = entt_last;

            mToIndex.erase(entt);
            mToEntity.erase(id_last);

            --mSize;
        }

        inline T& get_data(entity_t entt) {
            assert(mToIndex.find(entt) != mToIndex.end() && "Retrieving non-existent component.");

            return mComponentArray[mToIndex[entt]];
        }

        inline const T& get_data(entity_t entt) const {
            assert(mToIndex.find(entt) != mToIndex.end() && "Retrieving non-existent component.");

            return mComponentArray[mToIndex.at(entt)];
        }

        inline bool has_data(entity_t entt) const {
            return mToIndex.contains(entt);
        }

        inline void on_entity_destroyed(entity_t entt) override {
            if (mToIndex.find(entt) != mToIndex.end()) {
                remove_data(entt);
            }
        }

    private:
        T mComponentArray[MAX_ENTITIES];
        hashmap<entity_t, u64> mToIndex;
        hashmap<u64, entity_t> mToEntity;
        u64 mSize;
    };
}

#endif //WHITEGEAR_COMPONENT_ARRAY_HPP

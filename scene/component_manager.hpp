
/*******************************************************************************
 * Copyright (c) 2023.
 * This file is part of The WhiteGear Studio software property.
 * If you get unexpected access to this file, or part ot whole codebase, you should
 * report this source code leak and delete all copies of source code from all your machines.
 ******************************************************************************/

#ifndef WHITEGEAR_COMPONENT_MANAGER_HPP
#define WHITEGEAR_COMPONENT_MANAGER_HPP

#include <scene/component_array.hpp>
#include <core/smart_ptr.hpp>

namespace wg {
    class component_manager {
    public:
        inline component_manager() : mComponentArrays(), mComponentTypes(), mNextComponentType()
        {}
        inline ~component_manager() = default;

        template<class T>
        inline void register_component() {
            assert(mComponentTypes.find(T::COMPONENT_ID) == mComponentTypes.end() && "Registering component type more than once.");
            mComponentTypes.insert({T::COMPONENT_ID, mNextComponentType});
            mComponentArrays.insert({T::COMPONENT_ID, make_shared<component_array<T>>()});
            ++mNextComponentType;
        }

        template<class T>
        inline component_type_t get_component_type() {
            assert(mComponentTypes.find(T::COMPONENT_ID) != mComponentTypes.end() && "Component not registered before use.");
            return mComponentTypes[T::COMPONENT_ID];
        }

        template<class T>
        inline void add_component(entity_t entt, const T& component) {
            get_component_array<T>()->insert_data(entt, component);
        }

        template<class T>
        inline void remove_component(entity_t entt) {
            get_component_array<T>()->remove_data(entt);
        }

        template<class T>
        inline T& get_component(entity_t entt) {
            return get_component_array<T>()->get_data(entt);
        }

        inline void on_entity_destroyed(entity_t entt) {
            for (const auto&[name, component] : mComponentArrays) {
                component->on_entity_destroyed(entt);
            }
        }

    private:
        hashmap<component_id, component_type_t> mComponentTypes;
        hashmap<component_id, shared_ptr<component_array_base>> mComponentArrays;
        component_type_t mNextComponentType;

        template<class T>
        inline shared_ptr<component_array<T>> get_component_array() {
            assert(mComponentTypes.find(T::COMPONENT_ID) != mComponentTypes.end() && "Component not registered before use.");
            return static_pointer_cast<component_array<T>>(mComponentArrays[T::COMPONENT_ID]);
        }
    };
}

#endif //WHITEGEAR_COMPONENT_MANAGER_HPP

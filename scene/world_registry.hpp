
/*******************************************************************************
 * Copyright (c) 2023.
 * This file is part of The WhiteGear Studio software property.
 * If you get unexpected access to this file, or part ot whole codebase, you should
 * report this source code leak and delete all copies of source code from all your machines.
 ******************************************************************************/

#ifndef WHITEGEAR_WORLD_REGISTRY_HPP
#define WHITEGEAR_WORLD_REGISTRY_HPP

#include <scene/entity_manager.hpp>
#include <scene/component_manager.hpp>
#include <scene/system.hpp>

namespace wg {
    class world_registry {
    public:

        entity_t entity_create();
        void entity_destroy(entity_t entt);

        template<class T>
        inline void register_component() {
            mComponentManager->register_component<T>();
        }

        template<class T>
        inline void add_component(entity_t entt, const T& component) {
            mComponentManager->add_component<T>(entt, component);
            auto f = mEntityManager->get_footprint(entt);
            f.set(i32(mComponentManager->get_component_type<T>()), true);
            mEntityManager->assign_footprint(entt, f);
            mSceneSystemManager->on_entity_footprint_changed(entt, f);
        }

        template<class T>
        inline void remove_component(entity_t entt) {
            mComponentManager->remove_component<T>(entt);
            auto f = mEntityManager->get_footprint(entt);
            f.set(i32(mComponentManager->get_component_type<T>()), false);
            mEntityManager->assign_footprint(entt, f);
            mSceneSystemManager->on_entity_footprint_changed(entt, f);
        }

        template<class T>
        inline T& get_component(entity_t entt) {
            return mComponentManager->get_component<T>(entt);
        }

        template<class T>
        inline const T& get_component(entity_t entt) const {
            return mComponentManager->get_component<T>(entt);
        }

        template<class T>
        inline bool has_component(entity_t entt) const {
            return mComponentManager->has_component<T>(entt);
        }

        template<class T>
        inline component_type_t get_component_type() {
            return mComponentManager->get_component_type<T>();
        }

        template<class T, class...Args>
        inline ref_ptr<T> register_scene_system(Args&&...args) {
            return mSceneSystemManager->register_system<T>(std::forward<Args>(args)...);
        }

        template<class T>
        inline void assign_scene_system_footprint(const footprint& f) {
            mSceneSystemManager->assign_footprint<T>(f);
        }

    private:
        scoped_ptr<component_manager> mComponentManager = make_scoped<component_manager>();
        scoped_ptr<entity_manager> mEntityManager = make_scoped<entity_manager>();
        scoped_ptr<scene_system_manager> mSceneSystemManager = make_scoped<scene_system_manager>();
    };
}

#endif //WHITEGEAR_WORLD_REGISTRY_HPP

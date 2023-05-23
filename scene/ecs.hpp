
/*******************************************************************************
 * Copyright (c) 2023.
 * This file is part of The WhiteGear Studio software property.
 * If you get unexpected access to this file, or part ot whole codebase, you should
 * report this source code leak and delete all copies of source code from all your machines.
 ******************************************************************************/

#ifndef WHITEGEAR_ECS_HPP
#define WHITEGEAR_ECS_HPP

#include <scene/entity_manager.hpp>
#include <scene/component_manager.hpp>
#include <scene/system.hpp>

namespace wg {
    class ecs {
    public:

        static entity_t entity_create();
        static void entity_destroy(entity_t entt);

        template<class T>
        inline static void register_component() {
            mComponentManager->register_component<T>();
        }

        template<class T>
        inline static void add_component(entity_t entt, const T& component) {
            mComponentManager->add_component<T>(entt, component);
            auto f = mEntityManager->get_footprint(entt);
            f.set(mComponentManager->get_component_type<T>(), true);
            mEntityManager->assign_footprint(entt, f);
            mSceneSystemManager->on_entity_footprint_changed(entt, f);
        }

        template<class T>
        inline static void remove_component(entity_t entt) {
            mComponentManager->remove_component<T>(entt);
            auto f = mEntityManager->get_footprint(entt);
            f.set(mComponentManager->get_component_type<T>(), false);
            mEntityManager->assign_footprint(entt, f);
            mSceneSystemManager->on_entity_footprint_changed(entt, f);
        }

        template<class T>
        inline static T& get_component(entity_t entt) {
            return mComponentManager->get_component<T>(entt);
        }

        template<class T>
        inline static component_type_t get_component_type() {
            return mComponentManager->get_component_type<T>();
        }

        template<class T>
        inline static shared_ptr<T> register_scene_system() {
            mSceneSystemManager->register_system<T>();
        }

        template<class T>
        inline static void assign_scene_system_footprint(const footprint& f) {
            mSceneSystemManager->assign_footprint<T>(f);
        }

    private:
        static unique_ptr<component_manager> mComponentManager;
        static unique_ptr<entity_manager> mEntityManager;
        static unique_ptr<scene_system_manager> mSceneSystemManager;
    };
}

#endif //WHITEGEAR_ECS_HPP

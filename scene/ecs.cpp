
/*******************************************************************************
 * Copyright (c) 2023.
 * This file is part of The WhiteGear Studio software property.
 * If you get unexpected access to this file, or part ot whole codebase, you should
 * report this source code leak and delete all copies of source code from all your machines.
 ******************************************************************************/

#include <scene/ecs.hpp>

namespace wg {
    unique_ptr<component_manager> ecs::mComponentManager = make_unique<component_manager>();
    unique_ptr<entity_manager> ecs::mEntityManager = make_unique<entity_manager>();
    unique_ptr<scene_system_manager> ecs::mSceneSystemManager = make_unique<scene_system_manager>();

    entity_t ecs::entity_create() {
        return mEntityManager->create_entity();
    }

    void ecs::entity_destroy(entity_t entt) {
        mEntityManager->destroy_entity(entt);
        mComponentManager->on_entity_destroyed(entt);
        mSceneSystemManager->on_entity_destroyed(entt);
    }
}

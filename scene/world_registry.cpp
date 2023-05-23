
/*******************************************************************************
 * Copyright (c) 2023.
 * This file is part of The WhiteGear Studio software property.
 * If you get unexpected access to this file, or part ot whole codebase, you should
 * report this source code leak and delete all copies of source code from all your machines.
 ******************************************************************************/

#include <scene/world_registry.hpp>

namespace wg {
    entity_t world_registry::entity_create() {
        return mEntityManager->create_entity();
    }

    void world_registry::entity_destroy(entity_t entt) {
        mEntityManager->destroy_entity(entt);
        mComponentManager->on_entity_destroyed(entt);
        mSceneSystemManager->on_entity_destroyed(entt);
    }
}

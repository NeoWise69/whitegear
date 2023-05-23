
/*******************************************************************************
 * Copyright (c) 2023.
 * This file is part of The WhiteGear Studio software property.
 * If you get unexpected access to this file, or part ot whole codebase, you should
 * report this source code leak and delete all copies of source code from all your machines.
 ******************************************************************************/

#include <scene/entity_manager.hpp>
#include <cassert>

namespace wg {

    entity_manager::entity_manager() : mEntitiesInFlight(), mFootprints(), mAvailableEntities() {
        for (auto i = MAX_ENTITIES - MAX_ENTITIES; i < MAX_ENTITIES; ++i)
            mAvailableEntities.push(i);
    }

    entity_t entity_manager::create_entity() {
        assert(mEntitiesInFlight < MAX_ENTITIES && "Entities overflow!");

        const auto e = mAvailableEntities.front();
        mAvailableEntities.pop();
        ++mEntitiesInFlight;

        return e;
    }

    void entity_manager::destroy_entity(entity_t entt) {
        assert(entt < MAX_ENTITIES && "Entity is out of range!");

        mFootprints[entt].reset();
        mAvailableEntities.push(entt);
        --mEntitiesInFlight;
    }

    void entity_manager::assign_footprint(entity_t entt, const footprint &f) {
        assert(entt < MAX_ENTITIES && "Entity is out of range!");

        mFootprints[entt] = f;
    }

    footprint entity_manager::get_footprint(entity_t entt) const {
        assert(entt < MAX_ENTITIES && "Entity is out of range!");

        return mFootprints[entt];
    }
}

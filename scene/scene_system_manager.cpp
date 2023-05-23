
/*******************************************************************************
 * Copyright (c) 2023.
 * This file is part of The WhiteGear Studio software property.
 * If you get unexpected access to this file, or part ot whole codebase, you should
 * report this source code leak and delete all copies of source code from all your machines.
 ******************************************************************************/

#include <scene/system.hpp>

namespace wg {
    void scene_system_manager::on_entity_destroyed(entity_t entt) {
        for (const auto&[system_id, system] : mSystems) {
            system->entities.erase(entt);
        }
    }

    void scene_system_manager::on_entity_footprint_changed(entity_t entt, const footprint &f) {
        for (const auto&[system_id, system] : mSystems) {
            const auto& system_footprint = mFootprints[system_id];

            if ((f & system_footprint) == system_footprint) {
                system->entities.insert(entt);
            }
            else {
                system->entities.erase(entt);
            }
        }
    }

}

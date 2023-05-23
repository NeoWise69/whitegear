
/*******************************************************************************
 * Copyright (c) 2023.
 * This file is part of The WhiteGear Studio software property.
 * If you get unexpected access to this file, or part ot whole codebase, you should
 * report this source code leak and delete all copies of source code from all your machines.
 ******************************************************************************/

#ifndef WHITEGEAR_ENTITY_MANAGER_HPP
#define WHITEGEAR_ENTITY_MANAGER_HPP

#include <scene/entity.hpp>
#include <scene/component.hpp>
#include <queue>

namespace wg {
    class entity_manager {
    public:
        entity_manager();
        inline ~entity_manager() = default;

        entity_t create_entity();
        void destroy_entity(entity_t entt);
        void assign_footprint(entity_t entt, const footprint& f);
        footprint get_footprint(entity_t entt) const;

    private:
        std::queue<entity_t> mAvailableEntities;
        footprint mFootprints[MAX_ENTITIES];
        uint mEntitiesInFlight;
    };
}

#endif //WHITEGEAR_ENTITY_MANAGER_HPP

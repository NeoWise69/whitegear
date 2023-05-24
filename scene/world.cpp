
/*******************************************************************************
 * Copyright (c) 2023.
 * This file is part of The WhiteGear Studio software property.
 * If you get unexpected access to this file, or part ot whole codebase, you should
 * report this source code leak and delete all copies of source code from all your machines.
 ******************************************************************************/

#include <scene/world.hpp>
#include <core/logger.hpp>

// components
#include <scene/components/transform.hpp>

namespace wg {
    bool world::initialize(rendering_engine* p_renda) {
        this->renda = p_renda;

        registry.register_component<component_transform>();

        renderingSystem = registry.register_scene_system<rendering_system>(&registry);
        if (!renderingSystem) {
            out
            .error("Failed to register_scene_system<rendering_system>()!");
            return false;
        }
        {   /* setup rendering_system components model */
            footprint rendering_system_footprint;
            rendering_system_footprint.set(registry.get_component_type<component_transform>());
            registry.assign_scene_system_footprint<rendering_system>(rendering_system_footprint);
        }

        return true;
    }

    bool world::load() {
        /**
         * Load required data from disk
         */

        for (uint i = 0; i < 100; ++i) {
            const entity_t e = registry.entity_create();
            registry.add_component(e, component_transform{
                    vec3(scalar(i), scalar(i), scalar(i)),
                    vec3(0),
                    vec3(1)
            });
        }

        return true;
    }

    bool world::unload() {
        /**
         * Unload all loaded data from memory.
         */
        return true;
    }

    bool world::uninitialize() {
        return true;
    }

    bool world::on_tick(world_tick_data &data) {
        if (!renderingSystem->render_scene(renda))
            return false;

        return true;
    }
}

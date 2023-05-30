
/*******************************************************************************
 * Copyright (c) 2023.
 * This file is part of The WhiteGear Studio software property.
 * If you get unexpected access to this file, or part ot whole codebase, you should
 * report this source code leak and delete all copies of source code from all your machines.
 ******************************************************************************/

#include <scene/world.hpp>
#include <core/logger.hpp>
#include <renda/rendering_engine.hpp>

// components
#include <scene/components/transform.hpp>

namespace wg {
    bool world::initialize(rendering_engine* p_renda) {
        renda = p_renda;
        renda->set_parent_world(this);

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

        for (uint x = 0; x < 16; ++x) {
            for (uint y = 0; y < 16; ++y) {
                const entity_t e = registry.entity_create();
                registry.add_component(e, component_transform{
                        vec3(scalar(x * 4), scalar(0), scalar(y * 4)),
                        vec3(0),
                        vec3(1)
                });
                rendering_engine::mesh_load_data load_data = {};
                load_data.entity = e;
                load_data.p_registry = &registry;

                renda->load_mesh(&load_data);
            }
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
        if (!renderingSystem->render_scene(renda, data))
            return false;

        auto& world_stats = stats();
        out
        .trace("DC:%d VPS:%d IPS:%d VPF:%d IPF:%d",
               world_stats.draw_calls, world_stats.vertices_on_scene, world_stats.indices_on_scene,
                                        world_stats.vertices_per_frame, world_stats.indices_per_frame);

        return true;
    }
}


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
#include <scene/components/common_geometry.hpp>

namespace wg {
    bool world::initialize(rendering_engine* p_renda) {
        renda = p_renda;
        renda->set_parent_world(this);

        registry.register_component<component_transform>();
        registry.register_component<component_common_geometry>();

        renderingSystem = registry.register_scene_system<rendering_system>(&registry);
        commonMeshRenderingSystem = registry.register_scene_system<common_mesh_rendering_system>(&registry);
        if (!renderingSystem) {
            out
            .error("Failed to register_scene_system<rendering_system>()!");
            return false;
        }
        if (!commonMeshRenderingSystem) {
            out
            .error("Failed to register_scene_system<common_mesh_rendering_system>()!");
            return false;
        }
        {   /* setup rendering_system components model */
            footprint fp;
            fp.set(registry.get_component_type<component_transform>());
            registry.assign_scene_system_footprint<rendering_system>(fp);
        }
        {   /* setup common_mesh_rendering_system components model */
            footprint fp;
            fp.set(registry.get_component_type<component_transform>());
            fp.set(registry.get_component_type<component_common_geometry>());
            registry.assign_scene_system_footprint<common_mesh_rendering_system>(fp);
        }

        return true;
    }

    bool world::load() {
        /**
         * Load required data from disk
         */

        for (uint x = 0; x < 32; ++x) {
            for (uint y = 0; y < 32; ++y) {
                const entity_t e = registry.entity_create();
                registry.add_component(e, component_transform{
                        vec3(scalar(x * 4), scalar(0), scalar(y * 4)),
                        vec3(0),
                        vec3(1)
                });
                registry.add_component(e, component_common_geometry{
                    component_common_geometry::COMMON_GEOMETRY_CUBE
                });
                rendering_engine::common_mesh_create_info create_info = {};
                create_info.entity = e;
                create_info.p_registry = &registry;
                create_info.mesh = rendering_engine::common_mesh_create_info::COMMON_MESH_CUBE;

                renda->create_common_mesh(&create_info);
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
        if (!commonMeshRenderingSystem->render_common_meshes(renda, data))
            return false;
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

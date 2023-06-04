
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
#include <scene/components/name_id.hpp>
#include <scene/components/common_geometry.hpp>
#include "core/time.hpp"

namespace wg {
    bool world::initialize(rendering_engine* p_renda) {
        renda = p_renda;
        renda->set_parent_world(this);

        registry.register_component<component_transform>();
        registry.register_component<component_common_geometry>();
        registry.register_component<component_name_id>();

        commonMeshRenderingSystem = registry.register_scene_system<common_mesh_rendering_system>(&registry);
        renderingSystem = registry.register_scene_system<rendering_system>(&registry);
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
                registry.add_component(e, component_name_id{
                    "entity"
                });
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
                entities[e] = true;
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

        const auto start = time_point::now();

        if (!commonMeshRenderingSystem->render_common_meshes(renda, data))
            return false;
        if (!renderingSystem->render_scene(renda, data))
            return false;

        /**
         * HERE UPDATE PASS
         */
        {

        }

        const auto end = time_point::now();
        GTimeStats.world_tick_time = end - start;

        auto& world_stats = stats();
        //out
        //.trace("frame_time=%.2fms, tick_time=%.2fms frame_begin_time=%.2fms frame_end_time=%.2fms world_tick_time=%.2fms",
        //       GTimeStats.frame_time.get(time_point::milliseconds),
        //       GTimeStats.tick_time.get(time_point::milliseconds),
        //       GTimeStats.frame_begin_time.get(time_point::milliseconds),
        //       GTimeStats.frame_end_time.get(time_point::milliseconds),
        //       GTimeStats.world_tick_time.get(time_point::milliseconds)
        //       );

        return true;
    }
}

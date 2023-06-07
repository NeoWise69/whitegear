
/*******************************************************************************
 * Copyright (c) 2023.
 * This file is part of The WhiteGear Studio software property.
 * If you get unexpected access to this file, or part ot whole codebase, you should
 * report this source code leak and delete all copies of source code from all your machines.
 ******************************************************************************/

#include <scene/world.hpp>
#include <renda/rendering_engine.hpp>

// Components
#include <scene/components/transform.hpp>
#include <scene/components/common_geometry.hpp>

namespace wg {
    bool world::common_mesh_rendering_system::render_common_meshes(rendering_engine *renda, world_tick_data &data) {
        for (const auto& e : entities) {
            // get transform
            auto& transform_component = registry->get_component<component_transform>(e);
            transform_component.update();
            const auto common_geometry_component = registry->get_component<component_common_geometry>(e);
            // get some rendering stuff

            rendering_engine::mesh_render_data render_data = {};
            render_data.p_transform = &transform_component.transform_matrix;
            render_data.entity = e;
            render_data.delta_time = data.delta_time;
            render_data.p_position = &transform_component.world_position;
            render_data.p_regenerate_bound = &transform_component.scale_changed;

            if (!renda->draw_mesh(&render_data)) {
                // load mesh
                rendering_engine::common_mesh_create_info ci = {};
                ci.entity = e;
                ci.mesh = (rendering_engine::common_mesh_create_info::type_t)(common_geometry_component.type);
                ci.p_registry = registry;
                renda->create_common_mesh(&ci);
                renda->draw_mesh(&render_data);
            }
        }
        return true;
    }
}

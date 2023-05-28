
/*******************************************************************************
 * Copyright (c) 2023.
 * This file is part of The WhiteGear Studio software property.
 * If you get unexpected access to this file, or part ot whole codebase, you should
 * report this source code leak and delete all copies of source code from all your machines.
 ******************************************************************************/

#include <scene/world.hpp>
#include <renda/rendering_engine.hpp>

// components
#include <scene/components/transform.hpp>

namespace wg {
    extern window* GWindow;

    bool world::rendering_system::render_scene(rendering_engine *renda) {
        for (const auto& e : entities) {
            // get transform
            const auto transform_component = registry->get_component<component_transform>(e);
            mat4 model_transform = transform_component.get_matrix();
            // get some rendering stuff

            rendering_engine::mesh_render_data render_data = {};
            render_data.p_transform = &model_transform;
            render_data.entity = e;
            renda->draw_mesh(&render_data);
        }

        return true;
    }
}

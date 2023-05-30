
/*******************************************************************************
 * Copyright (c) 2023.
 * This file is part of The WhiteGear Studio software property.
 * If you get unexpected access to this file, or part ot whole codebase, you should
 * report this source code leak and delete all copies of source code from all your machines.
 ******************************************************************************/

#ifndef WHITEGEAR_DX_SCENE_RENDERABLE_HPP
#define WHITEGEAR_DX_SCENE_RENDERABLE_HPP

#include "dx_renderable.hpp"
#include <math/geometry_buffer.hpp>
#include <scene/world_registry.hpp>

#if WG_WINDOWS

namespace wg {
    struct dx_scene_renderable_configuration {
        union {
            const geometry_buffer<VERTEX_TYPE_MESH> *p_mesh_geometry_buffer;
            const geometry_buffer<VERTEX_TYPE_NONE> *p_basic_geometry_buffer;
        };
        string_view filename_vs;
        string_view filename_ps;
    };
    class dx_scene_renderable : public dx_renderable {
    public:
        dx_scene_renderable(dx_graphics& gfx, world_registry* p_world_reg, entity_t entt, const dx_scene_renderable_configuration& config);
    };
}

#endif

#endif //WHITEGEAR_DX_SCENE_RENDERABLE_HPP

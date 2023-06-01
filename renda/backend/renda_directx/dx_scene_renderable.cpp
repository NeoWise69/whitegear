
/*******************************************************************************
 * Copyright (c) 2023.
 * This file is part of The WhiteGear Studio software property.
 * If you get unexpected access to this file, or part ot whole codebase, you should
 * report this source code leak and delete all copies of source code from all your machines.
 ******************************************************************************/

#include "dx_scene_renderable.hpp"
#include "dx_bindable_vertex_buffer.hpp"
#include "dx_bindable_index_buffer.hpp"
#include "dx_bindable_vertex_shader.hpp"
#include "dx_bindable_pixel_shader.hpp"
#include "dx_bindable_input_layout.hpp"
#include "dx_bindable_geometry_topology.hpp"
#include "dx_bindable_transform_constant_buffer.hpp"

#if WG_WINDOWS

namespace wg {
    dx_scene_renderable::dx_scene_renderable(dx_graphics& gfx, const dx_scene_renderable_configuration& config) {

        mNumVertices = config.p_mesh_geometry_buffer->get_num_vertices();

        mBoundingCube = geometry::cube::generate_bounding(config.p_mesh_geometry_buffer->get_vertices(), mNumVertices);

        add_bind(make_unique<dx_bindable_vertex_buffer>(gfx, config.p_mesh_geometry_buffer));
        auto vs = make_unique<dx_bindable_vertex_shader>(gfx, config.filename_vs.c_str());
        auto vsbc = vs->get_bytecode();
        add_bind(std::move(vs));

        add_bind(make_unique<dx_bindable_pixel_shader>(gfx, config.filename_ps.c_str()));
        add_index_buffer(make_unique<dx_bindable_index_buffer>(gfx, config.p_mesh_geometry_buffer));

        const bounded_array<D3D11_INPUT_ELEMENT_DESC, 2> ied = {
            { "POSITION", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
            { "COLOR", 0, DXGI_FORMAT_R8G8B8A8_UNORM, 0, 16, D3D11_INPUT_PER_VERTEX_DATA, 0 },
        };
        add_bind(make_unique<dx_bindable_input_layout>(gfx, ied, vsbc));
        add_bind(make_unique<dx_bindable_geometry_topology>(gfx, D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST));
        add_bind(make_unique<dx_bindable_transform_constant_buffer>(gfx, *this));
    }
}

#endif

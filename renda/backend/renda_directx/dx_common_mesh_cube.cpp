
/*******************************************************************************
 * Copyright (c) 2023.
 * This file is part of The WhiteGear Studio software property.
 * If you get unexpected access to this file, or part ot whole codebase, you should
 * report this source code leak and delete all copies of source code from all your machines.
 ******************************************************************************/

#include "dx_common_mesh_cube.hpp"
#include "renda/backend/renda_directx/bindable/dx_vertex_buffer.hpp"
#include "renda/backend/renda_directx/bindable/dx_index_buffer.hpp"
#include "renda/backend/renda_directx/bindable/dx_vertex_shader.hpp"
#include "renda/backend/renda_directx/bindable/dx_pixel_shader.hpp"
#include "renda/backend/renda_directx/bindable/dx_input_layout.hpp"
#include "renda/backend/renda_directx/bindable/dx_geometry_topology.hpp"
#include "renda/backend/renda_directx/bindable/dx_per_renderable_constant_buffer.hpp"

#if WG_WINDOWS

namespace wg {
    static bool SCommonMeshInitialized = false;

    dx_common_mesh_cube::dx_common_mesh_cube(dx_graphics &gfx, const dx_common_mesh_cube::create_info &cv_create_info) {
        mNumVertices = 8;

        static const auto cube_geometry = geometry_buffer<VERTEX_TYPE_MESH>::get_cube();

        if (!SCommonMeshInitialized) {
            mBoundingCube = geometry::box::generate_bounding(cube_geometry.get_vertices(),
                                                             cube_geometry.get_num_vertices());

            add_static_bind(make_scoped<dx_bindable_vertex_buffer>(gfx, &cube_geometry));
            auto vs = make_scoped<dx_bindable_vertex_shader>(gfx, cv_create_info.filename_vs.c_str());
            auto bytecode = vs->get_bytecode();
            add_static_bind(std::move(vs));

            add_static_bind(make_scoped<dx_bindable_pixel_shader>(gfx, cv_create_info.filename_ps.c_str()));
            add_static_index_buffer(make_scoped<dx_bindable_index_buffer>(gfx, &cube_geometry));

            const bounded_array<D3D11_INPUT_ELEMENT_DESC, 2> ied = {
                    {"POSITION", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 0,  D3D11_INPUT_PER_VERTEX_DATA, 0},
                    {"COLOR",    0, DXGI_FORMAT_R8G8B8A8_UNORM,     0, 16, D3D11_INPUT_PER_VERTEX_DATA, 0},
            };

            add_static_bind(make_scoped<dx_bindable_input_layout>(gfx, ied, bytecode));
            add_static_bind(make_scoped<dx_bindable_geometry_topology>(gfx, D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST));

            SCommonMeshInitialized = true;
        }
        else {
            set_index_from_static();
        }
        add_bind(make_scoped<dx_bindable_per_renderable_constant_buffer>(gfx, *this));
    }
}

#endif


/*******************************************************************************
 * Copyright (c) 2023.
 * This file is part of The WhiteGear Studio software property.
 * If you get unexpected access to this file, or part ot whole codebase, you should
 * report this source code leak and delete all copies of source code from all your machines.
 ******************************************************************************/

#include "dx_common_mesh_cube.hpp"
#include "dx_bindable_vertex_buffer.hpp"
#include "dx_bindable_index_buffer.hpp"
#include "dx_bindable_vertex_shader.hpp"
#include "dx_bindable_pixel_shader.hpp"
#include "dx_bindable_input_layout.hpp"
#include "dx_bindable_geometry_topology.hpp"
#include "dx_bindable_transform_constant_buffer.hpp"

#if WG_WINDOWS

namespace wg {
    static bool SCommonMeshInitialized = false;

    dx_common_mesh_cube::dx_common_mesh_cube(dx_graphics &gfx, world_registry *p_world_reg, entity_t entt,
                                             const dx_common_mesh_cube::create_info &cv_create_info)
         : dx_renderable(p_world_reg, entt) {

        mNumVertices = 8;

        static const auto cube_geometry = geometry_buffer<VERTEX_TYPE_MESH>::get_cube();

        if (!SCommonMeshInitialized) {
            mBoundingCube = geometry::cube::generate_bounding(cube_geometry.get_vertices(),
                                                              cube_geometry.get_num_vertices());

            add_static_bind(make_unique<dx_bindable_vertex_buffer>(gfx, &cube_geometry));
            auto vs = make_unique<dx_bindable_vertex_shader>(gfx, cv_create_info.filename_vs.c_str());
            auto bytecode = vs->get_bytecode();
            add_static_bind(std::move(vs));

            add_static_bind(make_unique<dx_bindable_pixel_shader>(gfx, cv_create_info.filename_ps.c_str()));
            add_static_index_buffer(make_unique<dx_bindable_index_buffer>(gfx, &cube_geometry));

            const bounded_array<D3D11_INPUT_ELEMENT_DESC, 2> ied = {
                    {"POSITION", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 0,  D3D11_INPUT_PER_VERTEX_DATA, 0},
                    {"COLOR",    0, DXGI_FORMAT_R8G8B8A8_UNORM,     0, 16, D3D11_INPUT_PER_VERTEX_DATA, 0},
            };

            add_static_bind(make_unique<dx_bindable_input_layout>(gfx, ied, bytecode));
            add_static_bind(make_unique<dx_bindable_geometry_topology>(gfx, D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST));

            SCommonMeshInitialized = true;
        }
        else {
            set_index_from_static();
        }
        add_bind(make_unique<dx_bindable_transform_constant_buffer>(gfx, *this));
    }
}

#endif

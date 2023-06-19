
/*******************************************************************************
 * Copyright (c) 2023.
 * This file is part of The WhiteGear Studio software property.
 * If you get unexpected access to this file, or part ot whole codebase, you should
 * report this source code leak and delete all copies of source code from all your machines.
 ******************************************************************************/

#include <renda/drawing/common_skinned_cube_renderable.hpp>
#include <math/geometry_buffer.hpp>
#include "renda/resource_storage.hpp"
#include "constant_buffer_per_object.hpp"

namespace wg::renda {
    static bool SInitialized = false;
    common_skinned_cube_renderable::common_skinned_cube_renderable(const wg::renda::gpu_device &device,
                                                                   const wg::string_view &vs,
                                                                   const wg::string_view &ps) noexcept {
        num_vertices = 14u;
        if (!SInitialized) {
            static const auto cube_buffer = wg::geometry_buffer::get_cube();
            bounding_box = geometry::box::generate_bounding(cube_buffer.get_vertices(), cube_buffer.get_num_vertices());
            const auto vl = vertex_layout::create_for_mesh();
            { // add vertex buffer
                geometry_buffer::create_info ci = {};
                ci.memory.p_memory = cube_buffer.get_vertices();
                ci.count = cube_buffer.get_num_vertices();
                add_static_bind(make_ref<geometry_buffer>(device, BUFFER_TYPE_VERTEX_BUFFER, ci, &vl));
            }
            {
                // add texture resource
                auto& rs = resource_storage::global();
                add_static_bind(rs["image:default_cube"]);
            }
            {
                // add texture sampler
                add_static_bind(make_ref<sampler>(device));
            }
            i_object vs_code = nullptr;
            { // add vertex shader
                auto sp = make_ref<shader_program>(device, SHADER_TYPE_VERTEX_SHADER, vs);
                vs_code = sp->get_code();
                add_static_bind(sp);
            }
            { // add pixel shader
                add_static_bind(make_ref<shader_program>(device, SHADER_TYPE_PIXEL_SHADER, ps));
            }
            { // add index buffer
                geometry_buffer::create_info ci = {};
                ci.memory.p_memory = cube_buffer.get_indices();
                ci.count = cube_buffer.get_num_indices();
                add_static_index_buffer(make_ref<geometry_buffer>(device, BUFFER_TYPE_INDEX_BUFFER, ci));
            }
            { // add vertex layout
                add_static_bind(make_ref<vertex_input_layout>(device, vl, vs_code));
            }
            { // add topology
                add_static_bind(make_ref<topology>(TOPOLOGY_TRIANGLE_LIST));
            }


            SInitialized = true;
        }
        else {
            set_index_from_static();
        }
        {
            // add material
            add_bind(make_ref<constant_buffer_per_object>(device, uint(sizeof(material_data_t)), this));
        }
    }
}

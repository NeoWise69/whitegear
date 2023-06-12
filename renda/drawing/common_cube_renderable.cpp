
/*******************************************************************************
 * Copyright (c) 2023.
 * This file is part of The WhiteGear Studio software property.
 * If you get unexpected access to this file, or part ot whole codebase, you should
 * report this source code leak and delete all copies of source code from all your machines.
 ******************************************************************************/

#include <renda/drawing/common_cube_renderable.hpp>
#include <math/geometry_buffer.hpp>
#include <renda/drawing/constant_buffer_per_object.hpp>

namespace wg::renda {
    static bool SInitialized = false;
    common_cube_renderable::common_cube_renderable(const gpu_device &device, const string_view &vs,
                                                   const string_view &ps) noexcept {
        num_vertices = 8u;
        if (!SInitialized) {
            static const auto cube_geometry = wg::geometry_buffer<VERTEX_TYPE_COL>::get_cube();
            bounding_box = geometry::box::generate_bounding(cube_geometry.get_vertices(), cube_geometry.get_num_vertices());
            // get vertex layout
            vertex_layout vl = {
                    { "POSITION", FORMAT_RGBA32_FLOAT },
                    { "COLOR", FORMAT_RGBA8_UNORM },
            };

            { // add vertex buffer
                geometry_buffer::create_info ci = {};
                ci.memory.p_memory = cube_geometry.get_vertices();
                ci.count = cube_geometry.get_num_vertices();
                add_static_bind(make_ref<geometry_buffer>(device, BUFFER_TYPE_VERTEX_BUFFER, ci, &vl));
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
                ci.memory.p_memory = cube_geometry.get_indices();
                ci.count = cube_geometry.get_num_indices();
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

        { // add per object buffer
            add_bind(make_ref<constant_buffer_per_object>(device, uint(sizeof(material_data_t)), this));
        }
    }
}


/*******************************************************************************
 * Copyright (c) 2023.
 * This file is part of The WhiteGear Studio software property.
 * If you get unexpected access to this file, or part ot whole codebase, you should
 * report this source code leak and delete all copies of source code from all your machines.
 ******************************************************************************/

#ifndef WHITEGEAR_VERTEX_HPP
#define WHITEGEAR_VERTEX_HPP

#include <math/scalar_base.hpp>
#include <math/vec.hpp>
#include <math/mat.hpp>
#include <math/color.hpp>

namespace wg {
    enum vertex_type : u32 {
        VERTEX_TYPE_NONE,
        VERTEX_TYPE_COL,
        VERTEX_TYPE_TEX,
    };
    template<uint Type> struct vertex_t;

    using base_vertex_t = vertex_t<VERTEX_TYPE_NONE>;
    using col_vertex_t = vertex_t<VERTEX_TYPE_COL>;
    using tex_vertex_t = vertex_t<VERTEX_TYPE_TEX>;

    template<>
    struct vertex_t<VERTEX_TYPE_NONE> {
        vec4 v_position = {};
    };

    template<>
    struct vertex_t<VERTEX_TYPE_COL> {
        vec4 v_position = {};
        color32 v_color = {};
    };

    template<>
    struct vertex_t<VERTEX_TYPE_TEX> {
        vec4 v_position = {};
        vec2 v_texcoord = {};
    };

    struct material_data_t {
        mat4 model_matrix;
    };

    struct frame_data_t {
        mat4 projection_matrix;
        mat4 view_matrix;
    };
}

#endif //WHITEGEAR_VERTEX_HPP

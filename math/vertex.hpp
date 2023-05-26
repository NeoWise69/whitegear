
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
        VERTEX_TYPE_MESH,
    };
    template<uint Type> struct vertex_t;

    using base_vertex_t = vertex_t<VERTEX_TYPE_NONE>;
    using mesh_vertex_t = vertex_t<VERTEX_TYPE_MESH>;

    template<>
    struct vertex_t<VERTEX_TYPE_NONE> {
        vec4 v_position = {};
    };

    template<>
    struct vertex_t<VERTEX_TYPE_MESH> {
        vec4 v_position = {};
        color32 v_color = {};
    };

    struct material_data_t {
        mat4 model_matrix;
    };
}

#endif //WHITEGEAR_VERTEX_HPP

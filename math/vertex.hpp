
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
    struct mesh_vertex {
        vec4 position;
        vec2 texcoord;
        color32 color;
        vec3 normal;
        vec3 tangent;
        vec3 bitangent;
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

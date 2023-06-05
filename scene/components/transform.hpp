
/*******************************************************************************
 * Copyright (c) 2023.
 * This file is part of The WhiteGear Studio software property.
 * If you get unexpected access to this file, or part ot whole codebase, you should
 * report this source code leak and delete all copies of source code from all your machines.
 ******************************************************************************/

#ifndef WHITEGEAR_TRANSFORM_HPP
#define WHITEGEAR_TRANSFORM_HPP

#include <scene/component.hpp>
#include <math/vec.hpp>
#include <math/mat.hpp>

namespace wg {
    struct component_transform {
        WG_DECL_COMPONENT()

        vec3 world_position = {};
        vec3 world_rotation = {};
        vec3 world_scale = vec3(1);

        mat4 transform_matrix = mat4(1);

        bool scale_changed = false;

        inline const mat4& update() {
            transform_matrix = mat4(1);
            if (!is_zero(world_position)) {
                transform_matrix = translate(transform_matrix, world_position);
            }
            if (!is_zero(world_rotation)) {
                if (!is_zero(world_rotation.y)) {
                    transform_matrix = rotate(transform_matrix, world_rotation.y, {0, 1, 0});
                }
                if (!is_zero(world_rotation.z)) {
                    transform_matrix = rotate(transform_matrix, world_rotation.z, {0, 0, 1});
                }
                if (!is_zero(world_rotation.x)) {
                    transform_matrix = rotate(transform_matrix, world_rotation.x, {1, 0, 0});
                }
            }
            if (world_scale != vec3::one) {
                transform_matrix = scale(transform_matrix, world_scale);
            }
            return transform_matrix;
        }
    };
}

#endif //WHITEGEAR_TRANSFORM_HPP

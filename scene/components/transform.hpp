
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

        vec3 world_position;
        vec3 world_rotation;
        vec3 world_scale;

        inline mat4 get_matrix() const {
            mat4 m(1);
            m = scale(m, world_scale);
            m = rotate(m, world_rotation.x, { 1, 0, 0 });
            m = rotate(m, world_rotation.y, { 0, 1, 0 });
            m = rotate(m, world_rotation.z, { 0, 0, 1 });
            m = translate(m, world_position);
            return m;
        }
    };
}

#endif //WHITEGEAR_TRANSFORM_HPP

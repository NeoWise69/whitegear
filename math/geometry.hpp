
/*******************************************************************************
 * Copyright (c) 2023.
 * This file is part of The WhiteGear Studio software property.
 * If you get unexpected access to this file, or part ot whole codebase, you should
 * report this source code leak and delete all copies of source code from all your machines.
 ******************************************************************************/

#ifndef WHITEGEAR_GEOMETRY_HPP
#define WHITEGEAR_GEOMETRY_HPP

#include <math/scalar_base.hpp>
#include <math/vec.hpp>
#include <math/mat.hpp>

namespace wg {
    namespace geometry {
        struct sphere {
            vec3 position;
            scalar radius;
        };
        struct cube {
            vec3 center_position;
            scalar size;
        };
        struct box {
            vec3 pos0, pos1;
        };
    }

    struct frustum {

        inline frustum() : planes() {}
        frustum(const mat4& proj, const mat4& model);

        bool in_frustum(const vec3& point) const;
        bool in_frustum(const geometry::sphere& sp) const;
        bool in_frustum(const geometry::cube& c) const;

        void normalize(vec4* p_plane);

        union {
            /* x, y, z -> xyz normal values; w -> coordinates start distance */
            vec4 planes[6];
            struct {
                vec4 plane_right;
                vec4 plane_left;
                vec4 plane_bottom;
                vec4 plane_top;
                vec4 plane_back;
                vec4 plane_front;
            };
        };
    };
}

#endif //WHITEGEAR_GEOMETRY_HPP

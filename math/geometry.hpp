
/*******************************************************************************
 * Copyright (c) 2023.
 * This file is part of The WhiteGear Studio software property.
 * If you get unexpected access to this file, or part ot whole codebase, you should
 * report this source code leak and delete all copies of source code from all your machines.
 ******************************************************************************/

#ifndef WHITEGEAR_GEOMETRY_HPP
#define WHITEGEAR_GEOMETRY_HPP

#include <math/vertex.hpp>

namespace wg {
    namespace geometry {
        /**
         * Simplest mathematical sphere representation.
         * Used in math simulations.
         */
        struct sphere {
            vec3 position;
            scalar radius;
        };
        /**
         * Simplest mathematical cube representation.
         * Used in math simulations.
         */
        struct cube {
            vec3 center_position;
            scalar size;
        };
    }
    /**
     * Frustum clip space structure to check for
     * if elements (sphere, cube) is inside frustum
     * shape. Used for frustum fulling (mostly).
     */
    struct frustum {
        inline frustum() : planes() {}
        frustum(const mat4& proj, const mat4& model);
        /**
         * Check if point is inside frustum shape.
         */
        bool in_frustum(const vec3& point) const;
        /**
         * Check if sphere is inside frustum shape.
         */
        bool in_frustum(const geometry::sphere& sp) const;
        /**
         * Check if cube is inside frustum shape.
         */
        bool in_frustum(const geometry::cube& c) const;

        /**
         * Simple function to normalize vec4 plane.
         */
        void normalize(vec4* p_plane);

        union {
            /* x, y, z -> xyz normal values; w -> coordinates of start distance */
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

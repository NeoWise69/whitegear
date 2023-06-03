
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
         * Simplest mathematical box representation.
         * Used in math simulations.
         */
        struct box {
            vec3 center_position;
            vec3 size;

            static box generate_bounding(const mesh_vertex_t* vertices, u64 num_vertices);
            void set_position(const vec3& position);
        };
    }
    /**
     * Frustum clip space structure to check for
     * if elements (sphere, box) is inside frustum_view
     * shape. Used for frustum culling (mostly).
     */
    struct frustum_view {
        inline frustum_view() : planes() {}
        frustum_view(const mat4& proj, const mat4& model);
        /**
         * Check if point is inside frustum_view shape.
         */
        bool is_in_view(const vec3& point) const;
        /**
         * Check if sphere is inside frustum_view shape.
         */
        bool is_in_view(const geometry::sphere& b_sphere) const;
        /**
         * Check if box is inside frustum_view shape.
         */
        bool is_in_view(const geometry::box& b_box) const;

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
    private:
        /**
         * Simple function to normalize vec4 plane.
         */
        void normalize(vec4* p_plane);
    };
}

#endif //WHITEGEAR_GEOMETRY_HPP

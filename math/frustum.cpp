
/*******************************************************************************
 * Copyright (c) 2023.
 * This file is part of The WhiteGear Studio software property.
 * If you get unexpected access to this file, or part ot whole codebase, you should
 * report this source code leak and delete all copies of source code from all your machines.
 ******************************************************************************/

#include <math/geometry.hpp>
#include <limits>

namespace wg {
    void frustum_view::normalize(vec4* p_plane) {
        auto& plane = *p_plane;
        const scalar one_over_mag = rsqrt(plane.x * plane.x + plane.y * plane.y + plane.z * plane.z);
        plane *= one_over_mag;
    }

    frustum_view::frustum_view(const mat4 &proj, const mat4 &model) {
        scalar clip[16] = {};
        const scalar* mdl = &model[0][0];
        const scalar* prj = &proj[0][0];

        clip[ 0] = mdl[ 0] * prj[ 0] + mdl[ 1] * prj[ 4] + mdl[ 2] * prj[ 8] + mdl[ 3] * prj[12];
        clip[ 1] = mdl[ 0] * prj[ 1] + mdl[ 1] * prj[ 5] + mdl[ 2] * prj[ 9] + mdl[ 3] * prj[13];
        clip[ 2] = mdl[ 0] * prj[ 2] + mdl[ 1] * prj[ 6] + mdl[ 2] * prj[10] + mdl[ 3] * prj[14];
        clip[ 3] = mdl[ 0] * prj[ 3] + mdl[ 1] * prj[ 7] + mdl[ 2] * prj[11] + mdl[ 3] * prj[15];

        clip[ 4] = mdl[ 4] * prj[ 0] + mdl[ 5] * prj[ 4] + mdl[ 6] * prj[ 8] + mdl[ 7] * prj[12];
        clip[ 5] = mdl[ 4] * prj[ 1] + mdl[ 5] * prj[ 5] + mdl[ 6] * prj[ 9] + mdl[ 7] * prj[13];
        clip[ 6] = mdl[ 4] * prj[ 2] + mdl[ 5] * prj[ 6] + mdl[ 6] * prj[10] + mdl[ 7] * prj[14];
        clip[ 7] = mdl[ 4] * prj[ 3] + mdl[ 5] * prj[ 7] + mdl[ 6] * prj[11] + mdl[ 7] * prj[15];

        clip[ 8] = mdl[ 8] * prj[ 0] + mdl[ 9] * prj[ 4] + mdl[10] * prj[ 8] + mdl[11] * prj[12];
        clip[ 9] = mdl[ 8] * prj[ 1] + mdl[ 9] * prj[ 5] + mdl[10] * prj[ 9] + mdl[11] * prj[13];
        clip[10] = mdl[ 8] * prj[ 2] + mdl[ 9] * prj[ 6] + mdl[10] * prj[10] + mdl[11] * prj[14];
        clip[11] = mdl[ 8] * prj[ 3] + mdl[ 9] * prj[ 7] + mdl[10] * prj[11] + mdl[11] * prj[15];

        clip[12] = mdl[12] * prj[ 0] + mdl[13] * prj[ 4] + mdl[14] * prj[ 8] + mdl[15] * prj[12];
        clip[13] = mdl[12] * prj[ 1] + mdl[13] * prj[ 5] + mdl[14] * prj[ 9] + mdl[15] * prj[13];
        clip[14] = mdl[12] * prj[ 2] + mdl[13] * prj[ 6] + mdl[14] * prj[10] + mdl[15] * prj[14];
        clip[15] = mdl[12] * prj[ 3] + mdl[13] * prj[ 7] + mdl[14] * prj[11] + mdl[15] * prj[15];

        plane_right = {
                clip[3] - clip[0],
                clip[7] - clip[4],
                clip[11] - clip[8],
                clip[15] - clip[12]
        };
        normalize(&plane_right);
        plane_left = {
                clip[3] + clip[0],
                clip[7] + clip[4],
                clip[11] + clip[8],
                clip[15] + clip[12]
        };
        normalize(&plane_left);
        plane_bottom = {
                clip[3] + clip[1],
                clip[7] + clip[5],
                clip[11] + clip[9],
                clip[15] + clip[13]
        };
        normalize(&plane_bottom);
        plane_top = {
                clip[3] - clip[1],
                clip[7] - clip[5],
                clip[11] - clip[9],
                clip[15] - clip[13]
        };
        normalize(&plane_top);
        plane_back = {
                clip[3] - clip[2],
                clip[7] - clip[6],
                clip[11] - clip[10],
                clip[15] - clip[14]
        };
        normalize(&plane_back);
        plane_front = {
                clip[3] + clip[2],
                clip[7] + clip[6],
                clip[11] + clip[10],
                clip[15] + clip[14]
        };
        normalize(&plane_front);
    }

    bool frustum_view::is_in_view(const vec3 &point) const {
        for (auto & plane : planes) {
            if ((dot(plane, vec4(point, 1))) <= 0)
                return false;
        }
        return true;
    }

    bool frustum_view::is_in_view(const geometry::sphere &b_sphere) const {
        for (auto& plane : planes) {
            if (dot(plane, vec4(b_sphere.position, 1)) <= -b_sphere.radius)
                return false;
        }
        return true;
    }

    bool frustum_view::is_in_view(const geometry::box &b_box) const {
        const auto min_pos = b_box.center_position - b_box.size;
        const auto max_pos = b_box.center_position + b_box.size;

        for (auto& plane : planes) {
            const auto min_pos_dot = plane * min_pos;
            const auto max_pos_dot = plane * max_pos;

            if(min_pos_dot.x + min_pos_dot.y + min_pos_dot.z + plane.w > 0) continue;
            if(max_pos_dot.x + min_pos_dot.y + min_pos_dot.z + plane.w > 0) continue;
            if(min_pos_dot.x + max_pos_dot.y + min_pos_dot.z + plane.w > 0) continue;
            if(max_pos_dot.x + max_pos_dot.y + min_pos_dot.z + plane.w > 0) continue;
            if(min_pos_dot.x + min_pos_dot.y + max_pos_dot.z + plane.w > 0) continue;
            if(max_pos_dot.x + min_pos_dot.y + max_pos_dot.z + plane.w > 0) continue;
            if(min_pos_dot.x + max_pos_dot.y + max_pos_dot.z + plane.w > 0) continue;
            if(max_pos_dot.x + max_pos_dot.y + max_pos_dot.z + plane.w > 0) continue;
            return false;
        }
        return true;
    }

    geometry::box geometry::box::generate_bounding(const mesh_vertex_t *vertices, u64 num_vertices) {
        vec3 minAABB = vec3(std::numeric_limits<scalar>::max());
        vec3 maxAABB = vec3(std::numeric_limits<scalar>::min());
        for (u64 i = 0; i < num_vertices; ++i)
        {
            auto& pos = vertices[i].v_position;

            minAABB.x = fmin(minAABB.x, pos.x);
            minAABB.y = fmin(minAABB.y, pos.y);
            minAABB.z = fmin(minAABB.z, pos.z);

            maxAABB.x = fmax(maxAABB.x, pos.x);
            maxAABB.y = fmax(maxAABB.y, pos.y);
            maxAABB.z = fmax(maxAABB.z, pos.z);
        }

        const auto center = (minAABB + maxAABB) * 0.5f;

        const auto size = abs(maxAABB - minAABB);

        return { center, size };
    }

    void geometry::box::set_position(const vec3 &position) {
        center_position = position;
    }

    void geometry::box::accept_scale(const vec3 &r_scale) {
        size *= r_scale;
    }
}

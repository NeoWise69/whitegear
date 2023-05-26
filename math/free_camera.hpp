
/*******************************************************************************
 * Copyright (c) 2023.
 * This file is part of The WhiteGear Studio software property.
 * If you get unexpected access to this file, or part ot whole codebase, you should
 * report this source code leak and delete all copies of source code from all your machines.
 ******************************************************************************/

#ifndef WHITEGEAR_FREE_CAMERA_HPP
#define WHITEGEAR_FREE_CAMERA_HPP

#include <math/mat.hpp>

namespace wg {
    class free_camera {
    public:
        inline free_camera() = default;
        inline ~free_camera() = default;
        inline free_camera(const vec3& start_pos) : mPosition(start_pos) {}

        mat4 get_view_matrix() const;

        void set_position(const vec3& pos);
        void set_fly_speed(scalar s);
        void set_sensitivity(scalar s);

        void update();

    private:
        vec3 mPosition = {};
        vec3 mFront = {0, 0, -1};
        vec3 mUp = {0, 1, 0};
        scalar mFlySpeed = 0.05f;
        scalar mSense = 0.3f;
        bool mFirst = true;
        vec2 mLastMousePos = {};
        vec2 mYawPitch = {};
    };
}

#endif //WHITEGEAR_FREE_CAMERA_HPP

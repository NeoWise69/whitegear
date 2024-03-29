
/*******************************************************************************
 * Copyright (c) 2023.
 * This file is part of The WhiteGear Studio software property.
 * If you get unexpected access to this file, or part ot whole codebase, you should
 * report this source code leak and delete all copies of source code from all your machines.
 ******************************************************************************/

#include "free_camera.hpp"
#include <runtime/user_input.hpp>
#include <core/time.hpp>

namespace wg {

    const mat4& free_camera::get_view_matrix() const {
        mViewMatrix = look_at(mPosition,
                       mPosition + mFront,
                       mUp);
        return mViewMatrix;
    }

    void free_camera::set_position(const vec3 &pos) {
        mPosition = pos;
    }

    void free_camera::update() {
        auto fly_speed = mFlySpeed;
        if (input::get().kbd_is_pressed(KEY_LEFT_SHIFT)) {
            fly_speed *= mFlySpeedUpMultiplier;
        }

        auto acceleration = vec3(0);

        if (input::get().kbd_is_pressed(KEY_W)) {
            acceleration += mFront * fly_speed;
        }
        if (input::get().kbd_is_pressed(KEY_S)) {
            acceleration -= mFront * fly_speed;
        }
        if (input::get().kbd_is_pressed(KEY_A)) {
            acceleration -= normalize(cross(mFront, mUp)) * fly_speed;
        }
        if (input::get().kbd_is_pressed(KEY_D)) {
            acceleration += normalize(cross(mFront, mUp)) * fly_speed;
        }
        if (input::get().kbd_is_pressed(KEY_Q)) {
            acceleration -= mUp * fly_speed;
        }
        if (input::get().kbd_is_pressed(KEY_E)) {
            acceleration += mUp * fly_speed;
        }

        acceleration = fmin(acceleration, vec3(fly_speed));

        const scalar delta_time = scalar(GTimeStats.delta_time.get(time_point::milliseconds));

        mPosition += (acceleration * delta_time);

        { // camera rotation
            const auto ms = input::get().ms_get_position();
            if (mFirst) {
                mLastMousePos = ms;
                mFirst = false;
            }
            vec2 offset = {
                    ms.x - mLastMousePos.x,
                    mLastMousePos.y - ms.y
            };
            mLastMousePos = ms;
            offset *= mSense;

            if (input::get().ms_is_pressed(KEY_MOUSE_RIGHT)) {
                mYawPitch += offset;
            }

            if(mYawPitch.y > 89.0f)
                mYawPitch.y = 89.0f;
            if(mYawPitch.y < -89.0f)
                mYawPitch.y = -89.0f;
            vec3 front;
            front.x = cos(radians(mYawPitch.x)) * cos(radians(mYawPitch.y));
            front.y = sin(radians(mYawPitch.y));
            front.z = sin(radians(mYawPitch.x)) * cos(radians(mYawPitch.y));
            mFront = normalize(front);
        }
    }

    void free_camera::set_fly_speed(scalar s) {
        mFlySpeed = s;
    }

    void free_camera::set_sensitivity(scalar s) {
        mSense = s;
    }
}


/*******************************************************************************
 * Copyright (c) 2023.
 * This file is part of The WhiteGear Studio software property.
 * If you get unexpected access to this file, or part ot whole codebase, you should
 * report this source code leak and delete all copies of source code from all your machines.
 ******************************************************************************/

#include "free_camera.hpp"
#include "runtime/user_input.hpp"

namespace wg {

    mat4 free_camera::get_view_matrix() const {
        return look_at(mPosition,
                       mPosition + mFront,
                       mUp);
    }

    void free_camera::set_position(const vec3 &pos) {
        mPosition = pos;
    }

    void free_camera::update() {
        if (input::get().kbd_is_pressed(KEY_W)) {
            mPosition += mFront * mFlySpeed;
        }
        if (input::get().kbd_is_pressed(KEY_S)) {
            mPosition -= mFront * mFlySpeed;
        }
        if (input::get().kbd_is_pressed(KEY_A)) {
            mPosition -= normalize(cross(mFront, mUp)) * mFlySpeed;
        }
        if (input::get().kbd_is_pressed(KEY_D)) {
            mPosition += normalize(cross(mFront, mUp)) * mFlySpeed;
        }
        if (input::get().kbd_is_pressed(KEY_Q)) {
            mPosition -= mUp * mFlySpeed;
        }
        if (input::get().kbd_is_pressed(KEY_E)) {
            mPosition += mUp * mFlySpeed;
        }

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


/*******************************************************************************
 * Copyright (c) 2023.
 * This file is part of The WhiteGear Studio software property.
 * If you get unexpected access to this file, or part ot whole codebase, you should
 * report this source code leak and delete all copies of source code from all your machines.
 ******************************************************************************/

#ifndef WHITEGEAR_VIEWPORT_HPP
#define WHITEGEAR_VIEWPORT_HPP

#include <core/typedefs.hpp>
#include <math/mat.hpp>

namespace wg {
    class aspect_ratio {
    public:
        enum standard : uint {
            f4_3,
            f16_10,
            f16_9,
            f21_9,
            f32_9,
            f1_1,
        };

        inline ~aspect_ratio() = default;
        aspect_ratio(standard f = f16_9);
        inline aspect_ratio(uint w, uint h) : mValue(scalar(w) / scalar(h))
        {}

        uint get_reference_width() const;
        uint get_reference_height() const;

        inline operator scalar() const { return mValue; }
    private:
        scalar mValue = {};
    };
    /**
     * Every window have it's own viewport.
     * IMGUI will feed information to this viewport.
     */
    class viewport {
    public:
        inline viewport() = default;
        inline viewport(uint w, uint h) : mWidth(w), mHeight(h), mAspectRatio(w, h)
        {}

        inline void set_width(uint w) { mWidth = w; mDirty = true; }
        inline void set_height(uint h) { mHeight = h; mDirty = true; }
        inline void set_size(uint w, uint h) { mWidth = w; mHeight = h; mDirty = true; }
        inline void set_near_clipping_plane(scalar v) { mNearClipPlane = v; mDirty = true; }
        inline void set_far_clipping_plane(scalar v) { mFarClipPlane = v; mDirty = true; }
        inline void set_field_of_view_radians(scalar fov) { mFieldOfView = fov; mDirty = true; }

        inline mat4 get_projection_matrix() const { return mProjectionMatrix; }
        inline uint get_width() const { return mWidth; }
        inline uint get_height() const { return mHeight; }
        inline scalar get_aspect_ratio() const { mAspectRatio; }
        inline scalar get_field_of_view_radians() const { return mFieldOfView; }
        inline scalar get_near_clipping_plane() const { return mNearClipPlane; }
        inline scalar get_far_clipping_plane() const { return mFarClipPlane; }

        void set_standard_aspect_ratio(aspect_ratio::standard ar);
        void update();
    private:
        uint mWidth = {};
        uint mHeight = {};
        aspect_ratio mAspectRatio;
        scalar mFieldOfView = 65.0f;
        scalar mNearClipPlane = 0.05f;
        scalar mFarClipPlane = 5000.0f;
        mat4 mProjectionMatrix;
        bool mDirty = true;
    };
}

#endif //WHITEGEAR_VIEWPORT_HPP

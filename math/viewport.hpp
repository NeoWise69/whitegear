
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
    /**
     * Simple utility to handle aspect ratio in an easy way.
     */
    class aspect_ratio {
    public:
        /**
         * Standard (https://en.wikipedia.org/wiki/Display_aspect_ratio) recommended
         * and most common aspect ratios for viewport.
         */
        enum standard : uint {
            /**
             * The standard aspect ratio for computer software,
             * videogames, and analog video until the 2000s.
             */
            f4_3,
            /**
             * Common on computer displays of the 2000s and 2010s,
             * continued use on MacBooks, since 2021 becoming
             * increasingly popular again in notebooks.
             */
            f16_10,
            /**
             * The default aspect ratio for HDTV
             * and modern computer displays.
             */
            f16_9,
            /**
             * Used in some professional and gaming displays since the mid 2010s,
             * roughly matches various anamorphic formats.
             */
            f21_9,
            /**
             * Used in some high-end displays since 2017.
             */
            f32_9,
            /**
             * Used in some desktop and professional monitors.
             */
            f1_1,
        };

        inline ~aspect_ratio() = default;
        explicit aspect_ratio(standard f = f16_9);
        inline aspect_ratio(uint w, uint h) : mValue(scalar(w) / scalar(h))
        {}
        /**
         * Get reference width based on aspect ratio.
         */
        uint get_reference_width() const;
        /**
         * Get reference height based on aspect ratio.
         */
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
        inline viewport(uint w, uint h)
            : mWidth(w), mHeight(h), mIsResized(true), mAspectRatio(w, h)
        {}
        inline viewport(uint w, uint h, bool b_is_fullscreen)
            : mWidth(w), mHeight(h), mIsFullscreen(b_is_fullscreen), mIsResized(true), mAspectRatio(w, h)
        {}
        /**
         * Sets only width of the viewport.
         */
        inline void set_width(uint w) { mWidth = w; mIsResized = mDirty = true; }
        /**
         * Sets only height of the viewport.
         */
        inline void set_height(uint h) { mHeight = h; mIsResized = mDirty = true; }
        /**
         * Sets width and height of the viewport.
         */
        inline void set_size(uint w, uint h) { mWidth = w; mHeight = h; mIsResized = mDirty = true; }
        /**
         * Sets near clip plane distance.
         */
        inline void set_near_clipping_plane(scalar v) { mNearClipPlane = v; mDirty = true; }
        /**
         * Sets far clip plane distance.
         */
        inline void set_far_clipping_plane(scalar v) { mFarClipPlane = v; mDirty = true; }
        /**
         * Sets FOV on degrees.
         */
        inline void set_field_of_view_degrees(scalar fov) { mFieldOfView = radians(fov); mDirty = true; }
        /**
         * Sets FOV on radians.
         */
        inline void set_field_of_view_radians(scalar rad) { mFieldOfView = rad; mDirty = true; }
        /**
         * Get calculated projection matrix.
         */
        inline mat4 get_projection_matrix() const { return mProjectionMatrix; }
        /**
         * Access to width.
         */
        inline uint get_width() const { return mWidth; }
        /**
         * Access to height.
         */
        inline uint get_height() const { return mHeight; }
        /**
         * Aspect ration of width and height.
         */
        inline scalar get_aspect_ratio() const { return mAspectRatio; }
        /**
         * Access to FOV in radians.
         */
        inline scalar get_field_of_view_radians() const { return mFieldOfView; }
        /**
         * Access to FOV in degrees.
         */
        inline scalar get_field_of_view_degrees() const { return degrees(mFieldOfView); }
        /**
         * Access to distance to near clip plane.
         */
        inline scalar get_near_clipping_plane() const { return mNearClipPlane; }
        /**
         * Access to distance to far clip plane.
         */
        inline scalar get_far_clipping_plane() const { return mFarClipPlane; }
        /**
         * Tells if viewport is fullscreen.
         */
        inline bool is_fullscreen() const { return mIsFullscreen; }
        /**
         * Tells if viewport was resized.
         */
        inline bool is_resized() const { return mIsResized; }
        /**
         * Sets standard aspect ratio.
         * Affects width or height of viewport.
         */
        void set_standard_aspect_ratio(aspect_ratio::standard ar);
        /**
         * Recalculate matrix and aspect ratio, if required.
         */
        void update();
    private:
        uint mWidth = {};
        uint mHeight = {};
        aspect_ratio mAspectRatio;
        scalar mFieldOfView = radians(65.0f);
        scalar mNearClipPlane = 0.05f;
        scalar mFarClipPlane = 5000.0f;
        mat4 mProjectionMatrix;
        bool mIsFullscreen = false;
        bool mIsResized = false;
        bool mDirty = true;
    };
}

#endif //WHITEGEAR_VIEWPORT_HPP

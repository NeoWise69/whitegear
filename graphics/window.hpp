
/*******************************************************************************
 * Copyright (c) 2023.
 * This file is part of The WhiteGear Studio software property.
 * If you get unexpected access to this file, or part ot whole codebase, you should
 * report this source code leak and delete all copies of source code from all your machines.
 ******************************************************************************/

#ifndef WHITEGEAR_WINDOW_HPP
#define WHITEGEAR_WINDOW_HPP

#include <core/core.hpp>
#include <runtime/user_input.hpp>
#include <graphics/cursor.hpp>
#include <math/viewport.hpp>

/**
 * Forward declaration of GLFW's window opaque type.
 */
struct GLFWwindow;

namespace wg {
    /**
     * Initialization structure.
     */
    struct window_create_info {
        /**
         * Starting coords of the new window.
         */
        int x, y;
        /**
         * Size of the new window.
         */
        int w, h;
        /**
         * Name of the new window.
         */
        string title;
        /**
         * Whether it is fullscreen window or not.
         */
        bool fullscreen;
    };
    /**
     * Special viewport for window object.
     */
    class window_viewport : public viewport {
    public:
        using viewport::viewport;
        inline window_viewport(uint w, uint h, bool b_is_fullscreen) : viewport(w, h), mIsFullscreen(b_is_fullscreen)
        {}

        inline bool is_fullscreen() const { return mIsFullscreen; }

        using viewport::update;
    private:
        bool mIsFullscreen;
    };
    /**
     * Structure, contains whole data required for window.
     */
    struct window_info : window_create_info {
        bool alive;
        window_viewport vp = {};
    };
    /**
     * Main visual output device.
     */
    class window {
    public:
        window() = default;
        /**
         * Constructor that accepts create_info pointer
         * to create a new window.
         */
        window(window_create_info* p_info);
        virtual ~window();
        /**
         * Creates new window with parameters, accepted
         * through p_info window_create_info pointer.
         */
        void open(window_create_info* p_info);
        inline bool is_alive() const { return mInfo.alive; }
        /**
         * Tells whether window is minimized or not.
         * @return
         */
        inline bool is_suspended() const { return mInfo.w == 0 || mInfo.h == 0; }
        /**
         * Returns if window is fullscreen.
         */
        inline bool is_fullscreen() const { return mInfo.fullscreen; }
        /**
         * Requests window for close routine.
         */
        void request_close();
        /**
         * Setup cursor for current window.
         */
        void set_cursor(cursor c, cursor_state state = CURSOR_STATE_NORMAL);
        /**
         * Polls all platform-dependent events.
         * Updates viewport.
         */
        void platform_update();
        /**
         * Access to GLFW window pointer.
         */
        GLFWwindow* get() const;
        /**
         * Access to the window's viewport.
         */
        inline window_viewport get_viewport() const { return mInfo.vp; }
        /**
         * Access to the window's viewport.
         */
        inline window_viewport& get_viewport() { return mInfo.vp; }
    private:
        window_info mInfo = {};
        GLFWwindow* mWindow = {};
    };

}

#endif //WHITEGEAR_WINDOW_HPP

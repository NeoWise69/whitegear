
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
     * Structure, contains whole data required for window.
     */
    struct window_info : window_create_info {
        bool alive;
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
        /**
         * Returns current width of window.
         * [NOTE] Changes in realtime on window resize.
         */
        inline uint get_width() const { return mInfo.w; }
        /**
         * Returns current height of window.
         * [NOTE] Changes in realtime on window resize.
         */
        inline uint get_height() const { return mInfo.h; }
        /**
         * Tells whether window is still alive or not.
         */
        inline bool is_alive() const { return mInfo.alive; }
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
         */
        static void platform_update();
        /**
         * Access to GLFW window pointer.
         */
        GLFWwindow* get() const;
    private:
        window_info mInfo = {};
        GLFWwindow* mWindow = {};
    };

}

#endif //WHITEGEAR_WINDOW_HPP

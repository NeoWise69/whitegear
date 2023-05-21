
/*******************************************************************************
 * Copyright (c) 2023.
 * This file is part of The WhiteGear Studio software property.
 * If you get unexpected access to this file, or part ot whole codebase, you should
 * report this source code leak and delete all copies of source code from all your machines.
 ******************************************************************************/

#ifndef WHITEGEAR_USER_INPUT_HPP
#define WHITEGEAR_USER_INPUT_HPP

#include <core/typedefs.hpp>
#include <core/containers/string_view.hpp>
#include <core/containers/bounded_array.hpp>
#include <math/vec3.hpp>

#include <mutex>

namespace wg {
    enum key : i16 {
        KEY_MOUSE_1             = 00,
        KEY_MOUSE_2             = 01,
        KEY_MOUSE_3             = 02,
        KEY_MOUSE_4             = 03,
        KEY_MOUSE_5             = 04,
        KEY_MOUSE_6             = 05,
        KEY_MOUSE_7             = 06,
        KEY_MOUSE_8             = 07,
        KEY_MOUSE_LEFT          = KEY_MOUSE_1,
        KEY_MOUSE_RIGHT         = KEY_MOUSE_2,
        KEY_MOUSE_MIDDLE        = KEY_MOUSE_3,

        KEY_SPACE              = 32,
        KEY_APOSTROPHE         = 39,  /* ' */
        KEY_COMMA              = 44,  /* , */
        KEY_MINUS              = 45,  /* - */
        KEY_PERIOD             = 46,  /* . */
        KEY_SLASH              = 47,  /* / */
        KEY_0                  = 48,
        KEY_1                  = 49,
        KEY_2                  = 50,
        KEY_3                  = 51,
        KEY_4                  = 52,
        KEY_5                  = 53,
        KEY_6                  = 54,
        KEY_7                  = 55,
        KEY_8                  = 56,
        KEY_9                  = 57,
        KEY_SEMICOLON          = 59,  /* ; */
        KEY_EQUAL              = 61,  /* = */
        KEY_A                  = 65,
        KEY_B                  = 66,
        KEY_C                  = 67,
        KEY_D                  = 68,
        KEY_E                  = 69,
        KEY_F                  = 70,
        KEY_G                  = 71,
        KEY_H                  = 72,
        KEY_I                  = 73,
        KEY_J                  = 74,
        KEY_K                  = 75,
        KEY_L                  = 76,
        KEY_M                  = 77,
        KEY_N                  = 78,
        KEY_O                  = 79,
        KEY_P                  = 80,
        KEY_Q                  = 81,
        KEY_R                  = 82,
        KEY_S                  = 83,
        KEY_T                  = 84,
        KEY_U                  = 85,
        KEY_V                  = 86,
        KEY_W                  = 87,
        KEY_X                  = 88,
        KEY_Y                  = 89,
        KEY_Z                  = 90,
        KEY_LEFT_BRACKET       = 91,  /* [ */
        KEY_BACKSLASH          = 92,  /* \ */
        KEY_RIGHT_BRACKET      = 93,  /* ] */
        KEY_GRAVE_ACCENT       = 96,  /* ` */
        KEY_WORLD_1            = 161,  /* non-US #1 */
        KEY_WORLD_2            = 162,  /* non-US #2 */

        /* Function keys */
        KEY_ESCAPE             = 256,
        KEY_ENTER              = 257,
        KEY_TAB                = 258,
        KEY_BACKSPACE          = 259,
        KEY_INSERT             = 260,
        KEY_DELETE             = 261,
        KEY_RIGHT              = 262,
        KEY_LEFT               = 263,
        KEY_DOWN               = 264,
        KEY_UP                 = 265,
        KEY_PAGE_UP            = 266,
        KEY_PAGE_DOWN          = 267,
        KEY_HOME               = 268,
        KEY_END                = 269,
        KEY_CAPS_LOCK          = 280,
        KEY_SCROLL_LOCK        = 281,
        KEY_NUM_LOCK           = 282,
        KEY_PRINT_SCREEN       = 283,
        KEY_PAUSE              = 284,
        KEY_F1                 = 290,
        KEY_F2                 = 291,
        KEY_F3                 = 292,
        KEY_F4                 = 293,
        KEY_F5                 = 294,
        KEY_F6                 = 295,
        KEY_F7                 = 296,
        KEY_F8                 = 297,
        KEY_F9                 = 298,
        KEY_F10                = 299,
        KEY_F11                = 300,
        KEY_F12                = 301,
        KEY_F13                = 302,
        KEY_F14                = 303,
        KEY_F15                = 304,
        KEY_F16                = 305,
        KEY_F17                = 306,
        KEY_F18                = 307,
        KEY_F19                = 308,
        KEY_F20                = 309,
        KEY_F21                = 310,
        KEY_F22                = 311,
        KEY_F23                = 312,
        KEY_F24                = 313,
        KEY_F25                = 314,
        KEY_KP_0               = 320,
        KEY_KP_1               = 321,
        KEY_KP_2               = 322,
        KEY_KP_3               = 323,
        KEY_KP_4               = 324,
        KEY_KP_5               = 325,
        KEY_KP_6               = 326,
        KEY_KP_7               = 327,
        KEY_KP_8               = 328,
        KEY_KP_9               = 329,
        KEY_KP_DECIMAL         = 330,
        KEY_KP_DIVIDE          = 331,
        KEY_KP_MULTIPLY        = 332,
        KEY_KP_SUBTRACT        = 333,
        KEY_KP_ADD             = 334,
        KEY_KP_ENTER           = 335,
        KEY_KP_EQUAL           = 336,
        KEY_LEFT_SHIFT         = 340,
        KEY_LEFT_CONTROL       = 341,
        KEY_LEFT_ALT           = 342,
        KEY_LEFT_SUPER         = 343,
        KEY_RIGHT_SHIFT        = 344,
        KEY_RIGHT_CONTROL      = 345,
        KEY_RIGHT_ALT          = 346,
        KEY_RIGHT_SUPER        = 347,
        KEY_MENU               = 348,

        KEY_LAST
    };
    /**
     * ***
     */
    enum key_state {
        /**
         * Key is not neither pressed nor released.
         * it's just calm state, idle.
         */
        KEY_STATE_IDLE,
        /**
         * Key is pressed right now.
         */
        KEY_STATE_PRESSED,
        /**
         * Key was released on last frame and will be changed
         * it's state back to IDLE.
         */
        KEY_STATE_RELEASED,
    };
    /**
     * What input device source belongs to this.
     */
    enum source_device {
        IDEVICE_UNDEFINED,
        /**
         * This was called due to keyboard event.
         */
        IDEVICE_KEYBOARD,
        /**
         * This was called due to mouse event.
         */
        IDEVICE_MOUSE,
        /**
         * This was called due to gamepad event.
         */
        IDEVICE_GAMEPAD
    };
    /**
     * Generic class, contains required information to
     * get access to all possible input devices (such as keyboard, mouse, etc.)
     */
    class input_device {
    public:
        struct state {
            /**
             * Source type of input device.
             */
            source_device source = {};
            /**
             * All keys from any input device.
             */
            key_state keys[KEY_LAST] = {};
            /**
             * This is required for fast and simple statechange(released->idle).
             */
            bounded_array<key, 16> release_keys = {};
            /**
             * on mouse:
             * x, y -> position
             * z -> wheel
             * on keyboard:
             * none
             */
            vec3 value = {};
        };
        /**
         * Access type of source.
         */
        inline auto get_source() const {
            return mState.source;
        }
        /**
         * Returns if key is pressed or not.
         */
        inline bool is_pressed(key kc) const {
            return (mState.keys[kc] == KEY_STATE_PRESSED);
        }
        /**
         * Returns if key is released or not.
         */
        inline bool is_released(key kc) const {
            return (mState.keys[kc] == KEY_STATE_RELEASED);
        }
        /**
         * If key is calm, or behaves.
         */
        inline bool is_idle(key kc) const {
            return (mState.keys[kc] == KEY_STATE_IDLE);
        }
        /**
         * [MOUSE] Returns window space position.
         */
        inline auto get_position() const {
            return mState.value.xy();
        }
        /**
         * [MOUSE] Returns middle wheel value.
         */
        inline auto get_wheel() const {
            return mState.value.z;
        }
        /**
         * Get access to state.
         */
        inline auto& get_state() {
            return mState;
        }
        /**
         * Process transition (release->idle) for
         * every released key.
         */
        void process_release_keys();
    private:
        state mState = {};
    };
    /**
     * Main input manager class through one
     * you can access to keyboard, mouse and
     * gamepads.
     */
    class input {
    public:
        inline input() = default;
        inline ~input() = default;
        /**
         * Access to keyboard instance.
         */
        inline auto& get_keyboard() {
            return mKeyboard;
        }
        /**
         * Access to mouse instance.
         */
        inline auto& get_mouse() {
            return mMouse;
        }
        /**
         * Less-type version of get_keyboard().is_pressed(...)
         */
        inline bool kbd_is_pressed(key k) const {
            return mKeyboard.is_pressed(k);
        }
        /**
         * Less-type version of get_keyboard().is_released(...)
         */
        inline bool kbd_is_released(key k) const {
            return mKeyboard.is_released(k);
        }
        /**
         * Less-type version of get_keyboard().is_idle(...)
         */
        inline bool kbd_is_idle(key k) const {
            return mKeyboard.is_idle(k);
        }
        /**
         * Less-type version of get_mouse().is_pressed(...)
         */
        inline bool ms_is_pressed(key k) const {
            return mMouse.is_pressed(k);
        }
        /**
         * Less-type version of get_mouse().is_released(...)
         */
        inline bool ms_is_released(key k) const {
            return mMouse.is_released(k);
        }
        /**
         * Less-type version of get_mouse().is_idle(...)
         */
        inline bool ms_is_idle(key k) const {
            return mMouse.is_idle(k);
        }
        /**
         * Less-type version of get_mouse().get_position()
         */
        inline auto ms_get_position() const {
            return mMouse.get_position();
        }
        /**
         * Less-type version of get_mouse().get_position()
         */
        inline auto ms_get_wheel() const {
            return mMouse.get_wheel();
        }

        static input& get();
    private:
        input_device mKeyboard = {};
        input_device mMouse = {};
        std::mutex mMtx = {};
    };
}

#endif //WHITEGEAR_USER_INPUT_HPP

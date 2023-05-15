
/*******************************************************************************
 * Copyright (c) 2023.
 * This file is part of The WhiteGear Studio software property.
 * If you get unexpected access to this file, or part ot whole codebase, you should
 * report this source code leak and delete all copies of source code from all your machines.
 ******************************************************************************/

#ifndef WHITEGEAR_WINDOW_HPP
#define WHITEGEAR_WINDOW_HPP

#include <core/core.hpp>

struct GLFWwindow;

namespace wg::gfx {
    struct window_create_info {
        int x, y;
        int w, h;
        string title;
        bool fullscreen;
    };
    struct window_info : window_create_info {
        bool alive;

    };
    class window {
    public:
        window() = default;
        window(window_create_info* p_info);
        virtual ~window();

        void open(window_create_info* p_info);

        inline uint get_width() const { return mInfo.w; }
        inline uint get_height() const { return mInfo.h; }
        inline bool is_alive() const { return mInfo.alive; }

    private:
        window_info mInfo = {};
        GLFWwindow* mWindow = {};
    };
    void platform_update();
}

#endif //WHITEGEAR_WINDOW_HPP


/*******************************************************************************
 * Copyright (c) 2023.
 * This file is part of The WhiteGear Studio software property.
 * If you get unexpected access to this file, or part ot whole codebase, you should
 * report this source code leak and delete all copies of source code from all your machines.
 ******************************************************************************/

#include <editor/editor_application.hpp>

namespace wg {
    int editor_application::pre_init() {

        return 0;
    }

    int editor_application::init() {

        {
            window_create_info wnd_info = {};
            wnd_info.w = 800;
            wnd_info.h = 600;
            wnd_info.title = "ed";

            mWindow.open(&wnd_info);
        }


        const auto code = mCore.initialize();
        if (code) return code;

        return 0;
    }

    int editor_application::run() {

        runtime_tick_info tick_info = {};

        while (mCore.is_running() && mWindow.is_alive()) {
            window::platform_update();

            if (input::get().kbd_is_released(KEY_ESCAPE)) {
                request_exit();
            }

            if (input::get().ms_is_released(KEY_MOUSE_LEFT)) {
                const auto& pos = input::get().ms_get_position();
                out
                .trace("mouse click: %dx%d", i32(pos.x), i32(pos.y));
            }

            if (const auto code = mCore.tick(&tick_info)) {
                return code;
            }
        }

        return 0;
    }

    void editor_application::request_exit() {
        mWindow.request_close();
        mCore.exit();
    }

    editor_application::editor_application() {

    }

    editor_application::~editor_application() {

    }
}

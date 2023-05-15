
/*******************************************************************************
 * Copyright (c) 2023.
 * This file is part of The WhiteGear Studio software property.
 * If you get unexpected access to this file, or part ot whole codebase, you should
 * report this source code leak and delete all copies of source code from all your machines.
 ******************************************************************************/

#include <editor/editor_application.hpp>

#include <graphics/instance.hpp>

namespace wg {
    int editor_application::pre_init() {

        return 0;
    }

    int editor_application::init() {

        {
            gfx::window_create_info wnd_info = {};
            wnd_info.w = 1280;
            wnd_info.h = 720;
            wnd_info.title = "ed";

            mWindow.open(&wnd_info);
        }

        mRenderer.init(&mWindow);

        const auto code = mCore.initialize();
        if (code) return code;

        return 0;
    }

    int editor_application::run() {

        runtime_tick_info tick_info = {};

        while (mCore.is_running() && mWindow.is_alive()) {
            gfx::platform_update();

            if (const auto code = mCore.tick(&tick_info)) {
                return code;
            }
        }

        return 0;
    }

    void editor_application::exit() {
        mCore.exit();
        mRenderer.exit();
    }

    editor_application::editor_application() {

    }

    editor_application::~editor_application() {

    }
}

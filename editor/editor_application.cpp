
/*******************************************************************************
 * Copyright (c) 2023.
 * This file is part of The WhiteGear Studio software property.
 * If you get unexpected access to this file, or part ot whole codebase, you should
 * report this source code leak and delete all copies of source code from all your machines.
 ******************************************************************************/

#include <editor/editor_application.hpp>
#include <scene/scene_module.hpp>
#include <renda/renderer_api.hpp>

namespace wg {
    void notify_renderer_api() {
        string_view sv;
        switch (renderer_api::get_type()) {
            case renderer_api::vulkan_api: {
                sv = "\'Khronos Group VulkanAPI\'";
            } break;
            case renderer_api::directx: {
                sv = "\'Microsoft DirectX\'";
            } break;
        }
        out
        .trace("Renderer backend: %s", sv.c_str());
    }

    int editor_application::pre_init() {
        notify_renderer_api();

        return 0;
    }

    int editor_application::init() {

        {
            window_create_info wnd_info = {};
            wnd_info.w = 1920;
            wnd_info.h = 1080;
            wnd_info.title = "ed";
            wnd_info.fullscreen = true;

            mWindow.open(&wnd_info);
        }

        mCore.add_module<scene_module>(nullptr);

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

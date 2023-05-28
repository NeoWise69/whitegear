
/*******************************************************************************
 * Copyright (c) 2023.
 * This file is part of The WhiteGear Studio software property.
 * If you get unexpected access to this file, or part ot whole codebase, you should
 * report this source code leak and delete all copies of source code from all your machines.
 ******************************************************************************/

#include <editor/editor_application.hpp>
#include <scene/scene_module.hpp>

// modules
#include <editor/world_editor_module.hpp>

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

        {
            rendering_engine_create_info info = {};
            info.p_app_name = "wg_ed";
            info.p_window = &mWindow;

            mRenda = rendering_engine::create(info);
        }
        mCore.add_module<scene_module>(mRenda);
        mCore.add_module<world_editor_module>();

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

            if (mCore.is_running()) {
                mRenda->on_begin_tick();
                if (const auto code = mCore.tick(&tick_info)) {
                    return code;
                }
                mRenda->on_end_tick();
            }
        }

        return 0;
    }

    void editor_application::request_exit() {
        if (mCore.is_running() && mWindow.is_alive()) {
            delete mRenda;
            mWindow.request_close();
            mCore.exit();
        }
    }

    editor_application::editor_application() {

    }

    editor_application::~editor_application() {

    }
}

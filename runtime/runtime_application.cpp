
/*******************************************************************************
 * Copyright (c) 2023.
 * This file is part of The WhiteGear Studio software property.
 * If you get unexpected access to this file, or part ot whole codebase, you should
 * report this source code leak and delete all copies of source code from all your machines.
 ******************************************************************************/

#include "runtime_application.hpp"
#include <core/time.hpp>

// modules
#include <scene/scene_module.hpp>

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

    int runtime_application::pre_init() {
        notify_renderer_api();

        return 0;
    }

    int runtime_application::init() {

        {
            window_create_info wnd_info = {};
            wnd_info.w = 1280;
            wnd_info.h = 720;
            wnd_info.title = "ed";
            wnd_info.fullscreen = false;

            mWindow.open(&wnd_info);
        }
        /**
         * Create viewport based on window's one. (Copy)
         */
        mViewport = mWindow.get_viewport();
        {
            rendering_engine::create_info info = {};
            info.p_app_name = "wg_ed";
            info.p_window = &mWindow;
            info.p_viewport = &mViewport;

            mRenda = new rendering_engine(info);
        }
        mCore.add_module<scene_module>(mRenda);

        const auto code = mCore.initialize();
        if (code) return code;

        return 0;
    }

    int runtime_application::run() {

        runtime_tick_info tick_info = {};

        while (mCore.is_running() && mWindow.is_alive()) {

            const auto delta_time_begin = time_point::now();

            if (!mWindow.is_suspended() && mCore.is_running()) {
                /* RENDERING CODE */
                const auto begin_time_start = time_point::now();
                mRenda->on_begin_tick();
                const auto begin_time_end = time_point::now();
                GTimeStats.frame_begin_time = begin_time_end - begin_time_start;
                if (const auto code = mCore.tick(&tick_info)) {
                    return code;
                }
            }
            { /* UPDATE LOGIC CODE */
                mWindow.platform_update();
                {
                    // <-- here
                }
            }
            // this required because of potential request_exit and call to non-existing renda ptr.
            if (mCore.is_running())
            { /* FRAME END & PRESENT CODE */
                const auto end_time_start = time_point::now();
                mRenda->on_end_tick();
                const auto end_time_end = time_point::now();
                GTimeStats.frame_end_time = end_time_end - end_time_start;
            }

            const auto delta_time_end = time_point::now();
            GTimeStats.delta_time = delta_time_end - delta_time_begin;
        }

        return 0;
    }

    void runtime_application::request_exit() {
        if (mCore.is_running() && mWindow.is_alive()) {
            delete mRenda;
            mWindow.request_close();
            mCore.exit();
        }
    }

    runtime_application::runtime_application() {

    }

    runtime_application::~runtime_application() {

    }
}

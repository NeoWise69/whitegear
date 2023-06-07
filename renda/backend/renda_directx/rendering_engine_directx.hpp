
/*******************************************************************************
 * Copyright (c) 2023.
 * This file is part of The WhiteGear Studio software property.
 * If you get unexpected access to this file, or part ot whole codebase, you should
 * report this source code leak and delete all copies of source code from all your machines.
 ******************************************************************************/

#ifndef WHITEGEAR_RENDERING_ENGINE_DIRECTX_HPP
#define WHITEGEAR_RENDERING_ENGINE_DIRECTX_HPP

#include "minimal.hpp"
#include <core/containers/hashmap.hpp>

#include "dx_graphics.hpp"
#include "dx_info_manager.hpp"
#include "dx_renderable.hpp"
#include "core/time.hpp"
#include "core/containers/reused_queue.hpp"

#if WG_WINDOWS

namespace wg {
    class rendering_engine_directx : public rendering_engine {
    public:
        explicit rendering_engine_directx(const rendering_engine::create_info &info);
        ~rendering_engine_directx() override;

        inline rendering_engine_directx(const rendering_engine_directx&) = delete;

        bool draw_mesh(const mesh_render_data *p_data) override;
        void load_mesh(const mesh_load_data *load_data) override;
        void create_common_mesh(const common_mesh_create_info* create_data) override;
        void unload_mesh(entity_t entity_id) override;
        void on_begin_tick() override;
        void on_end_tick() override;
        frustum_view get_frustum() const override;
    private:
        dx_info_manager mInfoManager;
        dx_graphics mGraphics;
        GLFWwindow* mWindowP;
        viewport* mViewport;

        time_point mFrameStartTime = 0;
        scoped_ptr<dx_bindable_base> mFrameData;

        /**
         * This is not so good for rendering,
         * because we wanna e.g turn off some
         * renderables, and do this without
         * any conditional checks.
         */
        hashmap<entity_t, ref_ptr<dx_renderable>> mRenderables;
        reused_queue<dx_renderable> mRenderablesToDraw;
    };
}

#endif

#endif //WHITEGEAR_RENDERING_ENGINE_DIRECTX_HPP

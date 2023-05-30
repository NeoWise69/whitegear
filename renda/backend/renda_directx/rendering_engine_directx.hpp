
/*******************************************************************************
 * Copyright (c) 2023.
 * This file is part of The WhiteGear Studio software property.
 * If you get unexpected access to this file, or part ot whole codebase, you should
 * report this source code leak and delete all copies of source code from all your machines.
 ******************************************************************************/

#ifndef WHITEGEAR_RENDERING_ENGINE_DIRECTX_HPP
#define WHITEGEAR_RENDERING_ENGINE_DIRECTX_HPP

#include "minimal.hpp"

#include "dx_graphics.hpp"
#include "dx_info_manager.hpp"
#include "dx_renderable.hpp"

#if WG_WINDOWS

namespace wg {
    class rendering_engine_directx : public rendering_engine {
    public:
        explicit rendering_engine_directx(const rendering_engine_create_info &info);
        ~rendering_engine_directx() override;

        inline rendering_engine_directx(const rendering_engine_directx&) = delete;

        void draw_mesh(const mesh_render_data *p_data) override;
        void load_mesh(const mesh_load_data *load_data) override;
        void create_common_mesh(const common_mesh_create_info* create_data) override;
        void unload_mesh(entity_t entity_id) override;
        void on_begin_tick() override;
        void on_end_tick() override;
        frustum get_frustum() const override;
    private:
        void init_imgui();
        void pre_begin_imgui();
        void end_imgui();
        void shutdown_imgui();

        dx_info_manager mInfoManager;
        dx_graphics mGraphics;
        window* mWindow;

        hashmap<entity_t, unique_ptr<dx_renderable>> mRenderables;
    };
}

#endif

#endif //WHITEGEAR_RENDERING_ENGINE_DIRECTX_HPP

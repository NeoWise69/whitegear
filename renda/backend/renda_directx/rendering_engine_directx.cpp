
/*******************************************************************************
 * Copyright (c) 2023.
 * This file is part of The WhiteGear Studio software property.
 * If you get unexpected access to this file, or part ot whole codebase, you should
 * report this source code leak and delete all copies of source code from all your machines.
 ******************************************************************************/

#include "rendering_engine_directx.hpp"

#if WG_WINDOWS

namespace wg {

    rendering_engine_directx::rendering_engine_directx(const rendering_engine_create_info &info) : mGraphics(info.p_window) {

    }

    rendering_engine_directx::~rendering_engine_directx() {

    }

    void rendering_engine_directx::draw_mesh(const rendering_engine::mesh_render_data *p_data) {

    }

    void rendering_engine_directx::load_mesh(const rendering_engine::mesh_load_data *load_data) {

    }

    void rendering_engine_directx::unload_mesh(entity_t entity_id) {

    }

    void rendering_engine_directx::on_begin_tick() {

    }

    void rendering_engine_directx::on_end_tick() {

        mGraphics.clear_color({0.8f, 0.2f, 0.3f});
        mGraphics.end_frame();
    }
}

#endif

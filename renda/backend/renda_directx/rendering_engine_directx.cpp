
/*******************************************************************************
 * Copyright (c) 2023.
 * This file is part of The WhiteGear Studio software property.
 * If you get unexpected access to this file, or part ot whole codebase, you should
 * report this source code leak and delete all copies of source code from all your machines.
 ******************************************************************************/

#include "rendering_engine_directx.hpp"

#if WG_WINDOWS

#include "dx_common_mesh_cube.hpp"

namespace wg {
    namespace {
        /**
         * Required for handling editor render target,
         * with this design.
         * TODO: revisit editor viewport system.
         */
        dx_graphics* GGraphics = nullptr;
    }

    rendering_engine_directx::rendering_engine_directx(const rendering_engine::create_info &info)
        : mWindowP(info.p_window->get()), mViewport(info.p_viewport), mGraphics(info.p_window->get(), info.p_viewport) {
        GGraphics = &mGraphics;
        mFrameData = make_scoped<dx_bindable_per_frame_constant_buffer>(mGraphics);
    }

    rendering_engine_directx::~rendering_engine_directx() = default;

    bool rendering_engine_directx::draw_mesh(const mesh_render_data *p_data) {
        if (!mRenderables.contains(p_data->entity)) {
            out
            .error("failed to render object[eid=%d]! there are no such entity in loaded list!", p_data->entity)
            ;
            return false;
        }
        else {
            auto& world_stats = get_parent_world()->stats();

            auto& renderable = mRenderables[p_data->entity];

            const auto f = get_frustum();
            auto& bounding = renderable->get_bounding(*p_data->p_position);
            if (*p_data->p_regenerate_bound) {

                out
                .trace("bound regenerated!")
                ;

                bounding.accept_scale(get_scale(*p_data->p_transform));
                *p_data->p_regenerate_bound = false;
            }

            if (f.is_in_view(bounding)) {
                if (!renderable->is_transform_ptr_provided()) {
                    renderable->set_transform_matrix_ptr(p_data->p_transform);
                }

                renderable->render(mGraphics);
                world_stats.vertices_per_frame += renderable->get_num_vertices();
                world_stats.indices_per_frame += renderable->get_num_indices();
                ++world_stats.draw_calls;
            }
            return true;
        }
    }

    void rendering_engine_directx::load_mesh(const rendering_engine::mesh_load_data *load_data) {
        WG_NOT_IMPLEMENTED
    }

    void rendering_engine_directx::create_common_mesh(const rendering_engine::common_mesh_create_info *create_data) {
        auto& renderable = mRenderables[create_data->entity];
        auto& world_stats = get_parent_world()->stats();

        if (create_data->mesh == common_mesh_create_info::COMMON_MESH_CUBE) {
            world_stats.vertices_on_scene += 8;
            world_stats.indices_on_scene += 36;

            dx_common_mesh_cube::create_info config = {};
            config.filename_vs = WG_SHADER_PREFIX_PATH"compiled/vs_basic.cso";
            config.filename_ps = WG_SHADER_PREFIX_PATH"compiled/ps_basic.cso";
            renderable = make_ref<dx_common_mesh_cube>(mGraphics, config);
        }
    }

    void rendering_engine_directx::unload_mesh(entity_t entity_id) {

    }

    void rendering_engine_directx::on_begin_tick() {
        mFrameStartTime = time_point::now();

        D3D11_VIEWPORT vp = {
                  0.0f, 0.0f,
                  FLOAT(mViewport->get_width()),
                  FLOAT(mViewport->get_height()),
                  0.0f, 1.0f
        };
        mGraphics.rs()->set_viewports(&vp, 1);
        // mGraphics.begin_render_to_texture_buffer();

        // clearance
        mGraphics.clear_color({0.2f, 0.2f, 0.2f});
        auto& world_stats = get_parent_world()->stats();
        world_stats.draw_calls = 0;
        world_stats.indices_per_frame = 0;
        world_stats.vertices_per_frame = 0;

        mFrameData->bind(mGraphics);
    }

    void rendering_engine_directx::on_end_tick() {

        // mGraphics.end_render_to_texture_buffer();
        mGraphics.end_frame();

        const auto frame_end_time = time_point::now();
        GTimeStats.frame_time = frame_end_time - mFrameStartTime;
    }

    frustum_view rendering_engine_directx::get_frustum() const {
        return { mGraphics.get_viewport().get_projection_matrix(), mGraphics.get_view_matrix() };
    }
}

#endif

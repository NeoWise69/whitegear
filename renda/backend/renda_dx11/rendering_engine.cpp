
/*******************************************************************************
 * Copyright (c) 2023.
 * This file is part of The WhiteGear Studio software property.
 * If you get unexpected access to this file, or part ot whole codebase, you should
 * report this source code leak and delete all copies of source code from all your machines.
 ******************************************************************************/

#include <renda/rendering_engine.hpp>
#include <renda/drawing/common_cube_renderable.hpp>
#include "renda/drawing/constant_buffer_per_frame.hpp"

namespace wg {
    rendering_engine::rendering_engine(const rendering_engine::create_info &ci) {
        mViewport = *ci.p_viewport;
        mViewport.update(); // update to get invalidate projection matrix immediately

        device.initialize(ci.p_window);
        mFrameData = make_scoped<renda::constant_buffer_per_frame>(device,
                                                              &mViewport.get_projection_matrix(),
                                                              &mGlobalCamera.get_view_matrix());

        const auto dev_info = device.get_description();
        out
        .trace("Selected GPU: %s, VRAM: ~%dmb", dev_info.desc_string.c_str(), dev_info.vram_mb)
        ;

        renda::swapchain::create_info sci = {};
        sci.p_window = ci.p_window;
        sci.p_display_info = &device.get_screen_info();
        swapchain.create(&device, sci);
        swapchain.get_target_buffer(device, screen_buffer);
        screen_buffer.bind(device);
    }


    bool rendering_engine::draw_mesh(const rendering_engine::mesh_render_data *p_data) {
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

                mRenderablesToDraw.push(renderable.get());
                world_stats.vertices_per_frame += renderable->get_num_vertices();
                world_stats.indices_per_frame += renderable->get_num_indices();
                ++world_stats.draw_calls;
            }
        }
        return true;
    }

    void rendering_engine::load_mesh(const rendering_engine::mesh_load_data *load_data) {
        WG_NOT_IMPLEMENTED
    }

    void rendering_engine::create_common_mesh(const rendering_engine::common_mesh_create_info *create_data) {
        auto& renderable = mRenderables[create_data->entity];
        auto& world_stats = get_parent_world()->stats();

        if (create_data->mesh == common_mesh_create_info::COMMON_MESH_CUBE) {
            world_stats.vertices_on_scene += 8;
            world_stats.indices_on_scene += 36;
            renderable = make_ref<renda::common_cube_renderable>(device,
                             WG_SHADER_PREFIX_PATH"compiled/vs_basic.cso",
                             WG_SHADER_PREFIX_PATH"compiled/ps_basic.cso");
        }
    }

    void rendering_engine::unload_mesh(entity_t entity_id) {
        WG_NOT_IMPLEMENTED
    }

    void rendering_engine::on_begin_tick() {
        mFrameStartTime = time_point::now();
        device.update_viewport(mViewport);
        screen_buffer.clear(device, { 0.2f, 0.2f, 0.2f, 1.0f });


        mFrameData->bind(device);
        mRenderablesToDraw.reset();

        auto& world_stats = get_parent_world()->stats();
        world_stats.draw_calls = 0;
        world_stats.indices_per_frame = 0;
        world_stats.vertices_per_frame = 0;
    }

    void rendering_engine::on_end_tick() {
        /**
         * Here draw all queued renderables,
         * at the end of rendering engine
         * execution process.
         */

         for (auto it = mRenderablesToDraw.begin(); it != mRenderablesToDraw.end(); ++it) {
             it->render(device);
         }

        swapchain.present();

        /**
         * Viewport resize handling.
         */
        if (mViewport.is_resized()) {

            out
                .trace("Viewport resized: (%dx%d)", mViewport.get_width(), mViewport.get_height())
            ;
            //screen_buffer.create(device, &mViewport);
        }

        mGlobalCamera.update();
        mViewport.update();

        const auto frame_end_time = time_point::now();
        GTimeStats.frame_time = frame_end_time - mFrameStartTime;
    }

    frustum_view rendering_engine::get_frustum() const {
        return { mViewport.get_projection_matrix(), get_view_matrix() };
    }

}

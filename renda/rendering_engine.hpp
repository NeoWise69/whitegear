
/*******************************************************************************
 * Copyright (c) 2023.
 * This file is part of The WhiteGear Studio software property.
 * If you get unexpected access to this file, or part ot whole codebase, you should
 * report this source code leak and delete all copies of source code from all your machines.
 ******************************************************************************/

#ifndef WHITEGEAR_RENDERING_ENGINE_HPP
#define WHITEGEAR_RENDERING_ENGINE_HPP

#include <renda/renderer_api.hpp>
#include <graphics/window.hpp>
#include <math/mat.hpp>
#include <scene/world.hpp>
#include <math/geometry.hpp>

#include <renda/api/gpu_device.hpp>
#include <renda/api/swapchain.hpp>
#include <renda/api/target_buffer.hpp>
#include <core/time.hpp>
#include <math/free_camera.hpp>
#include <renda/drawing/renderable.hpp>
#include <core/containers/reused_queue.hpp>

#define WG_SHADER_PREFIX_PATH "./editor_shaders/"

namespace wg {
    class rendering_engine {
    public:

        struct create_info {
            window* p_window;
            viewport* p_viewport;
            const char* p_app_name;
        };

        virtual ~rendering_engine() = default;
        rendering_engine(const rendering_engine::create_info& create_info);

        struct mesh_render_data {
            const mat4* p_transform;
            const vec3* p_position;
            entity_t entity;
            scalar view_aspect;
            scalar delta_time;
            bool* p_regenerate_bound;
        };
        bool draw_mesh(const mesh_render_data* p_data);
        struct mesh_load_data {
            string_view filepath;
            entity_t entity;
            world_registry* p_registry;
        };
        void load_mesh(const mesh_load_data* load_data);
        struct common_mesh_create_info {
            enum type_t : uint {
                COMMON_MESH_CUBE,
            };
            type_t mesh;
            entity_t entity;
            world_registry* p_registry;
        };
        void create_common_mesh(const common_mesh_create_info* create_data);
        void unload_mesh(entity_t entity_id);

        void on_begin_tick();
        void on_end_tick();

        frustum_view get_frustum() const;

        world* get_parent_world() { return mParent; }
        const world* get_parent_world() const { return mParent; }
        void set_parent_world(world* p_parent) { mParent = p_parent; }

        inline const mat4& get_view_matrix() const { return mGlobalCamera.get_view_matrix(); }
        inline const viewport& get_viewport() const { return mViewport; }
        inline viewport& get_viewport() { return mViewport; }
    protected:
        renda::gpu_device device = {};
        renda::swapchain swapchain = {};
        renda::target_buffer screen_buffer = {};

        scoped_ptr<renda::gpu_resource> mFrameData = nullptr;
        hashmap<entity_t, ref_ptr<renda::renderable>> mRenderables;
        reused_queue<renda::renderable> mRenderablesToDraw;

        free_camera mGlobalCamera = {{0, 0, 3}};
        viewport mViewport = {};
        time_point mFrameStartTime = 0;
        world* mParent = nullptr;
    };
}

#endif //WHITEGEAR_RENDERING_ENGINE_HPP

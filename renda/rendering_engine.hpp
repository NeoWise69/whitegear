
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

        struct mesh_render_data {
            const mat4* p_transform;
            const vec3* p_position;
            entity_t entity;
            scalar view_aspect;
            scalar delta_time;
        };
        virtual void draw_mesh(const mesh_render_data* p_data) = 0;
        struct mesh_load_data {
            string_view filepath;
            entity_t entity;
            world_registry* p_registry;
        };
        virtual void load_mesh(const mesh_load_data* load_data) = 0;
        struct common_mesh_create_info {
            enum type_t : uint {
                COMMON_MESH_CUBE,
            };
            type_t mesh;
            entity_t entity;
            world_registry* p_registry;
        };
        virtual void create_common_mesh(const common_mesh_create_info* create_data) = 0;
        virtual void unload_mesh(entity_t entity_id) = 0;

        virtual void on_begin_tick() = 0;
        virtual void on_end_tick() = 0;

        virtual frustum_view get_frustum() const = 0;

        static rendering_engine* create(const rendering_engine::create_info& create_info);

        inline world* get_parent_world() { return mParent; }
        inline const world* get_parent_world() const { return mParent; }
        inline void set_parent_world(world* p_parent) { mParent = p_parent; }

    protected:
        world* mParent = nullptr;
    };
}

#endif //WHITEGEAR_RENDERING_ENGINE_HPP

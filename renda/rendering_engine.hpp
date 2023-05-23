
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

namespace wg {
    struct rendering_engine_create_info {
        window* p_window;
        const char* p_app_name;
    };
    class rendering_engine {
    public:
        virtual ~rendering_engine() = default;

        struct mesh_render_data {
            mat4* p_transform;
        };
        virtual void draw_mesh(const mesh_render_data* p_data) = 0;
        struct mesh_load_data {
            string_view filepath;
            entity_t entity_id;
        };
        virtual void load_mesh(const mesh_load_data* load_data) = 0;
        virtual void unload_mesh(entity_t entity_id) = 0;

        virtual void on_begin_tick() = 0;
        virtual void on_end_tick() = 0;

        static rendering_engine* create(const rendering_engine_create_info& create_info);
    };
}

#endif //WHITEGEAR_RENDERING_ENGINE_HPP

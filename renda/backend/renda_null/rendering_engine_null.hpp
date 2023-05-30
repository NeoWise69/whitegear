
/*******************************************************************************
 * Copyright (c) 2023.
 * This file is part of The WhiteGear Studio software property.
 * If you get unexpected access to this file, or part ot whole codebase, you should
 * report this source code leak and delete all copies of source code from all your machines.
 ******************************************************************************/

#ifndef WHITEGEAR_RENDERING_ENGINE_NULL_HPP
#define WHITEGEAR_RENDERING_ENGINE_NULL_HPP

#include "renda/rendering_engine.hpp"

namespace wg {
    class rendering_engine_null : public rendering_engine {
    public:
        inline explicit rendering_engine_null(const rendering_engine_create_info&) {}
        inline ~rendering_engine_null() override = default;

        inline void draw_mesh(const mesh_render_data*) override {}
        inline void load_mesh(const mesh_load_data*) override {}
        inline void unload_mesh(entity_t) override {}
        inline void on_begin_tick() override {}
        inline void on_end_tick() override {}
        inline frustum get_frustum() const override { return {}; }
    };
}

#endif //WHITEGEAR_RENDERING_ENGINE_NULL_HPP

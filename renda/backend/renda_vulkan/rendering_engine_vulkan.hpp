
/*******************************************************************************
 * Copyright (c) 2023.
 * This file is part of The WhiteGear Studio software property.
 * If you get unexpected access to this file, or part ot whole codebase, you should
 * report this source code leak and delete all copies of source code from all your machines.
 ******************************************************************************/

#ifndef WHITEGEAR_RENDERING_ENGINE_VULKAN_HPP
#define WHITEGEAR_RENDERING_ENGINE_VULKAN_HPP

#include "minimal.hpp"
#include "vk_graphics.hpp"

namespace wg {
    class rendering_engine_vulkan : public rendering_engine {
    public:
        explicit rendering_engine_vulkan(const rendering_engine::create_info& info);
        ~rendering_engine_vulkan() override;

        void on_begin_tick() override;
        void on_end_tick() override;

        void load_mesh(const mesh_load_data* load_data) override;
        void create_common_mesh(const common_mesh_create_info* create_data) override;
        void unload_mesh(entity_t entity_id) override;
        bool draw_mesh(const mesh_render_data *p_data) override;
        frustum_view get_frustum() const override;

    private:
        vk_graphics* mGraphics = nullptr;
    };
}

#endif //WHITEGEAR_RENDERING_ENGINE_VULKAN_HPP

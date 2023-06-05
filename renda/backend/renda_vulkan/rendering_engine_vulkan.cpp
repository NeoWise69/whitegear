
/*******************************************************************************
 * Copyright (c) 2023.
 * This file is part of The WhiteGear Studio software property.
 * If you get unexpected access to this file, or part ot whole codebase, you should
 * report this source code leak and delete all copies of source code from all your machines.
 ******************************************************************************/

#include "rendering_engine_vulkan.hpp"

namespace wg {

    rendering_engine_vulkan::rendering_engine_vulkan(const rendering_engine::create_info& info) {
        VkInstanceCreateInfo ici = { VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO };

        VkApplicationInfo app_info = { VK_STRUCTURE_TYPE_APPLICATION_INFO };
        app_info.apiVersion = VK_API_VERSION_1_0;
        app_info.pEngineName = "WhiteGear Engine";
        app_info.engineVersion = VK_MAKE_VERSION(1, 0, 0);
        app_info.pApplicationName = "wg_app";
        app_info.applicationVersion = VK_MAKE_VERSION(1, 1, 1);

        ici.pApplicationInfo = &app_info;
        mGraphics = new vk_graphics(ici);
    }

    rendering_engine_vulkan::~rendering_engine_vulkan() {
        delete mGraphics;
    }

    void rendering_engine_vulkan::on_begin_tick() {

    }

    void rendering_engine_vulkan::on_end_tick() {

    }

    void rendering_engine_vulkan::load_mesh(const rendering_engine::mesh_load_data *load_data) {

    }

    void rendering_engine_vulkan::create_common_mesh(const rendering_engine::common_mesh_create_info *create_data) {

    }

    void rendering_engine_vulkan::unload_mesh(entity_t entity_id) {

    }

    bool rendering_engine_vulkan::draw_mesh(const mesh_render_data *p_data) {
        return true;
    }

    frustum_view rendering_engine_vulkan::get_frustum() const {
        return frustum_view();
    }

}


/*******************************************************************************
 * Copyright (c) 2023.
 * This file is part of The WhiteGear Studio software property.
 * If you get unexpected access to this file, or part ot whole codebase, you should
 * report this source code leak and delete all copies of source code from all your machines.
 ******************************************************************************/

#include "world_editor_module.hpp"
#include <scene/scene_module.hpp>
#include <runtime/runtime_core.hpp>

namespace wg {
    extern bool GEnableImGui;

    int world_editor_module::on_tick() {
        if (!mWorldControls.is_ready()) {
            auto *s_module = get_core()->get_module_by_id<scene_module>(scene_module_id);
            mWorldControls = &s_module->get_active_world();
        }
        if (GEnableImGui) {

            // GUI RENDERING

        } // GEnableImGui
        return 0;
    }

    void world_editor_module::tools_ui() {
    }

    void world_editor_module::status_bar_ui() {
    }

    void world_editor_module::world_outline_ui() {
    }

    void world_editor_module::inspector_ui() {
    }

    void world_editor_module::console_ui() {
    }

    void world_editor_module::log_ui() {
    }

    void world_editor_module::draw_single_entity(entity_t e, world_registry* reg) {
    }

    void world_editor_module::draw_entity_components(entity_t e) {
    }
}

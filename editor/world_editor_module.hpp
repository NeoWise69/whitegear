
/*******************************************************************************
 * Copyright (c) 2023.
 * This file is part of The WhiteGear Studio software property.
 * If you get unexpected access to this file, or part ot whole codebase, you should
 * report this source code leak and delete all copies of source code from all your machines.
 ******************************************************************************/

#ifndef WHITEGEAR_WORLD_EDITOR_MODULE_HPP
#define WHITEGEAR_WORLD_EDITOR_MODULE_HPP

#include <runtime/runtime_module.hpp>
#include <math/viewport.hpp>
#include <scene/world.hpp>

namespace wg {
    inline const uint world_editor_module_id = acquire_runtime_module_id();
    class world_editor_module : public runtime_module {
    public:
        inline explicit world_editor_module(runtime_core* cp, viewport* p_viewport) : runtime_module(cp), mWorldViewport(p_viewport) {}

        int on_tick() override;

        inline void set_selected_entity(entity_t e) { mSelectedEntity = e; }

        WG_DECL_RUNTIME_MODULE(world_editor_module_id)
    private:
        void tools_ui();
        void status_bar_ui();
        void world_outline_ui();
        void inspector_ui();
        void console_ui();
        void log_ui();

        void draw_single_entity(entity_t, world_registry*);
        void draw_entity_components(entity_t);

        viewport* mWorldViewport = {};
        entity_t mSelectedEntity = {};
        world::controls mWorldControls = {};
    };
}

#endif //WHITEGEAR_WORLD_EDITOR_MODULE_HPP


/*******************************************************************************
 * Copyright (c) 2023.
 * This file is part of The WhiteGear Studio software property.
 * If you get unexpected access to this file, or part ot whole codebase, you should
 * report this source code leak and delete all copies of source code from all your machines.
 ******************************************************************************/

#ifndef WHITEGEAR_SCENE_MODULE_HPP
#define WHITEGEAR_SCENE_MODULE_HPP

#include <runtime/runtime_module.hpp>
#include <scene/world.hpp>

namespace wg {
    enum scene_module_error : i32 {
        SCENE_MODULE_ERROR_OK = 0,
        SCENE_MODULE_ERROR_WORLD_TICK_FAILED,
        SCENE_MODULE_ERROR_WORLD_INITIALIZE_FAILED,
        SCENE_MODULE_ERROR_WORLD_LOAD_FAILED,
        SCENE_MODULE_ERROR_WORLD_UNLOAD_FAILED,
        SCENE_MODULE_ERROR_WORLD_UNINITIALIZE_FAILED,
    };
    inline const uint scene_module_id = acquire_runtime_module_id();
    class scene_module : public runtime_module {
    public:
        explicit scene_module(runtime_core* cp, rendering_engine* p_renda);

        int on_tick() override;
        int on_init() override;
        int on_exit() override;

        inline world& get_active_world() {
            return mActiveWorld;
        }

        WG_DECL_RUNTIME_MODULE(scene_module_id)
    private:
        world mActiveWorld = {};
        rendering_engine* renda = nullptr;
    };
}

#endif //WHITEGEAR_SCENE_MODULE_HPP

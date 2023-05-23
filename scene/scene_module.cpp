
/*******************************************************************************
 * Copyright (c) 2023.
 * This file is part of The WhiteGear Studio software property.
 * If you get unexpected access to this file, or part ot whole codebase, you should
 * report this source code leak and delete all copies of source code from all your machines.
 ******************************************************************************/

#include <scene/scene_module.hpp>

namespace wg {

    scene_module::scene_module(runtime_core *cp, rendering_engine *p_renda) : runtime_module(cp), renda(p_renda) {}

    int scene_module::on_init() {
        if (!mActiveWorld.initialize(renda))
            return SCENE_MODULE_ERROR_WORLD_INITIALIZE_FAILED;

        if (!mActiveWorld.load())
            return SCENE_MODULE_ERROR_WORLD_LOAD_FAILED;

        out
        .info("Scene module has been initialized successfully!")
        .trace("with world '%s'", "UNNAMED.wld");

        return SCENE_MODULE_ERROR_OK;
    }

    int scene_module::on_tick() {
        static world_tick_data data = {};

        if (!mActiveWorld.on_tick(data))
            return SCENE_MODULE_ERROR_WORLD_TICK_FAILED;

        return SCENE_MODULE_ERROR_OK;
    }

    int scene_module::on_exit() {

        if (!mActiveWorld.unload())
            return SCENE_MODULE_ERROR_WORLD_UNLOAD_FAILED;

        return mActiveWorld.uninitialize();
    }

}

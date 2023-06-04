
/*******************************************************************************
 * Copyright (c) 2023.
 * This file is part of The WhiteGear Studio software property.
 * If you get unexpected access to this file, or part ot whole codebase, you should
 * report this source code leak and delete all copies of source code from all your machines.
 ******************************************************************************/

#include <runtime/runtime_core.hpp>
#include <core/time.hpp>

namespace wg {
    int runtime_core::initialize() {

        for (auto& [id, mod] : mModules) {
            if (const auto code = mod->on_init()) {
                return code;
            }
        }

        mIsRunning = true;
        return 0;
    }

    int runtime_core::exit() {

        for (auto& [id, mod] : mModules) {
            if (const auto code = mod->on_exit()) {
                return code;
            }
        }

        mIsRunning = false;

        return 0;
    }

    int runtime_core::tick(runtime_tick_info *info) {

        const auto start = time_point::now();

        for (auto& [id, mod] : mModules) {
            if (const auto code = mod->on_tick()) {
                return code;
            }
        }

        const auto end = time_point::now();
        GTimeStats.tick_time = end - start;

        return 0;
    }

}

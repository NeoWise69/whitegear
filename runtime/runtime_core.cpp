
/*******************************************************************************
 * Copyright (c) 2023.
 * This file is part of The WhiteGear Studio software property.
 * If you get unexpected access to this file, or part ot whole codebase, you should
 * report this source code leak and delete all copies of source code from all your machines.
 ******************************************************************************/

#include <runtime/runtime_core.hpp>

namespace wg {
    int runtime_core::initialize() {

        for (auto& mod : mModules) {
            if (const auto code = mod->on_init()) {
                return code;
            }
        }

        mIsRunning = true;
        return 0;
    }

    int runtime_core::exit() {

        for (auto& mod : mModules) {
            if (const auto code = mod->on_exit()) {
                return code;
            }
        }

        mIsRunning = false;

        return 0;
    }

    int runtime_core::tick(runtime_tick_info *info) {

        for (auto& mod : mModules) {
            if (const auto code = mod->on_tick()) {
                return code;
            }
        }

        return 0;
    }

}

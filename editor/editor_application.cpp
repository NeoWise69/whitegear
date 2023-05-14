
/*******************************************************************************
 * Copyright (c) 2023.
 * This file is part of The WhiteGear Studio software property.
 * If you get unexpected access to this file, or part ot whole codebase, you should
 * report this source code leak and delete all copies of source code from all your machines.
 ******************************************************************************/

#include <editor/editor_application.hpp>

namespace wg {
    int editor_application::pre_init() {
        return 0;
    }

    int editor_application::init() {
        const auto code = mCore.initialize();
        if (code) return code;

        return 0;
    }

    int editor_application::run() {
        runtime_tick_info tick_info = {};

        while (mCore.is_running()) {
            if (const auto code = mCore.tick(&tick_info)) {
                return code;
            }
        }

        return 0;
    }

    void editor_application::exit() {
        mCore.exit();
    }

    editor_application::editor_application() {

    }

    editor_application::~editor_application() {

    }
}

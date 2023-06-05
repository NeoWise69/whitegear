
/*******************************************************************************
 * Copyright (c) 2023.
 * This file is part of The WhiteGear Studio software property.
 * If you get unexpected access to this file, or part ot whole codebase, you should
 * report this source code leak and delete all copies of source code from all your machines.
 ******************************************************************************/

#include <editor/editor_application.hpp>

// modules
#include <editor/world_editor_module.hpp>

namespace wg {
    int editor_application::pre_init() {
        runtime_application::pre_init();

        return 0;
    }

    int editor_application::init() {
        mCore.add_module<world_editor_module>(&mViewport);
        if (const auto code = runtime_application::init())
            return code;

        return 0;
    }

}

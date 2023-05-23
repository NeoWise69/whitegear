
/*******************************************************************************
 * Copyright (c) 2023.
 * This file is part of The WhiteGear Studio software property.
 * If you get unexpected access to this file, or part ot whole codebase, you should
 * report this source code leak and delete all copies of source code from all your machines.
 ******************************************************************************/

#include <scene/world.hpp>

namespace wg {
    bool world::rendering_system::render_scene(rendering_engine *renda) {

        for (const auto& e : entities) {
            // get transform
            // get some rendering stuff
            // if rendering break somewhere, return false;
        }

        return true;
    }
}

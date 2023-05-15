
/*******************************************************************************
 * Copyright (c) 2023.
 * This file is part of The WhiteGear Studio software property.
 * If you get unexpected access to this file, or part ot whole codebase, you should
 * report this source code leak and delete all copies of source code from all your machines.
 ******************************************************************************/

#include <graphics/renderer.hpp>
#include <graphics/window.hpp>

namespace wg {
    void renderer::init(gfx::window *p_window) {
        mInstance = new gfx::instance();
        mDevice = new gfx::device();
    }

    void renderer::exit() {
        delete mDevice;
        delete mInstance;
    }
}

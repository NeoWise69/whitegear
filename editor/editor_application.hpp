
/*******************************************************************************
 * Copyright (c) 2023.
 * This file is part of The WhiteGear Studio software property.
 * If you get unexpected access to this file, or part ot whole codebase, you should
 * report this source code leak and delete all copies of source code from all your machines.
 ******************************************************************************/

#ifndef WHITEGEAR_EDITOR_APPLICATION_HPP
#define WHITEGEAR_EDITOR_APPLICATION_HPP

#include <core/core.hpp>
#include <runtime/runtime_core.hpp>
#include <graphics/window.hpp>
#include <graphics/renderer.hpp>

namespace wg {
    class editor_application {
    public:
        editor_application();
        ~editor_application();

        int pre_init();
        int init();
        void exit();

        int run();

    private:
        runtime_core mCore;
        gfx::window mWindow;
        renderer mRenderer;
    };
}

#endif //WHITEGEAR_EDITOR_APPLICATION_HPP

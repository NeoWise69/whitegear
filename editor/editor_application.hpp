
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
#include <renda/rendering_engine.hpp>

namespace wg {
    class editor_application {
    public:
        editor_application();
        ~editor_application();

        int pre_init();
        int init();
        void request_exit();

        int run();

    private:
        runtime_core mCore;
        window mWindow;
        rendering_engine* mRenda;
    };
}

#endif //WHITEGEAR_EDITOR_APPLICATION_HPP

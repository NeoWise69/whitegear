
/*******************************************************************************
 * Copyright (c) 2023.
 * This file is part of The WhiteGear Studio software property.
 * If you get unexpected access to this file, or part ot whole codebase, you should
 * report this source code leak and delete all copies of source code from all your machines.
 ******************************************************************************/

#ifndef WHITEGEAR_RUNTIME_APPLICATION_HPP
#define WHITEGEAR_RUNTIME_APPLICATION_HPP

#include <core/core.hpp>
#include <runtime/runtime_core.hpp>
#include <graphics/window.hpp>
#include <renda/rendering_engine.hpp>

namespace wg {
    class runtime_application {
    public:
        runtime_application();
        ~runtime_application();

        virtual int pre_init();
        virtual int init();
        virtual void request_exit();

        virtual int run();

    protected:
        runtime_core mCore;
        window mWindow;
        rendering_engine* mRenda;
        viewport mViewport;
    };
}

#endif //WHITEGEAR_RUNTIME_APPLICATION_HPP

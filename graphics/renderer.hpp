
/*******************************************************************************
 * Copyright (c) 2023.
 * This file is part of The WhiteGear Studio software property.
 * If you get unexpected access to this file, or part ot whole codebase, you should
 * report this source code leak and delete all copies of source code from all your machines.
 ******************************************************************************/


#ifndef WHITEGEAR_RENDERER_HPP
#define WHITEGEAR_RENDERER_HPP

#include <graphics/instance.hpp>
#include <graphics/device.hpp>

namespace wg {
    namespace gfx {
        class window;
    }

    class renderer {
    public:
        renderer() = default;
        virtual ~renderer() = default;

        void init(gfx::window* p_window);
        void exit();

    private:
        gfx::instance* mInstance;
        gfx::device* mDevice;
    };
}

#endif //WHITEGEAR_RENDERER_HPP

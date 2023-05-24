
/*******************************************************************************
 * Copyright (c) 2023.
 * This file is part of The WhiteGear Studio software property.
 * If you get unexpected access to this file, or part ot whole codebase, you should
 * report this source code leak and delete all copies of source code from all your machines.
 ******************************************************************************/

#ifndef WHITEGEAR_RUNTIME_MODULE_HPP
#define WHITEGEAR_RUNTIME_MODULE_HPP

#include <core/core.hpp>

namespace wg {
    class runtime_core;
    /**
     * Runtime modules is a pieces that running
     * inside RuntimeCore, possible concurrently.
     */
    class runtime_module {
    public:
        virtual ~runtime_module() = default;
        explicit runtime_module(runtime_core* cp);

        virtual int on_begin_tick() { return 0; }
        virtual int on_tick() { return 0; }
        virtual int on_end_tick() { return 0; }
        virtual int on_init() { return 0; }
        virtual int on_exit() { return 0; }

        inline auto get_core() const { return pCore; }
    private:
        runtime_core* pCore = nullptr;
    };
}

#endif //WHITEGEAR_RUNTIME_MODULE_HPP

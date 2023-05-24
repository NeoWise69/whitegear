
/*******************************************************************************
 * Copyright (c) 2023.
 * This file is part of The WhiteGear Studio software property.
 * If you get unexpected access to this file, or part ot whole codebase, you should
 * report this source code leak and delete all copies of source code from all your machines.
 ******************************************************************************/

#ifndef WHITEGEAR_WORLD_EDITOR_MODULE_HPP
#define WHITEGEAR_WORLD_EDITOR_MODULE_HPP

#include <runtime/runtime_module.hpp>

namespace wg {
    class world_editor_module : public runtime_module {
    public:
        inline explicit world_editor_module(runtime_core* cp) : runtime_module(cp) {}

        int on_tick() override;
    };
}

#endif //WHITEGEAR_WORLD_EDITOR_MODULE_HPP

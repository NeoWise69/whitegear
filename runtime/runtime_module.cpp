
/*******************************************************************************
 * Copyright (c) 2023.
 * This file is part of The WhiteGear Studio software property.
 * If you get unexpected access to this file, or part ot whole codebase, you should
 * report this source code leak and delete all copies of source code from all your machines.
 ******************************************************************************/

#include <runtime/runtime_module.hpp>

namespace wg {

#if WG_BUILD_EDITOR
    bool GEnableImGui = true;
#else
    bool GEnableImGui = false;
#endif

    runtime_module::runtime_module(wg::runtime_core *cp) : pCore(cp) {}
}

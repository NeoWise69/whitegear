
/*******************************************************************************
 * Copyright (c) 2023.
 * This file is part of The WhiteGear Studio software property.
 * If you get unexpected access to this file, or part ot whole codebase, you should
 * report this source code leak and delete all copies of source code from all your machines.
 ******************************************************************************/

#include <renda/renderer_api.hpp>

namespace wg {
#if WG_WINDOWS
    renderer_api::type renderer_api::mType = renderer_api::directx;
#elif WG_UNIX
    renderer_api::type renderer_api::mType = renderer_api::vulkan_api;
#endif
}

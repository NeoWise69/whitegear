
/*******************************************************************************
 * Copyright (c) 2023.
 * This file is part of The WhiteGear Studio software property.
 * If you get unexpected access to this file, or part ot whole codebase, you should
 * report this source code leak and delete all copies of source code from all your machines.
 ******************************************************************************/

#include <renda/rendering_engine.hpp>

#include "backend/renda_null/rendering_engine_null.hpp"
#include "backend/renda_vulkan/rendering_engine_vulkan.hpp"
#include "backend/renda_directx/rendering_engine_directx.hpp"

namespace wg {
    rendering_engine* rendering_engine::create(const rendering_engine_create_info &create_info) {
        switch (renderer_api::get_type()) {
            case renderer_api::vulkan_api:
                return new rendering_engine_vulkan(create_info);
            case renderer_api::directx:
#if WG_WINDOWS
                return new rendering_engine_directx(create_info);
#elif WG_UNIX
                return new rendering_engine_null(create_info);
#endif
        }
        return new rendering_engine_null(create_info);
    }
}

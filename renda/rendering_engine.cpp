
/*******************************************************************************
 * Copyright (c) 2023.
 * This file is part of The WhiteGear Studio software property.
 * If you get unexpected access to this file, or part ot whole codebase, you should
 * report this source code leak and delete all copies of source code from all your machines.
 ******************************************************************************/

#include <renda/rendering_engine.hpp>

#include "backend/renda_vulkan/rendering_engine_vulkan.hpp"

namespace wg {
    rendering_engine* rendering_engine::create(const rendering_engine_create_info &create_info) {
        switch (renderer_api::get_type()) {
            case renderer_api::vulkan_api:
                return new rendering_engine_vulkan(create_info);
            case renderer_api::directx:
                return (rendering_engine*)1;
            default: {
                out
                .error("Failed to create rendering_engine!")
                .trace("unknown renderer api was defined.");
                return nullptr;
            }
        }
    }
}

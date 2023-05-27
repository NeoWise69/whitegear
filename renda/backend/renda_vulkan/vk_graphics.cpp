
/*******************************************************************************
 * Copyright (c) 2023.
 * This file is part of The WhiteGear Studio software property.
 * If you get unexpected access to this file, or part ot whole codebase, you should
 * report this source code leak and delete all copies of source code from all your machines.
 ******************************************************************************/

#include "vk_graphics.hpp"

namespace wg {
    vk_graphics::vk_graphics(const VkInstanceCreateInfo &create_info) {
        ret_t(initialize_instance(create_info));
    }

    vk_graphics::~vk_graphics() {
        if (mInstance) {
            uninitialize_instance();
        }
    }

    VkResult vk_graphics::initialize_instance(const VkInstanceCreateInfo &create_info) {
        return vkCreateInstance(&create_info, nullptr, &mInstance);
    }

    void vk_graphics::uninitialize_instance() {
        vkDestroyInstance(mInstance, nullptr);
    }
}

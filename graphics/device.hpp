
/*******************************************************************************
 * Copyright (c) 2023.
 * This file is part of The WhiteGear Studio software property.
 * If you get unexpected access to this file, or part ot whole codebase, you should
 * report this source code leak and delete all copies of source code from all your machines.
 ******************************************************************************/

#ifndef WHITEGEAR_DEVICE_HPP
#define WHITEGEAR_DEVICE_HPP

#include <core/core.hpp>
#include <vulkan/vulkan.h>

namespace wg::gfx {
    class device {
    public:
        device();
        virtual ~device();

        inline auto get_logical() const { return mLogical; }
        inline auto get_physical() const { return mPhysical; }
    private:
        VkPhysicalDevice mPhysical = VK_NULL_HANDLE;
        VkDevice mLogical = VK_NULL_HANDLE;
    };
}

#endif //WHITEGEAR_DEVICE_HPP

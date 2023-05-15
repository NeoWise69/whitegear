
/*******************************************************************************
 * Copyright (c) 2023.
 * This file is part of The WhiteGear Studio software property.
 * If you get unexpected access to this file, or part ot whole codebase, you should
 * report this source code leak and delete all copies of source code from all your machines.
 ******************************************************************************/

#ifndef WHITEGEAR_INSTANCE_HPP
#define WHITEGEAR_INSTANCE_HPP

#include <core/core.hpp>
#include <vulkan/vulkan.h>

namespace wg::gfx {
    class instance {
    public:
        instance();
        virtual ~instance();

        inline operator VkInstance() const { return mInstance; }

        inline auto get_debug_messenger() const { return mDebugMessenger; }
    private:
        void create_instance();
        void setup_debug();
    private:
        VkInstance mInstance = VK_NULL_HANDLE;
        VkDebugUtilsMessengerEXT mDebugMessenger = VK_NULL_HANDLE;
    };
}

#endif //WHITEGEAR_INSTANCE_HPP

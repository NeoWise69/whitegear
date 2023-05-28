
/*******************************************************************************
 * Copyright (c) 2023.
 * This file is part of The WhiteGear Studio software property.
 * If you get unexpected access to this file, or part ot whole codebase, you should
 * report this source code leak and delete all copies of source code from all your machines.
 ******************************************************************************/

#ifndef WHITEGEAR_VK_GRAPHICS_HPP
#define WHITEGEAR_VK_GRAPHICS_HPP

#include "minimal.hpp"

namespace wg {
    class vk_graphics {
    public:
        inline vk_graphics() = default;
        virtual ~vk_graphics();

        inline vk_graphics(const vk_graphics&) = delete;
        inline vk_graphics& operator=(const vk_graphics&) = delete;
        inline vk_graphics(vk_graphics&&) noexcept = delete;
        inline vk_graphics& operator=(vk_graphics&&) noexcept = delete;

        vk_graphics(const VkInstanceCreateInfo& create_info);

        inline VkInstance get_instance() const { return mInstance; }

    private:
        VkResult initialize_graphics(const VkInstanceCreateInfo& create_info);
        void uninitialize_graphics();

        VkInstance mInstance = nullptr;
        VkDevice mLogicalDevice = nullptr;
    };
}

#endif //WHITEGEAR_VK_GRAPHICS_HPP

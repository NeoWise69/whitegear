
/*******************************************************************************
 * Copyright (c) 2023.
 * This file is part of The WhiteGear Studio software property.
 * If you get unexpected access to this file, or part ot whole codebase, you should
 * report this source code leak and delete all copies of source code from all your machines.
 ******************************************************************************/

#include <graphics/instance.hpp>
#include <core/containers/bounded_array.hpp>

#include <GLFW/glfw3.h>
#include <stdexcept>

namespace wg::gfx {
    instance::instance() {
        create_instance();
    }

    instance::~instance() {

    }

    void instance::create_instance() {
        VkApplicationInfo app_info = { VK_STRUCTURE_TYPE_APPLICATION_INFO };
        app_info.apiVersion = VK_API_VERSION_1_3;
        app_info.pApplicationName = "whitegear app";
        app_info.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
        app_info.pEngineName = "WhiteGear Engine";
        app_info.engineVersion = VK_MAKE_VERSION(0, 1, 0);

        VkInstanceCreateInfo instance_info = { VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO };
        instance_info.pApplicationInfo = &app_info;

        uint glfw_ext_count = 0;
        const char** glfw_exts = nullptr;

        glfw_exts = glfwGetRequiredInstanceExtensions(&glfw_ext_count);

        bounded_array<const char*, 8> required_exts;
        for (auto i = 0; i < glfw_ext_count; ++i)
            required_exts.emplace_back(glfw_exts[i]);

        required_exts.emplace_back(VK_KHR_PORTABILITY_ENUMERATION_EXTENSION_NAME);
        instance_info.flags |= VK_INSTANCE_CREATE_ENUMERATE_PORTABILITY_BIT_KHR;

        instance_info.enabledExtensionCount = required_exts.size();
        instance_info.ppEnabledExtensionNames = required_exts.data();

        const VkResult r = vkCreateInstance(&instance_info, nullptr, &mInstance);
        if (r != VK_SUCCESS) {
            throw std::runtime_error("Failed to create vulkan instance!");
        }
    }
}

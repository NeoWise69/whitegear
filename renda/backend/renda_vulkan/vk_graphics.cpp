
/*******************************************************************************
 * Copyright (c) 2023.
 * This file is part of The WhiteGear Studio software property.
 * If you get unexpected access to this file, or part ot whole codebase, you should
 * report this source code leak and delete all copies of source code from all your machines.
 ******************************************************************************/

#include "vk_graphics.hpp"

#include <GLFW/glfw3.h>

#define MAX_INSTANCE_EXTENSIONS 32

namespace wg {
    namespace {
        void get_instance_extensions(bounded_array<const char*, MAX_INSTANCE_EXTENSIONS>& extensions) {
            u32 glfwExtensionCount = 0;
            const char** glfwExtensions = nullptr;
            glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);
            for (uint i = 0; i < glfwExtensionCount; ++i)
                extensions.emplace_back(glfwExtensions[i]);

            if (WG_UNIX) {
                extensions.emplace_back(VK_KHR_PORTABILITY_ENUMERATION_EXTENSION_NAME);
            }
        }
    }

    vk_graphics::vk_graphics(const VkInstanceCreateInfo &create_info) {
        ret_t(initialize_graphics(create_info));
    }

    vk_graphics::~vk_graphics() {
        if (mInstance) {
            uninitialize_graphics();
        }
    }

    VkResult vk_graphics::initialize_graphics(const VkInstanceCreateInfo &create_info) {
        VkInstanceCreateInfo ici = create_info;
        bounded_array<const char*, MAX_INSTANCE_EXTENSIONS> extensions;
        get_instance_extensions(extensions);
        ici.ppEnabledExtensionNames = extensions.data();
        ici.enabledExtensionCount = extensions.size();

        if (WG_UNIX) {
            ici.flags |= VK_INSTANCE_CREATE_ENUMERATE_PORTABILITY_BIT_KHR;
        }

        return vkCreateInstance(&ici, nullptr, &mInstance);
    }

    void vk_graphics::uninitialize_graphics() {
        vkDestroyInstance(mInstance, nullptr);
    }
}


/*******************************************************************************
 * Copyright (c) 2023.
 * This file is part of The WhiteGear Studio software property.
 * If you get unexpected access to this file, or part ot whole codebase, you should
 * report this source code leak and delete all copies of source code from all your machines.
 ******************************************************************************/

#include "vk_graphics.hpp"

#include <GLFW/glfw3.h>

#define MAX_INSTANCE_EXTENSIONS 32
#define MAX_VALIDATION_LAYERS 8

namespace wg {
    namespace {
        bounded_array<const char*, MAX_VALIDATION_LAYERS> GValidationLayers = {
            "VK_LAYER_KHRONOS_validation",
        };
#if WG_BUILD_DEBUG
        constexpr bool GEnableValidationLayers = true;
#else
        constexpr bool GEnableValidationLayers = false;
#endif

        void get_instance_extensions(bounded_array<const char*, MAX_INSTANCE_EXTENSIONS>& extensions) {
            u32 glfwExtensionCount = 0;
            const char** glfwExtensions = nullptr;
            glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);
            for (uint i = 0; i < glfwExtensionCount; ++i)
                extensions.emplace_back(glfwExtensions[i]);

#if WG_UNIX
            extensions.emplace_back(VK_KHR_PORTABILITY_ENUMERATION_EXTENSION_NAME);
#endif
        }

        bool is_validation_layers_support() {
            uint layer_count = {};
            vkEnumerateInstanceLayerProperties(&layer_count, nullptr);
            VkLayerProperties available_layers[MAX_VALIDATION_LAYERS] = {};
            vkEnumerateInstanceLayerProperties(&layer_count, available_layers);

            for (uint i = 0; i < GValidationLayers.size(); ++i) {
                const auto& layer_name = GValidationLayers[i];
                bool found = false;
                for (uint j = 0; j < layer_count; ++j) {
                    const string_view name = available_layers[j].layerName;
                    if (name == layer_name) {
                        found = true;
                        break;
                    }
                }
                if (!found) {
                    return false;
                }
            }

            return true;
        }
    }

    vk_graphics::vk_graphics(const VkInstanceCreateInfo &create_info) {
        ret_t(initialize_instance(create_info));
    }

    vk_graphics::~vk_graphics() {
        if (mInstance) {
            uninitialize_instance();
        }
    }

    VkResult vk_graphics::initialize_instance(const VkInstanceCreateInfo &create_info) {
        VkInstanceCreateInfo ici = create_info;
        bounded_array<const char*, MAX_INSTANCE_EXTENSIONS> extensions;
        get_instance_extensions(extensions);
        ici.ppEnabledExtensionNames = extensions.data();
        ici.enabledExtensionCount = extensions.size();

#if WG_UNIX
            ici.flags |= VK_INSTANCE_CREATE_ENUMERATE_PORTABILITY_BIT_KHR;
#endif

        if (is_validation_layers_support() && GEnableValidationLayers) {
            ici.ppEnabledLayerNames = GValidationLayers.data();
            ici.enabledLayerCount = GValidationLayers.size();
        }

        return vkCreateInstance(&ici, nullptr, &mInstance);
    }

    void vk_graphics::uninitialize_instance() {
        vkDestroyInstance(mInstance, nullptr);
    }
}

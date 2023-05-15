
/*******************************************************************************
 * Copyright (c) 2023.
 * This file is part of The WhiteGear Studio software property.
 * If you get unexpected access to this file, or part ot whole codebase, you should
 * report this source code leak and delete all copies of source code from all your machines.
 ******************************************************************************/

#include <graphics/instance.hpp>
#include <core/containers/bounded_array.hpp>
#include <core/logger.hpp>

#include <GLFW/glfw3.h>
#include <stdexcept>

static VKAPI_ATTR VkBool32 VKAPI_CALL SVkMessageCallbackFunc(
        VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
        VkDebugUtilsMessageTypeFlagsEXT messageType, const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData, void*) {

    if (messageSeverity >= VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT) {
        wg::out.warning("VK: %s", pCallbackData->pMessage);
    }

    return VK_FALSE;
}

wg::bounded_array<const char*, 1> GVkValidationLayers = {

};

#if _DEBUG
inline static bool GVkEnableValidationLayers = true;
#else
inline static bool GVkEnableValidationLayers = false;
#endif

namespace wg::gfx {
    namespace {
        bool check_validation_layers_support() {
            uint layer_count = {};
            vkEnumerateInstanceLayerProperties(&layer_count, nullptr);

            bounded_array<VkLayerProperties, 32> available_layers(layer_count);
            vkEnumerateInstanceLayerProperties(&layer_count, available_layers.data());

            for (auto layer_name: GVkValidationLayers) {
                bool found = false;
                for (const auto &layer_props: available_layers) {
                    if (string_view(layer_name) == layer_props.layerName) {
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

        template<uint N>
        void populate_required_extensions(bounded_array<const char *, N> &exts) {
            uint glfw_ext_count = 0;
            const char **glfw_exts = nullptr;

            glfw_exts = glfwGetRequiredInstanceExtensions(&glfw_ext_count);

            for (auto i = 0u; i < glfw_ext_count; ++i)
                exts.emplace_back(glfw_exts[i]);

            if (GVkEnableValidationLayers) {
                exts.emplace_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
            }
        }

        VkResult create_debug_messenger(VkInstance instance,
                                        const VkDebugUtilsMessengerCreateInfoEXT *pCreateInfo,
                                        const VkAllocationCallbacks *pAllocator,
                                        VkDebugUtilsMessengerEXT *pDebugMessenger) {
            auto func = (PFN_vkCreateDebugUtilsMessengerEXT) vkGetInstanceProcAddr(instance, "vkCreateDebugUtilsMessengerEXT");
            if (func != nullptr) {
                return func(instance, pCreateInfo, pAllocator, pDebugMessenger);
            } else {
                return VK_ERROR_EXTENSION_NOT_PRESENT;
            }
        }
        void destroy_debug_messenger(VkInstance instance,
                                     VkDebugUtilsMessengerEXT debugMessenger,
                                     const VkAllocationCallbacks* pAllocator) {
            auto func = (PFN_vkDestroyDebugUtilsMessengerEXT) vkGetInstanceProcAddr(instance, "vkDestroyDebugUtilsMessengerEXT");
            if (func != nullptr) {
                func(instance, debugMessenger, pAllocator);
            }
        }
    }

    instance::instance() {
        create_instance();
        setup_debug();
    }

    instance::~instance() {
        if (GVkEnableValidationLayers) {
            destroy_debug_messenger(mInstance, mDebugMessenger, nullptr);
        }
        if (mInstance) {
            vkDestroyInstance(mInstance, nullptr);
            mInstance = VK_NULL_HANDLE;
        }
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

        bounded_array<const char*, 16> required_exts;
        populate_required_extensions(required_exts);

#if __APPLE__
        required_exts.emplace_back(VK_KHR_PORTABILITY_ENUMERATION_EXTENSION_NAME);
        instance_info.flags |= VK_INSTANCE_CREATE_ENUMERATE_PORTABILITY_BIT_KHR;
#endif

        instance_info.enabledExtensionCount = required_exts.size();
        instance_info.ppEnabledExtensionNames = required_exts.data();

        if (GVkEnableValidationLayers) {
            instance_info.enabledLayerCount = GVkValidationLayers.size();
            instance_info.ppEnabledLayerNames = GVkValidationLayers.data();
        }

        const VkResult r = vkCreateInstance(&instance_info, nullptr, &mInstance);
        if (r != VK_SUCCESS) {
            throw std::runtime_error("Failed to create vulkan instance!");
        }
    }

    void instance::setup_debug() {
        if (!GVkEnableValidationLayers)
            return;

        VkDebugUtilsMessengerCreateInfoEXT create_info = { VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT };
        create_info.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
        create_info.messageType     = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
        create_info.pfnUserCallback = SVkMessageCallbackFunc;

        const VkResult r = create_debug_messenger(mInstance, &create_info, nullptr, &mDebugMessenger);
        if (r != VK_SUCCESS) {
            throw std::runtime_error("Failed to create vulkan debug messenger!");
        }
    }
}

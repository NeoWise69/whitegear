
/*******************************************************************************
 * Copyright (c) 2023.
 * This file is part of The WhiteGear Studio software property.
 * If you get unexpected access to this file, or part ot whole codebase, you should
 * report this source code leak and delete all copies of source code from all your machines.
 ******************************************************************************/

#include <graphics/instance.hpp>
#include <graphics/device.hpp>
#include <core/containers/bounded_array.hpp>

#include <stdexcept>

namespace wg::gfx {
    /**
     * Performs certain checks and counts imaginable 'score'
     * to choose the best GPU, if there are several in a system.
     */
    uint device::get_gpu_score(instance* instance, VkPhysicalDevice phys) {
        VkPhysicalDeviceFeatures2 device_features2 = { VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_FEATURES_2 };
        vkGetPhysicalDeviceFeatures2(phys, &device_features2);
        VkPhysicalDeviceFeatures features = device_features2.features;
        VkPhysicalDeviceProperties device_properties = {};
        if (instance->get_support(HW_PHYSICAL_DEVICE_PROPERTIES_2)) {

            VkPhysicalDeviceProperties2 tmp = { VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_PROPERTIES_2 };
            vkGetPhysicalDeviceProperties2(phys, &tmp);
            device_properties = tmp.properties;
        }
        else {
            vkGetPhysicalDeviceProperties(phys, &device_properties);
        }
        uint score = device_properties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU ? 2 :
                     (device_properties.deviceType == VK_PHYSICAL_DEVICE_TYPE_INTEGRATED_GPU) ? 1 : 0;
        const VkBool32* features_array = &features.robustBufferAccess;
        const uint features_array_size = 55u;
        for (uint i = 0; i < features_array_size; ++i) {
            if (features_array[i] > 0)
                ++score;
        }
        return score;
    }

    device::device(instance* p_inst) {
        find_physical_device(p_inst);
    }
    /**
     * Performs checks for compatibility on every single
     * graphics GPU, and choose best one for use.
     */
    void device::find_physical_device(instance *instance) {
        /** Get count of GPU's in a system. **/
        uint gpu_count = 0;
        vkEnumeratePhysicalDevices(instance->get(), &gpu_count, nullptr);
        if (!gpu_count) {
            throw std::runtime_error("Failed to create gfx::device -> there're no GPU with Vulkan support!");
        }
        bounded_array<VkPhysicalDevice, 8> physical_devices(gpu_count);
        vkEnumeratePhysicalDevices(instance->get(), &gpu_count, physical_devices.data());
        constexpr uint max_score = 57u;
        bounded_array<VkPhysicalDevice*, 8> physical_device_candidates[max_score] = {};
        /**
         * Accumulate 'suitability' of every found GPU in order
         * to find better one.
         */
        for (auto& device : physical_devices) {
            /** Get 'score' of a GPU, and accumulate it. **/
            if (const uint score = get_gpu_score(instance, device)) {
                physical_device_candidates[score].emplace_back(&device);
                break;
            }
        }
        /**
         * There are may be several GPU with similar score.
         * And because of this I'm gonna use bounded_array.
         */
        for (uint i = max_score - 1; i > 0; --i) {
            if (const auto* devices = &physical_device_candidates[i]; !devices->empty()) {
                /**
                 * I'll choose the first video card, because
                 * this one probably going to be better than others
                 * with similar score.
                 */
                for (auto device : *devices) {
                    /** And this GPU we'll use. **/

                    const queue_family_indices family_indices = find_queue_families(*device);
                    if (family_indices.is_acceptable() || family_indices.is_complete()) {
                        mPhysical = *device;
                    }

                    break;
                }
            }
        }
        if (!mPhysical) {
            throw std::runtime_error("Failed to find a suitable GPU!");
        }
    }
    device::~device() {

    }

    queue_family_indices device::find_queue_families(VkPhysicalDevice phys) {
        queue_family_indices indices = {};

        uint queue_family_count = 0;
        vkGetPhysicalDeviceQueueFamilyProperties(phys, &queue_family_count, nullptr);

        bounded_array<VkQueueFamilyProperties, 8> queue_families(queue_family_count);
        vkGetPhysicalDeviceQueueFamilyProperties(phys, &queue_family_count, queue_families.data());

        uint i = 0;
        for (auto& queue_family : queue_families) {
            if (queue_family.queueFlags & VK_QUEUE_GRAPHICS_BIT) {
                indices.graphics_family = i;
            }
            if (queue_family.queueFlags & VK_QUEUE_COMPUTE_BIT) {
                indices.compute_family = i;
            }
            if (queue_family.queueFlags & VK_QUEUE_TRANSFER_BIT) {
                indices.transfer_family = i;
            }
            if (queue_family.queueFlags & VK_QUEUE_TRANSFER_BIT) {
                indices.transfer_family = i;
            }

            // TODO: add check for presentation support.
            // VkBool32 is_present_support = false;
            // vkGetPhysicalDeviceSurfaceSupportKHR(mDevice, i, mSurface, &is_present_support);
            // if (is_present_support) {
            //     indices.present_family = i;
            // }

            ++i;
        }

        return indices;
    }

}

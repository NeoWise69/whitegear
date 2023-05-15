
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
#include <optional>

namespace wg::gfx {
    class instance;

    enum device_feature_indices {
        DV_FEATURE_,

        _DV_MAX
    };

    struct queue_family_indices {
        std::optional<uint> present_family;
        std::optional<uint> graphics_family;
        std::optional<uint> transfer_family;
        std::optional<uint> compute_family;

        /**
         * Means 'fully complete family indices'
         */
        inline bool is_complete() const {
            return
                present_family.has_value() &&
                graphics_family.has_value() &&
                transfer_family.has_value() &&
                compute_family.has_value();
        }
        /**
         * Partially complete family indices.
         */
        inline bool is_acceptable() const {
            return present_family.has_value() && graphics_family.has_value();
        }
    };

    class device {
    public:
        device(instance* p_inst);
        virtual ~device();

        inline auto get_logical() const { return mLogical; }
        inline auto get_physical() const { return mPhysical; }
        inline auto get_feature_support(device_feature_indices fi) const { return mFeatures[fi]; }
    private:
        static uint get_gpu_score(instance* instance, VkPhysicalDevice phys);
        void find_physical_device(instance* instance);
        queue_family_indices find_queue_families(VkPhysicalDevice phys);
    private:
        VkPhysicalDevice mPhysical = VK_NULL_HANDLE;
        VkDevice mLogical = VK_NULL_HANDLE;
        uint mFeatures[_DV_MAX] = {};
    };
}

#endif //WHITEGEAR_DEVICE_HPP


/*******************************************************************************
 * Copyright (c) 2023.
 * This file is part of The WhiteGear Studio software property.
 * If you get unexpected access to this file, or part ot whole codebase, you should
 * report this source code leak and delete all copies of source code from all your machines.
 ******************************************************************************/

#ifndef WHITEGEAR_VULKAN_MINIMAL_HPP
#define WHITEGEAR_VULKAN_MINIMAL_HPP

#include <renda/rendering_engine.hpp>
#include <vulkan/vulkan.h>

#include "vk_result.hpp"

namespace wg {
    template<>
    inline ret_t<VkResult>::~ret_t() {
        if (!mReceived && FAILED(mValue)) {
            const char* error_name = VKGetErrorName(mValue);
            char buffer[VK_RESULT_MAX_BUFFER];
            char* pbuffer = buffer;
            VKGetErrorDescription(mValue, &pbuffer, VK_RESULT_MAX_BUFFER);
            out
            .error("error has occurred[%s]: %s", error_name, buffer)
            .dead_end()
            ;
        }
    }

    template<>
    inline bool ret_t<VkResult>::is_ok() const {
        return mValue == VK_SUCCESS;
    }

    template<>
    inline string ret_t<VkResult>::get_error_name() const {
        return VKGetErrorName(mValue);
    }

    template<>
    inline string ret_t<VkResult>::get_error_desc() const {
        char buffer[VK_RESULT_MAX_BUFFER];
        char* pbuffer = buffer;
        const uint len = VKGetErrorDescription(mValue, &pbuffer, VK_RESULT_MAX_BUFFER);
        return { pbuffer, len };
    }
}

#endif //WHITEGEAR_MINIMAL_HPP

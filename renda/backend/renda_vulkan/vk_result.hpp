
/*******************************************************************************
 * Copyright (c) 2023.
 * This file is part of The WhiteGear Studio software property.
 * If you get unexpected access to this file, or part ot whole codebase, you should
 * report this source code leak and delete all copies of source code from all your machines.
 ******************************************************************************/

#ifndef WHITEGEAR_VK_RESULT_HPP
#define WHITEGEAR_VK_RESULT_HPP

#include <core/typedefs.hpp>

#define VK_RESULT_MAX_BUFFER 512

namespace wg {
    /**
     * Tells if Vulkan result if error actually.
     */
    bool FAILED(i64 vk_result);
    /**
     * If VkResult is still success-ish.
     */
    bool SUCCESS(i64 vk_result);
    /**
     * Returns the name of VkResult.
     */
    const char* VKGetErrorName(i64 vk_result);
    /**
     * Populates 'pp_buffer' with description of VALID VkResult till 'count'.
     * @returns Number of actual written characters.
     */
    uint VKGetErrorDescription(i64 vk_result, char** pp_buffer, uint count);
}

#endif //WHITEGEAR_VK_RESULT_HPP

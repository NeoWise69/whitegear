
/*******************************************************************************
 * Copyright (c) 2023.
 * This file is part of The WhiteGear Studio software property.
 * If you get unexpected access to this file, or part ot whole codebase, you should
 * report this source code leak and delete all copies of source code from all your machines.
 ******************************************************************************/

#include "vk_result.hpp"
#include <core/core.hpp>

#define VK_ENABLE_BETA_EXTENSIONS
#include <vulkan/vulkan.h>
#include <cstring>

namespace wg {
    namespace {
        uint get_vk_result_index(i64 vk_result) {
            switch (vk_result) {
                case VK_SUCCESS:                                            return 0;
                case VK_NOT_READY:                                          return 1;
                case VK_TIMEOUT:                                            return 2;
                case VK_EVENT_SET:                                          return 3;
                case VK_EVENT_RESET:                                        return 4;
                case VK_INCOMPLETE:                                         return 5;
                case VK_SUBOPTIMAL_KHR:                                     return 6;
                case VK_THREAD_IDLE_KHR:                                    return 7;
                case VK_THREAD_DONE_KHR:                                    return 8;
                case VK_OPERATION_DEFERRED_KHR:                             return 9;
                case VK_OPERATION_NOT_DEFERRED_KHR:                         return 10;
                case VK_PIPELINE_COMPILE_REQUIRED:                          return 11;
                    // Error codes down below:
                case VK_ERROR_OUT_OF_HOST_MEMORY:                           return 12;
                case VK_ERROR_OUT_OF_DEVICE_MEMORY:                         return 13;
                case VK_ERROR_INITIALIZATION_FAILED:                        return 14;
                case VK_ERROR_DEVICE_LOST:                                  return 15;
                case VK_ERROR_MEMORY_MAP_FAILED:                            return 16;
                case VK_ERROR_LAYER_NOT_PRESENT:                            return 17;
                case VK_ERROR_EXTENSION_NOT_PRESENT:                        return 18;
                case VK_ERROR_FEATURE_NOT_PRESENT:                          return 19;
                case VK_ERROR_INCOMPATIBLE_DRIVER:                          return 20;
                case VK_ERROR_TOO_MANY_OBJECTS:                             return 21;
                case VK_ERROR_FORMAT_NOT_SUPPORTED:                         return 22;
                case VK_ERROR_FRAGMENTED_POOL:                              return 23;
                case VK_ERROR_SURFACE_LOST_KHR:                             return 24;
                case VK_ERROR_NATIVE_WINDOW_IN_USE_KHR:                     return 25;
                case VK_ERROR_OUT_OF_DATE_KHR:                              return 26;
                case VK_ERROR_INCOMPATIBLE_DISPLAY_KHR:                     return 27;
                case VK_ERROR_INVALID_SHADER_NV:                            return 28;
                case VK_ERROR_OUT_OF_POOL_MEMORY:                           return 29;
                case VK_ERROR_INVALID_EXTERNAL_HANDLE:                      return 30;
                case VK_ERROR_FRAGMENTATION:                                return 31;
                case VK_ERROR_INVALID_OPAQUE_CAPTURE_ADDRESS:               return 32;
                case VK_ERROR_FULL_SCREEN_EXCLUSIVE_MODE_LOST_EXT:          return 33;
                case VK_ERROR_COMPRESSION_EXHAUSTED_EXT:                    return 34;
                case VK_ERROR_IMAGE_USAGE_NOT_SUPPORTED_KHR:                return 35;
                case VK_ERROR_VIDEO_PICTURE_LAYOUT_NOT_SUPPORTED_KHR:       return 36;
                case VK_ERROR_VIDEO_PROFILE_OPERATION_NOT_SUPPORTED_KHR:    return 37;
                case VK_ERROR_VIDEO_PROFILE_FORMAT_NOT_SUPPORTED_KHR:       return 38;
                case VK_ERROR_VIDEO_PROFILE_CODEC_NOT_SUPPORTED_KHR:        return 39;
                case VK_ERROR_VIDEO_STD_VERSION_NOT_SUPPORTED_KHR:          return 40;
                case VK_ERROR_INVALID_VIDEO_STD_PARAMETERS_KHR:             return 41;
                    // For some unknown reason not provided at MacOS X
                    // case VK_ERROR_INCOMPATIBLE_SHADER_BINARY_EXT:
                default:
                    return 42;
            }
        }
        struct vk_result_desc_pair {
            const char* text;
            const uint length;

            inline constexpr vk_result_desc_pair(const char* _text, uint len) : text(_text), length(len) {}
        };
        constexpr const vk_result_desc_pair vk_result_description_table[] = {
        /* VK_SUCCESS */ { "Command successfully completed", 31 },
        /* VK_NOT_READY */ { "A fence or query has not yet completed", 39 },
        /* VK_TIMEOUT */ { "A wait operation has not completed in the specified time", 57 },
        /* VK_EVENT_SET */ { "An event is signaled", 21 },
        /* VK_EVENT_RESET */ { "An event is unsignaled", 23 },
        /* VK_INCOMPLETE */ { "A return array was too small for the result", 44 },
        /* VK_SUBOPTIMAL_KHR */ { "A swapchain no longer matches the surface properties exactly, but can still be used to present to the surface successfully", 123 },
        /* VK_THREAD_IDLE_KHR */ { "A deferred operation is not complete but there is currently no work for this thread to do at the time of this call", 115 },
        /* VK_THREAD_DONE_KHR */ { "A deferred operation is not complete but there is no work remaining to assign to additional threads", 100 },
        /* VK_OPERATION_DEFERRED_KHR */ { "A deferred operation was requested and at least some of the work was deferred", 78 },
        /* VK_OPERATION_NOT_DEFERRED_KHR */ { "A deferred operation was requested and no operations were deferred", 67 },
        /* VK_PIPELINE_COMPILE_REQUIRED */ { "A requested pipeline creation would have required compilation, but the application requested compilation to not be performed", 125 },
        // ERRORS:
        /* VK_ERROR_OUT_OF_HOST_MEMORY */ { "A host memory allocation has failed", 36 },
        /* VK_ERROR_OUT_OF_DEVICE_MEMORY */ { "A device memory allocation has failed", 38 },
        /* VK_ERROR_INITIALIZATION_FAILED */ { "Initialization of an object could not be completed for implementation-specific reasons", 87 },
        /* VK_ERROR_DEVICE_LOST */ { "The logical or physical device has been lost. (A logical device may become lost for a number of implementation-specific reasons, indicating that pending and future command execution may fail and cause resources and backing memory to become undefined)", 251 },
        /* VK_ERROR_MEMORY_MAP_FAILED */ { "Mapping of a memory object has failed", 38 },
        /* VK_ERROR_LAYER_NOT_PRESENT */ { "A requested layer is not present or could not be loaded", 56 },
        /* VK_ERROR_EXTENSION_NOT_PRESENT */ { "A requested extension is not supported", 39 },
        /* VK_ERROR_FEATURE_NOT_PRESENT */ { "A requested feature is not supported", 37 },
        /* VK_ERROR_INCOMPATIBLE_DRIVER */ { "The requested version of Vulkan is not supported by the driver or is otherwise incompatible for implementation-specific reasons", 128 },
        /* VK_ERROR_TOO_MANY_OBJECTS */ { "Too many objects of the type have already been created", 55 },
        /* VK_ERROR_FORMAT_NOT_SUPPORTED */ { "A requested format is not supported on this device", 51 },
        /* VK_ERROR_FRAGMENTED_POOL */ { "A pool allocation has failed due to fragmentation of the pool’s memory. This must only be returned if no attempt to allocate host or device memory was made to accommodate the new allocation. This should be returned in preference to VK_ERROR_OUT_OF_POOL_MEMORY, but only if the implementation is certain that the pool allocation failure was due to fragmentation", 363 },
        /* VK_ERROR_SURFACE_LOST_KHR */ { "A surface is no longer available", 33 },
        /* VK_ERROR_NATIVE_WINDOW_IN_USE_KHR */ { "The requested window is already in use by Vulkan or another API in a manner which prevents it from being used again", 116 },
        /* VK_ERROR_OUT_OF_DATE_KHR */ { "A surface has changed in such a way that it is no longer compatible with the swapchain, and further presentation requests using the swapchain will fail. Applications must query the new surface properties and recreate their swapchain if they wish to continue presenting to the surface", 284 },
        /* VK_ERROR_INCOMPATIBLE_DISPLAY_KHR */ { "The display used by a swapchain does not use the same presentable image layout, or is incompatible in a way that prevents sharing an image", 139 },
        /* VK_ERROR_INVALID_SHADER_NV */ { "One or more shaders failed to compile or link. More details are reported back to the application via VK_EXT_debug_report if enabled", 132 },
        /* VK_ERROR_OUT_OF_POOL_MEMORY */ { "A pool memory allocation has failed. This must only be returned if no attempt to allocate host or device memory was made to accommodate the new allocation.", 156 },
        /* VK_ERROR_INVALID_EXTERNAL_HANDLE */ { "An external handle is not a valid handle of the specified type", 63 },
        /* VK_ERROR_FRAGMENTATION */ { "A descriptor pool creation has failed due to fragmentation", 59 },
        /* VK_ERROR_INVALID_OPAQUE_CAPTURE_ADDRESS */ { "A buffer creation or memory allocation failed because the requested address is not available. A shader group handle assignment failed because the requested shader group handle information is no longer valid", 207 },
        /* VK_ERROR_FULL_SCREEN_EXCLUSIVE_MODE_LOST_EXT */ { "An operation on a swapchain created with VK_FULL_SCREEN_EXCLUSIVE_APPLICATION_CONTROLLED_EXT failed as it did not have exclusive full-screen access. This may occur due to implementation-dependent reasons, outside of the application’s control", 244 },
        /* VK_ERROR_COMPRESSION_EXHAUSTED_EXT */ { "An image creation failed because internal resources required for compression are exhausted. This must only be returned when fixed-rate compression is requested", 160 },
        /* VK_ERROR_IMAGE_USAGE_NOT_SUPPORTED_KHR */ { "The requested VkImageUsageFlags are not supported", 50 },
        /* VK_ERROR_VIDEO_PICTURE_LAYOUT_NOT_SUPPORTED_KHR */ { "The requested video picture layout is not supported", 52 },
        /* VK_ERROR_VIDEO_PROFILE_OPERATION_NOT_SUPPORTED_KHR */ { "A video profile operation specified via VkVideoProfileInfoKHR::videoCodecOperation is not supported", 100 },
        /* VK_ERROR_VIDEO_PROFILE_FORMAT_NOT_SUPPORTED_KHR */ { "Format parameters in a requested VkVideoProfileInfoKHR chain are not supported", 79 },
        /* VK_ERROR_VIDEO_PROFILE_CODEC_NOT_SUPPORTED_KHR */ { "Codec-specific parameters in a requested VkVideoProfileInfoKHR chain are not supported", 87 },
        /* VK_ERROR_VIDEO_STD_VERSION_NOT_SUPPORTED_KHR */ { "The specified video Std header version is not supported", 56 },
        /* VK_ERROR_INVALID_VIDEO_STD_PARAMETERS_KHR */ { "The specified Video Std parameters do not adhere to the syntactic or semantic requirements of the used video compression standard, or values derived from parameters according to the rules defined by the used video compression standard do not adhere to the capabilities of the video compression standard or the implementation", 325 },
        /* VK_ERROR_UNKNOWN */ { "Unknown Vulkan error (probably even not a vulkan error)", 56 }
        };
    }
    bool FAILED(i64 vk_result) {
        return !SUCCESS(vk_result);
    }
    bool SUCCESS(i64 vk_result) {
        switch (vk_result) {
            case VK_SUCCESS:
            case VK_NOT_READY:
            case VK_TIMEOUT:
            case VK_EVENT_SET:
            case VK_EVENT_RESET:
            case VK_INCOMPLETE:
            case VK_SUBOPTIMAL_KHR:
            case VK_THREAD_IDLE_KHR:
            case VK_THREAD_DONE_KHR:
            case VK_OPERATION_DEFERRED_KHR:
            case VK_OPERATION_NOT_DEFERRED_KHR:
            case VK_PIPELINE_COMPILE_REQUIRED:
                return true;
            default:
                return false;
        }
    }
    const char* VKGetErrorName(i64 vk_result) {
        switch (vk_result) {
            case VK_SUCCESS:                                            return "VK_SUCCESS";
            case VK_NOT_READY:                                          return "VK_NOT_READY";
            case VK_TIMEOUT:                                            return "VK_TIMEOUT";
            case VK_EVENT_SET:                                          return "VK_EVENT_SET";
            case VK_EVENT_RESET:                                        return "VK_EVENT_RESET";
            case VK_INCOMPLETE:                                         return "VK_INCOMPLETE";
            case VK_SUBOPTIMAL_KHR:                                     return "VK_SUBOPTIMAL_KHR";
            case VK_THREAD_IDLE_KHR:                                    return "VK_THREAD_IDLE_KHR";
            case VK_THREAD_DONE_KHR:                                    return "VK_THREAD_DONE_KHR";
            case VK_OPERATION_DEFERRED_KHR:                             return "VK_OPERATION_DEFERRED_KHR";
            case VK_OPERATION_NOT_DEFERRED_KHR:                         return "VK_OPERATION_NOT_DEFERRED_KHR";
            case VK_PIPELINE_COMPILE_REQUIRED:                          return "VK_PIPELINE_COMPILE_REQUIRED";
                // Error codes down below:
            case VK_ERROR_OUT_OF_HOST_MEMORY:                           return "VK_ERROR_OUT_OF_HOST_MEMORY";
            case VK_ERROR_OUT_OF_DEVICE_MEMORY:                         return "VK_ERROR_OUT_OF_DEVICE_MEMORY";
            case VK_ERROR_INITIALIZATION_FAILED:                        return "VK_ERROR_INITIALIZATION_FAILED";
            case VK_ERROR_DEVICE_LOST:                                  return "VK_ERROR_DEVICE_LOST";
            case VK_ERROR_MEMORY_MAP_FAILED:                            return "VK_ERROR_MEMORY_MAP_FAILED";
            case VK_ERROR_LAYER_NOT_PRESENT:                            return "VK_ERROR_LAYER_NOT_PRESENT";
            case VK_ERROR_EXTENSION_NOT_PRESENT:                        return "VK_ERROR_EXTENSION_NOT_PRESENT";
            case VK_ERROR_FEATURE_NOT_PRESENT:                          return "VK_ERROR_FEATURE_NOT_PRESENT";
            case VK_ERROR_INCOMPATIBLE_DRIVER:                          return "VK_ERROR_INCOMPATIBLE_DRIVER";
            case VK_ERROR_TOO_MANY_OBJECTS:                             return "VK_ERROR_TOO_MANY_OBJECTS";
            case VK_ERROR_FORMAT_NOT_SUPPORTED:                         return "VK_ERROR_FORMAT_NOT_SUPPORTED";
            case VK_ERROR_FRAGMENTED_POOL:                              return "VK_ERROR_FRAGMENTED_POOL";
            case VK_ERROR_SURFACE_LOST_KHR:                             return "VK_ERROR_SURFACE_LOST_KHR";
            case VK_ERROR_NATIVE_WINDOW_IN_USE_KHR:                     return "VK_ERROR_NATIVE_WINDOW_IN_USE_KHR";
            case VK_ERROR_OUT_OF_DATE_KHR:                              return "VK_ERROR_OUT_OF_DATE_KHR";
            case VK_ERROR_INCOMPATIBLE_DISPLAY_KHR:                     return "VK_ERROR_INCOMPATIBLE_DISPLAY_KHR";
            case VK_ERROR_INVALID_SHADER_NV:                            return "VK_ERROR_INVALID_SHADER_NV";
            case VK_ERROR_OUT_OF_POOL_MEMORY:                           return "VK_ERROR_OUT_OF_POOL_MEMORY";
            case VK_ERROR_INVALID_EXTERNAL_HANDLE:                      return "VK_ERROR_INVALID_EXTERNAL_HANDLE";
            case VK_ERROR_FRAGMENTATION:                                return "VK_ERROR_FRAGMENTATION";
            case VK_ERROR_INVALID_OPAQUE_CAPTURE_ADDRESS:               return "VK_ERROR_INVALID_OPAQUE_CAPTURE_ADDRESS";
            case VK_ERROR_FULL_SCREEN_EXCLUSIVE_MODE_LOST_EXT:          return "VK_ERROR_FULL_SCREEN_EXCLUSIVE_MODE_LOST_EXT";
            case VK_ERROR_COMPRESSION_EXHAUSTED_EXT:                    return "VK_ERROR_COMPRESSION_EXHAUSTED_EXT";
            case VK_ERROR_IMAGE_USAGE_NOT_SUPPORTED_KHR:                return "VK_ERROR_IMAGE_USAGE_NOT_SUPPORTED_KHR";
            case VK_ERROR_VIDEO_PICTURE_LAYOUT_NOT_SUPPORTED_KHR:       return "VK_ERROR_VIDEO_PICTURE_LAYOUT_NOT_SUPPORTED_KHR";
            case VK_ERROR_VIDEO_PROFILE_OPERATION_NOT_SUPPORTED_KHR:    return "VK_ERROR_VIDEO_PROFILE_OPERATION_NOT_SUPPORTED_KHR";
            case VK_ERROR_VIDEO_PROFILE_FORMAT_NOT_SUPPORTED_KHR:       return "VK_ERROR_VIDEO_PROFILE_FORMAT_NOT_SUPPORTED_KHR";
            case VK_ERROR_VIDEO_PROFILE_CODEC_NOT_SUPPORTED_KHR:        return "VK_ERROR_VIDEO_PROFILE_CODEC_NOT_SUPPORTED_KHR";
            case VK_ERROR_VIDEO_STD_VERSION_NOT_SUPPORTED_KHR:          return "VK_ERROR_VIDEO_STD_VERSION_NOT_SUPPORTED_KHR";
            case VK_ERROR_INVALID_VIDEO_STD_PARAMETERS_KHR:             return "VK_ERROR_INVALID_VIDEO_STD_PARAMETERS_KHR";
            // For some unknown reason not provided at MacOS X
            // case VK_ERROR_INCOMPATIBLE_SHADER_BINARY_EXT:
            default:
                return "VK_ERROR_UNKNOWN";
        }
    }
    uint VKGetErrorDescription(i64 vk_result, char** pp_buffer, uint count) {
        if (!pp_buffer || !count || (!(SUCCESS(vk_result) || FAILED(vk_result)))) return 0;
        char* buffer = *pp_buffer;

        const uint index = get_vk_result_index(vk_result);
        const auto& desc = vk_result_description_table[index];
        const uint len = min(count, desc.length);
        strncpy(buffer, desc.text, len);
        return len;
    }
}

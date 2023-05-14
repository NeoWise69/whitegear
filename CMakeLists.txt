CMAKE_MINIMUM_REQUIRED(VERSION 3.2)
PROJECT(WHITEGEAR)

SET(CMAKE_CXX_STANDARD 17)

INCLUDE_DIRECTORIES(.)

# FIND GLFW STEP
FIND_PATH(GLFW_PATH deps/glfw)

IF ((NOT GLFW_PATH) OR (NOT EXISTS ${GLFW_PATH}))

    EXECUTE_PROCESS(COMMAND git submodule update --init deps/glfw
                    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

ENDIF()
ADD_SUBDIRECTORY(deps/glfw)
# !FIND GLFW STEP

# FIND VULKAN SDK STEP
IF(NOT "$ENV{VK_SDK_PATH}" STREQUAL "")
    SET(VK_SDK_PATH $ENV{VK_SDK_PATH} CACHE INTERNAL "Copied from environment variable.")
ENDIF ()

IF ((NOT VK_SDK_PATH) OR (NOT EXISTS ${VK_SDK_PATH}))
    MESSAGE(SEND_ERROR "Vulkan SDK is not present!")
    MESSAGE("++ whitegear depends on VulkanSDK")
    MESSAGE("++ You should download VulkanSDK from 'https://vulkan.lunarg.com/#new_tab'")
    MESSAGE("++ If you're still messing around with this error, please check if your environment variables exports 'VK_SDK_PATH' variable.")
ENDIF ()

INCLUDE_DIRECTORIES(${VK_SDK_PATH}/Include)
FIND_LIBRARY(NAMES vulkan-1 PATHS ${VK_SDK_PATH}/Lib)

# !FIND VULKAN SDK STEP

ADD_SUBDIRECTORY(core)
ADD_SUBDIRECTORY(math)
ADD_SUBDIRECTORY(tests)

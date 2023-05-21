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

INCLUDE_DIRECTORIES(deps/glfw/include deps/stb)
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

IF(WIN32)
    INCLUDE_DIRECTORIES(${VK_SDK_PATH}/Include)
    FIND_LIBRARY(VK_LIB NAMES vulkan-1 PATHS ${VK_SDK_PATH}/Lib)
ELSE()
    INCLUDE_DIRECTORIES(${VK_SDK_PATH}/include)
    FIND_LIBRARY(VK_LIB NAMES vulkan PATHS ${VK_SDK_PATH}/lib)
ENDIF()

# !FIND VULKAN SDK STEP

ADD_SUBDIRECTORY(core)
ADD_SUBDIRECTORY(math)
ADD_SUBDIRECTORY(tests)
ADD_SUBDIRECTORY(runtime)
ADD_SUBDIRECTORY(graphics)
ADD_SUBDIRECTORY(entry)
ADD_SUBDIRECTORY(editor)

ADD_SUBDIRECTORY(tools)

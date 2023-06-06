CMAKE_MINIMUM_REQUIRED(VERSION 3.2)
PROJECT(WHITEGEAR)

SET(CMAKE_CXX_STANDARD 17)


IF(WIN32)
    SET(CMAKE_CXX_FLAGS_RELEASE "/O2")
    SET(CMAKE_CXX_FLAGS_RELEASE "/MD")
ELSE ()
    SET(CMAKE_CXX_FLAGS_RELEASE "-O3")
    SET(CMAKE_CXX_FLAGS_DEBUG "-D_DEBUG")
    SET(CMAKE_CXX_FLAGS_DEBUG "-g")
ENDIF ()

INCLUDE_DIRECTORIES(.)

# FIND GLFW STEP
FIND_PATH(GLFW_PATH deps/glfw)
IF ((NOT GLFW_PATH) OR (NOT EXISTS ${GLFW_PATH}))
    EXECUTE_PROCESS(COMMAND git submodule add https://github.com/glfw/glfw.git deps/glfw)
ENDIF()
ADD_SUBDIRECTORY(deps/glfw)
INCLUDE_DIRECTORIES(deps/glfw/include deps/stb)
# !FIND GLFW STEP

# FIND YAMLCPP STEP
FIND_PATH(YAMLCPP_PATH deps/yaml-cpp)
IF ((NOT YAMLCPP_PATH) OR (NOT EXISTS ${YAMLCPP_PATH}))
    EXECUTE_PROCESS(COMMAND git submodule add https://github.com/jbeder/yaml-cpp.git deps/yaml-cpp)
ENDIF()
ADD_SUBDIRECTORY(deps/yaml-cpp)

INCLUDE_DIRECTORIES(deps/glfw/include deps/yaml-cpp/include deps/stb)
# !FIND YAMLCPP STEP

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

INCLUDE_DIRECTORIES(deps/imgui/imgui-repo)

# WG_BUILD_TYPE_DIST -> used for distribution builds
SET(WG_BUILD_EDITOR OFF)
IF(WG_BUILD_EDITOR)
    IF(WIN32)
        SET(CMAKE_CXX_FLAGS "/D WG_BUILD_EDITOR")
    ELSE()
        SET(CMAKE_CXX_FLAGS "-DWG_BUILD_EDITOR")
    ENDIF()
ENDIF ()

# DXErr including
IF(WIN32)
    INCLUDE_DIRECTORIES(deps/DXErr)
    ADD_SUBDIRECTORY(deps/DXErr)
ENDIF()

ADD_SUBDIRECTORY(core)
ADD_SUBDIRECTORY(resources)
ADD_SUBDIRECTORY(math)
ADD_SUBDIRECTORY(scene)
ADD_SUBDIRECTORY(tests)
ADD_SUBDIRECTORY(runtime)
ADD_SUBDIRECTORY(graphics)
ADD_SUBDIRECTORY(renda)
ADD_SUBDIRECTORY(entry)
ADD_SUBDIRECTORY(editor)

ADD_SUBDIRECTORY(tools)

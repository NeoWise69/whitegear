SET(Renda_SOURCES renderer_api.hpp renderer_api.cpp rendering_engine.hpp rendering_engine.cpp backend/renda_vulkan/rendering_engine_vulkan.hpp backend/renda_vulkan/minimal.hpp backend/renda_vulkan/rendering_engine_vulkan.cpp)
ADD_LIBRARY(wg_renda STATIC ${Renda_SOURCES})
TARGET_LINK_LIBRARIES(wg_renda PRIVATE ${VK_LIB})
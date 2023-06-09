LIST(APPEND Renda_VK_SOURCES
        rendering_engine_vulkan.cpp
        vk_graphics.cpp
        vk_result.cpp
        )

ADD_LIBRARY(wg_renda_vk STATIC ${Renda_VK_SOURCES})
TARGET_LINK_LIBRARIES(wg_renda_vk PRIVATE ${VK_LIB})

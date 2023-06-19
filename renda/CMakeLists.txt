
SET(Renda_SOURCES
        renderer_api.cpp
        rendering_engine.cpp
        vertex_layout.cpp
        drawing/constant_buffer_per_frame.cpp
        drawing/renderable.cpp
        drawing/constant_buffer_per_object.cpp
        drawing/common_cube_renderable.cpp
        drawing/common_skinned_cube_renderable.cpp resource_storage.hpp resource_storage.cpp)

ADD_LIBRARY(wg_renda STATIC ${Renda_SOURCES})

IF (WIN32)
    ADD_SUBDIRECTORY(backend/renda_dx11)
    TARGET_LINK_LIBRARIES(wg_renda PRIVATE wg_renda_dx11)
ELSE ()
    ADD_SUBDIRECTORY(backend/renda_vulkan)
    TARGET_LINK_LIBRARIES(wg_renda PRIVATE wg_renda_vk)
ENDIF ()

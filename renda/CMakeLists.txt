SET(Renda_SOURCES renderer_api.hpp renderer_api.cpp rendering_engine.hpp rendering_engine.cpp backend/renda_vulkan/rendering_engine_vulkan.hpp backend/renda_vulkan/minimal.hpp backend/renda_vulkan/rendering_engine_vulkan.cpp backend/renda_directx/rendering_engine_directx.hpp backend/renda_directx/minimal.hpp backend/renda_null/rendering_engine_null.hpp backend/renda_directx/rendering_engine_directx.cpp backend/renda_directx/dx_graphics.cpp backend/renda_directx/dx_graphics.hpp backend/renda_directx/dx_info_manager.cpp backend/renda_directx/dx_info_manager.hpp backend/renda_directx/bindable/dx_bindable_base.hpp backend/renda_directx/dx_renderable.hpp backend/renda_directx/bindable/dx_vertex_buffer.hpp backend/renda_directx/bindable/dx_vertex_buffer.cpp backend/renda_directx/bindable/dx_vertex_shader.cpp backend/renda_directx/bindable/dx_vertex_shader.hpp backend/renda_directx/bindable/dx_geometry_topology.cpp backend/renda_directx/bindable/dx_geometry_topology.hpp backend/renda_directx/bindable/dx_pixel_shader.cpp backend/renda_directx/bindable/dx_pixel_shader.hpp backend/renda_directx/bindable/dx_input_layout.cpp backend/renda_directx/bindable/dx_input_layout.hpp backend/renda_directx/bindable/dx_index_buffer.cpp backend/renda_directx/bindable/dx_index_buffer.hpp backend/renda_directx/dx_renderable.cpp backend/renda_directx/bindable/dx_constant_buffer_base.hpp backend/renda_null/rendering_engine_null.cpp backend/renda_vulkan/vk_graphics.cpp backend/renda_vulkan/vk_graphics.hpp backend/renda_vulkan/vk_result.cpp backend/renda_vulkan/vk_result.hpp backend/renda_directx/bindable/dx_per_renderable_constant_buffer.cpp backend/renda_directx/bindable/dx_per_renderable_constant_buffer.hpp backend/renda_directx/dx_scene_renderable.hpp backend/renda_directx/dx_scene_renderable.cpp backend/renda_directx/dx_common_mesh_cube.cpp backend/renda_directx/dx_common_mesh_cube.hpp backend/renda_directx/bindable/dx_per_frame_constant_buffer.cpp backend/renda_directx/bindable/dx_per_frame_constant_buffer.hpp backend/renda_directx/dx_render_target_buffer.cpp backend/renda_directx/dx_render_target_buffer.hpp)
ADD_LIBRARY(wg_renda STATIC ${Renda_SOURCES})

LIST(APPEND WG_RENDA_LIBS ${VK_LIB})

IF((CMAKE_BUILD_TYPE STREQUAL "Debug") AND WIN32)
    LIST(APPEND WG_RENDA_LIBS dxguid)
ENDIF()

IF(WIN32)
    LIST(APPEND WG_RENDA_LIBS d3d11 DXErr)
ENDIF ()

TARGET_LINK_LIBRARIES(wg_renda PRIVATE ${WG_RENDA_LIBS})
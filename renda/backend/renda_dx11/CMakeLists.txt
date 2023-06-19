SET(Renda_DX11_SOURCES
        gpu_device_dx11.cpp
        swapchain_dx11.cpp
        target_buffer_dx11.cpp
        gpu_topology_dx11.cpp
        utils_dx11.cpp
        geometry_buffer_dx11.cpp
        shader_program_dx11.cpp
        vertex_input_layout_dx11.cpp
        constant_buffer_base_dx11.cpp
        texture_dx11.cpp
        sampler_dx11.cpp)

ADD_LIBRARY(wg_renda_dx11 STATIC ${Renda_DX11_SOURCES})

IF((CMAKE_BUILD_TYPE STREQUAL "Debug") AND WIN32)
    TARGET_LINK_LIBRARIES(wg_renda_dx11 PRIVATE dxguid)
ENDIF()

IF(WIN32)
    TARGET_LINK_LIBRARIES(wg_renda_dx11 PRIVATE d3d11 dxgi D3DCompiler DXErr)
ENDIF ()



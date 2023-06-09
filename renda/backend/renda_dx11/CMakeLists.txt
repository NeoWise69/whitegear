SET(Renda_DX11_SOURCES
        rendering_engine.cpp
        gpu_device.cpp
        swapchain.cpp
        target_buffer.cpp
        gpu_topology.cpp
        vertex_layout.cpp
        utils_dx11.cpp
        geometry_buffer_dx11.cpp
        shader_program.cpp
        vertex_input_layout.cpp
        constant_buffer_base_dx11.cpp
        )

ADD_LIBRARY(wg_renda_dx11 STATIC ${Renda_DX11_SOURCES})

IF((CMAKE_BUILD_TYPE STREQUAL "Debug") AND WIN32)
    TARGET_LINK_LIBRARIES(wg_renda_dx11 PRIVATE dxguid)
ENDIF()

IF(WIN32)
    TARGET_LINK_LIBRARIES(wg_renda_dx11 PRIVATE d3d11 dxgi D3DCompiler DXErr)
ENDIF ()



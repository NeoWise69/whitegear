SET(Renda_SOURCES renderer_api.hpp renderer_api.cpp rendering_engine.hpp rendering_engine.cpp backend/renda_vulkan/rendering_engine_vulkan.hpp backend/renda_vulkan/minimal.hpp backend/renda_vulkan/rendering_engine_vulkan.cpp backend/renda_directx/rendering_engine_directx.hpp backend/renda_directx/minimal.hpp backend/renda_null/rendering_engine_null.hpp backend/renda_directx/rendering_engine_directx.cpp)
ADD_LIBRARY(wg_renda STATIC ${Renda_SOURCES})

LIST(APPEND WG_RENDA_LIBS ${VK_LIB})

IF(WIN32)
    LIST(APPEND WG_RENDA_LIBS d3d11)
ENDIF ()

TARGET_LINK_LIBRARIES(wg_renda PRIVATE ${WG_RENDA_LIBS})
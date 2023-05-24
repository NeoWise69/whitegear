LIST(APPEND IMGUI_SOURCES imgui-repo/imgui.cpp imgui-repo/imgui_demo.cpp imgui-repo/imgui_draw.cpp imgui-repo/imgui_tables.cpp imgui-repo/imgui_widgets.cpp imgui-repo/backends/imgui_impl_glfw.cpp)
LIST(APPEND IMGUI_LIBS glfw)

IF(WIN32)
    # Include directX and win32 dependent sources
    LIST(APPEND IMGUI_SOURCES imgui-repo/backends/imgui_impl_dx11.cpp)
    LIST(APPEND IMGUI_LIBS d3d11)
ELSE ()
    # Include vulkan dependent sources
    LIST(APPEND IMGUI_SOURCES imgui-repo/backends/imgui_impl_vulkan.cpp)
    LIST(APPEND IMGUI_LIBS ${VK_LIB})
ENDIF ()

ADD_LIBRARY(wg_imgui STATIC ${IMGUI_SOURCES})
TARGET_LINK_LIBRARIES(wg_imgui PRIVATE ${IMGUI_LIBS})

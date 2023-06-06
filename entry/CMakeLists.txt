SET(Entry_SOURCES start.cpp)

ADD_EXECUTABLE(wg_app ${Entry_SOURCES})
LIST(APPEND WG_LIBS_TO_BUILD wg_core wg_resources wg_math ${VK_LIB} wg_runtime wg_graphics wg_renda wg_scene glfw yaml-cpp)

IF(WG_BUILD_EDITOR)
    LIST(APPEND WG_LIBS_TO_BUILD wg_editor)
ENDIF ()

TARGET_LINK_LIBRARIES(wg_app PRIVATE ${WG_LIBS_TO_BUILD})

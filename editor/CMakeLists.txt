SET(Editor_SOURCES editor_application.hpp editor_application.cpp world_editor_module.cpp world_editor_module.hpp imgui_tweaks.hpp imgui_tweaks.cpp)
ADD_LIBRARY(wg_editor STATIC ${Editor_SOURCES})

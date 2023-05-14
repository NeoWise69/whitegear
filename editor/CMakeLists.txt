SET(Editor_SOURCES editor_application.hpp editor_application.cpp)
ADD_LIBRARY(wg_editor STATIC ${Editor_SOURCES})
TARGET_LINK_LIBRARIES(wg_editor)
SET(Graphics_SOURCES window.hpp window.cpp cursor.hpp cursor.cpp)
ADD_LIBRARY(wg_graphics STATIC ${Graphics_SOURCES})
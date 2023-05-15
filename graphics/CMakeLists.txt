SET(Graphics_SOURCES instance.cpp window.hpp window.cpp renderer.hpp renderer.cpp device.hpp device.cpp)
ADD_LIBRARY(wg_graphics STATIC ${Graphics_SOURCES})
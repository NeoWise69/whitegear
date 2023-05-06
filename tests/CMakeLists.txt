SET(Tests_SOURCES main.cpp containers_array_view.hpp containers_string_view.hpp)
# SET(CMAKE_CXX_STANDARD 17)
ADD_EXECUTABLE(tests ${Tests_SOURCES})
TARGET_LINK_LIBRARIES(tests PUBLIC wg_core wg_math)
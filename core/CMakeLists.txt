SET(Core_SOURCES arch_info.cpp logger.cpp containers/string_view.hpp)
SET(CMAKE_CXX_STANDARD 17)
ADD_LIBRARY(wg_core STATIC ${Core_SOURCES})
SET(Math_SOURCES scalar_func.cpp noise.cpp)
SET(Math_HEADERS scalar_base.hpp vector_base.hpp vec2.hpp vec3.hpp vec4.hpp vec.hpp noise.hpp)
SET(CMAKE_CXX_STANDARD 17)
ADD_LIBRARY(wg_math STATIC ${Math_SOURCES} ${Math_HEADERS})
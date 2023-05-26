SET(Math_SOURCES scalar_func.cpp noise.cpp)
SET(Math_HEADERS scalar_base.hpp vector_base.hpp vec2.hpp vec3.hpp vec4.hpp vec.hpp noise.hpp color.hpp matrix_base.hpp mat4.hpp mat.hpp geometry.hpp frustum.cpp curve.hpp quaternion.hpp vertex.hpp free_camera.cpp free_camera.hpp geometry_buffer.hpp)
ADD_LIBRARY(wg_math STATIC ${Math_SOURCES} ${Math_HEADERS})
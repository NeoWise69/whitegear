SET(Runtime_SOURCES runtime_module.hpp runtime_module.cpp runtime_core.hpp runtime_core.cpp user_input.hpp user_input.cpp)
ADD_LIBRARY(wg_runtime STATIC ${Runtime_SOURCES})
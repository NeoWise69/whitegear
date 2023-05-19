SET(Runtime_SOURCES runtime_module.hpp runtime_module.cpp runtime_core.hpp runtime_core.cpp user_input.hpp)
ADD_LIBRARY(wg_runtime STATIC ${Runtime_SOURCES})
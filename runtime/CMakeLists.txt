SET(Runtime_SOURCES runtime_module.hpp runtime_module.cpp runtime_core.hpp)
ADD_LIBRARY(wg_runtime STATIC ${Runtime_SOURCES})
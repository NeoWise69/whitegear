SET(Resources_SOURCES base.hpp cache.hpp build.cpp name.cpp text_resource.hpp text_resource_loader.cpp text_resource_cache.cpp)
ADD_LIBRARY(wg_resources STATIC ${Resources_SOURCES})
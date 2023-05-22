SET(Renda_SOURCES renderer_api.hpp renderer_api.cpp)
ADD_LIBRARY(wg_renda STATIC ${Renda_SOURCES})
TARGET_LINK_LIBRARIES(wg_renda PRIVATE ${VK_LIB})
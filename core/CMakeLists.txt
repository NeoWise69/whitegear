SET(Core_SOURCES arch_info.cpp logger.cpp containers/string_view.hpp pts/pts_blob.hpp pts/pts_blob.cpp)
ADD_LIBRARY(wg_core STATIC ${Core_SOURCES})
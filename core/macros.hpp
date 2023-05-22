
/*******************************************************************************
 * Copyright (c) 2023.
 * This file is part of The WhiteGear Studio software property.
 * If you get unexpected access to this file, or part ot whole codebase, you should
 * report this source code leak and delete all copies of source code from all your machines.
 ******************************************************************************/

#ifndef WHITEGEAR_MACROS_HPP
#define WHITEGEAR_MACROS_HPP

#if defined(_MSC_VER) || defined(_WIN32) || defined(_WIN64)
#   define WG_WINDOWS 1
#elif defined(__APPLE__)
#   define WG_UNIX 1
#endif

#if defined(_DEBUG)
#   define WG_BUILD_DEBUG 1
#elif defined(WG_BUILD_TYPE_DIST)
#   define WG_BUILD_DIST 1
#else
#   define WG_BUILD_RELEASE 1
#endif

#endif //WHITEGEAR_MACROS_HPP

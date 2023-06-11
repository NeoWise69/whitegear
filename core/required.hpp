
/*******************************************************************************
 * Copyright (c) 2023.
 * This file is part of The WhiteGear Studio software property.
 * If you get unexpected access to this file, or part ot whole codebase, you should
 * report this source code leak and delete all copies of source code from all your machines.
 ******************************************************************************/

#ifndef WHITEGEAR_REQUIRED_HPP
#define WHITEGEAR_REQUIRED_HPP

#include <core/typedefs.hpp>

namespace wg {
    enum e_format : uint {
        FORMAT_NONE,

        FORMAT_RGBA32_FLOAT,
        FORMAT_RGBA32_UINT,
        FORMAT_RGBA32_SINT,
        FORMAT_RGB32_FLOAT,
        FORMAT_RGB32_UINT,
        FORMAT_RGB32_SINT,
        FORMAT_RG32_FLOAT,
        FORMAT_RG32_UINT,
        FORMAT_RG32_SINT,
        FORMAT_D32_FLOAT,
        FORMAT_R32_FLOAT,
        FORMAT_R32_UINT,
        FORMAT_R32_SINT,

        FORMAT_RGBA8_UNORM,
        FORMAT_RGBA8_SNORM,
        FORMAT_RGBA8_UINT,
        FORMAT_RGBA8_SINT,
        FORMAT_RGB8_UNORM,
        FORMAT_RGB8_SNORM,
        FORMAT_RGB8_UINT,
        FORMAT_RGB8_SINT,
        FORMAT_D24_UNORM_S8_UINT,
    };
}

#endif //WHITEGEAR_REQUIRED_HPP

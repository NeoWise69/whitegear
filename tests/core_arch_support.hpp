
/*******************************************************************************
 * Copyright (c) 2023.
 * This file is part of The WhiteGear Studio software property.
 * If you get unexpected access to this file, or part ot whole codebase, you should
 * report this source code leak and delete all copies of source code from all your machines.
 ******************************************************************************/

#ifndef WHITEGEAR_CORE_ARCH_SUPPORT_HPP
#define WHITEGEAR_CORE_ARCH_SUPPORT_HPP

#include <core/arch_info.hpp>

auto core_arch_support_test() -> bool {

    if (!wg::is_support(wg::HW_SSE))
        return false;
    if (!wg::is_support(wg::HW_SSE2))
        return false;
    if (!wg::is_support(wg::HW_SSE3))
        return false;
    if (!wg::is_support(wg::HW_SSE41))
        return false;
    if (!wg::is_support(wg::HW_SSE42))
        return false;
    if (!wg::is_support(wg::HW_AVX))
        return false;

    return true;
}

#endif //WHITEGEAR_CORE_ARCH_SUPPORT_HPP

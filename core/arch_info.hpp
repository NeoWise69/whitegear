
/*******************************************************************************
 * Copyright (c) 2023.
 * This file is part of The WhiteGear Studio software property.
 * If you get unexpected access to this file, or part ot whole codebase, you should
 * report this source code leak and delete all copies of source code from all your machines.
 ******************************************************************************/

#ifndef WHITEGEAR_ARCH_INFO_HPP
#define WHITEGEAR_ARCH_INFO_HPP

#include "typedefs.hpp"

namespace wg {
    enum e_hardware_support {
        HW_NONE,
        HW_MMX,
        HW_x64,
        HW_ABM,      // Advanced Bit Manipulation
        HW_RDRAND,
        HW_BMI1,
        HW_BMI2,
        HW_ADX,
        HW_PREFETCHWT1,

        //  SIMD: 128-bit
        HW_SSE,
        HW_SSE2,
        HW_SSE3,
        HW_SSSE3,
        HW_SSE41,
        HW_SSE42,
        HW_SSE4a,
        HW_AES,
        HW_SHA,

        //  SIMD: 256-bit
        HW_AVX,
        HW_XOP,
        HW_FMA3,
        HW_FMA4,
        HW_AVX2,

        //  SIMD: 512-bit
        HW_AVX512F,    //  AVX512 Foundation
        HW_AVX512CD,   //  AVX512 Conflict Detection
        HW_AVX512PF,   //  AVX512 Prefetch
        HW_AVX512ER,   //  AVX512 Exponential + Reciprocal
        HW_AVX512VL,   //  AVX512 Vector Length Extensions
        HW_AVX512BW,   //  AVX512 Byte + Word
        HW_AVX512DQ,   //  AVX512 Double-word + Quad-word
        HW_AVX512IFMA, //  AVX512 Integer 52-bit Fused Multiply-Add
        HW_AVX512VBMI, //  AVX512 Vector Byte Manipulation Instructions
    };

    bool is_support(e_hardware_support);
}

#endif //WHITEGEAR_ARCH_INFO_HPP


/*******************************************************************************
 * Copyright (c) 2023.
 * This file is part of The WhiteGear Studio software property.
 * If you get unexpected access to this file, or part ot whole codebase, you should
 * report this source code leak and delete all copies of source code from all your machines.
 ******************************************************************************/

#include "core.hpp"

/**
 * CPUID function declaration.
 */
#ifdef _WIN32
#include <intrin.h>
#define cpuid(info, x)    __cpuidex(info, x, 0)
#else
//  GCC Intrinsics
#include <cpuid.h>
void cpuid(int info[4], int InfoType){
    __cpuid_count(InfoType, 0, info[0], info[1], info[2], info[3]);
}
#endif

namespace wg {

    namespace {
        bool b_HW_MMX;
        bool b_HW_x64;
        bool b_HW_ABM;      // Advanced Bit Manipulation
        bool b_HW_RDRAND;
        bool b_HW_BMI1;
        bool b_HW_BMI2;
        bool b_HW_ADX;
        bool b_HW_PREFETCHWT1;

        //  SIMD: 128-bit
        bool b_HW_SSE;
        bool b_HW_SSE2;
        bool b_HW_SSE3;
        bool b_HW_SSSE3;
        bool b_HW_SSE41;
        bool b_HW_SSE42;
        bool b_HW_SSE4a;
        bool b_HW_AES;
        bool b_HW_SHA;

        //  SIMD: 256-bit
        bool b_HW_AVX;
        bool b_HW_XOP;
        bool b_HW_FMA3;
        bool b_HW_FMA4;
        bool b_HW_AVX2;

        //  SIMD: 512-bit
        bool b_HW_AVX512F;    //  AVX512 Foundation
        bool b_HW_AVX512CD;   //  AVX512 Conflict Detection
        bool b_HW_AVX512PF;   //  AVX512 Prefetch
        bool b_HW_AVX512ER;   //  AVX512 Exponential + Reciprocal
        bool b_HW_AVX512VL;   //  AVX512 Vector Length Extensions
        bool b_HW_AVX512BW;   //  AVX512 Byte + Word
        bool b_HW_AVX512DQ;   //  AVX512 Doubleword + Quadword
        bool b_HW_AVX512IFMA; //  AVX512 Integer 52-bit Fused Multiply-Add
        bool b_HW_AVX512VBMI; //  AVX512 Vector Byte Manipulation Instructions

        bool acquire_info() {
            i32 info[4];
            cpuid(info, 0);
            const int n = info[0];
            cpuid(info, 0x80000000);
            const unsigned nex = info[0];
            if (n >= 0x00000001) {
                cpuid(info, 0x00000001);
                b_HW_MMX    = (info[3] & ((int)1 << 23)) != 0;
                b_HW_SSE    = (info[3] & ((int)1 << 25)) != 0;
                b_HW_SSE2   = (info[3] & ((int)1 << 26)) != 0;
                b_HW_SSE3   = (info[2] & ((int)1 <<  0)) != 0;
                b_HW_SSSE3  = (info[2] & ((int)1 <<  9)) != 0;
                b_HW_SSE41  = (info[2] & ((int)1 << 19)) != 0;
                b_HW_SSE42  = (info[2] & ((int)1 << 20)) != 0;
                b_HW_AES    = (info[2] & ((int)1 << 25)) != 0;
                b_HW_AVX    = (info[2] & ((int)1 << 28)) != 0;
                b_HW_FMA3   = (info[2] & ((int)1 << 12)) != 0;
                b_HW_RDRAND = (info[2] & ((int)1 << 30)) != 0;
            }
            if (n >= 0x00000007) {
                cpuid(info, 0x00000007);
                b_HW_AVX2        = (info[1] & ((int)1 <<  5)) != 0;
                b_HW_BMI1        = (info[1] & ((int)1 <<  3)) != 0;
                b_HW_BMI2        = (info[1] & ((int)1 <<  8)) != 0;
                b_HW_ADX         = (info[1] & ((int)1 << 19)) != 0;
                b_HW_SHA         = (info[1] & ((int)1 << 29)) != 0;
                b_HW_PREFETCHWT1 = (info[2] & ((int)1 <<  0)) != 0;
                b_HW_AVX512F     = (info[1] & ((int)1 << 16)) != 0;
                b_HW_AVX512CD    = (info[1] & ((int)1 << 28)) != 0;
                b_HW_AVX512PF    = (info[1] & ((int)1 << 26)) != 0;
                b_HW_AVX512ER    = (info[1] & ((int)1 << 27)) != 0;
                b_HW_AVX512VL    = (info[1] & ((int)1 << 31)) != 0;
                b_HW_AVX512BW    = (info[1] & ((int)1 << 30)) != 0;
                b_HW_AVX512DQ    = (info[1] & ((int)1 << 17)) != 0;
                b_HW_AVX512IFMA  = (info[1] & ((int)1 << 21)) != 0;
                b_HW_AVX512VBMI  = (info[2] & ((int)1 <<  1)) != 0;
            }
            if (nex >= 0x80000001) {
                cpuid(info, 0x80000001);
                b_HW_x64   = (info[3] & ((int)1 << 29)) != 0;
                b_HW_ABM   = (info[2] & ((int)1 <<  5)) != 0;
                b_HW_SSE4a = (info[2] & ((int)1 <<  6)) != 0;
                b_HW_FMA4  = (info[2] & ((int)1 << 16)) != 0;
                b_HW_XOP   = (info[2] & ((int)1 << 11)) != 0;
            }
            return false;
        }

        bool _ = acquire_info();
    }

    bool is_support(e_hardware_support f) {
        switch (f) {
            case HW_NONE: return false;
            case HW_MMX: return b_HW_MMX;
            case HW_x64: return b_HW_x64;
            case HW_ABM: return b_HW_ABM;
            case HW_RDRAND: return b_HW_RDRAND;
            case HW_BMI1: return b_HW_BMI1;
            case HW_BMI2: return b_HW_BMI2;
            case HW_ADX: return b_HW_ADX;
            case HW_PREFETCHWT1: return b_HW_PREFETCHWT1;
            case HW_SSE: return b_HW_SSE;
            case HW_SSE2: return b_HW_SSE2;
            case HW_SSE3: return b_HW_SSE3;
            case HW_SSSE3: return b_HW_SSSE3;
            case HW_SSE41: return b_HW_SSE41;
            case HW_SSE42: return b_HW_SSE42;
            case HW_SSE4a: return b_HW_SSE4a;
            case HW_AES: return b_HW_AES;
            case HW_SHA: return b_HW_SHA;
            case HW_AVX: return b_HW_AVX;
            case HW_XOP: return b_HW_XOP;
            case HW_FMA3: return b_HW_FMA3;
            case HW_FMA4: return b_HW_FMA4;
            case HW_AVX2: return b_HW_AVX2;
            case HW_AVX512F: return b_HW_AVX512F;
            case HW_AVX512CD: return b_HW_AVX512CD;
            case HW_AVX512PF: return b_HW_AVX512PF;
            case HW_AVX512ER: return b_HW_AVX512ER;
            case HW_AVX512VL: return b_HW_AVX512VL;
            case HW_AVX512BW: return b_HW_AVX512BW;
            case HW_AVX512DQ: return b_HW_AVX512DQ;
            case HW_AVX512IFMA: return b_HW_AVX512IFMA;
            case HW_AVX512VBMI: return b_HW_AVX512VBMI;
        }
        return false;
    }

}

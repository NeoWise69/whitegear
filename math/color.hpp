
/*******************************************************************************
 * Copyright (c) 2023.
 * This file is part of The WhiteGear Studio software property.
 * If you get unexpected access to this file, or part ot whole codebase, you should
 * report this source code leak and delete all copies of source code from all your machines.
 ******************************************************************************/

#ifndef WHITEGEAR_COLOR_HPP
#define WHITEGEAR_COLOR_HPP

#include <math/scalar_base.hpp>
#include <math/vec4.hpp>

namespace wg {
    /**
     * Simple RGBA color representation with
     * format of R8G8B8A8, or whole 32 bit integer.
     */
    struct color32 {
        union {
            u32 rep32;
            struct {
                u8 r, g, b, a;
            };
        };

        inline constexpr color32() : rep32() {}
        inline constexpr color32(u8 _r, u8 _g, u8 _b, u8 _a) : r(_r), g(_g), b(_b), a(_a) {}
        inline constexpr color32(u8 v) : r(v), g(v), b(v), a(v) {}
        inline constexpr color32(u32 v) : rep32(v) {}

        inline constexpr explicit operator u32() const {
            return rep32;
        }
        inline constexpr explicit operator const u8*() const {
            return &r;
        }
        /**
         * Converts color32 into vec4 of normalized RGBA color.
         */
        inline vec4 to_rgba() const noexcept {
            return {
                scalar(r) / scalar(255),
                scalar(g) / scalar(255),
                scalar(b) / scalar(255),
                scalar(a) / scalar(255)
            };
        }
        /**
         * Converts color32 into vec3 of normalized RGB color.
         */
        inline vec3 to_rgb() const noexcept {
            return {
                scalar(r) / scalar(255),
                scalar(g) / scalar(255),
                scalar(b) / scalar(255)
            };
        }
    };
}

#endif //WHITEGEAR_COLOR_HPP

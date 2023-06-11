
/*******************************************************************************
 * Copyright (c) 2023.
 * This file is part of The WhiteGear Studio software property.
 * If you get unexpected access to this file, or part ot whole codebase, you should
 * report this source code leak and delete all copies of source code from all your machines.
 ******************************************************************************/

#ifndef WHITEGEAR_IMAGE_HPP
#define WHITEGEAR_IMAGE_HPP

#include <core/typedefs.hpp>
#include <core/smart_ptr.hpp>
#include <core/required.hpp>

namespace wg {
    typedef class image* image_ref;
    class image {
    public:
        inline image() = default;
        ~image();

        enum pattern_t : u8 {
            PATTERN_WHITE,
            PATTERN_BLACK,
            PATTERN_CHESS,
        };
        struct generate_info {
            pattern_t pattern;
            e_format format;
            uint width;
            uint height;
        };
        static image_ref generate(const generate_info& gen_info);
        static image_ref load_from_file(const char* p_filename);
        static image_ref load_from_memory(const void* p_image_data, uint image_size);

        inline uint get_width() const  noexcept{
            return mWidth;
        }
        inline uint get_height() const  noexcept{
            return mHeight;
        }
        inline e_format get_format() const  noexcept{
            return mFormat;
        }
        uint get_num_channels() const noexcept;
        inline void* get_data() const  noexcept{
            return mData;
        }
        inline u8* get_data_u8() const  noexcept{
            return (u8*)mData;
        }
        inline float* get_data_f32() const  noexcept{
            return (float*)mData;
        }

        inline uint get_pixel_u32(uint x, uint y) const {
            return ((uint*)mData)[x + y * mWidth];
        }

        uint get_pixel_size() const;
    private:
        inline image(void *const p_data, uint width, uint height, e_format format) noexcept
            : mData(p_data), mWidth(width), mHeight(height), mFormat(format) {}

        void* mData = nullptr;
        uint mWidth = {},
             mHeight = {};
        e_format mFormat = {};
    };
}

#endif //WHITEGEAR_IMAGE_HPP

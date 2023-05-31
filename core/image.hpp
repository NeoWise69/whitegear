
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
        enum channels_t : u8 {
            RGBA8_UNORM,    /* u8 [r,g,b,a] */
            RGBA32_FLOAT,   /* f32 [r,g,b,a] */
            RGB8_UNORM,     /* u8 [r,g,b] */
            RGB32_FLOAT,    /* f32 [r,g,b] */
        };
        struct generate_info {
            pattern_t pattern;
            channels_t channels;
            uint width;
            uint height;
        };
        static image_ref generate(const generate_info& gen_info);
        static image_ref load_from_file(const char* p_filename);
        static image_ref load_from_memory(const void* p_image_data, uint image_size);

        inline uint get_width() const {
            return mWidth;
        }
        inline uint get_height() const {
            return mHeight;
        }
        inline channels_t get_channels() const {
            return mChannels;
        }
        uint get_num_channels() const;
        inline void* get_data() const {
            return mData;
        }
        inline u8* get_data_u8() const {
            return (u8*)mData;
        }
        inline float* get_data_f32() const {
            return (float*)mData;
        }

        inline uint get_pixel_u32(uint x, uint y) const {
            return ((uint*)mData)[x + y * mWidth];
        }
    private:
        inline image(void *const p_data, uint width, uint height, channels_t channels)
            : mData(p_data), mWidth(width), mHeight(height), mChannels(channels) {}

        void* mData = nullptr;
        uint mWidth = {},
             mHeight = {};
        channels_t mChannels = {};
    };
}

#endif //WHITEGEAR_IMAGE_HPP

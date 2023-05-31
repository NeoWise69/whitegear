
/*******************************************************************************
 * Copyright (c) 2023.
 * This file is part of The WhiteGear Studio software property.
 * If you get unexpected access to this file, or part ot whole codebase, you should
 * report this source code leak and delete all copies of source code from all your machines.
 ******************************************************************************/

#include "image.hpp"
#include "logger.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.hpp>

namespace wg {
    image::~image() {
        stbi_image_free(mData);
    }

    image_ref image::load_from_file(const char *p_filename) {
        auto* im = new image();

        if (stbi_is_hdr(p_filename)) {
            int w, h, c;
            im->mData = (void*)stbi_loadf(p_filename, &w, &h, &c, 0);
            im->mWidth = w;
            im->mHeight = h;
            if (c == 3) {
                im->mChannels = RGB32_FLOAT;
            }
            else {
                im->mChannels = RGBA32_FLOAT;
            }
        }
        else {
            int w, h, c;
            im->mData = (void*)stbi_load(p_filename, &w, &h, &c, 0);
            im->mWidth = w;
            im->mHeight = h;
            if (c == 3) {
                im->mChannels = RGB8_UNORM;
            }
            else {
                im->mChannels = RGBA8_UNORM;
            }
        }

        return im;
    }

    image_ref image::load_from_memory(const void *p_image_data, uint image_size) {
        auto* im = new image();

        if (stbi_is_hdr_from_memory((u8*)p_image_data, image_size)) {
            int w, h, c;
            im->mData = (void*)stbi_loadf_from_memory((u8*)p_image_data, image_size, &w, &h, &c, 0);
            im->mWidth = w;
            im->mHeight = h;
            if (c == 3) {
                im->mChannels = RGB32_FLOAT;
            }
            else {
                im->mChannels = RGBA32_FLOAT;
            }
        }
        else {
            int w, h, c;
            im->mData = (void*)stbi_load_from_memory((u8*)p_image_data, image_size, &w, &h, &c, 0);
            im->mWidth = w;
            im->mHeight = h;
            if (c == 3) {
                im->mChannels = RGB8_UNORM;
            }
            else {
                im->mChannels = RGBA8_UNORM;
            }
        }

        return im;
    }

    uint image::get_num_channels() const {
        switch (mChannels) {
            case RGB32_FLOAT:
            case RGB8_UNORM:
                return 3;
            case RGBA32_FLOAT:
            case RGBA8_UNORM:
                return 4;
            default:
                return 0;
        }
    }

    image_ref image::generate(const image::generate_info &gen_info) {
        WG_NOT_IMPLEMENTED
        return new image{
            nullptr,
            1u, 1u,
            RGB8_UNORM
        };
    }
}

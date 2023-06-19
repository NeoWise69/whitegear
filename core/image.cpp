
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
        auto im = make_ref<image>();

        if (stbi_is_hdr(p_filename)) {
            int w, h, c;
            im->mData = (void*)stbi_loadf(p_filename, &w, &h, &c, 0);
            im->mWidth = w;
            im->mHeight = h;
            if (c == 3) {
                im->mFormat = FORMAT_RGB32_FLOAT;
            }
            else {
                im->mFormat = FORMAT_RGBA32_FLOAT;
            }
        }
        else {
            int w, h, c;
            im->mData = (void*)stbi_load(p_filename, &w, &h, &c, 0);
            im->mWidth = w;
            im->mHeight = h;
            if (c == 3) {
                im->mFormat = FORMAT_RGB8_UNORM;
            }
            else {
                im->mFormat = FORMAT_RGBA8_UNORM;
            }
        }

        return im;
    }

    image_ref image::load_from_memory(const void *p_image_data, uint image_size) {
        auto im = make_ref<image>();

        if (stbi_is_hdr_from_memory((u8*)p_image_data, int(image_size))) {
            int w, h, c;
            im->mData = (void*)stbi_loadf_from_memory((u8*)p_image_data, int(image_size), &w, &h, &c, 0);
            im->mWidth = w;
            im->mHeight = h;
            if (c == 3) {
                im->mFormat = FORMAT_RGB32_FLOAT;
            }
            else {
                im->mFormat = FORMAT_RGBA32_FLOAT;
            }
        }
        else {
            int w, h, c;
            im->mData = (void*)stbi_load_from_memory((u8*)p_image_data, int(image_size), &w, &h, &c, 0);
            im->mWidth = w;
            im->mHeight = h;
            if (c == 3) {
                im->mFormat = FORMAT_RGB8_UNORM;
            }
            else {
                im->mFormat = FORMAT_RGBA8_UNORM;
            }
        }

        return im;
    }

    uint image::get_num_channels() const noexcept {
        switch (mFormat) {
            case FORMAT_RGB32_FLOAT:
            case FORMAT_RGB8_UNORM:
                return 3;
            case FORMAT_RGBA32_FLOAT:
            case FORMAT_RGBA8_UNORM:
                return 4;
            default:
                return 0;
        }
    }

    image_ref image::generate(const image::generate_info &gen_info) {
        WG_NOT_IMPLEMENTED
        static u8 s_empty_data[16] = { 0xff, 0xff, 0xff, 0xff,
                                     0xff, 0xff, 0xff, 0xff,
                                     0xff, 0xff, 0xff, 0xff,
                                     0xff, 0xff, 0xff, 0xff };
        return make_ref<image>(
            s_empty_data,
            2u, 2u,
            FORMAT_RGBA8_UNORM
        );
    }

    uint image::get_pixel_size() const {
        switch (mFormat) {
            case FORMAT_RGB32_FLOAT:
                return sizeof(float[3]);
            case FORMAT_RGB8_UNORM:
                return sizeof(u8[3]);
            case FORMAT_RGBA32_FLOAT:
                return sizeof(float[4]);
            case FORMAT_RGBA8_UNORM:
                return sizeof(u8[4]);
            default:
                return 0;
        }
    }
}

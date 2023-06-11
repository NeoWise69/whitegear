
/*******************************************************************************
 * Copyright (c) 2023.
 * This file is part of The WhiteGear Studio software property.
 * If you get unexpected access to this file, or part ot whole codebase, you should
 * report this source code leak and delete all copies of source code from all your machines.
 ******************************************************************************/

#include "renda/api/common.hpp"

namespace wg::renda {
    namespace {
        uint _get_offset_by_format(e_format format) {
            switch (format) {
                case FORMAT_RGBA32_FLOAT:
                case FORMAT_RGBA32_UINT:
                case FORMAT_RGBA32_SINT: return 16u;
                case FORMAT_RGB32_FLOAT:
                case FORMAT_RGB32_UINT:
                case FORMAT_RGB32_SINT: return 12u;
                case FORMAT_RG32_FLOAT:
                case FORMAT_RG32_UINT:
                case FORMAT_RG32_SINT: return 8u;
                case FORMAT_D32_FLOAT:
                case FORMAT_R32_FLOAT:
                case FORMAT_R32_UINT:
                case FORMAT_R32_SINT:
                case FORMAT_RGBA8_UNORM:
                case FORMAT_RGBA8_SNORM:
                case FORMAT_RGBA8_UINT:
                case FORMAT_RGBA8_SINT:
                case FORMAT_D24_UNORM_S8_UINT: return 4u;

                default:
                    return 0u;
            }
        }
    }

    void vertex_layout::calculate_attribute_offsets() {
        for (uint i = 0; i < attributes.size(); ++i) {
            attribute& attr = attributes[i];
            attr.offset = i32(vertex_size);
            vertex_size += _get_offset_by_format(attr.format);
        }
        if (vertex_size > 16 && vertex_size < 32) {
            vertex_size = 32;
        }
        else if (vertex_size > 32 && vertex_size < 64) {
            vertex_size = 64;
        }
        else if (vertex_size > 64 && vertex_size < 128) {
            vertex_size = 128;
        }
    }

    vertex_layout vertex_layout::create_for(vertex_type type) {
        if (type == VERTEX_TYPE_MESH) {
            return {
                    { "POSITION", FORMAT_RGBA32_FLOAT },
                    { "COLOR", FORMAT_RGBA8_UNORM },
            };
        }
        /**
         * Minimal required vertex type just for geometry processing(at least)
         */
        return {
                { "POSITION", FORMAT_RGBA32_FLOAT },
        };
    }
}


/*******************************************************************************
 * Copyright (c) 2023.
 * This file is part of The WhiteGear Studio software property.
 * If you get unexpected access to this file, or part ot whole codebase, you should
 * report this source code leak and delete all copies of source code from all your machines.
 ******************************************************************************/

#include "utils_dx11.hpp"

namespace wg::renda {
    DXGI_FORMAT format_to_dxgi_format(e_format format) {
        switch (format) {
            case FORMAT_RGBA32_FLOAT: return DXGI_FORMAT_R32G32B32A32_FLOAT;
            case FORMAT_RGBA32_UINT: return DXGI_FORMAT_R32G32B32A32_UINT;
            case FORMAT_RGBA32_SINT: return DXGI_FORMAT_R32G32B32A32_SINT;
            case FORMAT_RGB32_FLOAT: return DXGI_FORMAT_R32G32B32_FLOAT;
            case FORMAT_RGB32_UINT: return DXGI_FORMAT_R32G32B32_UINT;
            case FORMAT_RGB32_SINT: return DXGI_FORMAT_R32G32B32_SINT;
            case FORMAT_RG32_FLOAT: return DXGI_FORMAT_R32G32_FLOAT;
            case FORMAT_RG32_UINT: return DXGI_FORMAT_R32G32_UINT;
            case FORMAT_RG32_SINT: return DXGI_FORMAT_R32G32_SINT;
            case FORMAT_D32_FLOAT: return DXGI_FORMAT_D32_FLOAT;
            case FORMAT_R32_FLOAT: return DXGI_FORMAT_R32_FLOAT;
            case FORMAT_R32_UINT: return DXGI_FORMAT_R32_UINT;
            case FORMAT_R32_SINT: return DXGI_FORMAT_R32_SINT;
            case FORMAT_RGBA8_UNORM: return DXGI_FORMAT_R8G8B8A8_UNORM;
            case FORMAT_RGBA8_SNORM: return DXGI_FORMAT_R8G8B8A8_SNORM;
            case FORMAT_RGBA8_UINT: return DXGI_FORMAT_R8G8B8A8_UINT;
            case FORMAT_RGBA8_SINT: return DXGI_FORMAT_R8G8B8A8_SINT;
            case FORMAT_D24_UNORM_S8_UINT: return DXGI_FORMAT_D24_UNORM_S8_UINT;
            default:
                return DXGI_FORMAT_UNKNOWN;
        }
    }

    void vertex_layout_to_d3d(bounded_array<D3D11_INPUT_ELEMENT_DESC, 16>& dst, const bounded_array<vertex_layout::attribute, 16>& src_attributes) {
        for (uint i = 0; i < src_attributes.size(); ++i) {
            const vertex_layout::attribute& attr = src_attributes[i];
            dst.emplace_back(
                D3D11_INPUT_ELEMENT_DESC{attr.semantic_name, 0u,
            format_to_dxgi_format(attr.format),
            0u,
            uint(attr.offset),
            D3D11_INPUT_CLASSIFICATION(attr.attribute_rate),
            attr.step_rate});
        }
    }
}

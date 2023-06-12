
/*******************************************************************************
 * Copyright (c) 2023.
 * This file is part of The WhiteGear Studio software property.
 * If you get unexpected access to this file, or part ot whole codebase, you should
 * report this source code leak and delete all copies of source code from all your machines.
 ******************************************************************************/

#ifndef WHITEGEAR_UTILS_DX11_HPP
#define WHITEGEAR_UTILS_DX11_HPP

#include <renda/api/common.hpp>
#include "minimal_dx11.hpp"

namespace wg::renda {
    DXGI_FORMAT format_to_dxgi_format(e_format format);
    void vertex_layout_to_d3d(bounded_array<D3D11_INPUT_ELEMENT_DESC, 16>& dst, const bounded_array<vertex_layout::attribute, 16>& src_attributes);

    D3D11_FILTER sampler_filter_to_d3d11_filter(e_sampler_filtering filter);
    const char* sampler_filter_to_string(e_sampler_filtering filter);
    D3D11_TEXTURE_ADDRESS_MODE sampler_mode_to_d3d11_address_mode(e_sampler_mode mode);
    const char* sampler_mode_to_string(e_sampler_mode mode);
}

#endif //WHITEGEAR_UTILS_DX11_HPP

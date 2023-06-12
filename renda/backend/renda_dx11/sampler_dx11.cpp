
/*******************************************************************************
 * Copyright (c) 2023.
 * This file is part of The WhiteGear Studio software property.
 * If you get unexpected access to this file, or part ot whole codebase, you should
 * report this source code leak and delete all copies of source code from all your machines.
 ******************************************************************************/

#include <renda/api/gpu_resource.hpp>

#include "minimal_dx11.hpp"
#include "utils_dx11.hpp"

namespace wg::renda {
    sampler::sampler(const gpu_device &device, e_sampler_mode sampler_mode, e_sampler_filtering sampler_filtering) noexcept {
        auto& samp = (ID3D11SamplerState*&)(handle);
        auto d3d = (ID3D11Device*)(device.get_device_instance());

        D3D11_SAMPLER_DESC desc = {};
        desc.Filter = sampler_filter_to_d3d11_filter(sampler_filtering);
        desc.AddressU =
        desc.AddressV =
        desc.AddressW = sampler_mode_to_d3d11_address_mode(sampler_mode);
        ret_t(d3d->CreateSamplerState(&desc, &samp));
    }

    sampler::~sampler() noexcept {
        auto& samp = (ID3D11SamplerState*&)(handle);
        SafeD3DRelease(samp);
    }

    void sampler::bind(gpu_device &device) const noexcept {
        auto samp = (ID3D11SamplerState*)(handle);
        auto context = (ID3D11DeviceContext*)(device.get_device_context());
        context->PSSetSamplers(0u, 1u, &samp);
    }
}

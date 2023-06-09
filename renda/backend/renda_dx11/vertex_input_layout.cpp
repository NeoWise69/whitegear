
/*******************************************************************************
 * Copyright (c) 2023.
 * This file is part of The WhiteGear Studio software property.
 * If you get unexpected access to this file, or part ot whole codebase, you should
 * report this source code leak and delete all copies of source code from all your machines.
 ******************************************************************************/

#include <renda/api/gpu_resource.hpp>

#include "minimal.hpp"
#include "utils_dx11.hpp"

namespace wg::renda {
    vertex_input_layout::vertex_input_layout(const gpu_device &device, const vertex_layout &vl, i_object vs_code) noexcept {
        resource_type = GPU_RESOURCE_VERTEX_INPUT_LAYOUT;

        const auto d3d = (ID3D11Device*)(device.get_device_instance());
        auto& layout = (ID3D11InputLayout*&)(handle);
        const auto code = (ID3DBlob*)(vs_code);

        bounded_array<D3D11_INPUT_ELEMENT_DESC, 16> attributes = {};
        vertex_layout_to_d3d(attributes, vl.attributes);
        ret_t(d3d->CreateInputLayout(attributes.data(), attributes.size(), code->GetBufferPointer(), code->GetBufferSize(), &layout));
    }

    void vertex_input_layout::bind(gpu_device &device) const noexcept {
        const auto layout = (ID3D11InputLayout*)(handle);
        const auto context = (ID3D11DeviceContext*)(device.get_device_context());
        context->IASetInputLayout(layout);
    }

    vertex_input_layout::~vertex_input_layout() noexcept {
        auto& layout = (ID3D11InputLayout*&)(handle);
        SafeD3DRelease(layout);
    }
}


/*******************************************************************************
 * Copyright (c) 2023.
 * This file is part of The WhiteGear Studio software property.
 * If you get unexpected access to this file, or part ot whole codebase, you should
 * report this source code leak and delete all copies of source code from all your machines.
 ******************************************************************************/

#include <renda/api/gpu_resource.hpp>

#include "minimal.hpp"

namespace wg::renda {
    constant_buffer::constant_buffer(const gpu_device &device, const memory_data_t &mem, e_bind_target tar) noexcept {
        resource_type = GPU_RESOURCE_CONSTANT_BUFFER;
        size = mem.size;
        target = tar;

        D3D11_BUFFER_DESC bd = {};
        bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
        bd.Usage = D3D11_USAGE_DYNAMIC;
        bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
        bd.MiscFlags = 0; // <-- for future fixme
        bd.ByteWidth = size;
        D3D11_SUBRESOURCE_DATA sd = {};
        sd.pSysMem = mem.p_memory;

        resource_type = e_gpu_resource_type(resource_type | (
                (target == BIND_TARGET_VERTEX_SHADER_STAGE) ?
                GPU_RESOURCE_VERTEX_CONSTANT_BUFFER :
                GPU_RESOURCE_PIXEL_CONSTANT_BUFFER));

        auto& buffer = (ID3D11Buffer*&)(handle);
        auto d3d = (ID3D11Device*)(device.get_device_instance());
        ret_t(d3d->CreateBuffer(&bd, (mem.p_memory != nullptr) ? &sd : nullptr, &buffer));
    }
    constant_buffer::~constant_buffer() noexcept {
        auto& buffer = (ID3D11Buffer*&)(handle);
        SafeD3DRelease(buffer);
    }

    void constant_buffer::update(gpu_device &device, const void *p_data) const noexcept {
        auto& buffer = (ID3D11Buffer*&)(handle);
        auto context = (ID3D11DeviceContext*)(device.get_device_context());
        D3D11_MAPPED_SUBRESOURCE msr = {};
        ret_t(context->Map(buffer, 0u, D3D11_MAP_WRITE_DISCARD, 0, &msr));
        memcpy(msr.pData, p_data, size);
        context->Unmap(buffer, 0u);
    }

    void constant_buffer::bind(gpu_device &device) const noexcept {
        auto context = (ID3D11DeviceContext*)(device.get_device_context());
        auto& buffer = (ID3D11Buffer*&)(handle);
        switch (target) {
            case BIND_TARGET_VERTEX_SHADER_STAGE: {
                context->VSSetConstantBuffers(0, 1, &buffer);
            } break;
            case BIND_TARGET_PIXEL_SHADER_STAGE: {
                context->PSSetConstantBuffers(0, 1, &buffer);
            } break;
            default: break;
        }
    }

    void constant_buffer::bind(gpu_device &device, uint start_slot) const noexcept {
        auto context = (ID3D11DeviceContext*)(device.get_device_context());
        auto& buffer = (ID3D11Buffer*&)(handle);
        switch (target) {
            case BIND_TARGET_VERTEX_SHADER_STAGE: {
                context->VSSetConstantBuffers(start_slot, 1, &buffer);
            } break;
            case BIND_TARGET_PIXEL_SHADER_STAGE: {
                context->PSSetConstantBuffers(start_slot, 1, &buffer);
            } break;
            default: break;
        }
    }
}

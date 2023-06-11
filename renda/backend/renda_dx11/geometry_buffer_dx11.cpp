
/*******************************************************************************
 * Copyright (c) 2023.
 * This file is part of The WhiteGear Studio software property.
 * If you get unexpected access to this file, or part ot whole codebase, you should
 * report this source code leak and delete all copies of source code from all your machines.
 ******************************************************************************/

#include <renda/api/gpu_resource.hpp>

#include "minimal_dx11.hpp"

namespace wg::renda {
    geometry_buffer::geometry_buffer(const gpu_device &device, e_buffer_type t,
                                 const geometry_buffer::create_info &ci,
                                 const vertex_layout *layout) noexcept {
        type = t;
        resource_type = GPU_RESOURCE_GEOMETRY_BUFFER;
        auto d3d = (ID3D11Device*)(device.get_device_instance());
        auto& buffer = (ID3D11Buffer*&)(handle);
        D3D11_BUFFER_DESC bd = {};
        D3D11_SUBRESOURCE_DATA sd = { ci.memory.p_memory };
        bd.Usage = D3D11_USAGE_DEFAULT;
        switch (type) {
            case BUFFER_TYPE_VERTEX_BUFFER: {
                resource_type = e_gpu_resource_type(resource_type | GPU_RESOURCE_VERTEX_BUFFER);
                num = layout->vertex_size;
                bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
                bd.ByteWidth = uint(layout->vertex_size * ci.count);
                bd.StructureByteStride = layout->vertex_size;
            } break;
            case BUFFER_TYPE_INDEX_BUFFER: {
                resource_type = e_gpu_resource_type(resource_type | GPU_RESOURCE_INDEX_BUFFER);
                num = ci.count;
                bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
                bd.ByteWidth = uint(num * sizeof(uint));
                bd.StructureByteStride = sizeof(uint);
            } break;
            default: break;
        }
        ret_t(d3d->CreateBuffer(&bd, &sd, &buffer));
    }

    void geometry_buffer::bind(gpu_device &device) const noexcept {
        auto context = (ID3D11DeviceContext*)(device.get_device_context());
        auto& buffer = (ID3D11Buffer*&)(handle);
        switch (type) {
            case BUFFER_TYPE_VERTEX_BUFFER: {
                const uint offset = 0u;
                context->IASetVertexBuffers(0, 1, &buffer, &num, &offset);
            } break;
            case BUFFER_TYPE_INDEX_BUFFER: {
                context->IASetIndexBuffer(buffer, DXGI_FORMAT_R32_UINT, 0);
            } break;
            default: break;
        }
    }

    geometry_buffer::~geometry_buffer() {
        auto& buffer = (ID3D11Buffer*&)(handle);
        SafeD3DRelease(buffer);
    }
}

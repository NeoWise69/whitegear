
/*******************************************************************************
 * Copyright (c) 2023.
 * This file is part of The WhiteGear Studio software property.
 * If you get unexpected access to this file, or part ot whole codebase, you should
 * report this source code leak and delete all copies of source code from all your machines.
 ******************************************************************************/

#include <renda/api/gpu_resource.hpp>

#include "minimal_dx11.hpp"

namespace wg::renda {
    shader_program::shader_program(const gpu_device& device, e_shader_type t, const string_view& filename) noexcept {
        type = t;
        resource_type = GPU_RESOURCE_SHADER_PROGRAM;

        auto& blob = (ID3DBlob*&)(code);
        auto d3d = (ID3D11Device*)(device.get_device_instance());

        WCHAR fpath[MAX_PATH] = {};
        string::u8_to_u16(filename, fpath, MAX_PATH);
        ret_t(D3DReadFileToBlob(fpath, &blob));
        switch (type) {
            case SHADER_TYPE_VERTEX_SHADER: {
                resource_type = e_gpu_resource_type(resource_type | GPU_RESOURCE_VERTEX_PROGRAM);
                auto& program = (ID3D11VertexShader*&)(handle);
                ret_t(d3d->CreateVertexShader(blob->GetBufferPointer(), blob->GetBufferSize(), nullptr, &program));
            } break;
            case SHADER_TYPE_PIXEL_SHADER: {
                resource_type = e_gpu_resource_type(resource_type | GPU_RESOURCE_PIXEL_PROGRAM);
                auto& program = (ID3D11PixelShader*&)(handle);
                ret_t(d3d->CreatePixelShader(blob->GetBufferPointer(), blob->GetBufferSize(), nullptr, &program));
            } break;
            default: break;
        }
    }

    void shader_program::bind(gpu_device &device) const noexcept {
        auto context = (ID3D11DeviceContext*)(device.get_device_context());
        switch (type) {
            case SHADER_TYPE_VERTEX_SHADER: {
                auto& program = (ID3D11VertexShader*&)(handle);
                context->VSSetShader(program, nullptr, 0);
            } break;
            case SHADER_TYPE_PIXEL_SHADER: {
                auto& program = (ID3D11PixelShader*&)(handle);
                context->PSSetShader(program, nullptr, 0);
            } break;
            default: break;
        }
    }

    shader_program::~shader_program() noexcept {
        auto& resource = (ID3D11Resource*&)(handle);
        SafeD3DRelease(resource);
    }
}

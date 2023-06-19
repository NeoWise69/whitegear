
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
    texture::texture(const gpu_device& device, const ref_ptr<image>& im) noexcept {
        auto& srv = (ID3D11ShaderResourceView*&)(handle);
        auto d3d = (ID3D11Device*)(device.get_device_instance());

        D3D11_TEXTURE2D_DESC desc = {};
        desc.Width = im->get_width();
        desc.Height = im->get_height();
        desc.MipLevels = 1u;
        desc.ArraySize = 1u;
        desc.Format = format_to_dxgi_format(im->get_format());
        desc.SampleDesc.Count = 1u;
        desc.Usage = D3D11_USAGE_DEFAULT;
        desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;

        D3D11_SUBRESOURCE_DATA sd = {};
        sd.pSysMem = im->get_data();
        sd.SysMemPitch = im->get_width() * im->get_pixel_size();
        wrl::ComPtr<ID3D11Texture2D> t2d = nullptr;
        ret_t(d3d->CreateTexture2D(&desc, &sd, &t2d));

        D3D11_SHADER_RESOURCE_VIEW_DESC srv_desc = {};
        srv_desc.Format = desc.Format;
        srv_desc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
        srv_desc.Texture2D.MipLevels = 1u;
        ret_t(d3d->CreateShaderResourceView(t2d.Get(), &srv_desc, &srv));
    }

    texture::~texture() noexcept {
        auto srv = (ID3D11ShaderResourceView*)(handle);
        SafeD3DRelease(srv);
    }

    void texture::bind(wg::renda::gpu_device &device) const noexcept {
        auto srv = (ID3D11ShaderResourceView*)(handle);
        auto context = (ID3D11DeviceContext*)(device.get_device_context());
        context->PSSetShaderResources(0u, 1u, &srv);
    }
}

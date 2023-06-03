
/*******************************************************************************
 * Copyright (c) 2023.
 * This file is part of The WhiteGear Studio software property.
 * If you get unexpected access to this file, or part ot whole codebase, you should
 * report this source code leak and delete all copies of source code from all your machines.
 ******************************************************************************/

#include "dx_render_target_buffer.hpp"

#if WG_WINDOWS

namespace wg {
    dx_render_target_buffer::dx_render_target_buffer(ID3D11Device* const p_device, uint width, uint height) {
        D3D11_TEXTURE2D_DESC texture_desc = {};
        texture_desc.Width = width;
        texture_desc.Height = height;
        texture_desc.MipLevels = 1;
        texture_desc.ArraySize = 1;
        texture_desc.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
        texture_desc.SampleDesc.Count = 1;
        texture_desc.Usage = D3D11_USAGE_DEFAULT;
        texture_desc.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;
        ret_t(p_device->CreateTexture2D(&texture_desc, nullptr, &mRenderTargetTexture));

        D3D11_RENDER_TARGET_VIEW_DESC rtv_desc = {};
        rtv_desc.Format = texture_desc.Format;
        rtv_desc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;
        ret_t(p_device->CreateRenderTargetView(mRenderTargetTexture.Get(), &rtv_desc, &mRenderTargetView));

        D3D11_SHADER_RESOURCE_VIEW_DESC srv_desc = {};
        srv_desc.Format = texture_desc.Format;
        srv_desc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
        srv_desc.Texture2D.MipLevels = 1;
        ret_t(p_device->CreateShaderResourceView(mRenderTargetTexture.Get(), &srv_desc, &mShaderResourceView));
    }
}

#endif

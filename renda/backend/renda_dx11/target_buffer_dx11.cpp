
/*******************************************************************************
 * Copyright (c) 2023.
 * This file is part of The WhiteGear Studio software property.
 * If you get unexpected access to this file, or part ot whole codebase, you should
 * report this source code leak and delete all copies of source code from all your machines.
 ******************************************************************************/

#include <renda/api/target_buffer.hpp>
#include <renda/api/gpu_device.hpp>

#include "minimal_dx11.hpp"

namespace wg::renda {
    target_buffer::~target_buffer() noexcept {
        SafeD3DRelease((ID3D11RenderTargetView*&)(target_view));
        SafeD3DRelease((ID3D11DepthStencilView*&)(depth_view));
    }

    bool target_buffer::create(const gpu_device& device, const viewport *p_viewport, bool depth) noexcept {
        return true;
    }

    void target_buffer::clear(const gpu_device& device, const vec4 &color) const noexcept {
        auto context = (ID3D11DeviceContext*)(device.get_device_context());
        auto& rtv = (ID3D11RenderTargetView*&)(target_view);
        auto& dsv = (ID3D11DepthStencilView*&)(depth_view);
        const FLOAT f_color[4] = { color.r, color.g, color.b, color.a };
        context->ClearRenderTargetView(rtv, f_color);
        context->ClearDepthStencilView(dsv, D3D11_CLEAR_DEPTH, 1.0f, 0);
    }

    void target_buffer::bind(const gpu_device& device) const noexcept {
        auto context = (ID3D11DeviceContext*)(device.get_device_context());
        auto& rtv = (ID3D11RenderTargetView*&)(target_view);
        auto& dsv = (ID3D11DepthStencilView*&)(depth_view);
        context->OMSetRenderTargets(1, &rtv, dsv);
    }

}

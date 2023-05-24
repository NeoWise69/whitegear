
/*******************************************************************************
 * Copyright (c) 2023.
 * This file is part of The WhiteGear Studio software property.
 * If you get unexpected access to this file, or part ot whole codebase, you should
 * report this source code leak and delete all copies of source code from all your machines.
 ******************************************************************************/

#include "dx_graphics.hpp"
#include <GLFW/glfw3.h>

#if WG_WINDOWS

namespace wg {
    dx_graphics::dx_graphics(wg::window *p_wnd) {
        HWND hWnd = glfwGetWin32Window(p_wnd->get());

        DXGI_SWAP_CHAIN_DESC swap_chain_desc = {};
        swap_chain_desc.BufferDesc.Width = p_wnd->get_width();
        swap_chain_desc.BufferDesc.Height = p_wnd->get_height();
        swap_chain_desc.BufferDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
        swap_chain_desc.BufferDesc.RefreshRate.Numerator = 0;
        swap_chain_desc.BufferDesc.RefreshRate.Denominator = 0;
        swap_chain_desc.SampleDesc.Count = 1;
        swap_chain_desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
        swap_chain_desc.BufferCount = 1;
        swap_chain_desc.OutputWindow = hWnd;
        swap_chain_desc.Windowed = !p_wnd->is_fullscreen();
        swap_chain_desc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

        UINT flags = {};

#if WG_BUILD_DEBUG
        flags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

        D3DCALL(D3D11CreateDeviceAndSwapChain(
                nullptr,
                D3D_DRIVER_TYPE_HARDWARE,
                nullptr,
                flags,
                nullptr,
                0,
                D3D11_SDK_VERSION,
                &swap_chain_desc,
                swapchain.GetAddressOf(),
                device.GetAddressOf(),
                nullptr,
                context.GetAddressOf()
        ));

        ID3D11Resource *p_back_buffer = {};
        D3DCALL(swapchain->GetBuffer(0, IID_PPV_ARGS(&p_back_buffer)));
        D3DCALL(device->CreateRenderTargetView(
                p_back_buffer,
                nullptr,
                rtv.GetAddressOf()
                ));
        p_back_buffer->Release();
    }

    dx_graphics::~dx_graphics() {
        // D3DSafeRelease(context);     // the thing is that I don't need to release these resources because of <wrl.h>
        // D3DSafeRelease(swapchain);   // the thing is that I don't need to release these resources because of <wrl.h>
        // D3DSafeRelease(device);      // the thing is that I don't need to release these resources because of <wrl.h>
    }

    void dx_graphics::end_frame() const {
        static HRESULT hr = S_OK;
        if (FAILED(hr = swapchain->Present(0u, 0))) {
            if (hr == DXGI_ERROR_DEVICE_REMOVED) {
                out
                .error("Failed to end DirectX frame![DXGI_ERROR_DEVICE_REMOVED]")
                .trace("%d", device->GetDeviceRemovedReason());
            }
        }
    }

    void dx_graphics::clear_color(const vec3 &color) const noexcept {
        const float col[4] = { float(color.r), float(color.g), float(color.b), 1.0f };
        context->OMSetRenderTargets(1, rtv.GetAddressOf(), nullptr);
        context->ClearRenderTargetView(rtv.Get(), col);
    }
}

#endif //WG_WINDOWS

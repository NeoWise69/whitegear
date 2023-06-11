
/*******************************************************************************
 * Copyright (c) 2023.
 * This file is part of The WhiteGear Studio software property.
 * If you get unexpected access to this file, or part ot whole codebase, you should
 * report this source code leak and delete all copies of source code from all your machines.
 ******************************************************************************/

#include <renda/api/swapchain.hpp>
#include <renda/api/target_buffer.hpp>
#include <graphics/window.hpp>

#include "minimal_dx11.hpp"

#include <GLFW/glfw3.h>
#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW/glfw3native.h>

namespace wg::renda {
    bool swapchain::create(const gpu_device* p_device, const create_info& ci) noexcept {
        auto& p_swapchain = (IDXGISwapChain*&)(handle);

        HWND hWnd = glfwGetWin32Window(ci.p_window->get());
        const auto vp = ci.p_window->get_viewport();

        DXGI_SWAP_CHAIN_DESC swap_chain_desc = {};
        swap_chain_desc.BufferDesc.Width = ci.p_display_info->screen_width;
        swap_chain_desc.BufferDesc.Height = ci.p_display_info->screen_height;
        swap_chain_desc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
        swap_chain_desc.BufferDesc.RefreshRate.Numerator = ci.p_display_info->hz_numerator;
        swap_chain_desc.BufferDesc.RefreshRate.Denominator = ci.p_display_info->hz_denominator;
        swap_chain_desc.SampleDesc.Count = 1;
        swap_chain_desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
        swap_chain_desc.BufferCount = 1;
        swap_chain_desc.OutputWindow = hWnd;
        swap_chain_desc.Windowed = !vp.is_fullscreen();
        swap_chain_desc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

        auto device = (ID3D11Device*)(p_device->get_device_instance());
        {
            IDXGIDevice *dxgi_device = nullptr;
            ret_t(device->QueryInterface(IID_PPV_ARGS(&dxgi_device)));
            IDXGIAdapter *adapter = nullptr;
            ret_t(dxgi_device->GetParent(IID_PPV_ARGS(&adapter)));
            IDXGIFactory *factory = nullptr;
            ret_t(adapter->GetParent(IID_PPV_ARGS(&factory)));

            ret_t(factory->CreateSwapChain(device, &swap_chain_desc, &p_swapchain));

            SafeD3DRelease(dxgi_device);
            SafeD3DRelease(adapter);
            SafeD3DRelease(factory);
        }

        return true;
    }

    swapchain::~swapchain() noexcept {
        auto& p_swapchain = (IDXGISwapChain*&)(handle);
        SafeD3DRelease(p_swapchain);
    }

    void swapchain::get_target_buffer(const gpu_device &device, target_buffer &buffer) noexcept {
        auto& p_swapchain = (IDXGISwapChain*&)(handle);
        auto& rtv = (ID3D11RenderTargetView*&)(buffer.target_view);
        auto& dsv = (ID3D11DepthStencilView*&)(buffer.depth_view);

        wrl::ComPtr<ID3D11Resource> p_back_buffer = nullptr;
        p_swapchain->GetBuffer(0, IID_PPV_ARGS(&p_back_buffer));

        auto d3d = (ID3D11Device*)(device.get_device_instance());
        auto context = (ID3D11DeviceContext*)(device.get_device_context());

        ret_t(d3d->CreateRenderTargetView(p_back_buffer.Get(), nullptr, &rtv));

        D3D11_DEPTH_STENCIL_DESC dsd = {};
        dsd.DepthEnable = TRUE;
        dsd.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
        dsd.DepthFunc = D3D11_COMPARISON_LESS;
        wrl::ComPtr<ID3D11DepthStencilState> dss = nullptr;
        ret_t(d3d->CreateDepthStencilState(&dsd, &dss));
        context->OMSetDepthStencilState(dss.Get(), 1u);

        DXGI_SWAP_CHAIN_DESC swap_chain_desc = {};
        ret_t(p_swapchain->GetDesc(&swap_chain_desc));

        wrl::ComPtr<ID3D11Texture2D> depth_texture = nullptr;
        D3D11_TEXTURE2D_DESC t2dd = {};
        t2dd.Width = swap_chain_desc.BufferDesc.Width;
        t2dd.Height = swap_chain_desc.BufferDesc.Height;
        t2dd.MipLevels = 1u;
        t2dd.ArraySize = 1u;
        t2dd.Format = DXGI_FORMAT_D32_FLOAT;
        t2dd.SampleDesc.Count = 1u;
        t2dd.Usage = D3D11_USAGE_DEFAULT;
        t2dd.BindFlags = D3D11_BIND_DEPTH_STENCIL;
        ret_t(d3d->CreateTexture2D(&t2dd, nullptr, &depth_texture));

        D3D11_DEPTH_STENCIL_VIEW_DESC dsv_desc = {};
        dsv_desc.Format = DXGI_FORMAT_D32_FLOAT;
        dsv_desc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
        ret_t(d3d->CreateDepthStencilView(depth_texture.Get(), &dsv_desc, &dsv));
    }

    void swapchain::present() const noexcept {
        auto& p_swapchain = (IDXGISwapChain*&)(handle);
        static ret_t hr = S_OK;
        if (hr = p_swapchain->Present(0u, 0); !hr) {
            if (*hr == DXGI_ERROR_DEVICE_REMOVED) {
                out
                        .error("Failed to end DirectX frame![DXGI_ERROR_DEVICE_REMOVED]")
                        .trace("%s", hr.get_error_desc().c_str())
                        .dead_end();
            }
        }

    }
}

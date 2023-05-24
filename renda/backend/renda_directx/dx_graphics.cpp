
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

        wrl::ComPtr<ID3D11Resource> back_buffer = {};
        D3DCALL(swapchain->GetBuffer(0, IID_PPV_ARGS(back_buffer.GetAddressOf())));
        D3DCALL(device->CreateRenderTargetView(
                back_buffer.Get(),
                nullptr,
                rtv.GetAddressOf()
                ));

        mIAStage = new input_assembly_stage(context);
        mVSStage = new vertex_shader_stage(context);
    }

    dx_graphics::~dx_graphics() {
        // D3DSafeRelease(context);     // I don't need to release these resources because of <wrl.h>
        // D3DSafeRelease(swapchain);   // I don't need to release these resources because of <wrl.h>
        // D3DSafeRelease(device);      // I don't need to release these resources because of <wrl.h>
    }

    void dx_graphics::end_frame() const {
        static HRESULT hr = S_OK;
        if (FAILED(hr = swapchain->Present(0u, 0))) {
            if (hr == DXGI_ERROR_DEVICE_REMOVED) {
                out
                .trace("%d", device->GetDeviceRemovedReason())
                .panic("Failed to end DirectX frame![DXGI_ERROR_DEVICE_REMOVED]")
                ;
            }
        }
    }

    void dx_graphics::clear_color(const vec3 &color) const noexcept {
        const float col[4] = { float(color.r), float(color.g), float(color.b), 1.0f };
        context->OMSetRenderTargets(1, rtv.GetAddressOf(), nullptr);
        context->ClearRenderTargetView(rtv.Get(), col);
    }

    void dx_graphics::draw_vertices(uint num_vertices) const {
        context->Draw(num_vertices, 0);
    }

    void dx_graphics::draw_indices(uint num_indices, uint start_indices_location) const {
        context->DrawIndexed(num_indices, start_indices_location, 0);
    }

    void dx_graphics::create_buffer(const D3D11_BUFFER_DESC &desc, ID3D11Buffer **pp_buffer, const D3D11_SUBRESOURCE_DATA* initial_data) const {
        D3DCALL(device->CreateBuffer(&desc, initial_data, pp_buffer));
    }

    void dx_graphics::create_vertex_shader(const wrl::ComPtr<ID3DBlob> &blob, ID3D11VertexShader **ppVS) const {
        D3DCALL(device->CreateVertexShader(blob->GetBufferPointer(), blob->GetBufferSize(), nullptr, ppVS));
    }

    /**
     * INPUT ASSEMBLY STAGE
     */

    void dx_graphics::input_assembly_stage::set_vertex_buffers(uint num_buffers, ID3D11Buffer*const* buffers, const uint* strides, const uint* offsets) const {
        context->IASetVertexBuffers(0, num_buffers, buffers, strides, offsets);
    }

    void dx_graphics::input_assembly_stage::set_primitive_topology(D3D11_PRIMITIVE_TOPOLOGY topo) const {
        context->IASetPrimitiveTopology(topo);
    }

    /**
     * VERTEX SHADER STAGE
     */

    void dx_graphics::vertex_shader_stage::bind(const wrl::ComPtr<ID3D11VertexShader> &vs) const {
        context->VSSetShader(vs.Get(), 0, 0);
    }
}

#endif //WG_WINDOWS

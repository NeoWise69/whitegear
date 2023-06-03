
/*******************************************************************************
 * Copyright (c) 2023.
 * This file is part of The WhiteGear Studio software property.
 * If you get unexpected access to this file, or part ot whole codebase, you should
 * report this source code leak and delete all copies of source code from all your machines.
 ******************************************************************************/

#include "dx_graphics.hpp"
#include <math/geometry_buffer.hpp>
#include <GLFW/glfw3.h>

#if WG_WINDOWS

namespace wg {
    dx_graphics::dx_graphics(GLFWwindow* p_window_handle, window_viewport* p_window_viewport) {
        mViewport = p_window_viewport;
        HWND hWnd = glfwGetWin32Window(p_window_handle);

        DXGI_SWAP_CHAIN_DESC swap_chain_desc = {};
        swap_chain_desc.BufferDesc.Width = mViewport->get_width();
        swap_chain_desc.BufferDesc.Height = mViewport->get_height();
        swap_chain_desc.BufferDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
        swap_chain_desc.BufferDesc.RefreshRate.Numerator = 0;
        swap_chain_desc.BufferDesc.RefreshRate.Denominator = 0;
        swap_chain_desc.SampleDesc.Count = 1;
        swap_chain_desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
        swap_chain_desc.BufferCount = 1;
        swap_chain_desc.OutputWindow = hWnd;
        swap_chain_desc.Windowed = !p_window_viewport->is_fullscreen();
        swap_chain_desc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

        UINT flags = {};

#if WG_BUILD_DEBUG
        flags |= D3D11_CREATE_DEVICE_DEBUG;
#endif
        ret_t(D3D11CreateDeviceAndSwapChain(
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
        ret_t(swapchain->GetBuffer(0, IID_PPV_ARGS(back_buffer.GetAddressOf())));
        ret_t(device->CreateRenderTargetView(
                back_buffer.Get(),
                nullptr,
                rtv.GetAddressOf()
                ));

        D3D11_DEPTH_STENCIL_DESC dsd = {};
        dsd.DepthEnable = TRUE;
        dsd.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
        dsd.DepthFunc = D3D11_COMPARISON_LESS;
        wrl::ComPtr<ID3D11DepthStencilState> dss = nullptr;
        ret_t(device->CreateDepthStencilState(&dsd, &dss));
        context->OMSetDepthStencilState(dss.Get(), 1u);

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
        ret_t(device->CreateTexture2D(&t2dd, nullptr, &depth_texture));

        D3D11_DEPTH_STENCIL_VIEW_DESC dsv_desc = {};
        dsv_desc.Format = DXGI_FORMAT_D32_FLOAT;
        dsv_desc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
        ret_t(device->CreateDepthStencilView(depth_texture.Get(), &dsv_desc, &dsv));

        context->OMSetRenderTargets(1, rtv.GetAddressOf(), dsv.Get());

        mIAStage = make_unique<input_assembly_stage>(context);
        mVSStage = make_unique<vertex_shader_stage>(context);
        mPSStage = make_unique<pixel_shader_stage>(context);
        mRSStage = make_unique<rasterizer_stage>(context);
    }

    dx_graphics::~dx_graphics() {
        // D3DSafeRelease(context);     // I don't need to release these resources because of <wrl.h>
        // D3DSafeRelease(swapchain);   // I don't need to release these resources because of <wrl.h>
        // D3DSafeRelease(device);      // I don't need to release these resources because of <wrl.h>
    }

    void dx_graphics::end_frame() {
        static ret_t hr = S_OK;
        if (hr = swapchain->Present(0u, 0); !hr) {
            if (*hr == DXGI_ERROR_DEVICE_REMOVED) {
                out
                .error("Failed to end DirectX frame![DXGI_ERROR_DEVICE_REMOVED]")
                .trace("%s", hr.get_error_desc().c_str())
                .dead_end();
            }
        }
        mGlobalCamera.update();
    }

    void dx_graphics::clear_color(const vec3 &color) const noexcept {
        const float col[4] = { float(color.r), float(color.g), float(color.b), 1.0f };
        context->ClearRenderTargetView(rtv.Get(), col);
        context->ClearDepthStencilView(dsv.Get(), D3D11_CLEAR_DEPTH, 1.0f, 0u);
    }

    void dx_graphics::draw_vertices(uint num_vertices) const {
        context->Draw(num_vertices, 0);
    }

    void dx_graphics::draw_indices(uint num_indices, uint start_indices_location) const {
        context->DrawIndexed(num_indices, start_indices_location, 0);
    }

    void dx_graphics::create_buffer(const D3D11_BUFFER_DESC &desc, ID3D11Buffer **pp_buffer, const D3D11_SUBRESOURCE_DATA* initial_data) const {
        ret_t(device->CreateBuffer(&desc, initial_data, pp_buffer));
    }

    void dx_graphics::create_vertex_shader(const wrl::ComPtr<ID3DBlob> &blob, wrl::ComPtr<ID3D11VertexShader> &VS) const {
        ret_t(device->CreateVertexShader(blob->GetBufferPointer(), blob->GetBufferSize(), nullptr, &VS));
    }

    void dx_graphics::create_pixel_shader(const wrl::ComPtr<ID3DBlob> &blob, wrl::ComPtr<ID3D11PixelShader> &PS) const {
        ret_t(device->CreatePixelShader(blob->GetBufferPointer(), blob->GetBufferSize(), nullptr, &PS));
    }

    void dx_graphics::create_input_layout(const D3D11_INPUT_ELEMENT_DESC *p_elements, uint num_elements,
                                          const wrl::ComPtr<ID3DBlob> &code,
                                          wrl::ComPtr<ID3D11InputLayout> &il) const {
        ret_t(device->CreateInputLayout(p_elements, num_elements, code->GetBufferPointer(), code->GetBufferSize(), &il));
    }

    void dx_graphics::map_resource(const wrl::ComPtr<ID3D11Resource> &resource, D3D11_MAP type,
                                   D3D11_MAPPED_SUBRESOURCE *p_mr) const {
        ret_t(context->Map(resource.Get(), 0u, type, 0u, p_mr));
    }

    void dx_graphics::unmap_resource(const wrl::ComPtr<ID3D11Resource> &resource) const {
        context->Unmap(resource.Get(), 0u);
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

    void dx_graphics::input_assembly_stage::set_input_layout(const wrl::ComPtr<ID3D11InputLayout> &il) const {
        context->IASetInputLayout(il.Get());
    }

    void dx_graphics::input_assembly_stage::set_index_buffer(ID3D11Buffer *p_index_buffer, DXGI_FORMAT format) const {
        context->IASetIndexBuffer(p_index_buffer, format, 0);
    }

    /**
     * VERTEX SHADER STAGE
     */

    void dx_graphics::vertex_shader_stage::bind(const wrl::ComPtr<ID3D11VertexShader> &ps) const {
        context->VSSetShader(ps.Get(), nullptr, 0);
    }

    void dx_graphics::vertex_shader_stage::set_constant_buffers(ID3D11Buffer **p_cbs, uint num,
                                                                uint start_slot) const {
        context->VSSetConstantBuffers(start_slot, num, p_cbs);
    }

    /**
     * PIXEL SHADER STAGE
     */

    void dx_graphics::pixel_shader_stage::bind(const wrl::ComPtr<ID3D11PixelShader> &vs) const {
        context->PSSetShader(vs.Get(), nullptr, 0);
    }

    void dx_graphics::pixel_shader_stage::set_constant_buffers(ID3D11Buffer **p_cbs, uint num, uint start_slot) const {
        context->PSSetConstantBuffers(start_slot, num, p_cbs);
    }

    /**
     * RASTERIZER STAGE
     */

    void dx_graphics::rasterizer_stage::set_viewports(const D3D11_VIEWPORT* p_vps, uint num_vps) const {
        context->RSSetViewports(num_vps, p_vps);
    }
}

#endif //WG_WINDOWS


/*******************************************************************************
 * Copyright (c) 2023.
 * This file is part of The WhiteGear Studio software property.
 * If you get unexpected access to this file, or part ot whole codebase, you should
 * report this source code leak and delete all copies of source code from all your machines.
 ******************************************************************************/

#include "rendering_engine_directx.hpp"

#if WG_WINDOWS
#include <GLFW/glfw3.h>
#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW/glfw3native.h>

namespace wg {

    rendering_engine_directx::rendering_engine_directx(const rendering_engine_create_info &info) {
        create_device_and_swapchain(info.p_window->get(), info.p_window->is_fullscreen());
    }

    rendering_engine_directx::~rendering_engine_directx() {

    }

    void rendering_engine_directx::draw_mesh(const rendering_engine::mesh_render_data *p_data) {

    }

    void rendering_engine_directx::load_mesh(const rendering_engine::mesh_load_data *load_data) {

    }

    void rendering_engine_directx::unload_mesh(entity_t entity_id) {

    }

    void rendering_engine_directx::on_begin_tick() {

    }

    void rendering_engine_directx::on_end_tick() {

    }

    void rendering_engine_directx::create_device_and_swapchain(GLFWwindow* window, bool fullscreen) {
        HWND hWnd = glfwGetWin32Window(window);
        i32 w, h;
        glfwGetWindowSize(window, &w, &h);

        DXGI_SWAP_CHAIN_DESC swap_chain_desc = {};
        swap_chain_desc.BufferDesc.Width = u32(w);
        swap_chain_desc.BufferDesc.Height = u32(h);
        swap_chain_desc.BufferDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
        swap_chain_desc.BufferDesc.RefreshRate.Numerator = 0;
        swap_chain_desc.BufferDesc.RefreshRate.Denominator = 0;
        swap_chain_desc.SampleDesc.Count = 1;
        swap_chain_desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
        swap_chain_desc.BufferCount = 1;
        swap_chain_desc.OutputWindow = hWnd;
        swap_chain_desc.Windowed = !fullscreen;
        swap_chain_desc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

        D3DCALL(D3D11CreateDeviceAndSwapChain(
                nullptr,
                D3D_DRIVER_TYPE_HARDWARE,
                nullptr,
                0,
                nullptr,
                0,
                D3D11_SDK_VERSION,
                &swap_chain_desc,
                swapchain.GetAddressOf(),
                device.GetAddressOf(),
                nullptr,
                context.GetAddressOf()
                ));

    }
}

#endif

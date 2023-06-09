
/*******************************************************************************
 * Copyright (c) 2023.
 * This file is part of The WhiteGear Studio software property.
 * If you get unexpected access to this file, or part ot whole codebase, you should
 * report this source code leak and delete all copies of source code from all your machines.
 ******************************************************************************/

#include <renda/api/gpu_device.hpp>
#include <graphics/window.hpp>
#include <math/viewport.hpp>

#include "minimal.hpp"

namespace wg::renda {

    bool gpu_device::initialize(const window *p_window) noexcept {
        auto& device = (ID3D11Device*&)(device_instance);
        auto& context = (ID3D11DeviceContext*&)(device_context);

        {
            auto &device_vram = device_desc.vram_mb;
            auto &str_desc = device_desc.desc_string;
            /**
             * Required for initialization.
             */
            IDXGIFactory *factory = nullptr;

            IDXGIAdapter *adapter = nullptr;
            DXGI_ADAPTER_DESC adapter_desc = {};

            IDXGIOutput *adapter_output = nullptr;
            uint num_monitor_modes = {};

            uint window_width = p_window->get_viewport().get_width();
            uint window_height = p_window->get_viewport().get_height();
            uint window_hz_numerator = {};
            uint window_hz_denominator = {};

            // Create DXGI Factory for initialization
            ret_t(CreateDXGIFactory(IID_PPV_ARGS(&factory)));
            // Choose primary system adapter (GPU instance)
            ret_t(factory->EnumAdapters(0, &adapter));
            // Choose primary monitor
            ret_t(adapter->EnumOutputs(0, &adapter_output));
            ret_t(adapter_output->GetDisplayModeList(
                    DXGI_FORMAT_R8G8B8A8_UNORM, DXGI_ENUM_MODES_INTERLACED, &num_monitor_modes, nullptr));
            bounded_array<DXGI_MODE_DESC, 128> output_modes(num_monitor_modes, DXGI_MODE_DESC{});
            ret_t(adapter_output->GetDisplayModeList(
                    DXGI_FORMAT_R8G8B8A8_UNORM, DXGI_ENUM_MODES_INTERLACED, &num_monitor_modes, output_modes.data()));
            for (uint i = 0; i < num_monitor_modes; ++i) {
                auto &mode = output_modes[i];
                if (mode.Width == window_width && mode.Height == window_height) {
                    window_hz_numerator = mode.RefreshRate.Numerator;
                    window_hz_denominator = mode.RefreshRate.Denominator;
                    break;
                }
            }

            ret_t(adapter->GetDesc(&adapter_desc));
            device_vram = uint(double(adapter_desc.DedicatedVideoMemory) * double(0.00000095367431640625));
            s_info.screen_width = window_width;
            s_info.screen_height = window_height;
            s_info.hz_numerator = window_hz_numerator;
            s_info.hz_denominator = window_hz_denominator;

            size_t s_len = {};
            char buf[128] = {};
            wcstombs_s(&s_len, buf, adapter_desc.Description, 128);
            str_desc = {buf, s_len};

            SafeD3DRelease(adapter_output);
            SafeD3DRelease(adapter);
            SafeD3DRelease(factory);
        }

        D3D_FEATURE_LEVEL d3d_levels[] = {
                D3D_FEATURE_LEVEL_11_1,
                D3D_FEATURE_LEVEL_11_0,
                D3D_FEATURE_LEVEL_10_1,
        };
        DWORD device_create_flags = {};
#if WG_BUILD_DEBUG
        device_create_flags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

        D3D_FEATURE_LEVEL selected_d3d_level = {};
        ret_t(D3D11CreateDevice(
                nullptr,
                D3D_DRIVER_TYPE_HARDWARE,
                nullptr,
                device_create_flags,
                d3d_levels,
                3,
                D3D11_SDK_VERSION,
                &device,
                &selected_d3d_level,
                &context
                ));

        return true;
    }

    gpu_device::~gpu_device() noexcept {
        auto& device = (ID3D11Device*&)(device_instance);
        auto& context = (ID3D11DeviceContext*&)(device_context);
        SafeD3DRelease(device);
        SafeD3DRelease(context);
    }

    void gpu_device::update_viewport(const viewport &vp) const noexcept {
        auto context = (ID3D11DeviceContext*)(device_context);
        D3D11_VIEWPORT d3d_vp = {
                0.0f, 0.0f,
                FLOAT(vp.get_width()),
                FLOAT(vp.get_height()),
                0.0f, 1.0f
        };
        context->RSSetViewports(1, &d3d_vp);
    }

    void gpu_device::draw_vertices(uint count) const {
        auto context = (ID3D11DeviceContext*)(device_context);
        context->Draw(count, 0u);
    }

    void gpu_device::draw_indices(uint count) const {
        auto context = (ID3D11DeviceContext*)(device_context);
        context->DrawIndexed(count, 0u, 0u);
    }
}

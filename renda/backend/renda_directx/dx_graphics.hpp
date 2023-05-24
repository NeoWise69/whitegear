
/*******************************************************************************
 * Copyright (c) 2023.
 * This file is part of The WhiteGear Studio software property.
 * If you get unexpected access to this file, or part ot whole codebase, you should
 * report this source code leak and delete all copies of source code from all your machines.
 ******************************************************************************/

#ifndef WHITEGEAR_DX_GRAPHICS_HPP
#define WHITEGEAR_DX_GRAPHICS_HPP

#include "minimal.hpp"
#include <graphics/window.hpp>

#if WG_WINDOWS

namespace wg {
    class dx_graphics {
    public:
        dx_graphics(window *p_wnd);
        ~dx_graphics();

        inline dx_graphics(const dx_graphics&) = delete;
        inline dx_graphics& operator=(const dx_graphics&) = delete;
        inline dx_graphics(dx_graphics&&) noexcept = delete;
        inline dx_graphics& operator=(dx_graphics&&) noexcept = delete;

        void end_frame() const;
        void clear_color(const vec3& color) const noexcept;

        inline auto get_device() const {
            return device;
        }
        inline auto get_swapchain() const {
            return swapchain;
        }
        inline auto get_context() const {
            return context;
        }
    private:
        wrl::ComPtr<ID3D11Device> device = nullptr;
        wrl::ComPtr<IDXGISwapChain> swapchain = nullptr;
        wrl::ComPtr<ID3D11DeviceContext> context = nullptr;
        wrl::ComPtr<ID3D11RenderTargetView> rtv = nullptr;
    };
}

#endif //WG_WINDOWS

#endif //WHITEGEAR_DX_GRAPHICS_HPP

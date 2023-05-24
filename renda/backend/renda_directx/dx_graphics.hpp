
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

#include <GLFW/glfw3.h>
#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW/glfw3native.h>

namespace wg {
    class dx_graphics {
    public:
        class input_assembly_stage {
        public:
            inline explicit input_assembly_stage(const wrl::ComPtr<ID3D11DeviceContext>& ctx) : context(ctx) {}

            void set_vertex_buffers(uint num_buffers, ID3D11Buffer*const* buffers, const uint* strides, const uint* offsets) const;
            void set_primitive_topology(D3D11_PRIMITIVE_TOPOLOGY topo) const;

        private:
            wrl::ComPtr<ID3D11DeviceContext> context = nullptr;
        };

        class vertex_shader_stage {
        public:
            inline explicit vertex_shader_stage(const wrl::ComPtr<ID3D11DeviceContext>& ctx) : context(ctx) {}

            void bind(const wrl::ComPtr<ID3D11VertexShader>& vs) const;
        private:
            wrl::ComPtr<ID3D11DeviceContext> context = nullptr;
        };

        dx_graphics(window *p_wnd);
        ~dx_graphics();

        inline dx_graphics(const dx_graphics&) = delete;
        inline dx_graphics& operator=(const dx_graphics&) = delete;
        inline dx_graphics(dx_graphics&&) noexcept = delete;
        inline dx_graphics& operator=(dx_graphics&&) noexcept = delete;

        void end_frame() const;
        void clear_color(const vec3& color) const noexcept;

        void draw_vertices(uint num_vertices) const;
        void draw_indices(uint num_indices, uint start_indices_location = 0) const;

        void create_buffer(const D3D11_BUFFER_DESC& desc, ID3D11Buffer** pp_buffer, const D3D11_SUBRESOURCE_DATA* initial_data = nullptr) const;
        void create_vertex_shader(const wrl::ComPtr<ID3DBlob>& blob, ID3D11VertexShader** ppVS) const;

        inline auto get_device() const {
            return device;
        }
        inline auto get_swapchain() const {
            return swapchain;
        }
        inline auto get_context() const {
            return context;
        }
        inline auto* ia() const {
            return mIAStage;
        }
        inline auto* vs() const {
            return mVSStage;
        }
    private:
        wrl::ComPtr<ID3D11Device> device = nullptr;
        wrl::ComPtr<IDXGISwapChain> swapchain = nullptr;
        wrl::ComPtr<ID3D11DeviceContext> context = nullptr;
        wrl::ComPtr<ID3D11RenderTargetView> rtv = nullptr;

        input_assembly_stage* mIAStage;
        vertex_shader_stage* mVSStage;
    };
}

#endif //WG_WINDOWS

#endif //WHITEGEAR_DX_GRAPHICS_HPP

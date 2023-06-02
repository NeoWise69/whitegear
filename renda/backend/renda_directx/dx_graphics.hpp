
/*******************************************************************************
 * Copyright (c) 2023.
 * This file is part of The WhiteGear Studio software property.
 * If you get unexpected access to this file, or part ot whole codebase, you should
 * report this source code leak and delete all copies of source code from all your machines.
 ******************************************************************************/

#ifndef WHITEGEAR_DX_GRAPHICS_HPP
#define WHITEGEAR_DX_GRAPHICS_HPP

#include "minimal.hpp"
#include <math/free_camera.hpp>
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
            void set_input_layout(const wrl::ComPtr<ID3D11InputLayout>& il) const;
            void set_index_buffer(ID3D11Buffer* p_index_buffer, DXGI_FORMAT format) const;

        private:
            wrl::ComPtr<ID3D11DeviceContext> context = nullptr;
        };

        class vertex_shader_stage {
        public:
            inline explicit vertex_shader_stage(const wrl::ComPtr<ID3D11DeviceContext>& ctx) : context(ctx) {}

            void bind(const wrl::ComPtr<ID3D11VertexShader>& vs) const;
            void set_constant_buffers(ID3D11Buffer** p_cbs, uint num, uint start_slot = 0) const;
        private:
            wrl::ComPtr<ID3D11DeviceContext> context = nullptr;
        };

        class pixel_shader_stage {
        public:
            inline explicit pixel_shader_stage(const wrl::ComPtr<ID3D11DeviceContext>& ctx) : context(ctx) {}

            void bind(const wrl::ComPtr<ID3D11PixelShader>& ps) const;
            void set_constant_buffers(ID3D11Buffer** p_cbs, uint num, uint start_slot = 0) const;
        private:
            wrl::ComPtr<ID3D11DeviceContext> context = nullptr;
        };

        class rasterizer_stage {
        public:
            inline explicit rasterizer_stage(const wrl::ComPtr<ID3D11DeviceContext>& ctx) : context(ctx) {}

            void set_viewports(const D3D11_VIEWPORT* p_vps, uint num_vps) const;
        private:
            wrl::ComPtr<ID3D11DeviceContext> context = nullptr;
        };

        dx_graphics(window *p_wnd);
        ~dx_graphics();

        inline dx_graphics(const dx_graphics&) = delete;
        inline dx_graphics& operator=(const dx_graphics&) = delete;
        inline dx_graphics(dx_graphics&&) noexcept = delete;
        inline dx_graphics& operator=(dx_graphics&&) noexcept = delete;

        void end_frame();
        void clear_color(const vec3& color) const noexcept;

        void draw_vertices(uint num_vertices) const;
        void draw_indices(uint num_indices, uint start_indices_location = 0) const;

        void create_buffer(const D3D11_BUFFER_DESC& desc, ID3D11Buffer** pp_buffer, const D3D11_SUBRESOURCE_DATA* initial_data = nullptr) const;
        void create_vertex_shader(const wrl::ComPtr<ID3DBlob>& blob, wrl::ComPtr<ID3D11VertexShader>& VS) const;
        void create_pixel_shader(const wrl::ComPtr<ID3DBlob>& blob, wrl::ComPtr<ID3D11PixelShader>& PS) const;
        void create_input_layout(const D3D11_INPUT_ELEMENT_DESC* p_elements, uint num_elements, const wrl::ComPtr<ID3DBlob>& code, wrl::ComPtr<ID3D11InputLayout>& il) const;

        void map_resource(const wrl::ComPtr<ID3D11Resource>& resource, D3D11_MAP type, D3D11_MAPPED_SUBRESOURCE* p_mr) const;
        void unmap_resource(const wrl::ComPtr<ID3D11Resource>& resource) const;

        inline mat4 get_view_matrix() const { return mGlobalCamera.get_view_matrix(); }
        inline mat4 get_projection_matrix() const { return mProjectionMatrix; }

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
            return mIAStage.get();
        }
        inline auto* vs() const {
            return mVSStage.get();
        }
        inline auto* ps() const {
            return mPSStage.get();
        }
        inline auto* rs() const {
            return mRSStage.get();
        }
    private:
        wrl::ComPtr<ID3D11Device> device = nullptr;
        wrl::ComPtr<IDXGISwapChain> swapchain = nullptr;
        wrl::ComPtr<ID3D11DeviceContext> context = nullptr;
        wrl::ComPtr<ID3D11RenderTargetView> rtv = nullptr;
        wrl::ComPtr<ID3D11DepthStencilView> dsv = nullptr;

        unique_ptr<input_assembly_stage> mIAStage;
        unique_ptr<vertex_shader_stage> mVSStage;
        unique_ptr<pixel_shader_stage> mPSStage;
        unique_ptr<rasterizer_stage> mRSStage;

        free_camera mGlobalCamera = {{0, 0, 3}};
        mat4 mProjectionMatrix = {};
    };
}

#endif //WG_WINDOWS

#endif //WHITEGEAR_DX_GRAPHICS_HPP

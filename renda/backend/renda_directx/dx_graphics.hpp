
/*******************************************************************************
 * Copyright (c) 2023.
 * This file is part of The WhiteGear Studio software property.
 * If you get unexpected access to this file, or part ot whole codebase, you should
 * report this source code leak and delete all copies of source code from all your machines.
 ******************************************************************************/

#ifndef WHITEGEAR_DX_GRAPHICS_HPP
#define WHITEGEAR_DX_GRAPHICS_HPP

#include "minimal.hpp"
#include "dx_render_target_buffer.hpp"
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

        dx_graphics(GLFWwindow* p_window_handle, window_viewport* p_window_viewport);
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

        inline const mat4& get_view_matrix() const { return mGlobalCamera.get_view_matrix(); }
        inline viewport& get_viewport() const { return *mViewport; }
        inline viewport& get_viewport() { return *mViewport; }

        inline auto get_device() const {
            return mDevice;
        }
        inline auto get_swapchain() const {
            return mSwapchain;
        }
        inline auto get_render_target_buffer() const {
            return mRenderTargetBuffer.get();
        }
        inline auto get_context() const {
            return mDeviceContext;
        }

        inline void set_viewport(viewport* p_viewport) {
            mViewport = p_viewport;
        }

        void begin_render_to_texture_buffer();
        void end_render_to_texture_buffer();

        inline auto* ia() const {
            return mInputAssemblyStage.get();
        }
        inline auto* vs() const {
            return mVertexShaderStage.get();
        }
        inline auto* ps() const {
            return mPixelShaderStage.get();
        }
        inline auto* rs() const {
            return mRasterStage.get();
        }
    private:
        wrl::ComPtr<ID3D11Device> mDevice = nullptr;
        wrl::ComPtr<IDXGISwapChain> mSwapchain = nullptr;
        wrl::ComPtr<ID3D11DeviceContext> mDeviceContext = nullptr;
        wrl::ComPtr<ID3D11RenderTargetView> mBackBufferRenderTargetView = nullptr;
        wrl::ComPtr<ID3D11DepthStencilView> mDepthStencilView = nullptr;

        unique_ptr<input_assembly_stage> mInputAssemblyStage = nullptr;
        unique_ptr<vertex_shader_stage> mVertexShaderStage = nullptr;
        unique_ptr<pixel_shader_stage> mPixelShaderStage = nullptr;
        unique_ptr<rasterizer_stage> mRasterStage = nullptr;
        unique_ptr<dx_render_target_buffer> mRenderTargetBuffer = nullptr;

        free_camera mGlobalCamera = {{0, 0, 3}};
        viewport* mViewport = nullptr;
    };
}

#endif //WG_WINDOWS

#endif //WHITEGEAR_DX_GRAPHICS_HPP

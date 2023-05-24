
/*******************************************************************************
 * Copyright (c) 2023.
 * This file is part of The WhiteGear Studio software property.
 * If you get unexpected access to this file, or part ot whole codebase, you should
 * report this source code leak and delete all copies of source code from all your machines.
 ******************************************************************************/

#ifndef WHITEGEAR_RENDERING_ENGINE_DIRECTX_HPP
#define WHITEGEAR_RENDERING_ENGINE_DIRECTX_HPP

#include "minimal.hpp"

#if WG_WINDOWS

namespace wg {
    class rendering_engine_directx : public rendering_engine {
    public:
        explicit rendering_engine_directx(const rendering_engine_create_info &info);
        ~rendering_engine_directx() override;

        void draw_mesh(const mesh_render_data *p_data) override;
        void load_mesh(const mesh_load_data *load_data) override;
        void unload_mesh(entity_t entity_id) override;
        void on_begin_tick() override;
        void on_end_tick() override;
    private:
        void create_device_and_swapchain(GLFWwindow* window, bool fullscreen);

        wrl::ComPtr<ID3D11Device> device = nullptr;
        wrl::ComPtr<IDXGISwapChain> swapchain = nullptr;
        wrl::ComPtr<ID3D11DeviceContext> context = nullptr;
    };
}

#endif

#endif //WHITEGEAR_RENDERING_ENGINE_DIRECTX_HPP

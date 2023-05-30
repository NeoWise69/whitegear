
/*******************************************************************************
 * Copyright (c) 2023.
 * This file is part of The WhiteGear Studio software property.
 * If you get unexpected access to this file, or part ot whole codebase, you should
 * report this source code leak and delete all copies of source code from all your machines.
 ******************************************************************************/

#include "rendering_engine_directx.hpp"

#if WG_WINDOWS

#include <imgui.h>
#include <imgui_internal.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_dx11.h>


namespace wg {
    extern bool GEnableImGui;

    void imgui_draw_viewport() {
        ImGui::Text("There are will be a viewporT!");
    }

    rendering_engine_directx::rendering_engine_directx(const rendering_engine_create_info &info) : mWindow(info.p_window), mGraphics(info.p_window) {

        if (GEnableImGui) {
            init_imgui();
        }

    }

    rendering_engine_directx::~rendering_engine_directx() {

        if (GEnableImGui) {
            shutdown_imgui();
        }
    }

    void rendering_engine_directx::draw_mesh(const rendering_engine::mesh_render_data *p_data) {
        if (mSceneRenderables.count(p_data->entity) < 1) {
            out
            .error("failed to render object[eid=%d]! there are no such entity in loaded list!", p_data->entity)
            ;
            return;
        }
        else {
            auto& world_stats = get_parent_world()->stats();
            ++world_stats.draw_calls;

            const auto& renderable = mSceneRenderables[p_data->entity];

            const auto f = get_frustum();
            if (f.in_frustum(renderable->get_bounding(*p_data->p_position))) {
                renderable->render(mGraphics);
                world_stats.vertices_per_frame += renderable->get_num_vertices();
                world_stats.indices_per_frame += renderable->get_num_indices();
            }
        }
    }

    void rendering_engine_directx::load_mesh(const rendering_engine::mesh_load_data *load_data) {
        auto& renderable = mSceneRenderables[load_data->entity];
        dx_scene_renderable_configuration config = {};

        const auto& cube_buffer = geometry_buffer<VERTEX_TYPE_MESH>::get_cube();

        auto& world_stats = get_parent_world()->stats();
        world_stats.vertices_on_scene += cube_buffer.get_num_vertices();
        world_stats.indices_on_scene += cube_buffer.get_num_indices();

        config.p_mesh_geometry_buffer = &cube_buffer;
        config.filename_vs = WG_SHADER_PREFIX_PATH"compiled/vs_basic.cso";
        config.filename_ps = WG_SHADER_PREFIX_PATH"compiled/ps_basic.cso";

        renderable = make_unique<dx_scene_renderable>(mGraphics, load_data->p_registry, load_data->entity, config);
    }

    void rendering_engine_directx::unload_mesh(entity_t entity_id) {

    }

    void rendering_engine_directx::on_begin_tick() {
        D3D11_VIEWPORT vp = {
                  0.0f, 0.0f,
                  FLOAT(mWindow->get_width()),
                  FLOAT(mWindow->get_height()),
                  0.0f, 1.0f
        };
        mGraphics.rs()->set_viewports(&vp, 1);

        if (GEnableImGui) {
            pre_begin_imgui();
        }
        // clearance
        mGraphics.clear_color({0.2f, 0.2f, 0.2f});
        auto& world_stats = get_parent_world()->stats();
        world_stats.draw_calls = 0;
        world_stats.indices_per_frame = 0;
        world_stats.vertices_per_frame = 0;
    }

    void rendering_engine_directx::on_end_tick() {
        if (GEnableImGui) {
            end_imgui();
        }
        mGraphics.end_frame();
    }

    void rendering_engine_directx::init_imgui() {
        // Setup Dear ImGui context
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO(); (void)io;
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       // Enable Keyboard Controls
        //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
        io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking
        io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;         // Enable Multi-Viewport / Platform Windows
        //io.ConfigFlags |= ImGuiConfigFlags_ViewportsNoTaskBarIcons;
        //io.ConfigFlags |= ImGuiConfigFlags_ViewportsNoMerge;

        // float fontSize = 18.0f;// *2.0f;
        // io.Fonts->AddFontFromFileTTF("assets/fonts/opensans/OpenSans-Bold.ttf", fontSize);
        // io.FontDefault = io.Fonts->AddFontFromFileTTF("assets/fonts/opensans/OpenSans-Regular.ttf", fontSize);

        // Setup Dear ImGui style
        ImGui::StyleColorsDark();
        //ImGui::StyleColorsClassic();

        // When viewports are enabled we tweak WindowRounding/WindowBg so platform windows can look identical to regular ones.
        ImGuiStyle& style = ImGui::GetStyle();
        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
        {
            style.WindowRounding = 0.0f;
            style.Colors[ImGuiCol_WindowBg].w = 1.0f;
        }

        // Setup Platform/Renderer bindings
        ImGui_ImplGlfw_InitForOther(mWindow->get(), true);
        ImGui_ImplDX11_Init(mGraphics.get_device().Get(), mGraphics.get_context().Get());
    }

    void rendering_engine_directx::shutdown_imgui() {
        ImGui_ImplDX11_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
    }

    void rendering_engine_directx::pre_begin_imgui() {
        ImGui_ImplDX11_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
    }

    void rendering_engine_directx::end_imgui() {
        ImGuiIO& io = ImGui::GetIO();
        io.DisplaySize.x = float(mWindow->get_width());
        io.DisplaySize.y = float(mWindow->get_height());

        // Rendering IMGUI
        ImGui::Render();
        ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
            ImGui::UpdatePlatformWindows();
            ImGui::RenderPlatformWindowsDefault();
        }
    }

    frustum rendering_engine_directx::get_frustum() const {
        return { mGraphics.get_projection_matrix(), mGraphics.get_view_matrix() };
    }
}

#endif

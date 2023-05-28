
/*******************************************************************************
 * Copyright (c) 2023.
 * This file is part of The WhiteGear Studio software property.
 * If you get unexpected access to this file, or part ot whole codebase, you should
 * report this source code leak and delete all copies of source code from all your machines.
 ******************************************************************************/

#include "rendering_engine_directx.hpp"
#include <math/vertex.hpp>
#include <math/free_camera.hpp>

#if WG_WINDOWS

#include <imgui.h>
#include <imgui_internal.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_dx11.h>


namespace wg {
    extern bool GEnableImGui;

    window* GWindow;

    void imgui_draw_viewport() {
        ImGui::Text("There are will be a viewporT!");
    }

    rendering_engine_directx::rendering_engine_directx(const rendering_engine_create_info &info) : mWindow(info.p_window), mGraphics(info.p_window) {

        if (GEnableImGui) {
            init_imgui();
        }
        GWindow = info.p_window;

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
            const auto& renderable = mSceneRenderables[p_data->entity];
            renderable->render(mGraphics);
        }
    }

    void rendering_engine_directx::load_mesh(const rendering_engine::mesh_load_data *load_data) {
        auto& renderable = mSceneRenderables[load_data->entity];
        dx_scene_renderable_configuration config = {};

        geometry_buffer<VERTEX_TYPE_MESH> cube_buffer(8, 36);
        cube_buffer.emplace_vertex(vec4(-1.0f,-1.0f,-1.0f, 1.0f), color32(255, 000, 255, 255));
        cube_buffer.emplace_vertex(vec4(1.0f,-1.0f,-1.0f, 1.0f), color32(255, 000, 000, 255));
        cube_buffer.emplace_vertex(vec4(-1.0f,1.0f,-1.0f, 1.0f), color32(000, 255, 000, 255));
        cube_buffer.emplace_vertex(vec4(1.0f,1.0f,-1.0f, 1.0f), color32(000, 000, 255, 255));
        cube_buffer.emplace_vertex(vec4(-1.0f,-1.0f,1.0f, 1.0f), color32(255, 255, 000, 255));
        cube_buffer.emplace_vertex(vec4(1.0f,-1.0f,1.0f, 1.0f), color32(000, 255, 255, 255));
        cube_buffer.emplace_vertex(vec4(-1.0f,1.0f,1.0f, 1.0f), color32(255, 255, 255, 255));
        cube_buffer.emplace_vertex(vec4(1.0f,1.0f,1.0f, 1.0f), color32(000, 000, 000, 255));

        cube_buffer.emplace_index(0); cube_buffer.emplace_index(2); cube_buffer.emplace_index(1);
        cube_buffer.emplace_index(2); cube_buffer.emplace_index(3); cube_buffer.emplace_index(1);
        cube_buffer.emplace_index(1); cube_buffer.emplace_index(3); cube_buffer.emplace_index(5);
        cube_buffer.emplace_index(3); cube_buffer.emplace_index(7); cube_buffer.emplace_index(5);
        cube_buffer.emplace_index(2); cube_buffer.emplace_index(6); cube_buffer.emplace_index(3);
        cube_buffer.emplace_index(3); cube_buffer.emplace_index(6); cube_buffer.emplace_index(7);
        cube_buffer.emplace_index(4); cube_buffer.emplace_index(5); cube_buffer.emplace_index(7);
        cube_buffer.emplace_index(4); cube_buffer.emplace_index(7); cube_buffer.emplace_index(6);
        cube_buffer.emplace_index(0); cube_buffer.emplace_index(4); cube_buffer.emplace_index(2);
        cube_buffer.emplace_index(2); cube_buffer.emplace_index(4); cube_buffer.emplace_index(6);
        cube_buffer.emplace_index(0); cube_buffer.emplace_index(1); cube_buffer.emplace_index(4);
        cube_buffer.emplace_index(1); cube_buffer.emplace_index(5); cube_buffer.emplace_index(4);

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
}

#endif

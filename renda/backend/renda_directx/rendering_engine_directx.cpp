
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

#include "dx_common_mesh_cube.hpp"

namespace wg {
    namespace {
        dx_graphics* GGraphics = nullptr;
    }
    extern bool GEnableImGui;
    extern viewport* GEditorViewport;
    extern bool GViewportResized;

    void imgui_draw_viewport() {
        static vec2 viewport_size = { ImGui::GetWindowSize().x, ImGui::GetWindowSize().y };

        const auto render_target_buffer = GGraphics->get_render_target_buffer();
        const auto viewport_srv = render_target_buffer->get_shader_resource_view();
        const auto viewport_texture = ImTextureID(viewport_srv.Get());
        vec2 v_size = {float(GEditorViewport->get_width()), float(GEditorViewport->get_height())};
        ImGui::Image(viewport_texture, {v_size.x, v_size.y});

        const vec2 current_viewport_size = { ImGui::GetWindowSize().x, ImGui::GetWindowSize().y };
        if (current_viewport_size != viewport_size) {
            viewport_size = current_viewport_size;
            GViewportResized = true;
        }

        if (GViewportResized) {
            GEditorViewport->set_size(viewport_size.x + 18, viewport_size.y - 35);
        }
    }

    rendering_engine_directx::rendering_engine_directx(const rendering_engine_create_info &info)
        : mWindowP(info.p_window->get()), mViewport(info.p_window->get_viewport().to_base()), mGraphics(info.p_window->get(), &info.p_window->get_viewport()) {
        if (GEnableImGui) {
            init_imgui();
        }

        GGraphics = &mGraphics;
        GEditorViewport = mViewport;

        mFrameData = make_unique<dx_bindable_per_frame_constant_buffer>(mGraphics);
    }

    rendering_engine_directx::~rendering_engine_directx() {

        if (GEnableImGui) {
            shutdown_imgui();
        }
    }

    void rendering_engine_directx::draw_mesh(const rendering_engine::mesh_render_data *p_data) {
        if (!mRenderables.contains(p_data->entity)) {
            out
            .error("failed to render object[eid=%d]! there are no such entity in loaded list!", p_data->entity)
            ;
            return;
        }
        else {
            auto& world_stats = get_parent_world()->stats();

            const auto& renderable = mRenderables[p_data->entity];

            const auto f = get_frustum();
            if (f.is_in_view(renderable->get_bounding(*p_data->p_position))) {
                if (!renderable->is_transform_ptr_provided()) {
                    renderable->set_transform_matrix_ptr(p_data->p_transform);
                }

                renderable->render(mGraphics);
                world_stats.vertices_per_frame += renderable->get_num_vertices();
                world_stats.indices_per_frame += renderable->get_num_indices();
                ++world_stats.draw_calls;
            }
        }
    }

    void rendering_engine_directx::load_mesh(const rendering_engine::mesh_load_data *load_data) {
        WG_NOT_IMPLEMENTED
    }

    void rendering_engine_directx::create_common_mesh(const rendering_engine::common_mesh_create_info *create_data) {
        auto& renderable = mRenderables[create_data->entity];
        auto& world_stats = get_parent_world()->stats();

        if (create_data->mesh == common_mesh_create_info::COMMON_MESH_CUBE) {
            world_stats.vertices_on_scene += 8;
            world_stats.indices_on_scene += 36;

            dx_common_mesh_cube::create_info config = {};
            config.filename_vs = WG_SHADER_PREFIX_PATH"compiled/vs_basic.cso";
            config.filename_ps = WG_SHADER_PREFIX_PATH"compiled/ps_basic.cso";
            renderable = make_shared<dx_common_mesh_cube>(mGraphics, config);
        }
    }

    void rendering_engine_directx::unload_mesh(entity_t entity_id) {

    }

    void rendering_engine_directx::on_begin_tick() {
        mFrameStartTime = time_point::now();

        // --> TODO: temporal code!
        int w, h;
        glfwGetWindowSize(mWindowP, &w, &h);
        // --> TODO: temporal code!

        D3D11_VIEWPORT vp = {
                  0.0f, 0.0f,
                  FLOAT(w),
                  FLOAT(h),
                  0.0f, 1.0f
        };
        mGraphics.rs()->set_viewports(&vp, 1);

        if (GEnableImGui) {
            pre_begin_imgui();
        }

        mGraphics.begin_render_to_texture_buffer();

        // clearance
        mGraphics.clear_color({0.2f, 0.2f, 0.2f});
        auto& world_stats = get_parent_world()->stats();
        world_stats.draw_calls = 0;
        world_stats.indices_per_frame = 0;
        world_stats.vertices_per_frame = 0;

        mFrameData->bind(mGraphics);
    }

    void rendering_engine_directx::on_end_tick() {

        mGraphics.end_render_to_texture_buffer();

        if (GEnableImGui) {
            end_imgui();
        }
        mGraphics.end_frame();

        const auto frame_end_time = time_point::now();
        GTimeStats.frame_time = frame_end_time - mFrameStartTime;
    }

    void rendering_engine_directx::init_imgui() {
        // Setup Dear ImGui context
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO(); (void)io;
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       // Enable Keyboard Controls
        //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
        io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking
        // io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;         // Enable Multi-Viewport / Platform Windows
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
        ImGui_ImplGlfw_InitForOther(mWindowP, true);
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
        io.DisplaySize.x = float(mViewport->get_width());
        io.DisplaySize.y = float(mViewport->get_height());

        // Rendering IMGUI
        ImGui::Render();
        ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
            ImGui::UpdatePlatformWindows();
            ImGui::RenderPlatformWindowsDefault();
        }
    }

    frustum_view rendering_engine_directx::get_frustum() const {
        return { mGraphics.get_viewport().get_projection_matrix(), mGraphics.get_view_matrix() };
    }
}

#endif

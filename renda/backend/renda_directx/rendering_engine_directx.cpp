
/*******************************************************************************
 * Copyright (c) 2023.
 * This file is part of The WhiteGear Studio software property.
 * If you get unexpected access to this file, or part ot whole codebase, you should
 * report this source code leak and delete all copies of source code from all your machines.
 ******************************************************************************/

#include "rendering_engine_directx.hpp"
#include "math/vertex.hpp"

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

    }

    void rendering_engine_directx::load_mesh(const rendering_engine::mesh_load_data *load_data) {

    }

    void rendering_engine_directx::unload_mesh(entity_t entity_id) {

    }

    void rendering_engine_directx::on_begin_tick() {
        if (GEnableImGui) {
            pre_begin_imgui();
        }

        test_draw_first_triangle();
    }

    void rendering_engine_directx::on_end_tick() {
        if (GEnableImGui) {
            begin_imgui();
        }

        // clearance
        mGraphics.clear_color({0.1f, 0.1f, 0.1f});

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
        bool res = ImGui_ImplGlfw_InitForOther(mWindow->get(), true);
        res = ImGui_ImplDX11_Init(mGraphics.get_device().Get(), mGraphics.get_context().Get());
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

    void rendering_engine_directx::begin_imgui() {
        ImGuiIO& io = ImGui::GetIO();
        io.DisplaySize.x = float(mWindow->get_width());
        io.DisplaySize.y = float(mWindow->get_height());

        // Rendering IMGUI
        ImGui::Render();
    }

    void rendering_engine_directx::end_imgui() {
        ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
        if (ImGui::GetIO().ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
            ImGui::UpdatePlatformWindows();
            ImGui::RenderPlatformWindowsDefault();
        }
    }

    void rendering_engine_directx::test_draw_first_triangle() {

        const base_vertex_t vertices[] = {
                { { 0.0f, 0.5f, 0.0f } },
                { { 0.5f,-0.5f, 0.0f } },
                { {-0.5f,-0.5f, 0.0f } },
        };

        wrl::ComPtr<ID3D11Buffer> vb = nullptr;
        D3D11_BUFFER_DESC bd = {};
        bd.Usage = D3D11_USAGE_DEFAULT;
        bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
        bd.ByteWidth = sizeof(vertices);
        bd.StructureByteStride = sizeof(vertices[0]);

        D3D11_SUBRESOURCE_DATA sd = {};
        sd.pSysMem = vertices;

        mGraphics.create_buffer(bd, vb.GetAddressOf(), &sd);

        const uint strides[1] = {
            sizeof(vertices[0])
        };

        const uint offsets[1] = {
            0
        };

        mGraphics.ia()->set_primitive_topology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
        mGraphics.ia()->set_vertex_buffers(1, vb.GetAddressOf(), strides, offsets);

        wrl::ComPtr<ID3D11VertexShader> vs = nullptr;
        wrl::ComPtr<ID3DBlob> vs_blob = nullptr;

        const auto filename = L"" WG_SHADER_PREFIX_PATH "compiled/vs_basic.cso";
        D3DCALL(D3DReadFileToBlob(filename, &vs_blob));
        mGraphics.create_vertex_shader(vs_blob, vs.GetAddressOf());

        mGraphics.vs()->bind(vs);

        mGraphics.draw_vertices(sizeof(vertices) / sizeof(vertices[0]));
    }
}

#endif

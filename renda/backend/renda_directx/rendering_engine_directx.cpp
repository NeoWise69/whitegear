
/*******************************************************************************
 * Copyright (c) 2023.
 * This file is part of The WhiteGear Studio software property.
 * If you get unexpected access to this file, or part ot whole codebase, you should
 * report this source code leak and delete all copies of source code from all your machines.
 ******************************************************************************/

#include "rendering_engine_directx.hpp"
#include "math/vertex.hpp"
#include "math/free_camera.hpp"

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
    }

    void rendering_engine_directx::on_end_tick() {
        // clearance
        mGraphics.clear_color({0.6f, 0.4f, 0.5f});

        if (GEnableImGui) {
            begin_imgui();
        }

        test_draw_first_triangle();

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

    static free_camera camera({0, 0, 3});

    void rendering_engine_directx::test_draw_first_triangle() {
        // Let's say we have a geometry to draw
        const mesh_vertex_t vertices[] = {
                { { 0.0f, 0.5f, 0.0f, 1.0f }, { 255, 000, 000, 255 } },
                { { 0.5f,-0.5f, 0.0f, 1.0f }, { 000, 255, 000, 255 } },
                { {-0.5f,-0.5f, 0.0f, 1.0f }, { 000, 000, 255, 255 } },
                { {-0.3f, 0.3f, 0.0f, 1.0f }, { 000, 255, 000, 255 } },
                { { 0.3f, 0.3f, 0.0f, 1.0f }, { 000, 000, 255, 255 } },
                { { 0.0f,-1.0f, 0.0f, 1.0f }, { 255, 000, 000, 255 } },
        };
        // Indices too
        const uint indices[] = {
             0, 1, 2,
             0, 2, 3,
             0, 4, 1,
             2, 1, 5,
        };

        const uint strides[1] = {
                sizeof(vertices[0])
        };

        const uint offsets[1] = {
                0
        };

        // Creating vertex buffer
        wrl::ComPtr<ID3D11Buffer> vb = nullptr;
        D3D11_BUFFER_DESC bd = {};
        bd.Usage = D3D11_USAGE_DEFAULT;
        bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
        bd.ByteWidth = sizeof(vertices);
        bd.StructureByteStride = sizeof(vertices[0]);
        D3D11_SUBRESOURCE_DATA sd = {};
        sd.pSysMem = vertices;
        mGraphics.create_buffer(bd, vb.GetAddressOf(), &sd);

        // Creating index buffer
        wrl::ComPtr<ID3D11Buffer> ib = nullptr;
        bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
        bd.ByteWidth = sizeof(indices);
        bd.StructureByteStride = sizeof(indices[0]);
        sd.pSysMem = indices;
        mGraphics.create_buffer(bd, ib.GetAddressOf(), &sd);

        // Creating constant buffer
        wrl::ComPtr<ID3D11Buffer> cb = nullptr;
        bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
        bd.Usage = D3D11_USAGE_DYNAMIC;
        bd.ByteWidth = sizeof(material_data_t);
        bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

        static scalar t = 0.1f;

        t += 1 * 0.016f;

        auto mm = mat4(1);
        mm = translate(mm, {0, 0, 0});
        //mm = rotate(mm, radians(t), vec3(1, 0, 0));
        mm = rotate(mm, radians(t), vec3(0, 1, 0));

        // camera
        camera.update();
        const auto view = camera.get_view_matrix();

        const auto proj = perspective(radians(65.0f), mWindow->get_aspect(), 0.05f, 1000.0f);

        const material_data_t mat_data = {
                proj * view * mm
        };
        sd.pSysMem = &mat_data;
        mGraphics.create_buffer(bd, cb.GetAddressOf(), &sd);

        // Creating vertex and pixel shaders
        wrl::ComPtr<ID3D11VertexShader> vs = nullptr;
        wrl::ComPtr<ID3D11PixelShader> ps = nullptr;
        wrl::ComPtr<ID3DBlob> blob = nullptr;
        const auto ps_filename = L"" WG_SHADER_PREFIX_PATH "compiled/ps_basic.cso";
        D3DCALL(D3DReadFileToBlob(ps_filename, &blob));
        mGraphics.create_pixel_shader(blob, ps);
        const auto vs_filename = L"" WG_SHADER_PREFIX_PATH "compiled/vs_basic.cso";
        D3DCALL(D3DReadFileToBlob(vs_filename, &blob));
        mGraphics.create_vertex_shader(blob, vs);

        // Creating input layout
        wrl::ComPtr<ID3D11InputLayout> il = nullptr;
        // ...describing how our vertex looks like.
        const D3D11_INPUT_ELEMENT_DESC ied[] = {
                /* SEMANTIC_NAME | SEMANTIC_INDEX | FORMAT | INPUT_SLOT | OFFSET | INPUT_SLOT_CLASS | STEP_RATE */
                { "POSITION", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
                { "COLOR", 0, DXGI_FORMAT_R8G8B8A8_UNORM, 0, 16, D3D11_INPUT_PER_VERTEX_DATA, 0 },
        };
        mGraphics.create_input_layout(ied, std::size(ied), blob, il);

        // Setting constant buffers
        mGraphics.vs()->set_constant_buffers(cb.GetAddressOf(), 1);
        // Setting vertex buffers for rendering
        mGraphics.ia()->set_vertex_buffers(1, vb.GetAddressOf(), strides, offsets);
        mGraphics.ia()->set_index_buffer(ib.Get(), DXGI_FORMAT_R32_UINT);
        // Setting shaders for rendering
        mGraphics.ps()->bind(ps);
        mGraphics.vs()->bind(vs);
        // Setting input layout for rendering
        mGraphics.ia()->set_input_layout(il);
        // Telling out primitive topology to draw (for rendering)
        mGraphics.ia()->set_primitive_topology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

        // Setting up viewport (once per frame)
        D3D11_VIEWPORT vp = {};
        vp.Width = FLOAT(mWindow->get_width());
        vp.Height = FLOAT(mWindow->get_height());
        vp.MinDepth = 0;
        vp.MaxDepth = 1;
        mGraphics.rs()->set_viewports(&vp, 1);

        // Finally drawing geometry (indices)
        mGraphics.draw_indices(std::size(indices));
    }
}

#endif

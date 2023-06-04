
/*******************************************************************************
 * Copyright (c) 2023.
 * This file is part of The WhiteGear Studio software property.
 * If you get unexpected access to this file, or part ot whole codebase, you should
 * report this source code leak and delete all copies of source code from all your machines.
 ******************************************************************************/

#include "world_editor_module.hpp"
#include "scene/scene_module.hpp"
#include <runtime/runtime_core.hpp>

#include <imgui.h>

namespace wg {
    extern bool GEnableImGui;
    void imgui_draw_viewport(viewport* p_viewport);

    int world_editor_module::on_tick() {
        if (!mWorld) {
            auto *s_module = get_core()->get_module_by_id<scene_module>(scene_module_id);
            mWorld = &s_module->get_active_world();
        }
        if (GEnableImGui) {

            // Note: Switch this to true to enable dockspace
            static bool dockspaceOpen = true;
            static bool opt_fullscreen_persistant = true;
            bool opt_fullscreen = opt_fullscreen_persistant;
            static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

            // We are using the ImGuiWindowFlags_NoDocking flag to make the parent window not dockable into,
            // because it would be confusing to have two docking targets within each others.
            ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
            if (opt_fullscreen) {
                ImGuiViewport *viewport = ImGui::GetMainViewport();
                ImGui::SetNextWindowPos(viewport->Pos);
                ImGui::SetNextWindowSize(viewport->Size);
                ImGui::SetNextWindowViewport(viewport->ID);
                ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
                ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
                window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize |
                                ImGuiWindowFlags_NoMove;
                window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
            }

            // When using ImGuiDockNodeFlags_PassthruCentralNode, DockSpace() will render our background and handle the pass-thru hole, so we ask Begin() to not render a background.
            if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
                window_flags |= ImGuiWindowFlags_NoBackground;

            // Important: note that we proceed even if Begin() returns false (aka window is collapsed).
            // This is because we want to keep our DockSpace() active. If a DockSpace() is inactive,
            // all active windows docked into it will lose their parent and become undocked.
            // We cannot preserve the docking relationship between an active window and an inactive docking, otherwise
            // any change of dockspace/settings would lead to windows being stuck in limbo and never being visible.
            ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
            ImGui::Begin("DockSpace Demo", &dockspaceOpen, window_flags);
            ImGui::PopStyleVar();

            if (opt_fullscreen)
                ImGui::PopStyleVar(2);

            // DockSpace
            ImGuiIO &io = ImGui::GetIO();
            ImGuiStyle &style = ImGui::GetStyle();
            float minWinSizeX = style.WindowMinSize.x;
            style.WindowMinSize.x = 64.0f;
            if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable) {
                ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
                ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
            }

            style.WindowMinSize.x = 64;

            if (ImGui::BeginMenuBar()) {
                if (ImGui::BeginMenu("More..")) {

                    if (ImGui::MenuItem("Exit", "Esc")) {
                        get_core()->exit();
                    }

                    ImGui::EndMenu();
                }
                ImGui::EndMenuBar();
            }

            { // Main viewport
                if (ImGui::Begin("Game")) {
                    imgui_draw_viewport(mWorldViewport);
                }
                ImGui::End();
            }

            tools_ui();
            status_bar_ui();
            world_outline_ui();
            inspector_ui();
            console_ui();
            log_ui();

            ImGui::End();
        } // GEnableImGui
        return 0;
    }

    void world_editor_module::tools_ui() {
        if (ImGui::Begin("::TOOLS::")) {

        }
        ImGui::End();
    }

    void world_editor_module::status_bar_ui() {
        if (ImGui::Begin("::STATUS::BAR::")) {

        }
        ImGui::End();
    }

    void world_editor_module::world_outline_ui() {
        if (ImGui::Begin("world tree")) {
            mWorld->on_each_entity(world_editor_module::draw_single_entity);
        }
        ImGui::End();
    }

    void world_editor_module::inspector_ui() {
        if (ImGui::Begin("inspector")) {

        }
        ImGui::End();
    }

    void world_editor_module::console_ui() {
        if (ImGui::Begin("console")) {

        }
        ImGui::End();
    }

    void world_editor_module::log_ui() {
        if (ImGui::Begin("log")) {

        }
        ImGui::End();
    }

    void world_editor_module::draw_single_entity(entity_t e, world_registry* reg) {

    }
}

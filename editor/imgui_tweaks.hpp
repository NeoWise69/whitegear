
/*******************************************************************************
 * Copyright (c) 2023.
 * This file is part of The WhiteGear Studio software property.
 * If you get unexpected access to this file, or part ot whole codebase, you should
 * report this source code leak and delete all copies of source code from all your machines.
 ******************************************************************************/

#ifndef WHITEGEAR_IMGUI_TWEAKS_HPP
#define WHITEGEAR_IMGUI_TWEAKS_HPP

#include <math/vec.hpp>
#include <scene/world_registry.hpp>

#include <imgui_internal.h>
#include <imgui.h>

namespace ImGui {
    void DrawControlVec3(const char* p_label, wg::scalar* p_values, float reset_value = 0.0f, float column_width = 100.0f);

    template<typename T, typename UIFunction>
    inline void DrawComponent(const char* p_name, wg::entity_t entity, wg::world_registry* p_reg, UIFunction uiFunction)
    {
        const ImGuiTreeNodeFlags treeNodeFlags = ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_Framed | ImGuiTreeNodeFlags_SpanAvailWidth | ImGuiTreeNodeFlags_AllowItemOverlap | ImGuiTreeNodeFlags_FramePadding;
        if (p_reg->has_component<T>(entity))
        {
            auto& component = p_reg->get_component<T>(entity);
            ImVec2 contentRegionAvailable = ImGui::GetContentRegionAvail();

            ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2{ 4, 4 });
            float lineHeight = GImGui->Font->FontSize + GImGui->Style.FramePadding.y * 2.0f;
            ImGui::Separator();
            bool open = ImGui::TreeNodeEx((void*)typeid(T).hash_code(), treeNodeFlags, p_name);
            ImGui::PopStyleVar(
            );
            ImGui::SameLine(contentRegionAvailable.x - lineHeight * 0.5f);
            if (ImGui::Button("+", ImVec2{ lineHeight, lineHeight })) {
                ImGui::OpenPopup("component settings");
            }

            bool removeComponent = false;
            if (ImGui::BeginPopup("component settings")) {
                if (ImGui::MenuItem("remove component"))
                    removeComponent = true;

                ImGui::EndPopup();
            }

            if (open)
            {
                uiFunction(component);
                ImGui::TreePop();
            }

            if (removeComponent)
                p_reg->remove_component<T>(entity);
        }
    }}

#endif //WHITEGEAR_IMGUI_TWEAKS_HPP

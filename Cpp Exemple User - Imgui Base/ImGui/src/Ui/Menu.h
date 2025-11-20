#pragma once
#include <src/Includes.hpp>
#include <Utils/MouseMov/MouseMov.hpp>
#include <Utils/Security/XorStr.hpp>
#include <src/Config.hpp>

void Menu() {
    ImGui::SetCursorPos((I_Init.Size - ImVec2(300, 300)) * 0.5f);
    ImGui::BeginChild(XorStr("Menu").c_str(), ImVec2(300, 300), ImGuiChildFlags_Border, ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse);
    {
        MouseMovement();
        
        // Label com a expiração
        ImGui::SetCursorPos(ImVec2((300 - 280) * 0.5f, 20));
        ImGui::Text("Expiracao:");
        ImGui::SetCursorPos(ImVec2((300 - 280) * 0.5f, 40));
        if (!g_Config.General.Expiration.empty()) {
            ImGui::Text("%s", g_Config.General.Expiration.c_str());
        }
        else {
            ImGui::Text("N/A");
        }
        
    }
    ImGui::EndChild();
}
#pragma once
#include <imgui.h>
#include <Windows.h>
#include <src/Config.hpp>
#include <Init/Init.hpp>

void MouseMovement() {
    if (ImGui::IsItemActive()) {
        static RECT Rect = { 0 };
        GetWindowRect(I_Init.hwnd, &Rect);
        ImGui::GetWindowSize();
        MoveWindow(I_Init.hwnd, Rect.left + ImGui::GetMouseDragDelta().x, Rect.top + ImGui::GetMouseDragDelta().y, I_Init.Size.x, I_Init.Size.y, TRUE);
    }
}
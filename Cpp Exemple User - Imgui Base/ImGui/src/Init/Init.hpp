#pragma once
#include <Windows.h>
#include <d3d11.h>
#include <imgui.h>

class InitApp {
public:
    static ID3D11Device* g_pd3dDevice;
    static ID3D11DeviceContext* g_pd3dDeviceContext;
    static IDXGISwapChain* g_pSwapChain;
    static ID3D11RenderTargetView* g_mainRenderTargetView;

    static void Initialize();
    static void Shutdown();
    static inline ImVec2 Size = ImVec2(500, 500);
    static inline HWND hwnd = nullptr;
private:
    static inline WNDCLASSEXW wc = {};
    static bool CreateDeviceD3D(HWND hWnd);
    static void CleanupDeviceD3D();
    static void CreateRenderTarget();
    static void CleanupRenderTarget();
    static LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
}; inline InitApp I_Init;
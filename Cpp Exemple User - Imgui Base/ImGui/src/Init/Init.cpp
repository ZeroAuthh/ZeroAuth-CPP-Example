#include "Init.hpp"
#include <src/Includes.hpp>
#include <Utils/MouseMov/MouseMov.hpp>
#include <Utils/Log/Log.hpp>

ID3D11Device* InitApp::g_pd3dDevice = nullptr;
ID3D11DeviceContext* InitApp::g_pd3dDeviceContext = nullptr;
IDXGISwapChain* InitApp::g_pSwapChain = nullptr;
ID3D11RenderTargetView* InitApp::g_mainRenderTargetView = nullptr;

void InitApp::Initialize() {
#ifdef _DEBUG
    Log.Init();
#endif
    ImGui_ImplWin32_EnableDpiAwareness();
    wc = { sizeof(wc), CS_CLASSDC, WndProc, 0L, 0L, GetModuleHandle(nullptr), nullptr, nullptr, nullptr, nullptr, XorStr(L"_").c_str(), nullptr };
    SafeCall(RegisterClassExW)(&wc);

    hwnd = CreateWindowExW(NULL, wc.lpszClassName, XorStr(L"__").c_str(), WS_POPUP, (GetSystemMetrics(SM_CXSCREEN) / 2) - (Size.x / 2),
        (GetSystemMetrics(SM_CYSCREEN) / 2) - (Size.y / 2), Size.x, Size.y, NULL, NULL, wc.hInstance, NULL);

    MARGINS Margins = { -1 };
    DwmExtendFrameIntoClientArea(hwnd, &Margins);

    if (!CreateDeviceD3D(hwnd))
    {
        CleanupDeviceD3D();
        SafeCall(UnregisterClassW)(wc.lpszClassName, wc.hInstance);
        return;
    }

    SafeCall(ShowWindow)(hwnd, SW_SHOWDEFAULT);
    SafeCall(UpdateWindow)(hwnd);

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    Init::Fonts::LoadStyle(g_pd3dDevice);
    Init::Fonts::Initialize(g_pd3dDevice);

    ImGui_ImplWin32_Init(hwnd);
    ImGui_ImplDX11_Init(g_pd3dDevice, g_pd3dDeviceContext);

    bool shouldClose = false;
    while (!shouldClose) {
        MSG msg;
        while (PeekMessage(&msg, nullptr, 0U, 0U, PM_REMOVE)) {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
            if (msg.message == WM_QUIT)
                shouldClose = true;
        }

        if (shouldClose)
            break;

        ImGui_ImplDX11_NewFrame();
        ImGui_ImplWin32_NewFrame();
        ImGui::NewFrame();
        {
            ImGui::SetNextWindowPos(ImVec2(0, 0));
            ImGui::SetNextWindowSize(Size);
            ImGui::Begin(XorStr("Hello").c_str(), nullptr, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoScrollWithMouse);
            {
                MouseMovement();
                if (g_Config.General.Tab == 0) {
                    Login();
                }
                else if (g_Config.General.Tab == 1) {
                    Menu();
                }
            }
            ImGui::End();
        }

        ImGui::Render();
        float clearColor[4] = { 0.0f, 0.0f, 0.0f, 0.0f };
        g_pd3dDeviceContext->OMSetRenderTargets(1, &g_mainRenderTargetView, nullptr);
        g_pd3dDeviceContext->ClearRenderTargetView(g_mainRenderTargetView, clearColor);
        ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
        g_pSwapChain->Present(1, 0);
    }
    Shutdown();
}

void InitApp::Shutdown() {
#ifdef _DEBUG
    Log.Shutdown();
#endif
    ImGui_ImplDX11_Shutdown();
    ImGui_ImplWin32_Shutdown();
    ImGui::DestroyContext();

    CleanupDeviceD3D();
    SafeCall(DestroyWindow)(hwnd);
    SafeCall(UnregisterClassW)(wc.lpszClassName, wc.hInstance);
}

bool InitApp::CreateDeviceD3D(HWND hWnd) {
    DXGI_SWAP_CHAIN_DESC sd;
    ZeroMemory(&sd, sizeof(sd));
    sd.BufferCount = 2;
    sd.BufferDesc.Width = 0;
    sd.BufferDesc.Height = 0;
    sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    sd.BufferDesc.RefreshRate.Numerator = 60;
    sd.BufferDesc.RefreshRate.Denominator = 1;
    sd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
    sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    sd.OutputWindow = hWnd;
    sd.SampleDesc.Count = 1;
    sd.SampleDesc.Quality = 0;
    sd.Windowed = TRUE;
    sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

    UINT createDeviceFlags = 0;
    D3D_FEATURE_LEVEL featureLevel;
    const D3D_FEATURE_LEVEL featureLevelArray[2] = { D3D_FEATURE_LEVEL_11_0, D3D_FEATURE_LEVEL_10_0, };
    HRESULT res = D3D11CreateDeviceAndSwapChain(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, createDeviceFlags, featureLevelArray, 2, D3D11_SDK_VERSION, &sd, &g_pSwapChain, &g_pd3dDevice, &featureLevel, &g_pd3dDeviceContext);
    if (res == DXGI_ERROR_UNSUPPORTED)
        res = D3D11CreateDeviceAndSwapChain(nullptr, D3D_DRIVER_TYPE_WARP, nullptr, createDeviceFlags, featureLevelArray, 2, D3D11_SDK_VERSION, &sd, &g_pSwapChain, &g_pd3dDevice, &featureLevel, &g_pd3dDeviceContext);
    if (res != S_OK) return false;

    CreateRenderTarget();
    return true;
}

void InitApp::CleanupDeviceD3D() {
    CleanupRenderTarget();
    if (g_pSwapChain) { g_pSwapChain->Release(); g_pSwapChain = nullptr; }
    if (g_pd3dDeviceContext) { g_pd3dDeviceContext->Release(); g_pd3dDeviceContext = nullptr; }
    if (g_pd3dDevice) { g_pd3dDevice->Release(); g_pd3dDevice = nullptr; }
}

void InitApp::CreateRenderTarget() {
    ID3D11Texture2D* pBackBuffer;
    g_pSwapChain->GetBuffer(0, IID_PPV_ARGS(&pBackBuffer));
    g_pd3dDevice->CreateRenderTargetView(pBackBuffer, nullptr, &g_mainRenderTargetView);
    pBackBuffer->Release();
}

void InitApp::CleanupRenderTarget() {
    if (g_mainRenderTargetView) {
        g_mainRenderTargetView->Release();
        g_mainRenderTargetView = nullptr;
    }
}

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
LRESULT WINAPI InitApp::WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    if (ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam))
        return true;

    switch (msg) {
    case WM_SIZE:
        return 0;
    case WM_SYSCOMMAND:
        if ((wParam & 0xfff0) == SC_KEYMENU)
            return 0;
        break;
    case WM_DESTROY:
    case WM_CLOSE:
        ::PostQuitMessage(0);
        return 0;
    }
    return ::DefWindowProcW(hWnd, msg, wParam, lParam);
}
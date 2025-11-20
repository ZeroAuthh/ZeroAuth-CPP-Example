#include "ui.hh"
#include "../globals.hh"
#include "../imgui/imgui.h"
#include "../imgui/imgui_internal.h"
#include "../imgui/imanimation.h"
#include "../auth/auth.h"
#include "../auth/json.hpp"  // nlohmann json header file

using json = nlohmann::json;

// Instância estática da classe Auth
static Auth* authInstance = nullptr;
static bool authInitialized = false;
static bool isLoggedIn = false;
static std::string expirationInfo = "";

void ui::render() {
    if (!globals.active) return;



    ImGui::SetNextWindowPos(ImVec2(window_pos.x, window_pos.y), ImGuiCond_Once);
    ImGui::SetNextWindowSize(ImVec2(window_size.x, window_size.y));
    ImGui::SetNextWindowBgAlpha(1.0f);

    ImGui::Begin(window_title, &globals.active, window_flags);
    {
        if (isLoggedIn) {
            // Informações após login
            ImGui::SetCursorPos({ 20, 50 });
            ImGui::PushFont(globals.fontgrande);
            ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(255, 255, 255, 255));
            ImGui::Text("Informações da Conta");
            ImGui::PopStyleColor();
            ImGui::PopFont();

            ImGui::SetCursorPos({ 20, 100 });
            ImGui::Text("Expiração:");
            
            ImGui::SetCursorPos({ 20, 130 });
            ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(171, 110, 248, 255));
            ImGui::Text(expirationInfo.c_str());
            ImGui::PopStyleColor();
        }
        else {
            ImAnimation::Fade([]() {
            ImGui::SetCursorPos({ 252 , 80 });
            ImGui::PushFont(globals.fontgrande);
            ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(255, 255, 255, 255));
            ImGui::Text("Welcome!");
            ImGui::PopStyleColor();
            ImGui::PopFont();

            ImGui::SetCursorPos({ 220 , 106 });
            ImGui::Text("ZeroAuth exemple cpp");

            ImGui::SetCursorPos({ 166 , 160 });
            ImGui::Text("License Key");

            ImGui::SetNextItemWidth(260);
            ImGui::SetCursorPos({ 167 ,182 });
            ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(8, 9.5));
            ImGui::InputText("##InviteCode", globals.user_name, IM_ARRAYSIZE(globals.user_name));
            ImGui::PopStyleVar();

            // Configuração do AppID e OwnerID
            std::string Application = " ";  // ID do aplicativo
            std::string OwnerID = " ";  // Banco de dados do aplicativo

            ImGui::SetCursorPos({ 167 ,231 });
            if (ImGui::Button("Authorization", ImVec2(260, 35))) {
                // Inicializar Auth se ainda não foi inicializado
                if (!authInitialized) {
                    if (authInstance == nullptr) {
                        authInstance = new Auth(Application, OwnerID);
                    }
                    
                    if (!authInstance->Init()) {
                        // Se Init() falhar, error() já foi chamado e o programa será encerrado
                        return;
                    }
                    authInitialized = true;
                }

                std::string key = globals.user_name;

                // Usar o método LoginWithKey da classe Auth
                AuthResult result = authInstance->LoginWithKey(key);

                if (result.Success()) {
                    ShowMessageBox("Sucesso", "Login com a Key bem-sucedido!");
                    
                    // Obter informações de expiração
                    expirationInfo = authInstance->GetExpiration(key, "{d} Days {h} Hours {m} Minutes", true);
                    isLoggedIn = true;
                }
                else {
                    ShowMessageBoxError("Erro", result.Message);
                }
            }
            }, 1.8f);
        }
    }
    ImGui::End();
}

void ui::init(LPDIRECT3DDEVICE9 device) {
    dev = device;
	
    ImGuiStyle& style = ImGui::GetStyle();
    ImGui::StyleColorsDark();

    style.WindowPadding = ImVec2(0, 0);
    style.FramePadding = ImVec2(8, 11);
    style.WindowRounding = 3;
    style.FrameRounding = 3.0f;

    style.WindowTitleAlign = ImVec2(0.0, 0.5f);


    style.ItemSpacing = ImVec2(10, 10);
    style.ItemInnerSpacing = ImVec2(10, 10);
    style.IndentSpacing = 0.0f;

    // Changing Colors
    ImVec4* colors = ImGui::GetStyle().Colors;

    // Background Colors
    colors[ImGuiCol_WindowBg] = ImColor(15, 15, 15);
    colors[ImGuiCol_FrameBg] = ImColor(20, 20, 20, 255);

    colors[ImGuiCol_TitleBg] = ImColor(20, 20, 20);
    colors[ImGuiCol_TitleBgActive] = ImColor(20, 20, 20);
    colors[ImGuiCol_TitleBgCollapsed] = ImColor(20, 20, 20);

    // Border Color
    colors[ImGuiCol_Border] = ImColor(1, 37, 37,0);
    colors[ImGuiCol_BorderShadow] = ImColor(0, 0, 0, 255);

    // Text Color
    colors[ImGuiCol_Text] = ImColor(80, 80, 80);
    colors[ImGuiCol_TextDisabled] = ImColor(80, 80, 80);

    // Button Color
    colors[ImGuiCol_Button] = ImColor(171, 110, 248);
    colors[ImGuiCol_CloseButtonActive] = ImColor(75, 25, 25);


    // Components Hover
    colors[ImGuiCol_ButtonHovered] = ImColor(85, 25, 25);
    colors[ImGuiCol_FrameBgHovered] = ImColor(145, 98, 231);

    colors[ImGuiCol_ButtonActive] = ImColor(30, 30, 30);
    colors[ImGuiCol_FrameBgActive] = ImColor(145, 98, 231);

	if (window_pos.x == 0) {
		RECT screen_rect{};
		GetWindowRect(GetDesktopWindow(), &screen_rect);
		screen_res = ImVec2(float(screen_rect.right), float(screen_rect.bottom));
		window_pos = (screen_res - window_size) * 0.5f;

		// init images here
	}
}

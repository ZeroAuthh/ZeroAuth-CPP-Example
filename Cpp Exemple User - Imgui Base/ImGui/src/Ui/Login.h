#pragma once
#include <src/Includes.hpp>
#include <Utils/MouseMov/MouseMov.hpp>
#include <Utils/Security/XorStr.hpp>
#include <src/Config.hpp>
#include <src/auth/auth.h>
#include <src/auth/json.hpp>  // nlohmann json header file


using json = nlohmann::json;




void Login() {
    ImGui::SetCursorPos((I_Init.Size - ImVec2(300, 300)) * 0.5f);
    ImGui::BeginChild(XorStr("Login").c_str(), ImVec2(300, ImGui::GetContentRegionAvail().y), ImGuiChildFlags_Border, ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse);
    {
        MouseMovement();

        // Instância estática da classe Auth
        static Auth* auth = nullptr;
        static bool initialized = false;
        
        std::string Application = " ";  // ID do aplicativo
        std::string OwnerID = " ";  // Banco de dados do aplicativo

        // Inicializar Auth na primeira vez
        if (!initialized) {
            auth = new Auth(Application, OwnerID);
            if (!auth->Init()) {
                ShowMessageBoxError("Erro", "Falha ao inicializar ZeroAuth.");
                exit(0);
            }
            initialized = true;
        }

       
        // Entrada de usuário e senha
        ImGui::SetCursorPos(ImVec2((300 - 280) * 0.5f, 100));
        ImGui::InputTextEx("##0", "user", g_Config.General.Username, 20, ImVec2(280, 30), ImGuiInputTextFlags_None);

        ImGui::SetCursorPos(ImVec2((300 - 280) * 0.5f, 100 + 35));
        ImGui::InputTextEx("##1", "pass", g_Config.General.PassWord, 20, ImVec2(280, 30), ImGuiInputTextFlags_Password);

        // Botão de login
        ImGui::SetCursorPos(ImVec2((300 - 280) * 0.5f, 100 + (35) * 2));
        if (ImGui::Button("Sign In", ImVec2(280, 35))) {
            std::string username = g_Config.General.Username;
            std::string password = g_Config.General.PassWord;

            AuthResult result = auth->LoginWithUser(username, password);

            if (result.Success()) {
                ShowMessageBox("Sucesso", "Login com o Usuario bem-sucedido!");
                
                // Obter e armazenar expiração
                std::string expiration = auth->GetExpiration(username, "{d} Days {h} Hours {m} Minutes", false);
                g_Config.General.Expiration = expiration;
                
                g_Config.General.Tab = 1;
            }
            else {
                ShowMessageBoxError("Erro", result.Message);
            }
        }

    }
    ImGui::EndChild();
}

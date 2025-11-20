#include <iostream>
#include <fstream>
#include <sstream>
#include <thread>
#include <string>
#include <windows.h>
#include <consoleapi.h> 
#include "auth/Auth.h"
#include <Windows.h>
#include "auth/json.hpp"

using json = nlohmann::json;

int main() {
    std::string Application = " ";  // ID do aplicativo
    std::string OwnerID = " ";  // Banco de dados do aplicativo

    // Criar instância da classe Auth
    Auth auth(Application, OwnerID);

    // Inicializar e verificar status do AppID
    std::cout << "Inicializando ZeroAuth..." << std::endl;
    if (!auth.Init()) {
        // Se Init() falhar, error() já foi chamado e o programa será encerrado
        return 1;
    }

    std::string username, password, key, input;

    // Menu para outras opções
    int option;
    while (true) {
        system("cls");
        std::cout << "=== ZeroAuth Menu ===" << std::endl;
        std::cout << "1. Login com Key" << std::endl;
        std::cout << "2. Login com Usuario" << std::endl;
        std::cout << "3. Registrar" << std::endl;
        std::cout << "4. Verificar Expiracao" << std::endl;
        std::cout << "5. Sair" << std::endl;
        std::cout << "\nOpcao: ";
        std::cin >> option;

        switch (option) {
        case 1: { // Login com Key
            system("cls");
            std::cout << "\n\n=== Login com Key ===" << std::endl;
            std::cout << "Digite sua Key: ";
            std::cin >> key;

            AuthResult result = auth.LoginWithKey(key);

            if (result.Success()) {
                std::cout << "\n[SUCESSO] Login com a Key bem-sucedido!" << std::endl;
                
                // Obter e exibir expiração
                std::cout << "\nObtendo informacoes de expiracao..." << std::endl;
                std::string expiration = auth.GetExpiration(key, "{d} Days {h} Hours {m} Minutes", true);
                std::cout << "Expiry in: " << expiration << std::endl;
            }
            else {
                std::cout << "\n[ERRO] " << result.Message << std::endl;
            }

            std::cout << "\nPressione qualquer tecla para continuar...";
            std::cin.ignore();
            std::cin.get();
            break;
        }

        case 2: { // Login com Usuário
            system("cls");
            std::cout << "\n\n=== Login com Usuario ===" << std::endl;
            std::cout << "Digite o nome de usuario: ";
            std::cin >> username;
            std::cout << "Digite a senha: ";
            std::cin >> password;

            AuthResult result = auth.LoginWithUser(username, password);


            if (result.Success()) {
                std::cout << "\n[SUCESSO] Login com o Usuario bem-sucedido!" << std::endl;
                
                // Obter e exibir expiração
                std::cout << "\nObtendo informacoes de expiracao..." << std::endl;
                std::string expiration = auth.GetExpiration(username, "{d} Days {h} Hours {m} Minutes", false);
                std::cout << "Expiry in: " << expiration << std::endl;
            }
            else {
                std::cout << "\n[ERRO] " << result.Message << std::endl;
            }

            std::cout << "\nPressione qualquer tecla para continuar...";
            std::cin.ignore();
            std::cin.get();
            break;
        }

        case 3: { // Registrar
            system("cls");
            std::cout << "\n\n=== Registrar Usuario ===" << std::endl;
            std::cout << "Digite o nome de usuario para registro: ";
            std::cin >> username;
            std::cout << "Digite a senha para registro: ";
            std::cin >> password;
            std::cout << "Digite a chave de registro: ";
            std::cin >> key;

            AuthResult result = auth.RegisterUserWithKey(username, password, key);


            if (result.Success()) {
                std::cout << "\n[SUCESSO] Usuario registrado com sucesso!" << std::endl;
            }
            else {
                std::cout << "\n[ERRO] " << result.Message << std::endl;
            }

            std::cout << "\nPressione qualquer tecla para continuar...";
            std::cin.ignore();
            std::cin.get();
            break;
        }

        case 4: { // Verificar Expiração
            system("cls");
            std::cout << "\n\n=== Verificar Expiracao ===" << std::endl;
            std::cout << "1. Verificar por Key" << std::endl;
            std::cout << "2. Verificar por Username" << std::endl;
            std::cout << "Opcao: ";
            int subOption;
            std::cin >> subOption;




            std::string format = "{d} Days {h} Hours {m} Minutes";
            bool isKey = false;
            std::string inputValue;

            if (subOption == 1) {
                std::cout << "Digite a Key: ";
                std::cin >> inputValue;
                isKey = true;
            }
            else if (subOption == 2) {
                std::cout << "Digite o Username: ";
                std::cin >> inputValue;
                isKey = false;
            }
            else {
                std::cout << "Opcao invalida!" << std::endl;
                std::cout << "\nPressione qualquer tecla para continuar...";
                std::cin.ignore();
                std::cin.get();
                break;
            }

            std::cout << "\nObtendo informacoes de expiracao..." << std::endl;
            std::string expiration = auth.GetExpiration(inputValue, format, isKey);
            std::cout << "\nExpiracao: " << expiration << std::endl;

            std::cout << "\nPressione qualquer tecla para continuar...";
            std::cin.ignore();
            std::cin.get();
            break;
        }

        case 5: { // Sair
            std::cout << "Saindo do programa..." << std::endl;
            return 0;
        }

        default:
            std::cout << "Opcao invalida!" << std::endl;
            std::cout << "\nPressione qualquer tecla para continuar...";
            std::cin.ignore();
            std::cin.get();
            break;
        }
    }

    return 0;
}

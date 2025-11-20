# Sistema de Autenticação ZeroAuth - Exemplo em C++

Aplicativo C++ que demonstra a integração com o sistema de autenticação ZeroAuth, permitindo login e registro de usuários através de chaves de licença ou credenciais de usuário.

## 📋 Sobre o Projeto

Este projeto é um exemplo de implementação do ZeroAuth em uma aplicação C++, oferecendo três métodos de autenticação:
- **Login com Chave de Licença**: Autenticação usando apenas uma chave de licença
- **Login com Usuário e Senha**: Autenticação tradicional com credenciais
- **Registro de Novo Usuário**: Criação de conta com usuário, senha e chave de licença

## 🛠️ Tecnologias Utilizadas

- **C++17** ou superior
- **cURL** para requisições HTTP
- **nlohmann/json** ou **rapidjson** para manipulação de JSON
- **Windows API** para obtenção de HWID (Windows)
- **std::thread** e **std::async** para operações assíncronas

## 📦 Dependências

O projeto utiliza as seguintes bibliotecas:

### Bibliotecas Incluídas no Projeto ✅

- **libcurl** - Para requisições HTTP/HTTPS
  - ✅ **Já incluído** na pasta `auth/curl/`
  - Não é necessário instalar separadamente
  - Biblioteca estática (`libcurl_a.lib`) já configurada no projeto

- **nlohmann/json** - Parser JSON header-only
  - ✅ **Já incluído** como `auth/json.hpp`
  - Não é necessário baixar ou instalar separadamente

### Bibliotecas do Sistema

- **Windows**: 
  - `windows.h` - APIs do Windows
  - `consoleapi.h` - APIs do console
  - Bibliotecas do sistema: `ws2_32`, `wininet` (já configuradas no projeto)

## 🚀 Como Configurar

### Pré-requisitos

- **Visual Studio 2019 ou superior** (recomendado Visual Studio 2022)
  - Com suporte a C++17 ou superior
  - Platform Toolset v143 (Visual Studio 2022)
- **Windows SDK 10.0** ou superior
- **Conta no ZeroAuth** com AppID e OwnerID configurados
- **Todas as dependências já estão incluídas** no projeto (cURL e nlohmann/json)

### Instalação no Windows

1. Clone ou baixe este repositório
2. **Dependências já incluídas**:
   - ✅ **cURL**: Já está incluído na pasta `auth/curl/` (não precisa instalar)
   - ✅ **nlohmann/json**: Já está incluído como `auth/json.hpp` (não precisa instalar)
3. Abra o arquivo `.sln` no Visual Studio 2019 ou superior
4. Configure suas credenciais ZeroAuth:

```cpp
std::string Application = "seu-appid-aqui";  // ID do aplicativo
std::string OwnerID = "seu-ownerid-aqui";   // Banco de dados do aplicativo
```

5. **⚠️ IMPORTANTE**: Sempre compile o projeto em modo **Release** para produção:
   - No Visual Studio, selecione **"Release"** no dropdown de configuração (ao lado do botão de executar)
   - Selecione a plataforma **"x64"** (recomendado)
   - Ou use: `Build > Configuration Manager > Active solution configuration: Release`
   - O modo Debug contém informações de depuração, símbolos e código não otimizado que podem expor detalhes sensíveis do código

6. Compile o projeto: `Build > Build Solution` (ou pressione `Ctrl+Shift+B`)
7. O executável será gerado em `x64/Release/svchost.exe`

> **Nota**: Este projeto está configurado especificamente para Windows com Visual Studio. Para Linux ou macOS, será necessário adaptar o projeto e configurar as dependências manualmente.

## 📁 Estrutura do Projeto

```
├── auth/
│   ├── Auth.cpp             # Implementação da classe Auth (ZeroAuth)
│   ├── Auth.h               # Cabeçalho da classe Auth
│   ├── json.hpp             # nlohmann/json (biblioteca JSON header-only)
│   └── curl/                # Biblioteca cURL (incluída no projeto)
│       ├── curl.h           # Cabeçalho principal do cURL
│       ├── easy.h           # API fácil do cURL
│       ├── multi.h          # API multi do cURL
│       ├── libcurl_a.lib    # Biblioteca estática do cURL
│       └── ...              # Outros arquivos do cURL
```

## 🔑 Funcionalidades

### Classe Auth

A classe `Auth`  fornece os seguintes métodos:

#### Inicialização

```cpp
Auth auth("seu-appid", "seu-ownerid");
bool success = auth.Init();
```

- **`Init()`**: Inicializa a conexão com a API ZeroAuth e verifica o status do AppID
- Retorna `true` se a inicialização foi bem-sucedida

#### Autenticação

```cpp
// Login com chave
AuthResult result = auth.LoginWithKey("chave-de-licenca");
if (result.Success()) {
    // Login bem-sucedido
}

// Login com usuário e senha
AuthResult result = auth.LoginWithUser("usuario", "senha");
if (result.Success()) {
    // Login bem-sucedido
}

// Registrar novo usuário
AuthResult result = auth.RegisterUserWithKey("usuario", "senha", "chave");
if (result.Success()) {
    // Registro bem-sucedido
}
```

- **`LoginWithKey(string key)`**: Realiza login usando apenas uma chave de licença
- **`LoginWithUser(string username, string password)`**: Realiza login com usuário e senha
- **`RegisterUserWithKey(string username, string password, string key)`**: Registra um novo usuário com chave de licença

#### Informações

```cpp
// Obter expiração
string expiration = auth.GetExpiration("chave-ou-usuario", "{d} Days {h} Hours {m} Minutes", true);

// Verificar disponibilidade da API
bool available = auth.CheckApiAvailability();
```

- **`GetExpiration(string keyOrUsername, string format, bool isKey)`**: Obtém informações de expiração da licença
- **`CheckApiAvailability()`**: Verifica se a API está disponível

### Estrutura AuthResult

```cpp
struct AuthResult {
    int StatusCode;
    std::string Message;
    bool Success() const { return StatusCode >= 200 && StatusCode < 300; }
};
```

## 💻 Exemplo de Uso

```cpp
#include "auth/Auth.h"
#include <iostream>

int main() {
    // Configurar credenciais
    std::string Application = "seu-appid-aqui";
    std::string OwnerID = "seu-ownerid-aqui";
    
    // Criar instância da classe Auth
    Auth auth(Application, OwnerID);
    
    // Inicializar ZeroAuth
    if (!auth.Init()) {
        std::cerr << "Erro ao inicializar ZeroAuth" << std::endl;
        return 1;
    }
    
    // Login com chave
    std::string key;
    std::cout << "Digite sua chave: ";
    std::cin >> key;
    
    AuthResult result = auth.LoginWithKey(key);
    
    if (result.Success()) {
        std::cout << "Login bem-sucedido!" << std::endl;
        
        // Obter expiração
        std::string expiration = auth.GetExpiration(
            key, 
            "{d} Days {h} Hours {m} Minutes", 
            true
        );
        std::cout << "Expiry in: " << expiration << std::endl;
    } else {
        std::cerr << "Erro: " << result.Message << std::endl;
        return 1;
    }
    
    return 0;
}
```

### Menu Interativo

Os projetos as seguintes opções:

1. **Login com Key**: Autenticação usando apenas uma chave de licença
   - Solicita a chave do usuário
   - Exibe mensagem de sucesso/erro
   - Mostra informações de expiração após login bem-sucedido

2. **Login com Usuario**: Autenticação tradicional com usuário e senha
   - Solicita nome de usuário e senha
   - Exibe mensagem de sucesso/erro
   - Mostra informações de expiração após login bem-sucedido

3. **Registrar**: Criação de nova conta
   - Solicita nome de usuário, senha e chave de registro
   - Exibe mensagem de sucesso/erro

4. **Verificar Expiracao**: Consulta de expiração de licença
   - Opção para verificar por Key ou por Username
   - Exibe o tempo restante formatado (dias, horas, minutos)

5. **Sair**: Encerra o programa

O menu é executado em loop até que o usuário escolha a opção de sair.

## 🔒 Segurança

O sistema implementa as seguintes medidas de segurança:

- **HWID (Hardware ID)**: Identificação única do hardware para vinculação de licenças
  - Windows: Baseado em identificadores do sistema
  - Linux/macOS: Baseado em identificadores da máquina
- **Logs de Acesso**: Registro de todas as tentativas de login com informações de IP e hardware
- **Validação de Licença**: Verificação em tempo real com o servidor ZeroAuth
- **Tratamento de Erros**: Sistema robusto de tratamento de exceções e erros de conexão
- **Timeout de Requisições**: Limite de tempo para evitar travamentos

## 📝 Logs de Erro

O sistema cria automaticamente um arquivo de log em `Logs/ErrorLogs.txt` sempre que ocorre um erro crítico. Os logs incluem:

- Data e hora do erro
- Mensagem de erro detalhada
- Informações de conexão
- Stack trace (quando disponível)

### Exemplo de Implementação de Log

```cpp
void logError(const std::string& message) {
    std::ofstream logFile("Logs/ErrorLogs.txt", std::ios::app);
    if (logFile.is_open()) {
        auto now = std::chrono::system_clock::now();
        auto time = std::chrono::system_clock::to_time_t(now);
        logFile << std::put_time(std::localtime(&time), "%Y-%m-%d %H:%M:%S")
                << " > " << message << std::endl;
        logFile.close();
    }
}
```

## ⚙️ Configuração da API

A API ZeroAuth está configurada para usar o endpoint:
```
https://api.zeroauth.cc
```

Certifique-se de que este endpoint está acessível e que suas credenciais (AppID e OwnerID) estão corretas.

### Configuração de Timeout

```cpp
// No construtor ou método init()
curl_easy_setopt(curl, CURLOPT_TIMEOUT, 15L);  // 15 segundos
curl_easy_setopt(curl, CURLOPT_CONNECTTIMEOUT, 10L);  // 10 segundos
```

## 🐛 Tratamento de Erros

O sistema trata os seguintes tipos de erros:

- **Erros de Conexão**: Timeout ou falha na comunicação com a API
- **Erros de Autenticação**: Credenciais inválidas ou chave expirada
- **Erros de JSON**: Respostas inválidas da API
- **Erros de Inicialização**: AppID inválido ou API offline
- **Erros de Memória**: Falhas de alocação (em sistemas críticos)

### Códigos de Status HTTP

- **200-299**: Sucesso
- **400**: Requisição inválida
- **401**: Não autorizado
- **404**: Recurso não encontrado
- **500+**: Erro do servidor

## 🔧 Compilação

### Visual Studio

O projeto está configurado para compilar diretamente no Visual Studio:

1. Abra `.sln` no Visual Studio
2. Selecione a configuração **Release** e plataforma **x64**
3. Compile: `Build > Build Solution` (ou `Ctrl+Shift+B`)
4. O executável será gerado em `x64/Release/svchost.exe`

### Configurações do Projeto

- **Tipo**: Aplicação Console e Imgui
- **Plataforma**: x64 (recomendado) ou Win32
- **Character Set**: MultiByte (x64) ou Unicode (Win32)
- **Bibliotecas Linkadas**:
  - `libcurl_a.lib` (cURL estático)
  - `ws2_32` (Winsock)
  - `wininet` (Windows Internet API)
- **C++ Standard**: C++17 ou superior

## 📄 Licença

Este projeto é um exemplo de implementação. Verifique a licença do ZeroAuth para uso comercial.

## 🤝 Contribuições

Este é um projeto de exemplo. Sinta-se livre para adaptá-lo às suas necessidades.

## ⚠️ Avisos

- **⚠️ SEMPRE COMPILE EM MODO RELEASE**: O modo Debug contém informações de depuração, símbolos, código não otimizado e pode incluir informações sensíveis que facilitam engenharia reversa. Use Release para todas as compilações de produção.
- **Nunca compartilhe suas credenciais** (AppID e OwnerID) publicamente
- **Use ofuscação de código** em produção para proteger sua aplicação
- **Implemente verificações de integridade** para prevenir modificações no código
- **Mantenha suas dependências atualizadas** para segurança
- **Valide todas as entradas do usuário** para prevenir vulnerabilidades
- **Use HTTPS sempre** para comunicação segura com a API


## 📞 Suporte

Para questões sobre o ZeroAuth, consulte a documentação oficial ou entre em contato com o suporte do ZeroAuth.

---

**Nota**: Este é um projeto de exemplo educacional. Adapte-o conforme necessário para seu uso específico.


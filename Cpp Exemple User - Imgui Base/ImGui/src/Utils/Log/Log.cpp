#include "Log.hpp"
#include <cstdio>
#include <Utils/Security/LazyImporter.hpp>
#include <Utils/Security/XorStr.hpp>

FILE* fDummy;

void Console::Init()
{
    if (!SafeCall(AllocConsole)()) {
        return;
    }

    freopen_s(&fDummy, XorStr("CONOUT$").c_str(), XorStr("w").c_str(), stdout);
    freopen_s(&fDummy, XorStr("CONOUT$").c_str(), XorStr("w").c_str(), stderr);
    freopen_s(&fDummy, XorStr("CONIN$").c_str(), XorStr("r").c_str(), stdin);

    std::cout.clear();
    std::clog.clear();
    std::cerr.clear();
    std::cin.clear();

    SafeCall(SetConsoleOutputCP)(CP_UTF8);
    SafeCall(SetConsoleCP)(CP_UTF8);
    SafeCall(SetConsoleTitleA)(XorStr("Debug Console").c_str());
}

void Console::Shutdown() {
    SafeCall(fclose)(stdin);
    SafeCall(fclose)(stdout);
    SafeCall(fclose)(stderr);
    SafeCall(FreeConsole)();
}
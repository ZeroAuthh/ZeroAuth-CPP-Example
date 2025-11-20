#pragma once
/*ImGui*/
#include <imgui.h>
#include <imgui_internal.h>
#include <imgui_impl_win32.h>
#include <imgui_impl_dx11.h>
#include <imgui_freetype.h>

/*Windows*/
#include <Windows.h>
#include <tchar.h>
#include <dwmapi.h>
#include <ostream>
#include <iostream>
#include <thread>

/*Fonts*/
#include <Fonts/Fonts.hpp>

/*Src/Ui*/
#include <Ui/Menu.h>
#include <Ui/Login.h>

#include <src/Config.hpp>

/*Src/Utils*/
#include <Utils/Security/XorStr.hpp>
#include <Utils/MouseMov/MouseMov.hpp>
#include <Utils/Security/LazyImporter.hpp>

/*Dx11*/
#include <d3d11.h>
#include <D3DX11.h>
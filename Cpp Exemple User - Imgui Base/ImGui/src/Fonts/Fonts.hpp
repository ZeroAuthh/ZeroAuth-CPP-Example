#pragma once
#include <imgui.h>
#include <imgui_freetype.h>
#include <d3d11.h>
#include <D3DX11.h>
#include <Fonts/Bytes/BytesFonts.hpp>
#include <Fonts/Bytes/FontAwesome.hpp>

namespace Init
{
	namespace Fonts
	{
		inline ImFont* FontAwesomeRegular = nullptr;
		inline ImFont* FontAwesomeSolid = nullptr;
		inline ImFont* FontAwesomeSolid18 = nullptr;
		inline ImFont* FontAwesomeSolidBig = nullptr;

		inline ImFont* InterExtraLight = nullptr;
		inline ImFont* InterLight = nullptr;
		inline ImFont* InterThin = nullptr;
		inline ImFont* InterRegular = nullptr;
		inline ImFont* InterRegular14 = nullptr;
		inline ImFont* InterMedium = nullptr;
		inline ImFont* InterSemiBold = nullptr;
		inline ImFont* InterBold = nullptr;
		inline ImFont* InterBold12 = nullptr;
		inline ImFont* InterExtraBold = nullptr;
		inline ImFont* InterBlack = nullptr;

		inline ID3D11ShaderResourceView* Logo;
		inline ID3D11ShaderResourceView* LogoMenu;
		inline D3DX11_IMAGE_LOAD_INFO ImageLoadInfo;
		inline ID3DX11ThreadPump* Pump = nullptr;
		void Initialize(ID3D11Device* Device);
		void LoadStyle(ID3D11Device* Device);
	}
}
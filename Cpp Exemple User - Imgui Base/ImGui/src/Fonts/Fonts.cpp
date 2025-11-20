#include <Fonts/Fonts.hpp>


namespace Init {
	namespace Fonts {
		void Initialize(ID3D11Device* Device)
		{
			ImGuiIO& io = ImGui::GetIO(); (void)io;

			io.IniFilename = nullptr;
			io.LogFilename = nullptr;
			io.Framerate = 240.0f;

			ImFontConfig cfg;
			cfg.FontBuilderFlags = ImGuiFreeTypeBuilderFlags_ForceAutoHint | ImGuiFreeTypeBuilderFlags_LightHinting | ImGuiFreeTypeBuilderFlags_LoadColor;

			InterBlack = io.Fonts->AddFontFromMemoryCompressedTTF(InterBlack_compressed_data, InterBlack_compressed_size, 15, &cfg);
			InterBold = io.Fonts->AddFontFromMemoryCompressedTTF(InterBold_compressed_data, InterBold_compressed_size, 17, &cfg);
			InterBold12 = io.Fonts->AddFontFromMemoryCompressedTTF(InterBold_compressed_data, InterBold_compressed_size, 15, &cfg);
			InterExtraBold = io.Fonts->AddFontFromMemoryCompressedTTF(InterExtraBold_compressed_data, InterExtraBold_compressed_size, 13, &cfg);
			InterExtraLight = io.Fonts->AddFontFromMemoryCompressedTTF(InterExtraLight_compressed_data, InterExtraLight_compressed_size, 14, &cfg);
			InterLight = io.Fonts->AddFontFromMemoryCompressedTTF(InterLight_compressed_data, InterLight_compressed_size, 12, &cfg);
			InterMedium = io.Fonts->AddFontFromMemoryCompressedTTF(InterMedium_compressed_data, InterMedium_compressed_size, 17, &cfg);
			InterRegular = io.Fonts->AddFontFromMemoryCompressedTTF(InterRegular_compressed_data, InterRegular_compressed_size, 17, &cfg);
			InterRegular14 = io.Fonts->AddFontFromMemoryCompressedTTF(InterRegular_compressed_data, InterRegular_compressed_size, 15, &cfg);
			InterSemiBold = io.Fonts->AddFontFromMemoryCompressedTTF(InterSemiBold_compressed_data, InterSemiBold_compressed_size, 16, &cfg);
			InterThin = io.Fonts->AddFontFromMemoryCompressedTTF(InterThin_compressed_data, InterThin_compressed_size, 14, &cfg);

			static const ImWchar IconRanges[] = { ICON_MIN_FA, ICON_MAX_FA, 0 };
			ImFontConfig FontAwesomeConfig;
			FontAwesomeConfig.MergeMode = true;
			FontAwesomeConfig.PixelSnapH = true;
			FontAwesomeConfig.GlyphMinAdvanceX = 25.f * (2.0f / 3.0f);
			FontAwesomeConfig.FontBuilderFlags = ImGuiFreeTypeBuilderFlags_ForceAutoHint | ImGuiFreeTypeBuilderFlags_LightHinting | ImGuiFreeTypeBuilderFlags_LoadColor;

			FontAwesomeRegular = io.Fonts->AddFontFromMemoryCompressedTTF(FontAwesomeRegular_compressed_data, FontAwesomeRegular_compressed_size, 25.f * (2.0f / 3.0f), &FontAwesomeConfig, &IconRanges[0]);
			FontAwesomeSolid = ImGui::GetIO().Fonts->AddFontFromMemoryCompressedTTF(FontAwesomeSolid_compressed_data, FontAwesomeSolid_compressed_size, 27.f * (2.0f / 3.0f), &FontAwesomeConfig, &IconRanges[0]);
			FontAwesomeSolid18 = ImGui::GetIO().Fonts->AddFontFromMemoryCompressedTTF(FontAwesomeSolid_compressed_data, FontAwesomeSolid_compressed_size, 18.f * (2.0f / 3.0f), &FontAwesomeConfig, &IconRanges[0]);
			FontAwesomeSolidBig = io.Fonts->AddFontFromMemoryCompressedTTF(FontAwesomeSolid_compressed_data, FontAwesomeSolid_compressed_size, 30.f * (2.0f / 3.0f), &FontAwesomeConfig, &IconRanges[0]);

		

			//ID3DX11ThreadPump* ThreadPump = nullptr;
			//if (SUCCEEDED(D3DX11CreateThreadPump(0, 0, &ThreadPump))) {
			//	D3DX11CreateShaderResourceViewFromMemory(Device, LogoRawData, sizeof(LogoRawData), &ImageLoadInfo, ThreadPump, &Logo, nullptr); 
			//	ThreadPump->Release();
			//}

			//if (SUCCEEDED(D3DX11CreateThreadPump(0, 0, &ThreadPump))) {
			//	D3DX11CreateShaderResourceViewFromMemory(Device, MenuRawData, sizeof(MenuRawData), &ImageLoadInfo, ThreadPump, &LogoMenu, nullptr);
			//	ThreadPump->Release();
			//}
		}

		void LoadStyle(ID3D11Device* Device) {
			ImGuiStyle* Style = &ImGui::GetStyle();
			Style->AntiAliasedLines = true;
			Style->AntiAliasedLinesUseTex = true;
			Style->AntiAliasedFill = true;

			Style->ChildBorderSize = 0;
			Style->WindowRounding = 10;
			Style->FrameRounding = 3.f;
			Style->WindowBorderSize = 0;
			Style->ScrollbarSize = 1;
			Style->ScrollbarRounding = 5;
			Style->Colors[ImGuiCol_NavHighlight] = ImVec4(0, 0, 0, 0);
			Style->Colors[ImGuiCol_NavWindowingHighlight] = ImVec4(0, 0, 0, 0);
			Style->Colors[ImGuiCol_Separator] = ImColor(0, 0, 0, 0);
			Style->Colors[ImGuiCol_SeparatorActive] = ImColor(0, 0, 0, 0);
			Style->Colors[ImGuiCol_SeparatorHovered] = ImColor(0, 0, 0, 0);
			Style->Colors[ImGuiCol_ResizeGrip] = ImColor(0, 0, 0, 0);
			Style->Colors[ImGuiCol_ResizeGripActive] = ImColor(0, 0, 0, 0);
			Style->Colors[ImGuiCol_ResizeGripHovered] = ImColor(0, 0, 0, 0);
			Style->Colors[ImGuiCol_PopupBg] = ImColor(14, 14, 14);
			Style->Colors[ImGuiCol_ScrollbarBg] = ImColor(0, 0, 0, 0);
			Style->Colors[ImGuiCol_ScrollbarGrab] = ImColor(188, 0, 155);
			Style->Colors[ImGuiCol_ScrollbarGrabActive] = ImColor(188, 0, 155);
			Style->Colors[ImGuiCol_ScrollbarGrabHovered] = ImColor(188, 0, 155);
			Style->Colors[ImGuiCol_WindowBg] = ImColor(15, 15, 15);
			Style->Colors[ImGuiCol_Border] = ImColor(24, 23, 25);
		}
	}
}
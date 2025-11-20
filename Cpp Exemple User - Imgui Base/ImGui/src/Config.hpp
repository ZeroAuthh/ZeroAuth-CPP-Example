#pragma once 
#include <Windows.h> 
#include <imgui.h>
#include <string>

class Config {
public:
	struct General
	{

		int Tab = 0;
		char Username[20] = "";
		char PassWord[20] = "";
		std::string Expiration = "";
	} General;
};

inline Config g_Config;
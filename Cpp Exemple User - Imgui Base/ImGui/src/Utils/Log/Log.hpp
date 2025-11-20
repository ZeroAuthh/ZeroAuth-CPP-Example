#pragma once
#include <Windows.h>
#include <iostream>

class Console {
public:
	void Init();
	void Shutdown();
};

inline Console Log;
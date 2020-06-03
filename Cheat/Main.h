#pragma once
#include "Include/Headers.h"
#include "Include/Def.h"
#include "Engine/SDK/Color.hpp"

using namespace SDK;

class CMain
{
public:

	Color BackgroundColor = Color(18, 18, 22, 255);
	Color TitleColor = Color(112, 112, 116, 255);
	Color TextColor = Color(255, 255, 255, 255);
	Color FrameColor = Color(34, 35, 37, 255);
	Color ButtonColor = Color(128, 135, 140, 255);
	Color DisableButtonColor = Color(225, 20, 20, 255);
	Color LineColor = Color(120, 121, 123, 255);

	int MenuButton = VK_INSERT;

	string HintMsg = "";

	void SetMenuColors();

	static CMain& Singleton()
	{
		static CMain pObject;
		return pObject;
	}
};

CMain& MainSettings();
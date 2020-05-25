#include "Misc.h"
#include "../../GUI/Gui.h"

#define SAME_LINE_1 168

#define PUSH_1 200
#define PUSH_2 360
#define PUSH_3 240

void CMisc::Menu()
{
	DCheckBox("Bunny hop", BHop);
	if (BHop)
	{
		X1Gui().SameLine(SAME_LINE_1);
		DCheckBox("Air strafe", AutoStrafe);
	}
	X1Gui().Spacing();
	X1Gui().Separator();
	X1Gui().Spacing();
	//DCheckBox("Edge Jump", EdgeJump);
	//if (EdgeJump)
	//{
	//	X1Gui().PushItemWidth(PUSH_1);
	//	HotsKey("Button##edgejump", EdgeJumpBind.Button);
	//	X1Gui().SameLine();
	//	DCheckBox("Hold##edgejump", EdgeJumpBind.Hold);
	//}
	//X1Gui().Spacing();
	//X1Gui().Separator();
	//X1Gui().Spacing();
	DCheckBox("Left Hand Knife", LeftHandKnife);
	X1Gui().Spacing();
	X1Gui().Separator();
	X1Gui().Spacing();
	DCheckBox("Infinite duck", InfiniteDuck);
	X1Gui().Spacing();
	X1Gui().Separator();
	X1Gui().Spacing();
	DCheckBox("ThirdPerson", ThirdPerson);
	if (ThirdPerson)
	{
		X1Gui().SameLine(SAME_LINE_1);
		X1Gui().PushItemWidth(PUSH_1);
		SliderFloats("Distance##ThirdPerson", ThirdPersonDistance, 50.f, 500.f);
		X1Gui().PushItemWidth(PUSH_1);
		HotsKey("Button##thirdperson", ThirdPersonBind.Button);
		X1Gui().SameLine();
		DCheckBox("Hold##thirdperson", ThirdPersonBind.Hold);
	}
	X1Gui().Spacing();
	X1Gui().Separator();
	X1Gui().Spacing();
	DCheckBox("Anti-Kick", AntiKick);
	X1Gui().Spacing();
	X1Gui().Separator();
	X1Gui().Spacing();
	DCheckBox("Legit AA", LegitAA);
	if (LegitAA)
	{
		X1Gui().SameLine(SAME_LINE_1);
		X1Gui().PushItemWidth(PUSH_1);
		VectorEx<const char* >itemsCSS = { lolc("Off") , lolc("Static"), lolc("Balance") };
		DComboBox("Type##LegitAA", LegitAA_type, itemsCSS);
		DCheckBox("Autodirection", LegitAA_ad);
		X1Gui().SameLine(SAME_LINE_1);
		HotsKey("Button##LegitAA", LegitAABind.Button);
		X1Gui().SameLine();
		DCheckBox("Hold##LegitAA", LegitAABind.Hold);
	}
	X1Gui().Spacing();
	X1Gui().Separator();
	X1Gui().Spacing();
	DCheckBox("Show Competitive Rank", ShowCompetitiveRank);
	X1Gui().Spacing();
	X1Gui().Separator();
	X1Gui().Spacing();
	DCheckBox("Auto-accept matchmaking", AutoAccept);
	X1Gui().Spacing();
	X1Gui().Separator();
	X1Gui().Spacing();
	DCheckBox("Spectators", SpectatorList);
	if (SpectatorList)
	{
		X1Gui().SameLine(SAME_LINE_1);
		X1Gui().PushItemWidth(PUSH_1);
		SliderInts("Alpha##spec", SpectatorListAlpha, 0, 255);
		X1Gui().PushItemWidth(PUSH_2);
		SliderInts("Pos X##spec", SpectatorListPosX, 0, CGlobal::iScreenWidth);
		X1Gui().PushItemWidth(PUSH_2);
		SliderInts("Pos Y##spec", SpectatorListPosY, 0, CGlobal::iScreenHeight);
		DCheckBox("Auto Hide", SpectatorListAutoHide);
	}
	X1Gui().Spacing();
	X1Gui().Separator();
	X1Gui().Spacing();
	DCheckBox("Override FOV", FovChanger);
	if (FovChanger)
	{
		X1Gui().SameLine(SAME_LINE_1);
		X1Gui().PushItemWidth(PUSH_1);
		SliderInts("FOV view", FovView, 1, 180);
	}
	X1Gui().Spacing();
	X1Gui().Separator();
	X1Gui().Spacing();
	DCheckBox("Viewmodel FOV", FovModelChanger);
	if (FovModelChanger)
	{
		X1Gui().SameLine(SAME_LINE_1);
		X1Gui().PushItemWidth(PUSH_1);
		SliderInts("FOV model", FovModel, 1, 180);
	}
	X1Gui().Spacing();
	X1Gui().Separator();
	X1Gui().Spacing();
	DCheckBox("No visual recoil", NoVisualRecoil);
	X1Gui().Spacing();
	X1Gui().Separator();
	X1Gui().Spacing();
	DCheckBox("Free look", FreeCam);
	if (FreeCam)
	{
		X1Gui().SameLine(SAME_LINE_1);
		X1Gui().PushItemWidth(PUSH_1);
		SliderInts("Speed##frecam", FreeCamSpeed, 1, 40);

		HotsKey("Button##frcam", FreeCamBind.Button);
		X1Gui().SameLine();
		DCheckBox("Hold##frcam", FreeCamBind.Hold);
	}
	X1Gui().Spacing();
	X1Gui().Separator();
	X1Gui().Spacing();
	DCheckBox("Crosshair", Crosshair);
	if (Crosshair)
	{
		X1Gui().SameLine(SAME_LINE_1);
		X1Gui().PushItemWidth(PUSH_1);
		VectorEx<const char* >itemsCSS = { lolc("Type1") , lolc("Type2"), lolc("Type3") };
		DComboBox("Style##Crossh", CrosshairStyle, itemsCSS);

		X1Gui().PushItemWidth(PUSH_2);
		SliderInts("Size##Crossh", CrosshairSize, 1, 100);

		DCheckBox("Recoil##Crossh", CrosshairRecoil);
		X1Gui().SameLine(SAME_LINE_1);
		DCheckBox("Outline##Crossh", CrosshairOutline);

		DColorEdit("Color##Crossh", CrosshairColor);
	}
	X1Gui().Spacing();
	X1Gui().Separator();
	X1Gui().Spacing();
	DCheckBox("Sniper crosshair", SnipCrosshair);
	if (SnipCrosshair)
	{
		X1Gui().SameLine(SAME_LINE_1);

		X1Gui().PushItemWidth(PUSH_1);
		VectorEx<const char* >itemsCSS = { lolc("Type 1") , lolc("Type 2"), lolc("Type 3") };
		DComboBox("Style##Crosshsnip", SnipCrosshairStyle, itemsCSS);

		X1Gui().PushItemWidth(PUSH_2);
		if (SnipCrosshairStyle == 2)
		SliderInts("Size##Crosshsnip", SnipCrosshairSize, 1, 100);

		DCheckBox("Recoil##Crosshsnip", SnipCrosshairRecoil);
		X1Gui().SameLine(SAME_LINE_1);
		if (SnipCrosshairStyle <= 1)
		DCheckBox("Outline##Crosshsnip", SnipCrosshairOutline);

		DColorEdit("Color##Crosshsnip", SnipCrosshairColor);
	}
	X1Gui().Spacing();
	X1Gui().Separator();
	X1Gui().Spacing();
	DCheckBox("Spread circle", SpreadCircel);
	if (SpreadCircel)
	{
		X1Gui().SameLine(SAME_LINE_1);
		DColorEdit("Color##spread", SpreadColor);
	}
	X1Gui().Spacing();
	X1Gui().Separator();
	X1Gui().Spacing();
	DCheckBox("Hit marker", HitMarker);
	if (HitMarker)
	{
		X1Gui().SameLine(SAME_LINE_1);
		X1Gui().PushItemWidth(PUSH_3);
		SliderInts("Size##Hits", HitMarkerSize, 1, 10);
		X1Gui().PushItemWidth(PUSH_2);
		SliderInts("Tickness##Hits", HitMarkerTickness, 1, 100);
		DColorEdit("Color##Hits", HitMarkerColor);
	}
	X1Gui().Spacing();
	X1Gui().Separator();
	X1Gui().Spacing();
	DCheckBox("Hit marker sound", HitSound);
	if (HitSound)
	{
		if (!SoundList.empty())
		{
			X1Gui().SameLine(SAME_LINE_1);
			X1Gui().PushItemWidth(PUSH_1);

			VectorEx<const char*> itemsHSS;
			for (size_t i(0); i < SoundList.size(); i++)
			{
				itemsHSS.push_back(SoundList[i].c_str());
			}
			X1Gui().ComboBox(XorStr("Style##Hts"), &HitSoundStyle, itemsHSS);
		}
	}
	X1Gui().Spacing();
	X1Gui().Separator();
	X1Gui().Spacing();
	DCheckBox("Remove flashbang", AntiFlash);
	if (AntiFlash)
	{
		X1Gui().SameLine(SAME_LINE_1);
		X1Gui().PushItemWidth(PUSH_3);
		SliderInts("Alpha##flash", AntiFlashAlpha, 1, 255);
	}
	X1Gui().Spacing();
	X1Gui().Separator();
	X1Gui().Spacing();
	DCheckBox("Remove smoke", NoSmoke);
//	if (NoSmoke)
//	{
	//	X1Gui().SameLine(SAME_LINE_1);
	//	X1Gui().PushItemWidth(PUSH_1);
	//	VectorEx<const char* >itemsCSS = { lolc("No Draw Smoke") , lolc("Wireframe Smoke") };
	//	DComboBox("Type##NoSmoke", TypeNoSmoke, itemsCSS);
//	}
	X1Gui().Spacing();
	X1Gui().Separator();
	X1Gui().Spacing();
	DCheckBox("Clan tag spammer", ClanTagChanger);
	if (ClanTagChanger)
	{
		X1Gui().SameLine(SAME_LINE_1);
		X1Gui().PushItemWidth(PUSH_1);
		VectorEx<const char* >itemsCS = { lolc("X1N3 > All"),lolc("VALVE"), lolc("Animation X1N3"), lolc("Animation THELUPA"), lolc("X1N3"), lolc("Custom") };
		DComboBox("Style##clan", ClanTagChangerStyle, itemsCS);

		if (ClanTagChangerStyle == 5)
		{
			static char ClanBuf[32] = { 0 };
			TextEdit("Text##clan", ClanTagChangerText, ClanBuf, 32);
		}
	}
	X1Gui().Spacing();
	X1Gui().Separator();
	X1Gui().Spacing();
	DCheckBox("Chat spammer", ChatSpam);
	if (ChatSpam)
	{
		X1Gui().SameLine(SAME_LINE_1);
		X1Gui().PushItemWidth(PUSH_1);
		VectorEx<const char* >itemsCS = { lolc("Standard"), lolc("Custom") };
		DComboBox("Style##spam", ChatSpamStyle, itemsCS);
		if (ChatSpamStyle == 1)
		{
			X1Gui().PushItemWidth(450);
			static char ChatBuf[64] = { 0 };
			TextEdit("Text##spam", ChatSpamText, ChatBuf, 64);
		}
		if (X1Gui().Button(ChatSpamStart ? XorStr("Stop") : XorStr("Start")))
			ChatSpamStart = !ChatSpamStart;

	}
	X1Gui().Spacing();
	X1Gui().Separator();
	X1Gui().Spacing();
	DCheckBox("Radio spammer", RadioSpam);
	if (RadioSpam)
	{
		X1Gui().SameLine(SAME_LINE_1);
		X1Gui().PushItemWidth(PUSH_1);
		if (X1Gui().Button(RadioSpamStart ? XorStr("Stop") : XorStr("Start")))
			RadioSpamStart = !RadioSpamStart;
	}
	X1Gui().Spacing();
	X1Gui().Separator();
	X1Gui().Spacing();
	DCheckBox("Hand chams", HandChams);
	if (HandChams)
	{
		X1Gui().SameLine(SAME_LINE_1);
		X1Gui().PushItemWidth(PUSH_1);
		VectorEx<const char* >itemsCS = { lolc("Textured"),lolc("Flat"), lolc("Wireframe"), lolc("Metallic"), lolc("Material"), lolc("Disable") };
		DComboBox("Style##hand", HandChamsStyle, itemsCS);
		DColorEdit("Color##hand", HandChamsColor);
	}
	X1Gui().Spacing();
	X1Gui().Separator();
	X1Gui().Spacing();
	DCheckBox("Damage info", DamageInfo);
	if (DamageInfo)
	{
		X1Gui().SameLine(SAME_LINE_1);

		X1Gui().PushItemWidth(PUSH_1);
		X1Gui().PushItemWidth(PUSH_1);
		VectorEx<const char* >itemsCS = { lolc("On screen") , lolc("In world") };
		DComboBox("Position##damage", DamageInfoPosition, itemsCS);
		X1Gui().Spacing();
		X1Gui().SameLine(SAME_LINE_1);
		X1Gui().PushItemWidth(PUSH_1);
		X1Gui().PushItemWidth(PUSH_1);
		VectorEx<const char* >itemsDSS = { lolc("Damage"), lolc("Health") };
		DComboBox("Style##damage", DamageInfoStyle, itemsDSS);
		X1Gui().PushItemWidth(PUSH_2);
		SliderInts("Text Size##damage", TextDamageInfo, 9, MAX_FONT_SIZE);
		if (DamageInfoPosition == 0)
		{
			SliderFloats("Show Time", DamageInfoShowTime, 0.1, 10);
			SliderInts("Position X", DamageInfoPosX, 1, CGlobal::iScreenWidth);
			SliderInts("Position Y", DamageInfoPosY, 1, CGlobal::iScreenHeight);
		}
		else if (DamageInfoPosition == 1)
		{
			SliderInts("Height", DamageInfoHeight, 1, 100);
			SliderInts("Speed", DamageInfoSpeed, 1, 100);
		}
		DColorEdit("Color##damage", DamageInfoColor);
	}
	X1Gui().Spacing();
	X1Gui().Separator();
	X1Gui().Spacing();
	DCheckBox("Night mode", NightMode);
	X1Gui().Spacing();
	X1Gui().Separator();
	X1Gui().Spacing();
	DCheckBox("Fake lag", FakeLag);
	if (FakeLag)
	{
		X1Gui().SameLine(SAME_LINE_1);
		X1Gui().PushItemWidth(PUSH_1);
		SliderInts("Factor", FakeLagFactor, 1, 50);
		DCheckBox("Bind##fake", FakeLagBind.Enable);
		if (FakeLagBind.Enable)
		{
			X1Gui().SameLine(SAME_LINE_1);
			DCheckBox("Hold##fake", FakeLagBind.Hold);
			X1Gui().PushItemWidth(PUSH_2);
			HotsKey("Button##fake", FakeLagBind.Button);
		}
	}
	X1Gui().Spacing();
	X1Gui().Separator();
	X1Gui().Spacing();
	DCheckBox("Colored walls", ColoredWalls);
	if (ColoredWalls)
	{
		X1Gui().SameLine(SAME_LINE_1);
		X1Gui().PushItemWidth(PUSH_1);
		DColorEdit("Color##clrwall", ColoredWallsColor);
	}
	X1Gui().Spacing();
	X1Gui().Separator();
	X1Gui().Spacing();
	DCheckBox("Knifebot", KnifeBot);
	if (KnifeBot)
	{
		X1Gui().SameLine(SAME_LINE_1);
		X1Gui().PushItemWidth(PUSH_1);
		SliderInts("Distance##knfb", KnifeBotDistance, 1, 100);
		X1Gui().Spacing();
		X1Gui().SameLine(SAME_LINE_1);
		X1Gui().PushItemWidth(PUSH_1);
		VectorEx<const char* >itemsKNF = { lolc("All"), lolc("Team"), lolc("Enemy") };
		DComboBox("Attack##knfb", KnifeBotFilter, itemsKNF);
		X1Gui().PushItemWidth(PUSH_2);
		VectorEx<const char* >itemsKNFM = { lolc("Auto"), lolc("Left, right"), lolc("Right"), lolc("Left") };
		DComboBox("Mode##knfb", KnifeBotMode, itemsKNFM);

		DCheckBox("Bind##knfb", KnifeBotBind.Enable);
		if (KnifeBotBind.Enable)
		{
			X1Gui().SameLine(SAME_LINE_1);
			DCheckBox("Hold##knfb", KnifeBotBind.Hold);
			X1Gui().PushItemWidth(PUSH_2);
			HotsKey("Button##knfb", KnifeBotBind.Button);
		}
	}
}

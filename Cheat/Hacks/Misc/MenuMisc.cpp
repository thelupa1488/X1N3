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
		X1Gui().PushItemWidth(PUSH_1);
		VectorEx<const char* >itemsCSS = { lolc("Default"), lolc("Legit") };
		DComboBox("Type##BHop", BHopType, itemsCSS);
		if (BHopType == 1)
		{
			X1Gui().PushItemWidth(PUSH_2);
			SliderInts("Chance##LegitBHop", BHopChance, 0, 100);
			SliderInts("Hops limit##LegitBHop", BHopLimit, 0, 15);
			SliderInts("Max hops limit##LegitBHop", BHopMaxHit, 0, 15);

		}
		DCheckBox("Auto strafe", AutoStrafe);
		if (AutoStrafe)
		{
			X1Gui().SameLine(SAME_LINE_1);
			X1Gui().PushItemWidth(PUSH_1);
			SliderInts("Speed##AutoStrafe", AutoStrafeSpeed, 0, 15);
		}
	}
	X1Gui().Spacing();
	X1Gui().Separator();
	X1Gui().Spacing();
	DCheckBox("Edge jump", EdgeJump);
	if (EdgeJump)
	{
		X1Gui().SameLine(SAME_LINE_1);
		X1Gui().PushItemWidth(PUSH_1);
		HotsKey("Button##edgejump", EdgeJumpBind.Button);
		X1Gui().SameLine();
		DCheckBox("Hold##edgejump", EdgeJumpBind.Hold);
	}
	X1Gui().Spacing();
	X1Gui().Separator();
	X1Gui().Spacing();
	DCheckBox("Left/Right hand knife", LRHandKnife);
	X1Gui().Spacing();
	X1Gui().Separator();
	X1Gui().Spacing();
	DCheckBox("Swap hand", SwapHand);
	if (SwapHand)
	{
		X1Gui().SameLine(SAME_LINE_1);
		X1Gui().PushItemWidth(PUSH_1);
		HotsKey("Button##SwapHand", SwapHandBind.Button);
		X1Gui().SameLine();
		DCheckBox("Hold##SwapHand", SwapHandBind.Hold);
	}
	X1Gui().Spacing();
	X1Gui().Separator();
	X1Gui().Spacing();
	DCheckBox("Infinite crouch", InfiniteCrouch);
	X1Gui().Spacing();
	X1Gui().Separator();
	X1Gui().Spacing();
	DCheckBox("Third person", ThirdPerson);
	if (ThirdPerson)
	{
		X1Gui().SameLine(SAME_LINE_1);
		X1Gui().PushItemWidth(PUSH_1);
		SliderInts("Distance##ThirdPerson", ThirdPersonDistance, 50, 300);
		X1Gui().PushItemWidth(PUSH_1);
		HotsKey("Button##ThirdPerson", ThirdPersonBind.Button);
		X1Gui().SameLine();
		DCheckBox("Hold##ThirdPerson", ThirdPersonBind.Hold);
	}
	X1Gui().Spacing();
	X1Gui().Separator();
	X1Gui().Spacing();
	DCheckBox("Legit desync", LDesync);
	if (LDesync)
	{
		X1Gui().SameLine(SAME_LINE_1);
		X1Gui().PushItemWidth(PUSH_1);
		VectorEx<const char* >itemsLDT = { lolc("Static") , lolc("Balanced") };
		DComboBox("Type##Desync", LDesyncType, itemsLDT);
		//DCheckBox("Autodirection##Desync", LDesyncAd);
		if (!LDesyncAd)
		{
			//X1Gui().SameLine();
			X1Gui().PushItemWidth(PUSH_1);
			HotsKey("Button##Desync", LDesyncBind.Button);
			X1Gui().SameLine();
			DCheckBox("Hold##Desync", LDesyncBind.Hold);
		}
		X1Gui().PushItemWidth(PUSH_2);
		SliderFloats("Yaw##Desync", LDesyncYaw, 1, 120);
		DCheckBox("Angle lines", LDesyncLines);
		if (LDesyncLines)
		{
			X1Gui().SameLine(SAME_LINE_1);
			X1Gui().PushItemWidth(PUSH_1);
			SliderInts("Lines length", LDesyncLinesLength, 15, 30);
		}
		DCheckBox("Desync arrows", LDesyncArrows);
		if (LDesyncArrows)
			DColorEdit("Color##Desync", LDesyncArrowsColor);
	}
	X1Gui().Spacing();
	X1Gui().Separator();
	X1Gui().Spacing();
	DCheckBox("Show competitive rank", ShowCompetitiveRank);
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
	DCheckBox("Viewmodel XYZ", ViewModelXYZ);
	if (ViewModelXYZ)
	{
		X1Gui().PushItemWidth(PUSH_2);
		SliderFloats("ViewModel X", ViewModelX, -30, 30);
		SliderFloats("ViewModel Y", ViewModelY, -30, 30);
		SliderFloats("ViewModel Z", ViewModelZ, -30, 30);
	}
	X1Gui().Spacing();
	X1Gui().Separator();
	X1Gui().Spacing();
	DCheckBox("Aspect", Aspect);
	if (Aspect)
	{
		X1Gui().PushItemWidth(PUSH_2);
		SliderInts("Width", AspectWidth, 1, CGlobal::iScreenWidth);
		SliderInts("Height", AspectHeight, 1, CGlobal::iScreenHeight);
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
			DComboBox("Style##Hts", HitSoundStyle, itemsHSS);
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
	if (NoSmoke)
	{
		X1Gui().SameLine(SAME_LINE_1);
		X1Gui().PushItemWidth(PUSH_1);
		VectorEx<const char* >itemsCSS = { lolc("No draw"), lolc("Wireframe") };
		DComboBox("Type##NoSmoke", NoSmokeStyle, itemsCSS);
	}
	X1Gui().Spacing();
	X1Gui().Separator();
	X1Gui().Spacing();
	DCheckBox("Name stealer", NameStealer);
	X1Gui().Spacing();
	X1Gui().Separator();
	X1Gui().Spacing();
	DCheckBox("Clan tag spammer", ClanTagChanger);
	if (ClanTagChanger)
	{
		X1Gui().SameLine(SAME_LINE_1);
		X1Gui().PushItemWidth(PUSH_1);
		VectorEx<const char* >itemsCS = { lolc("None"),lolc("Static"), lolc("Dynamic 1"), lolc("Dynamic 2"), lolc("Dynamic 3"), lolc("Dynamic 4") };
		DComboBox("Type##ClanTag", ClanTagChangerStyle, itemsCS);
		static char ClanBuf[32] = { 0 };
		TextEdit("Text##ClanTag", ClanTagChangerText, ClanBuf, 32);
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
		VectorEx<const char* >itemsCS = { lolc("Textured"),lolc("Flat"), lolc("Metallic"), lolc("Metallic Plus"), lolc("Pearlescent"), lolc("Animated"), lolc("Disable") };
		DComboBox("Style##HandChams", HCStyle, itemsCS);
		if (HCStyle <= 5)
		{
			X1Gui().Spacing();
			X1Gui().SameLine(SAME_LINE_1);
			X1Gui().PushItemWidth(PUSH_1);
			VectorEx<const char* >itemsCSd = { lolc("None"),lolc("Wireframe") };
			DComboBox("Double##HandChams", HCDouble, itemsCSd);
		}
		DColorEdit("Color##HandChams", HandChamsColor);
	}
	X1Gui().Spacing();
	X1Gui().Separator();
	X1Gui().Spacing();
	DCheckBox("Hand glow", HandGlow);
	if (HandGlow)
	{
		X1Gui().SameLine(SAME_LINE_1);
		X1Gui().PushItemWidth(PUSH_1);
		VectorEx<const char*>itemsCS = { lolc("Default"), lolc("Static pulse"), lolc("Dynamic pulse") };
		DComboBox("Style##HandGlow", HGStyle, itemsCS);
		DColorEdit("Color##HandGlow", HandGlowColor);
		if (HGStyle == 2)
		{
			X1Gui().PushItemWidth(PUSH_2);
			SliderInts("Speed##HandGlow", HGPSpeed, 1, 15);
			SliderFloats("Range##HandGlow", HGPRange, 0.1, 1)
		}
	}
	X1Gui().Spacing();
	X1Gui().Separator();
	X1Gui().Spacing();
	DCheckBox("Weapon chams", WeaponChams);
	if (WeaponChams)
	{
		X1Gui().SameLine(SAME_LINE_1);
		X1Gui().PushItemWidth(PUSH_1);
		VectorEx<const char* >itemsCS = { lolc("Textured"),lolc("Flat"), lolc("Metallic"), lolc("Metallic Plus"), lolc("Pearlescent"), lolc("Animated"), lolc("Disable") };
		DComboBox("Style##WeaponChams", WCStyle, itemsCS);
		if (WCStyle <= 5)
		{
			X1Gui().Spacing();
			X1Gui().SameLine(SAME_LINE_1);
			X1Gui().PushItemWidth(PUSH_1);
			VectorEx<const char* >itemsCSd = { lolc("None"),lolc("Wireframe") };
			DComboBox("Double##WeaponChams", WCDouble, itemsCSd);
		}
		DColorEdit("Color##WeaponChams", WeaponChamsColor);
	}
	X1Gui().Spacing();
	X1Gui().Separator();
	X1Gui().Spacing();
	DCheckBox("Weapon glow", WeaponGlow);
	if (WeaponGlow)
	{
		X1Gui().SameLine(SAME_LINE_1);
		X1Gui().PushItemWidth(PUSH_1);
		VectorEx<const char*>itemsCS = { lolc("Default"), lolc("Static pulse"), lolc("Dynamic pulse") };
		DComboBox("Style##WeaponGlow", WGStyle, itemsCS);
		DColorEdit("Color##WeaponGlow", WeaponGlowColor);
		if (WGStyle == 2)
		{
			X1Gui().PushItemWidth(PUSH_2);
			SliderInts("Speed##WeaponGlow", WGPSpeed, 1, 15);
			SliderFloats("Range##WeaponGlow", WGPRange, 0.1, 1)
		}
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
			SliderFloats("Show Time##damage", DamageInfoShowTime, 0.1, 10);
			SliderInts("Position X##damage", DamageInfoPosX, 1, CGlobal::iScreenWidth);
			SliderInts("Position Y##damage", DamageInfoPosY, 1, CGlobal::iScreenHeight);
		}
		else if (DamageInfoPosition == 1)
		{
			SliderInts("Height##damage", DamageInfoHeight, 1, 100);
			SliderInts("Speed##damage", DamageInfoSpeed, 1, 100);
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
	DCheckBox("Fakelag", FakeLag);
	if (FakeLag)
	{
		X1Gui().SameLine(SAME_LINE_1);
		X1Gui().PushItemWidth(PUSH_1);
		VectorEx<const char* >itemsCSS = { lolc("Switch"), lolc("Static"), lolc("Adaptive"), lolc("Random"), lolc("Legit peek") };
		DComboBox("Type##FakeLag", FakeLagType, itemsCSS);
		X1Gui().PushItemWidth(PUSH_2);
		SliderInts("Factor##FakeLag", FakeLagFactor, 0, 15);
		DCheckBox("Standing", FakeLagStanding);
		X1Gui().SameLine();
		DCheckBox("Moving", FakeLagMoving);
		X1Gui().SameLine();
		DCheckBox("Unducking", FakeLagUnducking);
		DCheckBox("Bind##FakeLag", FakeLagBind.Enable);
		if (FakeLagBind.Enable)
		{
			X1Gui().SameLine();
			X1Gui().PushItemWidth(PUSH_1);
			HotsKey("Button##FakeLag", FakeLagBind.Button);
			X1Gui().SameLine();
			DCheckBox("Hold##FakeLag", FakeLagBind.Hold);
		}
	}
	X1Gui().Spacing();
	X1Gui().Separator();
	X1Gui().Spacing();
	DCheckBox("Colored walls", ColoredWalls);
	if (ColoredWalls)
	{
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
	X1Gui().Spacing();
	X1Gui().Separator();
	X1Gui().Spacing();
	DCheckBox("Auto block", AutoBlock);
	if (AutoBlock)
	{
		X1Gui().SameLine();
		DCheckBox("Bind##AutoBlock", AutoBlockBind.Enable);
		if (AutoBlockBind.Enable)
		{
			X1Gui().PushItemWidth(PUSH_1);
			HotsKey("Button##AutoBlock", AutoBlockBind.Button);
			X1Gui().SameLine();
			DCheckBox("Hold##AutoBlock", AutoBlockBind.Hold);
		}
	}
}

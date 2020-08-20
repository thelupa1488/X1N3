#include "Esp.h"
#include  "../../GUI/Gui.h"

#define SAME_LINE_1 115
#define SAME_LINE_2 230

#define PUSH_1 200
#define PUSH_2 400

void CEsp::Menu()
{
	auto LMenu = [&]()->void
	{
		static int VisType = 0;

		VectorEx<const char*>VisArr = { lolc("Player ESP"), lolc("Other ESP") };
		TabsLabels(VisType, VisArr, Vec2(320, 19), false);

		X1Gui().SameLine(325);

		if (X1Gui().Button(ShowPreview ? XorStr("Preview >>>") :
			XorStr("Preview <<<"), Vec2(136, 19)))
			ShowPreview = !ShowPreview;

		X1Gui().Spacing();
		X1Gui().Separator();
		X1Gui().Spacing();

		if (VisType == 1)
		{
			X1Gui().PushItemWidth(PUSH_1);

			DCheckBox("Grenades", WorldGrenade);
			if (WorldGrenade)
			{
				X1Gui().SameLine(SAME_LINE_1);
				X1Gui().PushItemWidth(PUSH_1);
				VectorEx<const char*>itemsGS = { lolc("Text") , lolc("Circle"), lolc("Icon") };
				DComboBox("Style##grenade", WorldGrenadeStyle, itemsGS);

				if (WorldGrenadeStyle != 1)
				{
					X1Gui().PushItemWidth(PUSH_2);
					SliderInts("Text size##gre", TextGrenadeSize, 9, MAX_FONT_SIZE);
				}
				X1Gui().Spacing();

				DColorEdit("High explosive grenade", HEGrenadeColor);
				X1Gui().SameLine(SAME_LINE_2);
				DColorEdit("Molotov", MolotovGrenadeColor);

				DColorEdit("Flashbang", FlashGrenadeColor);
				X1Gui().SameLine(SAME_LINE_2);
				DColorEdit("Incendiary grenade", IncGrenadeColor);

				DColorEdit("Smoke grenade", SmokeGrenadeColor);
				X1Gui().SameLine(SAME_LINE_2);
				DColorEdit("Decoy grenade", DecoyGrenadeColor);
			}
			X1Gui().Spacing();
			X1Gui().Separator();
			X1Gui().Spacing();
			DCheckBox("Weapons", WorldWeapons);
			if (WorldWeapons)
			{
				X1Gui().SameLine(SAME_LINE_1);
				X1Gui().PushItemWidth(PUSH_1);
				VectorEx<const char*>itemsWS = { lolc("Text"), lolc("Icon") };
				DComboBox("Style##weapon", WorldWeaponsStyle, itemsWS);

				X1Gui().PushItemWidth(PUSH_2);
				SliderInts("Text size##weapon",TextWorldWeaponSize, 9, MAX_FONT_SIZE);

				X1Gui().Spacing();
				DColorEdit("Color##weapon", WorldWeaponsColor);
			}
			X1Gui().Spacing();
			X1Gui().Separator();
			X1Gui().Spacing();
			DCheckBox("Bomb", WorldBomb);
			if (WorldBomb)
			{
				X1Gui().SameLine(SAME_LINE_1);
				X1Gui().PushItemWidth(PUSH_1);
				VectorEx<const char*>itemsBS = { lolc("Text"), lolc("Icon") };
				DComboBox("Style##bomb", WorldBombStyle, itemsBS);

				X1Gui().PushItemWidth(PUSH_2);
				SliderInts("Text size##bomb", TextBombSize, 9, MAX_FONT_SIZE);

				X1Gui().Spacing();
				DColorEdit("Color##bomb", WorldBombColor);
			}
			DCheckBox("Bomb info", WorldBombInfo);
			X1Gui().Spacing();
			X1Gui().Separator();
			X1Gui().Spacing();
			DCheckBox("Grenade trajectory", GranadePrediction);
			if (GranadePrediction)
			{
				X1Gui().Spacing();
				DColorEdit("Color##trajgr", GranadePredictionColor);
			}
		}
		else if (VisType == 0)
		{

			DCheckBox("Enemy##Esp", Enemy);
			X1Gui().SameLine(SAME_LINE_1);
			DCheckBox("Team##Esp", Team);
			X1Gui().SameLine(SAME_LINE_2);
			DCheckBox("Visible only##Esp", BoxVisibleOnly);
			X1Gui().PushItemWidth(100);
			DCheckBox("Bind##Esp", BindEnable.Enable);
			if (BindEnable.Enable)
			{
				X1Gui().SameLine(SAME_LINE_1);
				DCheckBox("Hold##Esp", BindEnable.Hold);
				X1Gui().SameLine(SAME_LINE_2);
				HotsKey("Button##Esp", BindEnable.Button);
			}

			X1Gui().Spacing();
			X1Gui().Separator();
			X1Gui().Spacing();

			X1Gui().PushItemWidth(PUSH_1);

			DCheckBox("Box", BoxEnable);
			if (BoxEnable)
			{
				X1Gui().SameLine(SAME_LINE_1);
				X1Gui().PushItemWidth(PUSH_1);
				VectorEx<const char*>itemsBS = { lolc("Full") , lolc("Angular"), lolc("3D"), lolc("Circled") };
				DComboBox("Style##Box", BoxStyle, itemsBS);
				if (BoxStyle != 2)
				{
					X1Gui().Spacing();
					X1Gui().PushItemWidth(PUSH_2);
					SliderInts("Size##Box", BoxSize, 1, 20);
				}
				X1Gui().PushItemWidth(PUSH_1);
				X1Gui().Spacing();
				DCheckBox("Outline##Box", BoxOutline);
				X1Gui().Spacing();

				DColorEdit("CT color##Box", BoxCT);
				X1Gui().SameLine(100);
				DColorEdit("T color##Box", BoxTT);

				X1Gui().SameLine(200);

				DColorEdit("Visible CT color##Box", BoxVisibleCT);
				X1Gui().SameLine(340);
				DColorEdit("Visible T color##Box", BoxVisibleTT);
			}

			X1Gui().Spacing();
			X1Gui().Separator();
			X1Gui().Spacing();

			DCheckBox("Fill box", FillBox);
			if (FillBox)
			{
				X1Gui().SameLine(SAME_LINE_2);
				DColorEdit("Color##fillbox", FillBoxColor);
			}

			X1Gui().Spacing();
			X1Gui().Separator();
			X1Gui().Spacing();

			DCheckBox("Chams", Chams);
			if (Chams)
			{
				X1Gui().SameLine(SAME_LINE_1);
				X1Gui().PushItemWidth(PUSH_1);
				VectorEx<const char*>itemsCSVis = { lolc("Textured"), lolc("Flat"), lolc("Wireframe"), lolc("Metallic"), lolc("Pearlescent"), lolc("Animated") };
				DComboBox("Style##Chams", ChamsStyle, itemsCSVis);
				X1Gui().SameLine(SAME_LINE_1 + PUSH_1 + 40);
				DCheckBox("Visible only##Chams", ChamsVisibleOnly);

				DColorEdit("CT color##Chams", ChamsCT);
				X1Gui().SameLine(100);
				DColorEdit("T color##Chams", ChamsTT);
				X1Gui().SameLine(200);
				DColorEdit("Visible CT color##Chams", ChamsVisibleCT);
				X1Gui().SameLine(340);
				DColorEdit("Visible T color##Chams", ChamsVisibleTT);
			}

			X1Gui().Spacing();
			X1Gui().Separator();
			X1Gui().Spacing();

			DCheckBox("Glow", Glow)
				if (Glow)
				{
					X1Gui().SameLine(SAME_LINE_1);
					X1Gui().PushItemWidth(PUSH_1);
					VectorEx<const char*>itemsCS = { lolc("Default"), lolc("Static pulse"), lolc("Dynamic pulse") };
					DComboBox("Style##Glow", GlowStyle, itemsCS);
					X1Gui().SameLine(SAME_LINE_1 + PUSH_1 + 40);
					DCheckBox("Visible only##Glow", GlowVisibleOnly);

					DColorEdit("CT color##Glow", GlowCT);
					X1Gui().SameLine(100);
					DColorEdit("T color##Glow", GlowTT);
					X1Gui().SameLine(200);
					DColorEdit("Visible CT color##Glow", GlowVisibleCT);
					X1Gui().SameLine(340);
					DColorEdit("Visible T color##Glow", GlowVisibleTT);
					if (GlowStyle == 2)
					{
						X1Gui().PushItemWidth(PUSH_2);
						SliderInts("Speed", GlowPulseSpeed, 1, 15);
						SliderFloats("Range", GlowPulseRange, 0, 1, "%.2f");
					}
				}

			X1Gui().Spacing();
			X1Gui().Separator();
			X1Gui().Spacing();

			DCheckBox("Health", Health);
			X1Gui().SameLine(SAME_LINE_1);
			DCheckBox("Armor", Armor);
			X1Gui().Spacing();
			X1Gui().Separator();
			X1Gui().Spacing();
			DCheckBox("Name", Name);
			DCheckBox("Distance", Distance);
			DCheckBox("Weapon", Weapon);
			X1Gui().SameLine(SAME_LINE_1);
			DCheckBox("Ammo", Ammo);
			DCheckBox("Money", Money);
			X1Gui().Spacing();
			X1Gui().Separator();
			X1Gui().Spacing();
			DCheckBox("Flashed", Flashing);
			X1Gui().SameLine();
			DCheckBox("Defusing", Defusing);
			X1Gui().SameLine();
			DCheckBox("Scoped", Scope);
			X1Gui().Spacing();
			X1Gui().Separator();
			X1Gui().Spacing();

			DCheckBox("Head", HeadEsp);
			if (HeadEsp)
			{
				X1Gui().SameLine(SAME_LINE_1);
				DColorEdit("Color##head", HeadEspColor);
			}

			DCheckBox("Line", Line);
			if (Line)
			{
				X1Gui().SameLine(SAME_LINE_1);
				DColorEdit("Color##line", LineColor);
			}

			DCheckBox("Skeleton", Skeleton);
			if (Skeleton)
			{
				X1Gui().SameLine(SAME_LINE_1);
				DColorEdit("Color##skel", SkeletonColor);
			}
			X1Gui().Spacing();
			X1Gui().Separator();
			X1Gui().Spacing();
			DCheckBox("Sound Esp", SoundEspEnable);
			if (SoundEspEnable)
			{
				X1Gui().SameLine(SAME_LINE_1);
				DColorEdit("Color##Sound", SoundColor);
				X1Gui().SameLine(200);
				VectorEx<const char*>itemsSE = { lolc("Circle") , lolc("Dynamic Circle(+)"), lolc("Dynamic Circle(-)"), lolc("Box"),lolc("Filled Box"), lolc("Star") };
				X1Gui().PushItemWidth(PUSH_1);
				DComboBox("Style##Sound", SoundEspStyle, itemsSE);

				X1Gui().Spacing();
				X1Gui().PushItemWidth(PUSH_2);
				SliderInts("Size##Sound", SoundEspSize, 1, 100);
				X1Gui().PushItemWidth(PUSH_1);
				X1Gui().Spacing();
				DCheckBox("Distance Text##sound", SoundEspDistance);
				if (SoundEspDistance)
				{
					X1Gui().SameLine(SAME_LINE_2);
					DColorEdit("Color##SoundDistance", SoundDistanceColor);

					X1Gui().PushItemWidth(PUSH_2);
					SliderInts("Text Size##Sound", TextSoundSize, 9, MAX_FONT_SIZE);

				}
			}
		}
	};
	LMenu();
}

#define iText(text)

void CEsp::VisualPreview()
{
	static MoveStruct *MV_Hp = &MVItemList[MI_HEALTH_BAR];
	static MoveStruct *MV_Armor = &MVItemList[MI_ARMOR_BAR];
	static MoveStruct *MV_Hp_Text = &MVItemList[MI_HEALTH_TEXT];
	static MoveStruct *MV_Armor_Text = &MVItemList[MI_ARMOR_TEXT];
	static MoveStruct *MV_Name = &MVItemList[MI_NAME_TEXT];
	static MoveStruct *MV_Weapon = &MVItemList[MI_WEAPON_TEXT];
	static MoveStruct *MV_Ammo = &MVItemList[MI_AMMO_TEXT];
	static MoveStruct *MV_Distance = &MVItemList[MI_DISTANCE_TEXT];
	static MoveStruct *MV_Money = &MVItemList[MI_MONEY_TEXT];
	static MoveStruct *MV_Scope = &MVItemList[MI_SCOPE_TEXT];
	static MoveStruct *MV_Flashed = &MVItemList[MI_FLASHED_TEXT];
	static MoveStruct *MV_Defusing = &MVItemList[MI_DEFUSING_TEXT];

	Vec2 ZoneStartPos = X1Gui().GetCursorPosEx();

	CustomVisuals(ZoneStartPos);

	if ((MITypes)MoveStruct::LastActive == MI_AMMO_TEXT)
	{
		iText("Selected: Ammo");

		X1Gui().Spacing();
		X1Gui().Separator();
		X1Gui().Spacing();
		VectorEx<const char*>itemsGS = { lolc("Type 1") ,lolc("Type 2"), lolc("Type 3") };
		DComboBox("Style", AmmoStyle, itemsGS);
		X1Gui().Spacing();
		X1Gui().Separator();
		X1Gui().Spacing();
		SliderInts("Text size", TextAmmoSize, 9, MAX_FONT_SIZE);
		X1Gui().Spacing();
		X1Gui().Separator();
		X1Gui().Spacing();
		DColorEdit("Color", AmmoColor);
	}
	else if ((MITypes)MoveStruct::LastActive == MI_ARMOR_TEXT)
	{
		iText("Selected: Armor");

		X1Gui().Spacing();
		X1Gui().Separator();
		X1Gui().Spacing();

		int OldStyle = ArmorStyle;

		VectorEx<const char*>NumStyle = { lolc("Line") , lolc("Text") };

		DComboBox("Style", ArmorStyle, NumStyle);
		X1Gui().Spacing();
		X1Gui().Separator();
		X1Gui().Spacing();
		SliderInts("Text size", TextArmorSize, 9, MAX_FONT_SIZE);

		if (OldStyle != ArmorStyle)
			MoveStruct::LastActive = MI_ARMOR_BAR;

		X1Gui().Spacing();
		X1Gui().Separator();
		X1Gui().Spacing();
		DColorEdit("Color", ArmorColor);
	}
	else if ((MITypes)MoveStruct::LastActive == MI_ARMOR_BAR)
	{
		iText("Selected: Armor");

		X1Gui().Spacing();
		X1Gui().Separator();
		X1Gui().Spacing();

		int OldStyle = ArmorStyle;

		VectorEx<const char*>NumStyle = { lolc("Line") , lolc("Text") };

		DComboBox("Style", ArmorStyle, NumStyle);


		if (OldStyle != ArmorStyle)
			MoveStruct::LastActive = MI_ARMOR_TEXT;

		X1Gui().Spacing();
		X1Gui().Separator();
		X1Gui().Spacing();

		DColorEdit("Main color", ArmorColor);
		DColorEdit("Background color", ArmorColor2);
		DColorEdit("Outline color", ArmorColor3);

		X1Gui().Spacing();
		X1Gui().Separator();
		X1Gui().Spacing();

		SliderInts("Separators", MV_Armor->NumParam1, 0, 10);
		SliderInts("Tickness", MV_Armor->NumParam2, 0, 20);

		X1Gui().Spacing();
		X1Gui().Separator();
		X1Gui().Spacing();
		DCheckBox("Background", MV_Armor->boolParam1);
		X1Gui().SameLine();
		DCheckBox("Outline", MV_Armor->boolParam2);
		X1Gui().SameLine();
		DCheckBox("Inverse", MV_Armor->boolParam3);
	}
	else if ((MITypes)MoveStruct::LastActive == MI_DISTANCE_TEXT)
	{
		iText("Selected: Selected");
		X1Gui().Spacing();
		X1Gui().Separator();
		X1Gui().Spacing();

		SliderInts("Text size", TextDistanceSize, 9, MAX_FONT_SIZE);
		X1Gui().Spacing();
		X1Gui().Separator();
		X1Gui().Spacing();
		DColorEdit("Color", DistanceColor);
	}
	else if ((MITypes)MoveStruct::LastActive == MI_HEALTH_TEXT)
	{
		iText("Selected: Health");

		X1Gui().Spacing();
		X1Gui().Separator();
		X1Gui().Spacing();

		VectorEx<const char*>NumStyle = { lolc("Line"), lolc("Text") };

		int OldStyle = HealthStyle;

		DComboBox("Style", HealthStyle, NumStyle);
		X1Gui().Spacing();
		X1Gui().Separator();
		X1Gui().Spacing();
		SliderInts("Text size", TextHealthSize, 9, MAX_FONT_SIZE);

		if (OldStyle != HealthStyle)
			MoveStruct::LastActive = MI_HEALTH_BAR;

		X1Gui().Spacing();
		X1Gui().Separator();
		X1Gui().Spacing();
		DColorEdit("Color", HealthColor);
	}
	else if ((MITypes)MoveStruct::LastActive == MI_HEALTH_BAR)
	{
		iText("Selected: Health");

		X1Gui().Spacing();
		X1Gui().Separator();
		X1Gui().Spacing();

		VectorEx<const char*>NumStyle = { lolc("Line"), lolc("Text") };

		int OldStyle = HealthStyle;

		DComboBox("Style", HealthStyle, NumStyle);

		if (OldStyle != HealthStyle)
			MoveStruct::LastActive = MI_HEALTH_TEXT;

		X1Gui().Spacing();
		X1Gui().Separator();
		X1Gui().Spacing();

		DColorEdit("Main Color", HealthColor);
		DColorEdit("Background Color", HealthColor2);
		DColorEdit("Outline Color", HealthColor3);
		X1Gui().Spacing();
		X1Gui().Separator();
		X1Gui().Spacing();

		SliderInts("Separators", MV_Hp->NumParam1, 0, 10);
		SliderInts("Tickness", MV_Hp->NumParam2, 0, 20);

		X1Gui().Spacing();
		X1Gui().Separator();
		X1Gui().Spacing();
		DCheckBox("Background", MV_Hp->boolParam1);
		X1Gui().SameLine();
		DCheckBox("Outline", MV_Hp->boolParam2);
		X1Gui().SameLine();
		DCheckBox("Inverse", MV_Hp->boolParam3);
	}
	else if ((MITypes)MoveStruct::LastActive == MI_NAME_TEXT)
	{
		iText("Selected: Name");

		X1Gui().Spacing();
		X1Gui().Separator();
		X1Gui().Spacing();

		SliderInts("Text size", TextNameSize, 9, MAX_FONT_SIZE);
		X1Gui().Spacing();
		X1Gui().Separator();
		X1Gui().Spacing();
		DColorEdit("Color", NameColor);

		X1Gui().Spacing();
		X1Gui().Separator();
		X1Gui().Spacing();

		DCheckBox("Background", NameBackground);

		X1Gui().Spacing();
		X1Gui().Separator();
		X1Gui().Spacing();

		if (NameBackground)
		{
			X1Gui().Spacing();
			DColorEdit("Background color", NameColorBack);
		}
	}
	else if ((MITypes)MoveStruct::LastActive == MI_WEAPON_TEXT)
	{
		iText("Selected: Weapon");
		X1Gui().Spacing();
		X1Gui().Separator();
		X1Gui().Spacing();
		VectorEx<const char*>itemsGS = { lolc("Text"), lolc("Icon") };
		DComboBox("Style", WeaponStyle, itemsGS);
		X1Gui().Spacing();
		X1Gui().Separator();
		X1Gui().Spacing();
		SliderInts("Text size", TextWeaponSize, 9, MAX_FONT_SIZE);
		X1Gui().Spacing();
		X1Gui().Separator();
		X1Gui().Spacing();
		DColorEdit("Color", WeaponColor);
	}
	else if ((MITypes)MoveStruct::LastActive == MI_MONEY_TEXT)
	{
		iText("Selected: Money");
		X1Gui().Spacing();
		X1Gui().Separator();
		X1Gui().Spacing();

		SliderInts("Text size", TextMoneySize, 9, MAX_FONT_SIZE);
		X1Gui().Spacing();
		X1Gui().Separator();
		X1Gui().Spacing();
		DColorEdit("Color", MoneyColor);
	}
	else if ((MITypes)MoveStruct::LastActive == MI_SCOPE_TEXT)
	{
		iText("Selected: Scoped");
		X1Gui().Spacing();
		X1Gui().Separator();
		X1Gui().Spacing();

		SliderInts("Text size", TextScopedSize, 9, MAX_FONT_SIZE);
		X1Gui().Spacing();
		X1Gui().Separator();
		X1Gui().Spacing();
		DColorEdit("Color", ScopeColor);
	}
	else if ((MITypes)MoveStruct::LastActive == MI_FLASHED_TEXT)
	{
		iText("Selected: Flashed");
		X1Gui().Spacing();
		X1Gui().Separator();
		X1Gui().Spacing();

		SliderInts("Text size", TextFlashedSize, 9, MAX_FONT_SIZE);
		X1Gui().Spacing();
		X1Gui().Separator();
		X1Gui().Spacing();
		DColorEdit("Color", FlashingColor);

	}
	else if ((MITypes)MoveStruct::LastActive == MI_DEFUSING_TEXT)
	{
		iText("Selected: Defusing");
		X1Gui().Spacing();
		X1Gui().Separator();
		X1Gui().Spacing();

		SliderInts("Text size", TextDefusingSize, 9, MAX_FONT_SIZE);
		X1Gui().Spacing();
		X1Gui().Separator();
		X1Gui().Spacing();
		DColorEdit("Color", DefusingColor);
	}

	float long_item_w = X1Gui().GetThis()->Info.Size.x - (X1Gui().GetStyle().wndPadding.x * 2);
	X1Gui().SetCursorPos(Vec2(X1Gui().GetStyle().wndPadding.x, 638), 0);
	if (X1Gui().Button(XorStr("Reset"), Vec2(long_item_w, 22)))
		MoveStruct::InitMItems = false;
}

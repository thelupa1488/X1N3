#include "GreandeHelper.h"
#include "../../GUI/Gui.h"

void CGHelper::ChangeGHI(GHInfo* info, char NameBuf[], char DescpBuf[], char MapName[], bool AdvMap)
{
	TextEdit("Name", info->name, NameBuf, 64);
	X1Gui().Spacing();
	X1Gui().Separator();
	X1Gui().Spacing();

	if (AdvMap)
	{
		static int SelecteMapMode = 0;

		VectorEx<const char*> itemsGHSS;
		itemsGHSS.push_back(XorStr("Auto"));
		itemsGHSS.push_back(XorStr("Custom"));

		for (size_t i(2); i < maps.size() + 2; i++)
		{
			itemsGHSS.push_back(maps[i - 2].game_name.c_str());
		}

		X1Gui().ComboBox(XorStr("Map"), &SelecteMapMode, itemsGHSS);

		if (SelecteMapMode == 1)
		{
			X1Gui().InputText(XorStr("Map Name"), MapName, 300);
		}
		else if (SelecteMapMode == 0)
		{
			strcpy(MapName, string(I::Engine()->GetLevelName()).c_str());
		}
		else
		{
			strcpy(MapName, itemsGHSS[SelecteMapMode]);
		}


		//delete[] itemsGHSS;
	}
	else
	{
		X1Gui().InputText(XorStr("Map Name"), MapName, 300);
	}
	X1Gui().Spacing();
	X1Gui().Separator();
	X1Gui().Spacing();
	if (!AdvMap)
	{

		VectorEx<const char*> itemsCS = { lolc("Incendiary grenade"), lolc("Molotov"), lolc("High explosive grenade"), lolc("Smoke grenade"), lolc("Decoy grenade"), lolc("Flashbang") };

		int bg = 0;

		switch (info->grenade)
		{
		case WEAPON_INCGRENADE: bg = 0; break;
		case WEAPON_MOLOTOV: bg = 1; break;
		case WEAPON_HEGRENADE: bg = 2; break;
		case WEAPON_SMOKEGRENADE: bg = 3; break;
		case WEAPON_DECOY: bg = 4; break;
		case WEAPON_FLASHBANG: bg = 5; break;
		default: break;
		}

		DComboBox("Grenade", bg, itemsCS);

		switch (bg)
		{
		case 0: info->grenade = WEAPON_INCGRENADE; break;
		case 1: info->grenade = WEAPON_MOLOTOV; break;
		case 2: info->grenade = WEAPON_HEGRENADE; break;
		case 3: info->grenade = WEAPON_SMOKEGRENADE; break;
		case 4: info->grenade = WEAPON_DECOY; break;
		case 5: info->grenade = WEAPON_FLASHBANG; break;
		default: break;
		}
	}
	else
	{
		VectorEx<const char*> itemsCS_ = { lolc("Auto"), lolc("Incendiary grenade"), lolc("Molotov"), lolc("High explosive grenade"), lolc("Smoke grenade"), lolc("Decoy grenade"), lolc("Flashbang") };

		int bg = 0;

		switch (info->grenade)
		{
		case WEAPON_NONE: bg = 0; break;
		case WEAPON_INCGRENADE: bg = 1; break;
		case WEAPON_MOLOTOV: bg = 2; break;
		case WEAPON_HEGRENADE: bg = 3; break;
		case WEAPON_SMOKEGRENADE: bg = 4; break;
		case WEAPON_DECOY: bg = 5; break;
		case WEAPON_FLASHBANG: bg = 6; break;
		default: break;
		}

		DComboBox("Grenade", bg, itemsCS_,);

		switch (bg)
		{
		case 0: info->grenade = WEAPON_NONE; break;
		case 1: info->grenade = WEAPON_INCGRENADE; break;
		case 2: info->grenade = WEAPON_MOLOTOV; break;
		case 3: info->grenade = WEAPON_HEGRENADE; break;
		case 4: info->grenade = WEAPON_SMOKEGRENADE; break;
		case 5: info->grenade = WEAPON_DECOY; break;
		case 6: info->grenade = WEAPON_FLASHBANG; break;
		default: break;
		}
	}
	X1Gui().Spacing();
	X1Gui().Separator();
	X1Gui().Spacing();
	SliderFloats("Direction X", info->directn.y, -179.9, 179.9);
	SliderFloats("Direction Y", info->directn.x, -179.9, 179.9);
};

void CGHelper::Menu()
{
	float long_item_w = X1Gui().GetThis()->Info.Size.x - (X1Gui().GetStyle().wndPadding.x * 2);

	DCheckBox("Enabled", Enable);

	X1Gui().SameLine();

	DCheckBox("Only for hand grenades", EnableFor1Grenade);

	X1Gui().Spacing();
	X1Gui().Separator();
	X1Gui().Spacing();
	DCheckBox("Show description", ShowDiscp);
	X1Gui().SameLine();
	DCheckBox("Show name", ShowName);
	X1Gui().Spacing();
	SliderFloats("Show info distance", DistShowInfo, 1, 400);
	SliderFloats("Show distance", DistShowHelp, 1, 2000);

	VectorEx<const char*> itemsCS = { lolc("Type 1"), lolc("Type 2") };

	DComboBox("Crosshair", CrosshairStyle, itemsCS,);

	X1Gui().Spacing();
	X1Gui().Separator();
	X1Gui().Spacing();

	static int Mode = 1;
	static GHInfo InfoProt;

	if (X1Gui().ListBoxHeader(XorStr("##GHelpList"), Vec2(long_item_w, 268)))
	{
		GuiStyle& style = X1Gui().GetStyle();

		Vec2 cur_menu_pos = X1Gui().GetCursorPos();
		Vec2 prev_pos_1 = Vec2(0, 0);
		Vec2 prev_pos_2 = Vec2(0, 0);

		auto CreateNode = [&](float cor_x, float len, bool check, Vec2 &prev) -> void
		{
			cur_menu_pos = X1Gui().GetCursorPosEx();
			Vec2 cur_pos = X1Gui().GetCursorPos();

			Vec2 next_pos = Vec2(cur_pos.x + len + cor_x, cur_pos.y);

			X1Gui().DrawLine(Vec2(cur_pos.x + cor_x, cur_pos.y + 9), Vec2(next_pos.x - 3, next_pos.y + 9), MainSettings().LineColor);
			X1Gui().DrawLine(Vec2(cur_pos.x + cor_x, (prev.y != 0) ? prev.y : (cur_pos.y - (check ? 9 : 3))), Vec2(cur_pos.x + cor_x, next_pos.y + 9), MainSettings().LineColor);

			prev = Vec2(cur_pos.x + cor_x, next_pos.y + 9);

			X1Gui().SetCursorPos(Vec2(cur_menu_pos.x + len + cor_x, cur_menu_pos.y), 0);
		};

		string CurrentMapName = I::Engine()->GetLevelName();

		for (int i = 0; i < maps.size(); i++)
		{
			CreateNode(3, 15, i != 0, prev_pos_1);

			bool selected_map = SelectedMap && SelectedMap == &maps[i];

			if (CurrentMapName == maps[i].game_name)
				style.clrText = Color::Green();

			bool tree_open = X1Gui().BeginTreeNode((maps[i].game_name + "##" + to_string(i)).c_str(), Vec2(long_item_w - 30, 0), false);
			if (X1Gui().IsItemClicked())
			{
				SelectedMap = &maps[i];
				SelectedGHInf = nullptr;
				Mode = 0;
			}

			if (CurrentMapName == maps[i].game_name)
				style.clrText = MainSettings().TextColor;

			if (tree_open)
			{
				for (int j = 0; j < maps[i].helpers.size(); j++)
				{
					X1Gui().Spacing();
					CreateNode(24, 20, j != 0, prev_pos_2);
					bool selected = SelectedGHInf && SelectedGHInf == &maps[i].helpers[j];

					if (X1Gui().SelectLabel((maps[i].helpers[j].name + XorStr(" (") + GetGName(maps[i].helpers[j].grenade) + XorStr(")##") + to_string((i + 1) + (j + 1))).c_str(),
						selected, Vec2(selected ? 305 : 395, 0)))
					{
						SelectedGHInf = &maps[i].helpers[j];
						SelectedMap = nullptr;
						Mode = 0;
					}

					if (selected)
					{
						X1Gui().SameLine();

						style.clrFrame = Color(MainSettings().FrameColor.r() + 18.f,
							MainSettings().FrameColor.g() + 18.f,
							MainSettings().FrameColor.b() + 18.f, 255);
						float old_pad_y = style.itmPadding.y;
						style.itmPadding.y = 0;

						DCheckBox("Enable", maps[i].helpers[j].enable);

						style.clrFrame = MainSettings().FrameColor;
						style.itmPadding.y = old_pad_y;
					}
				}
				prev_pos_2 = Vec2(0, 0);
			}

			X1Gui().Spacing();
		}
	}
	X1Gui().ListBoxFooter();

	X1Gui().Spacing();
	X1Gui().Separator();
	X1Gui().Spacing();

	VectorEx<const char*> itemsCSS = { lolc("Editing"), lolc("Adding") };

	TabsLabels(Mode, itemsCSS, Vec2(long_item_w, 20), false);

	X1Gui().Spacing();
	X1Gui().Separator();
	X1Gui().Spacing();

	if (Mode == 0)
	{
		auto RemvMapHelp = [&](Map* map, GHInfo* info) -> void
		{
			if (!map || !info)
				return;

			if (map->helpers.size() == 1)
			{
				DeleteMap(map->game_name);
				map = nullptr;
				info = nullptr;
			}
			else
			{
				DeleteHelp(info);
				info = nullptr;
			}
		};

		if (SelectedGHInf)
		{
			char NameBuf[64] = { 0 };
			char DescpBuf[300] = { 0 };
			char MapNameBuf[300] = { 0 };

			Map* CurMap = GetMapByHelp(SelectedGHInf);
			if (CurMap)
			{
				string OldName = CurMap->game_name;

				strcpy(MapNameBuf, CurMap->game_name.c_str());
				ChangeGHI(SelectedGHInf, NameBuf, DescpBuf, MapNameBuf, false);

				if (OldName != string(MapNameBuf))
				{
					GHInfo tempInfo = *SelectedGHInf;
					RemvMapHelp(CurMap, SelectedGHInf);
					Add(string(MapNameBuf), tempInfo);

					Map* NewMap = GetMapByGName(string(MapNameBuf));
					if (NewMap)
						SelectedGHInf = &NewMap->helpers.back();
				}

				X1Gui().Spacing();
				X1Gui().Separator();
				X1Gui().Spacing();

				if (X1Gui().Button(XorStr("Remove"), Vec2(long_item_w, 22)))
					if (CurMap)
						RemvMapHelp(CurMap, SelectedGHInf);
			}
		}
		if (SelectedMap)
		{
			char MapNameBuf[300] = { 0 };

			TextEdit("Map", SelectedMap->game_name, MapNameBuf, 300);

			if (SelectedMap->game_name.empty())
				SelectedMap->game_name = I::Engine()->GetLevelName();


			if (X1Gui().Button(XorStr("Remove"), Vec2(long_item_w, 22)))
			{
				while (SelectedMap)
				{
					if (SelectedMap->helpers.empty())
						SelectedMap = nullptr;
					else
						RemvMapHelp(SelectedMap, &SelectedMap->helpers[0]);
				}
			}
		}
	}
	else if (Mode == 1)
	{
		char NameBuf[64] = { 0 };
		char DescpBuf[300] = { 0 };
		char MapNameBuf[300] = { 0 };
		static string tempMapName = "";

		strcpy(MapNameBuf, tempMapName.c_str());
		ChangeGHI(&InfoProt, NameBuf, DescpBuf, MapNameBuf, true);
		tempMapName = MapNameBuf;

		X1Gui().Spacing();
		X1Gui().Separator();
		X1Gui().Spacing();

		if (X1Gui().Button(XorStr("Add"), Vec2(long_item_w, 22)))
		{
			AddHelp(tempMapName.empty() ? I::Engine()->GetLevelName() : tempMapName, InfoProt);

			InfoProt = GHInfo();
			SelectedGHInf = nullptr;
		}
	}
	X1Gui().Spacing();
	X1Gui().Separator();
	X1Gui().Spacing();
	if (X1Gui().Button(XorStr("Load"), Vec2(228, 22)))
	{
		if (LoadMaps());
	}
	X1Gui().SameLine();
	if (X1Gui().Button(XorStr("Save"), Vec2(228, 22)))
	{
		if (SaveMaps());
	}
	X1Gui().Spacing();
	X1Gui().Separator();
	X1Gui().Spacing();
	if (X1Gui().Button(XorStr("Reset"), Vec2(long_item_w, 22)))
	{
		maps.clear();
		SelectedGHInf = nullptr;
		SelectedMap = nullptr;
	}
}
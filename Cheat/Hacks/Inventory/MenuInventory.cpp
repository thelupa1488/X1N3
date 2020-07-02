#include "Inventory.h"
#include "../Setup.h"
#include "../../GUI/Gui.h"

#define lol(e)  string(XorStr(e))
#define lolc(e) XorStr(e)

string IGlovesModels[49] =
{
	lol("default"),
	lol("Sport Superconductor"),
	lol("Sport Pandora's Box"),
	lol("Sport Hedge Maze"),
	lol("Sport Arid"),
	lol("Sport Vice"),
	lol("Sport Omega"),
	lol("Sport Bronze Morph"),
	lol("Sport Amphibious"),
	lol("Moto Eclipse"),
	lol("Moto Spearmint"),
	lol("Moto Boom!"),
	lol("Moto Cool Mint"),
	lol("Moto Polygon"),
	lol("Moto Transport"),
	lol("Moto Turtle"),
	lol("Moto Pow"),
	lol("Specialist Crimson Kimono"),
	lol("Specialist Emerald Web"),
	lol("Specialist Foundation"),
	lol("Specialist Forest DDPAT"),
	lol("Specialist Mogul"),
	lol("Specialist Fade"),
	lol("Specialist Buckshot"),
	lol("Specialist Crimson Web"),
	lol("Driver Lunar Weave"),
	lol("Driver Convoy"),
	lol("Driver Crimson Weave"),
	lol("Driver Diamondback"),
	lol("Driver Racing Green"),
	lol("Driver Overtake"),
	lol("Driver Imperial Plad"),
	lol("Driver King Snake"),
	lol("Hand Wraps Leather"),
	lol("Hand Wraps Spruce DDPAT"),
	lol("Hand Wraps Badlands"),
	lol("Hand Wraps Slaughter"),
	lol("Hand Wraps Aboreal"),
	lol("Hand Wraps Duct Tape"),
	lol("Hand Wraps Overprint"),
	lol("Hand Wraps Cobalt Skulls"),
	lol("Bloodhound Charred"),
	lol("Bloodhound Snakebite"),
	lol("Bloodhound Bronzed"),
	lol("Bloodhound Guerrilla"),
	lol("Hydra Case Hardened"),
	lol("Hydra Rattler"),
	lol("Hydra Mangrove"),
	lol("Hydra Emerald")
};

int IPage = 0;

inline bool FindLower(string data, string find)
{
	if (find.empty())
		return true;
	transform(data.begin(), data.end(), data.begin(), ::tolower);
	transform(find.begin(), find.end(), find.begin(), ::tolower);

	if (data.find(find) != string::npos)
		return true;

	return false;
}
void CInventory::Menu()
{
	float long_item_w = X1Gui().GetThis()->Info.Size.x - (X1Gui().GetStyle().wndPadding.x * 2);
	auto SkinParams = [&](SkinSettings &Item) -> void
	{
		Inventory invBuffer;
		X1Gui().PushItemWidth(360);
		SliderFloats("Seed", Item.seed, 0.f, 2.f);
		SliderFloats("Wear", Item.wear, 0.f, 2.f, "%.9f");
		X1Gui().PushItemWidth(230);
		SliderInts("StatTrak", Item.stat_track, 0, 5000);
		X1Gui().SameLine();
		DCheckBox("Auto StatTrak", Item.auto_stat_track);

		X1Gui().PushItemWidth(360);

		vector<string> ItemsRarity = { lolc("Default"), lolc("Consumer"), lolc("Industrial"), lolc("Mil-Spec"), lolc("Restricted"), lolc("Classified") ,
	        lolc("Covert"), lolc("Contraband") };

		VectorEx<const char* > ItemsRR = { ItemsRarity[0].c_str(), ItemsRarity[1].c_str(), ItemsRarity[2].c_str(), ItemsRarity[3].c_str(), ItemsRarity[4].c_str(), ItemsRarity[5].c_str(),
			ItemsRarity[6].c_str(), ItemsRarity[7].c_str() };

		vector<string> ItemsQuality = { lolc("Default"), lolc("Genuine"), lolc("Vintage"), lolc("Knife Star"), lolc("Tournament"), lolc("Community") ,
	        lolc("Valve"), lolc("Prototype"), lolc("Customized"), lolc("StatTrak"), lolc("Complited") };

		VectorEx<const char* > ItemsQQ = { ItemsQuality[0].c_str(), ItemsQuality[1].c_str(), ItemsQuality[2].c_str(), ItemsQuality[3].c_str(), ItemsQuality[4].c_str(), ItemsQuality[5].c_str(),
			ItemsQuality[6].c_str(), ItemsQuality[7].c_str(), ItemsQuality[8].c_str(), ItemsQuality[9].c_str(), ItemsQuality[10].c_str() };

		DComboBox("Rarity", Item.rarity, ItemsRR);
		DComboBox("Quality", Item.quality, ItemsQQ);
		X1Gui().InputText(XorStr("Name##InvChr"), Item.custom_name, 32);
	};

	if (WeaponNames.size() > 0)
	{
		VectorEx<const char* > InvArr = { lolc("Weapon"), lolc("Knife"),lolc("Gloves"), lolc("Medals"), lolc ("Profile") };
		static int InvSettingsMode = 0;

		TabsLabels(InvSettingsMode, InvArr, Vec2(long_item_w-4,20), false);
		X1Gui().Spacing();

		if (InvSettingsMode == 0)
		{
			VectorEx<const char* > WeapSkinArr = { lolc("Skin##InventChanger"),lolc("Stickers##InventChanger") };
			static int WeapSkinSettingsMode = 0;

			TabsLabels(WeapSkinSettingsMode, WeapSkinArr, Vec2(long_item_w, 0), false);

			X1Gui().Spacing();
			X1Gui().Separator();
			X1Gui().Spacing();

			ItemSettings* WItem = &WeaponNames[InvSelectedWeapon];
			if (GP_Skins)
			{
				if (WeapSkinSettingsMode == 0)
				{
					ItemsList(WeaponNames, InvSelectedWeapon, Vec2(225, 389), XorStr("##AllWeapons"));
					WeaponPreview = WItem->CdnName;
					X1Gui().SameLine();
					X1Gui().BeginGroup();
					{
						X1Gui().PushItemWidth(185);
						VectorEx<const char* > ItemsSM = { lolc("All") , lolc("Distributed") };
						DComboBox("Skins##InventChanger", WItem->Skin.skins_mode, ItemsSM);
						static char FindBuf[128] = { 0 };
						static string FindSkin = "";
						TextEdit("Find##InventChanger", FindSkin, FindBuf, 128);
						X1Gui().Spacing();
						if (WItem->Skin.skins_mode == 0)
						{
							SkinsList(GP_Skins->skin_kits, WItem->Skin.paint_kit_menu, Vec2(221, 340), XorStr("##AllSkins"), FindSkin);
							WItem->Skin.paint_kit_id = GP_Skins->skin_kits[WItem->Skin.paint_kit_menu].id;
							GP_Skins->SkinPreview = GP_Skins->skin_kits[WItem->Skin.paint_kit_menu].cdn_name;
						}
						else if (WItem->Skin.skins_mode == 1)
						{
							if (GP_Skins->AllSkinsLoaded)
							{
								SortSkinsList(GP_Skins->SortedWeapons[InvSelectedWeapon].kits, WItem->Skin.paint_kit_menu, Vec2(221, 340), XorStr("##AllSkins"), FindSkin);
								if (WItem->Skin.paint_kit_menu < (int)GP_Skins->SortedWeapons[InvSelectedWeapon].kits.size())
								{
									WItem->Skin.paint_kit_id = GP_Skins->SortedWeapons[InvSelectedWeapon].kits[WItem->Skin.paint_kit_menu].kit;
									GP_Skins->SkinPreview = GP_Skins->SortedWeapons[InvSelectedWeapon].kits[WItem->Skin.paint_kit_menu].cdn_name;
								}
							}
							else
							{
								X1Gui().ListBoxHeader(XorStr("##AllSkinsEmpty"), Vec2(221, 340));
								X1Gui().Text(XorStr("Loading Skins..."));
								X1Gui().ListBoxFooter();
							}
						}
					}
					X1Gui().EndGroup();


					X1Gui().Spacing();

					SkinParams(WItem->Skin);
				}
				else if (WeapSkinSettingsMode == 1)
				{
					X1Gui().Spacing();
					X1Gui().PushItemWidth(192);
					X1Gui().Spacing();

					X1Gui().PushItemWidth(320);

					static int iSlot = 0;

					VectorEx<const char* > Slots = { lolc("1"),lolc("2"), lolc("3"), lolc("4") };
					DComboBox("Slot##InvChrSS", iSlot, Slots, Slots);

					static int StikersMode = 1;
					static int SortSelectedS = 0;

					VectorEx<const char* > ItemsSM = { lolc("All") ,lolc("Distributed") };
					DComboBox("Stickers##InvChrSS", StikersMode, ItemsSM);
					static char FindBuf[128] = { 0 };
					static string FindSticker = "";

					X1Gui().Spacing();

					StickerSettings* SItem = &WItem->Skin.Stickers[iSlot];

					if (StikersMode == 0)
					{
						TextEdit("Find##InvChrSS", FindSticker, FindBuf, 128);
						X1Gui().ListBoxHeader(XorStr("##StikerSerials"), Vec2(453, 326));
						for (size_t i = 0; i < GP_Skins->sticker_kits.size(); i++)
						{
							if (!FindLower(GP_Skins->sticker_kits[i].name, FindSticker))
								continue;

							bool selected = i == SItem->kit_menu_index;
							if (X1Gui().SelectLabel(GP_Skins->sticker_kits[i].name.c_str(), selected))
								SItem->kit_menu_index = i;
						}
						X1Gui().ListBoxFooter();
						SItem->kit = GP_Skins->sticker_kits[SItem->kit_menu_index].id;
					}
					else if (StikersMode == 1)
					{
						if (GP_Skins->AllSkinsLoaded)
						{
							X1Gui().ListBoxHeader(XorStr("##SortStikerSerials"), Vec2(71, 363));
							for (size_t i = 0; i < GP_Skins->SortedStickers.size(); i++)
							{
								bool selected = i == SortSelectedS;
								if (X1Gui().SelectLabel(GP_Skins->SortedStickers[i].sub_name.c_str(), selected))
									SortSelectedS = i;
							}
							X1Gui().ListBoxFooter();
							X1Gui().SameLine();
							X1Gui().BeginGroup();
							{
								TextEdit("Find##InvChrSS", FindSticker, FindBuf, 128);
								X1Gui().ListBoxHeader(XorStr("##StikerSerials"), Vec2(376, 340));
								for (size_t i = 0; i < GP_Skins->SortedStickers[SortSelectedS].Stckers.size(); i++)
								{
									if (!FindLower(GP_Skins->SortedStickers[SortSelectedS].Stckers[i].name, FindSticker))
										continue;

									bool selected = i == SItem->kit_menu_index;

									if (X1Gui().SelectLabel(GP_Skins->SortedStickers[SortSelectedS].Stckers[i].name.c_str(), selected))
										SItem->kit_menu_index = i;
								}
								X1Gui().ListBoxFooter();
							}
							X1Gui().EndGroup();

							if (SItem->kit_menu_index > 0 && SItem->kit_menu_index < (int)GP_Skins->SortedStickers[SortSelectedS].Stckers.size())
								SItem->kit = GP_Skins->SortedStickers[SortSelectedS].Stckers[SItem->kit_menu_index].id;
						}
						else
							X1Gui().Text(XorStr("Loading Stickers..."));
					}

					SliderFloats("Wear", SItem->wear, 0.f, 1.f);
					SliderFloats("Scale", SItem->scale, 0.f, 1.f);
					SliderFloats("Rotation", SItem->rotation, 0.f, 360);
				}
				

				if (X1Gui().Button(XorStr("ADD##Sticker"), Vec2(long_item_w, 22)))
				{
					Inventory invBuffer;
					invBuffer.ItemType = IT_WEAPON;

					invBuffer.Index = InventoryList.size() == 0 ? Inventory::LastIndex + 1 : InventoryList.back().Index + 1;
					if (invBuffer.Index < Inventory::LastIndex)
						invBuffer.Index += Inventory::LastIndex - invBuffer.Index;

					if (invBuffer.Index == Inventory::LastIndex)
						invBuffer.Index = Inventory::LastIndex + 1;

					invBuffer.Weapon = WItem->ID;
					invBuffer.WeaponSkinId = WItem->Skin.paint_kit_id;
					invBuffer.Wear = WItem->Skin.wear;
					invBuffer.Seed = WItem->Skin.seed;
					invBuffer.StatTrack = WItem->Skin.stat_track;
					invBuffer.AutoStatTrack = WItem->Skin.auto_stat_track;
					invBuffer.Rarity = WItem->Skin.rarity;
					invBuffer.Quality = WItem->Skin.quality;

					if (WItem->Skin.custom_name)
						snprintf(invBuffer.Name, 32, "%s", WItem->Skin.custom_name);

					for (int si(0); si < 5; si++)
					{
						invBuffer.Stickers[si] = WItem->Skin.Stickers[si];
					}

					invBuffer.WeaponName = WeaponNames[InvSelectedWeapon].Name;
					if (WItem->Skin.skins_mode == 0)
						invBuffer.SkinName = GP_Skins->skin_kits[WeaponNames[InvSelectedWeapon].Skin.paint_kit_menu].name_eng;
					else if (WItem->Skin.skins_mode == 1)
						invBuffer.SkinName = GP_Skins->SortedWeapons[InvSelectedWeapon].kits[WItem->Skin.paint_kit_menu].name;

					InventoryList.push_back(invBuffer);

					SendClientHello();
				}
			}
		}
		else if (InvSettingsMode == 1)
		{
			ItemsList(GP_Skins->KnifeNames, InvSelectedKnife, Vec2(225, 419), XorStr("##AllKnifes"));
			X1Gui().SameLine();

			if (GP_Skins)
			{
				ItemSettings* WItem = &GP_Skins->KnifeNames[InvSelectedKnife];

				WeaponPreview = WItem->CdnName;

				X1Gui().BeginGroup();
				{
					X1Gui().PushItemWidth(185);
					VectorEx<const char* > ItemsSM = { "All" , "Distributed" };
					DComboBox("Skins##InvChr", WItem->Skin.skins_mode, ItemsSM);
					static char FindBuf[128] = { 0 };
					static string FindSkin = "";
					TextEdit("Find##InvChr", FindSkin, FindBuf, 128);
					X1Gui().Spacing();
					if (WItem->Skin.skins_mode == 0)
					{
						SkinsList(GP_Skins->skin_kits, WItem->Skin.paint_kit_menu, Vec2(221, 370), XorStr("##AllKnifSkins"), FindSkin);
						WItem->Skin.paint_kit_id = GP_Skins->skin_kits[WItem->Skin.paint_kit_menu].id;
						SkinPreview = GP_Skins->skin_kits[WItem->Skin.paint_kit_menu].cdn_name;
					}
					else if (WItem->Skin.skins_mode == 1)
					{
						if (GP_Skins->AllSkinsLoaded)
						{
							SortSkinsList(GP_Skins->SortedKnives[InvSelectedKnife].kits, WItem->Skin.paint_kit_menu, Vec2(221, 370), XorStr("##AllKnifSkins"), FindSkin);
							if (WItem->Skin.paint_kit_menu < (int)GP_Skins->SortedKnives[InvSelectedKnife].kits.size())
							{
								WItem->Skin.paint_kit_id = GP_Skins->SortedKnives[InvSelectedKnife].kits[WItem->Skin.paint_kit_menu].kit;
								SkinPreview = GP_Skins->SortedKnives[InvSelectedKnife].kits[WItem->Skin.paint_kit_menu].cdn_name;
							}
						}
						else
						{
							X1Gui().ListBoxHeader(XorStr("##AllKnifSkinsEmpty"), Vec2(221, 370));
							X1Gui().Text(XorStr("Loading Skins..."));
							X1Gui().ListBoxFooter();
						}
					}
				}
				X1Gui().EndGroup();

				X1Gui().Spacing();

				SkinParams(WItem->Skin);

				if (X1Gui().Button(XorStr("ADD##Skins"), Vec2(long_item_w, 22)))
				{

					Inventory invBuffer;
					invBuffer.ItemType = IT_KNIFE;

					invBuffer.Index = InventoryList.size() == 0 ? Inventory::LastIndex + 1 : InventoryList.back().Index + 1;
					if (invBuffer.Index < Inventory::LastIndex)
						invBuffer.Index += Inventory::LastIndex - invBuffer.Index;

					if (invBuffer.Index == Inventory::LastIndex)
						invBuffer.Index = Inventory::LastIndex + 1;

					invBuffer.Weapon = WItem->ID;
					invBuffer.WeaponSkinId = WItem->Skin.paint_kit_id;
					invBuffer.Wear = WItem->Skin.wear;
					invBuffer.Seed = WItem->Skin.seed;
					invBuffer.StatTrack = WItem->Skin.stat_track;
					invBuffer.AutoStatTrack = WItem->Skin.auto_stat_track;
					invBuffer.Rarity = WItem->Skin.rarity;
					invBuffer.Quality = WItem->Skin.quality;

					if (WItem->Skin.custom_name)
						snprintf(invBuffer.Name, 32, "%s", WItem->Skin.custom_name);

					invBuffer.WeaponName = KnifeNames[InvSelectedKnife].Name;
					if (WItem->Skin.skins_mode == 0)
						invBuffer.SkinName = GP_Skins->skin_kits[KnifeNames[InvSelectedKnife].Skin.paint_kit_menu].name_eng;
					else if (WItem->Skin.skins_mode == 1)
						invBuffer.SkinName = GP_Skins->SortedKnives[InvSelectedKnife].kits[WItem->Skin.paint_kit_menu].name;

					InventoryList.push_back(invBuffer);

					SendClientHello();
				}
			}

			/*X1Gui().ListBoxHeader("##AllKnifes", Vec2(225, 424));
			for (size_t i = 0; i < KnifeNamesCT.size(); i++)
			{
				bool selected = i == InvSelectedKnife;
				if (X1Gui().Selectable((string(KnifeNamesCT[i].Name) + "##" + to_string(i)).c_str(), selected, 0, Vec2(150, 0)))
					InvSelectedKnife = i;
			}
			X1Gui().ListBoxFooter();
			if (InvSelectedKnife < KnifeNamesCT.size())
			{
				X1Gui().SameLine();
				X1Gui().ListBoxHeader("##AllKnifSkins", Vec2(225, 424));
				for (size_t i = 0; i < GP_Skins->skin_kits.size(); i++)
				{
					bool selected = i == KnifeNamesCT[InvSelectedKnife].Skin.paint_kit_menu;
					if (X1Gui().Selectable((GP_Skins->skin_kits[i].name + "##" + to_string(i)).c_str(), selected, 0, Vec2(150, 0)))
						KnifeNamesCT[InvSelectedKnife].Skin.paint_kit_menu = i;

					X1Gui().SameLine();

					if (X1Gui().Selectable(("| " + to_string(GP_Skins->skin_kits[i].id)).c_str(), selected, 0, Vec2(75, 0)))
						KnifeNamesCT[InvSelectedKnife].Skin.paint_kit_menu = i;
				}
				X1Gui().ListBoxFooter();

			}*/
			
		}
		else if (InvSettingsMode == 2)
		{
			X1Gui().ListBoxHeader(XorStr("##Gloves"), Vec2(long_item_w, 535));
			for (int i = 0; i < sizeof(IGlovesModels) / sizeof(IGlovesModels[0]); i++)
			{
				bool selected = i == InvSelectedGlove;
				if (X1Gui().SelectLabel(IGlovesModels[i].c_str(), selected))
					InvSelectedGlove = i;
			}
			X1Gui().ListBoxFooter();

			if (X1Gui().Button(XorStr("ADD##Gloves"), Vec2(long_item_w, 22)) && InvSelectedGlove != 0)
			{
				Inventory invBuffer;
				invBuffer.ItemType = IT_GLOVE;

				invBuffer.Index = InventoryList.size() == 0 ? Inventory::LastIndex + 1 : InventoryList.back().Index + 1;
				if (invBuffer.Index < Inventory::LastIndex)
					invBuffer.Index += Inventory::LastIndex - invBuffer.Index;

				if (invBuffer.Index == Inventory::LastIndex)
					invBuffer.Index = Inventory::LastIndex + 1;

				invBuffer.Weapon = GlovesSkin_Array[InvSelectedGlove - 1].ItemIndex;
				invBuffer.WeaponSkinId = GlovesSkin_Array[InvSelectedGlove - 1].PaintKit;

				invBuffer.Rarity = 6;
				invBuffer.Quality = 4;

				invBuffer.WeaponName = IGlovesModels[InvSelectedGlove];

				InventoryList.push_back(invBuffer);

				SendClientHello();
			}
		}
		else if (InvSettingsMode == 3)
		{
			static int SelectedMedal = 0;
			if (GP_Skins->AllSkinsLoaded)
			{
				X1Gui().ListBoxHeader(XorStr("##Medals"), Vec2(long_item_w, 535));
				for (size_t i = 0; i < Medals.size(); i++)
				{
					bool selected = i == SelectedMedal;
					if (X1Gui().SelectLabel(Medals[i].Name.c_str(), selected))
						SelectedMedal = i;
				}
				X1Gui().ListBoxFooter();
			}
			else
			{
				X1Gui().ListBoxHeader(XorStr("##MedalsEmpty"), Vec2(long_item_w, 535));
				X1Gui().Text(XorStr("Loading Medals..."));
				X1Gui().ListBoxFooter();
			}
			if (X1Gui().Button(XorStr("ADD##Medals"), Vec2(long_item_w, 22)))
			{
				Inventory invBuffer;
				invBuffer.ItemType = IT_MEDAL;

				invBuffer.Index = InventoryList.size() == 0 ? Inventory::LastIndex + 1 : InventoryList.back().Index + 1;
				if (invBuffer.Index < Inventory::LastIndex)
					invBuffer.Index += Inventory::LastIndex - invBuffer.Index;

				if (invBuffer.Index == Inventory::LastIndex)
					invBuffer.Index = Inventory::LastIndex + 1;

				invBuffer.WeaponName = Medals[SelectedMedal].Name;
				invBuffer.WeaponSkinId = Medals[SelectedMedal].Id;

				InventoryList.push_back(invBuffer);

				SendClientHello();
			}
		}
		else if (InvSettingsMode == 4)
		{
			VectorEx<const char* > RankList =
			{
				lolc("Unranked"),
				lolc("Silver - I"),
				lolc("Silver - II"),
				lolc("Silver - III"),
				lolc("Silver - IV"),
				lolc("Silver - Elite"),
				lolc("Silver - Elite Master"),
				lolc("Gold Nova - I"),
				lolc("Gold Nova - II"),
				lolc("Gold Nova - III"),
				lolc("Gold Nova - Master"),
				lolc("Master Guardian - I"),
				lolc("Master Guardian - II"),
				lolc("Master Guardian - Elite"),
				lolc("Distinguished Master Guardian"),
				lolc("Legendary Eagle"),
				lolc("Legendary Eagle Master"),
				lolc("Supreme Master First Class"),
				lolc("Global Elite")
			};

			DComboBox("Rank", ProfileRank, RankList);
			X1Gui().Spacing();
			X1Gui().Separator();
			X1Gui().Spacing();

			SliderInts("Private LVL", ProfileLevel, 1, 40);
			SliderInts("XP", ProfileXP, 1, 10000);
			X1Gui().Spacing();
			X1Gui().Separator();
			X1Gui().Spacing();
			SliderInts("Wins", ProfileWins, 1, 10000);
			X1Gui().Spacing();
			X1Gui().Separator();
			X1Gui().Spacing();
			SliderInts("Friendly", ProfileFriendly, 1, 10000);
			SliderInts("Leader", ProfileLeader, 1, 10000);
			SliderInts("Teacher", ProfileTeacher, 1, 10000);
			X1Gui().Spacing();
			X1Gui().Separator();
			X1Gui().Spacing();
			if (X1Gui().Button(XorStr("Update Profile"), Vec2(long_item_w, 22)))
			{
				SendMMHello();
			}
		}
	}
}

string GetStickerByIdx(int idx)
{
	string entry = "";
	if (GP_Skins->AllSkinsLoaded)
	{
		for (auto &v : GP_Skins->sticker_kits)
			if (v.id == idx)
				return v.name;
	}
	return entry;
}

void CInventory::InvListMenu()
{
	float long_item_w = X1Gui().GetThis()->Info.Size.x - (X1Gui().GetStyle().wndPadding.x * 2);
	static int InventSelectItem = 0;

	X1Gui().Text((XorStr("Items: ") + to_string(InventoryList.size())).c_str());

	X1Gui().ListBoxHeader(XorStr("##InventoryList"), Vec2(long_item_w, 390));
	for (size_t i = 0; i < InventoryList.size(); i++)
	{
		bool Select = i == InventSelectItem;

		if (X1Gui().SelectLabel((InventoryList[i].WeaponName + "##" + to_string(i)).c_str(), Select, Vec2(157, 0)))
			InventSelectItem = i;

		X1Gui().SameLine();

		if (X1Gui().SelectLabel(("| " + InventoryList[i].SkinName + " (" + to_string(InventoryList[i].WeaponSkinId) + ")" + "##" + to_string(i)).c_str(), Select))
			InventSelectItem = i;

	}
	X1Gui().ListBoxFooter();
	if (InventSelectItem >= (int)InventoryList.size())
		InventSelectItem = InventoryList.size() - 1;

	if ((int)InventoryList.size() > 0 && InventSelectItem > -1 && InventSelectItem < (int)InventoryList.size())
	{
		X1Gui().PushItemWidth(171);
		//VectorEx<const char* > InventoryTypes = { lolc(u8"Ширпотреб"), lolc(u8"Промышленное качество"),lolc(u8"Армейское качество"), lolc(u8"Запрещенное"),
		//	lolc(u8"Засекреченное"), lolc(u8"Тайное"), lolc(u8"Контрабанда") };
		//X1Gui().Combo(!MainSettings().Russian ? XorStr("Rarity") : XorStr(u8"Раритетность"), &InventoryList[InventSelectItem].Rarity, InventoryTypes, IM_ARRAYSIZE(InventoryTypes));
		////X1Gui().SameLine();
		//X1Gui().SliderFloat(!MainSettings().Russian ? XorStr("Quality") : XorStr(u8"Качество"), &InventoryList[InventSelectItem].Wear, 0.000f, 1.f, "%.9f");
		if (InventoryList[InventSelectItem].ItemType == IT_WEAPON)
		{
			X1Gui().Spacing();
			X1Gui().Separator();
			X1Gui().Spacing();

			X1Gui().Text("Stickers:");
			X1Gui().Text("Slot1: ");
			X1Gui().SameLine();
			X1Gui().Text(GetStickerByIdx(InventoryList[InventSelectItem].Stickers[0].kit).c_str());
			X1Gui().Text("Slot2: ");
			X1Gui().SameLine();
			X1Gui().Text(GetStickerByIdx(InventoryList[InventSelectItem].Stickers[1].kit).c_str());
			X1Gui().Text("Slot3: ");
			X1Gui().SameLine();
			X1Gui().Text(GetStickerByIdx(InventoryList[InventSelectItem].Stickers[2].kit).c_str());
			X1Gui().Text("Slot4: ");
			X1Gui().SameLine();
			X1Gui().Text(GetStickerByIdx(InventoryList[InventSelectItem].Stickers[3].kit).c_str());

			X1Gui().Spacing();
			X1Gui().Separator();
			X1Gui().Spacing();
		}

		if (X1Gui().Button(XorStr("Update Inventory"), Vec2(long_item_w, 22)))
			SendClientHello();

		X1Gui().Spacing();
		if (X1Gui().Button(XorStr("Remove"), Vec2(long_item_w, 22)))
		{
			InventoryList.erase(InventoryList.begin() + InventSelectItem);
			SendClientHello();
		}
		//X1Gui().SameLine();
		//if (X1Gui().Button(XorStr("Remove all"), Vec2(176, 22)) && InventoryList.size() > 0) //need fix
		//{
		//	InventoryList.clear();
		//	SendClientHello();
		//}

	}
}
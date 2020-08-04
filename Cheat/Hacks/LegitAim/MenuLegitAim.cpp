#include "LegitAim.h"
#include "../../GUI/Gui.h"

#define GetWeap(a) ((a < 0) ? 0 : (a >= GP_LegitAim->Weapons.size() ? GP_LegitAim->Weapons.size()-1 : a))

void CLegitAim::Menu()
{
	if (SelectedWeapon == -1)
		SelectedWeapon = 0;

	if (SelectedWeapon >= (int)Weapons.size())
		SelectedWeapon = 0;

	DCheckBox("Enabled", Enable);

	VectorEx<const char*> CustomTypes = { lolc("One weapon"),lolc("Standard subsections") , lolc("Custom subsections"), lolc("All weapons") };

	static int old_type = WeaponCustomTypes;
	X1Gui().SameLine(126);
	X1Gui().PushItemWidth(194);
	DComboBox("##pods", WeaponCustomTypes, CustomTypes);

	if (old_type != WeaponCustomTypes)
		SetSelectedWeapon(false);

	old_type = WeaponCustomTypes;

	string A_WeaponList_L = XorStr("Weapon list");
	string A_Subsections_L = XorStr("Subsections");

	if (WeaponCustomTypes == 0)
	{
		if (false)
			X1Gui().SameLine(331);
		else
			X1Gui().SameLine(351);

		if (X1Gui().Button(ShowWeaponList ? (A_WeaponList_L + XorStr(" <<<")).c_str() : (A_WeaponList_L + XorStr(" >>>")).c_str()))
			ShowWeaponList = !ShowWeaponList;
	}
	else if (WeaponCustomTypes == 1 || WeaponCustomTypes == 2)
	{
		if (false)
			X1Gui().SameLine(349);
		else
			X1Gui().SameLine(355);

		if (X1Gui().Button(ShowWeaponList ? (A_Subsections_L + XorStr(" <<<")).c_str() : (A_Subsections_L + XorStr(" >>>")).c_str()))
			ShowWeaponList = !ShowWeaponList;
	}
	else if (WeaponCustomTypes == 3)
	{
		ShowWeaponList = false;
	}

	X1Gui().Spacing();

	if (X1Gui().BeginChild(XorStr("MainChild"), Vec2(0, 180), true))
	{
		VectorEx<const char*> AimP = { lolc("Page 1"), lolc("Page 2") };
		static int SubtabAimMiscSelected = 0;

		TabsLabels(SubtabAimMiscSelected, AimP, Vec2(X1Gui().GetCurWindowSize().x - (X1Gui().GetStyle().wndPadding.x * 2), 0), false);
		if (SubtabAimMiscSelected == 0)
		{
			X1Gui().Spacing();
			DCheckBox("Aim at teammates##LegitAim", Deathmatch);

			X1Gui().SameLine(246);
			DCheckBox("Automatic fire##LegitAim", AutoFire);
			DCheckBox("Flash check##LegitAim", FlashCheck);

			X1Gui().SameLine(246);
			DCheckBox("Jump check##LegitAim", JumpCheck);
			DCheckBox("Smoke check##LegitAim", SmokeCheck);
			X1Gui().SameLine(246);
			DCheckBox("Enemy jump check##LegitAim", JumpEnemyCheck);

			X1Gui().Spacing();
			X1Gui().Spacing();
			X1Gui().Spacing();
			X1Gui().Separator();
			X1Gui().Spacing();
			X1Gui().Spacing();
			X1Gui().Spacing();

			DCheckBox("Draw FOV", DrawFov);

			X1Gui().SameLine(185.f);
			DColorEdit("Color##FovClr", FovColor);
			X1Gui().SameLine(246);

			DCheckBox("Show target", ShowSpot);

			DCheckBox("Draw silent FOV", DrawSilentFov);

			X1Gui().SameLine(185.f);
			DColorEdit("Color##SFovClr", SilentFovColor);

			X1Gui().SameLine(246);

			DCheckBox("Wall Check", WallCheck);
			
			if (SelectedWeapon <= 9 || WeaponCustomTypes == 3 || WeaponCustomTypes == 2 || WeaponCustomTypes == 1)
			{
				DCheckBox("Automatic pistol", Weapons[GetWeap(SelectedWeapon)].AutoPistol);
			}
			if (SelectedWeapon >= 30 || WeaponCustomTypes == 3 || WeaponCustomTypes == 2 || WeaponCustomTypes)
			{
				DCheckBox("Fast zoom", Weapons[GetWeap(SelectedWeapon)].FastZoom);
				X1Gui().SameLine(246);
				DCheckBox("Only Zoom", Weapons[GetWeap(SelectedWeapon)].OnlyZoom);
			}

		}
		else if (SubtabAimMiscSelected == 1)
		{
			X1Gui().Spacing();
			DCheckBox("Aim bind", AimBind.Enable);
			if (AimBind.Enable)
			{
				X1Gui().SameLine();
				DCheckBox("Hold", AimBind.Hold);
				X1Gui().Spacing();
				HotsKey("Button", AimBind.Button);
			}
			X1Gui().Spacing();
			X1Gui().Separator();
			X1Gui().Spacing();
			X1Gui().PushItemWidth(250.f);
			DCheckBox("FACEIT", FaceIt);
			if (FaceIt)
			{
				X1Gui().SameLine();
				SliderFloats("RCS correction", MouseSense, 0.0001, 8);
			}
			X1Gui().PushItemWidth(379);
			X1Gui().Spacing();
			X1Gui().Separator();
			X1Gui().Spacing();

			DCheckBox("Entity aim", EntityAim);
			if (EntityAim)
			{
				X1Gui().SameLine();
				DCheckBox("Show entity name", ShowEntitysName);
				static char ModelN[64] = { 0 };
				TextEdit("Target entity name", EntityTargetName, ModelN, 64);
			}
			X1Gui().PushItemWidth(379);
			X1Gui().Spacing();
			X1Gui().Separator();
			X1Gui().Spacing();

			DCheckBox("Legit Resolver", Resolver);
		//	X1Gui().Spacing();
		//	DCheckBox("Debug", Debug);
		}
	}
	X1Gui().EndChild();

	VectorEx<const char*> AimPSettings = { lolc("Basic"), lolc("RCS"), lolc("Silent"), lolc("Delays") };

	TabsLabels(SubTabAimSelected, AimPSettings, Vec2(X1Gui().GetCurWindowSize().x - (X1Gui().GetStyle().wndPadding.x * 2), 0), false);

	if (X1Gui().BeginChild(XorStr("Main2Child4"), Vec2(0, 215), true))
	{
		X1Gui().PushItemWidth(379.f);

		if (SubTabAimSelected == 0)
		{
			VectorEx<const char*> itemsSMF = { lolc("Deceleration of speed") , lolc("Constant speed") };
			DComboBox("Smooth factor", Weapons[GetWeap(SelectedWeapon)].SmoothMoveFactor, itemsSMF);

			if (Weapons[GetWeap(SelectedWeapon)].SmoothMethod == 0)
			{
				SliderFloats("Smooth", Weapons[GetWeap(SelectedWeapon)].Smooth, 0, 100);
			}
			else if (Weapons[GetWeap(SelectedWeapon)].SmoothMethod == 1)
			{

			}

			X1Gui().Spacing();
			X1Gui().Separator();
			X1Gui().Spacing();

			SliderFloats("Fov", Weapons[GetWeap(SelectedWeapon)].Fov, 0, 300, "");

			VectorEx<const char*> itemsFP = { lolc("Screen center") , lolc("Recoil"), lolc("On player") };
			DComboBox("FOV Pos", Weapons[GetWeap(SelectedWeapon)].FovPos, itemsFP);

			if (!EntityAim)
			{
				X1Gui().Spacing();
				X1Gui().Separator();
				X1Gui().Spacing();

				DCheckBox("Nearest", Weapons[GetWeap(SelectedWeapon)].Nearest);

				if (!Weapons[GetWeap(SelectedWeapon)].Nearest)
				{
					VectorEx<const char*> itemsHB = { lolc("Head"), lolc("Neck"), lolc("Low neck"), lolc("Body"), lolc("Thorax"), lolc("Chest"), lolc("Upper chest") };
					DComboBox("Hitbox", Weapons[GetWeap(SelectedWeapon)].HitBox, itemsHB);
				}

				if (!FaceIt)
				{
					X1Gui().Spacing();
					X1Gui().Separator();
					X1Gui().Spacing();

					DCheckBox("Backtrack", Weapons[GetWeap(SelectedWeapon)].Backtrack);
					if (Weapons[GetWeap(SelectedWeapon)].Backtrack)
					{
						X1Gui().SameLine(128.f);
						DCheckBox("Show backtrack", ShowBacktrack);
						if (ShowBacktrack)
						{
							X1Gui().Spacing();
							X1Gui().SameLine(128.f);
							X1Gui().PushItemWidth(175.f);
							VectorEx<const char*> itemsSBT = { lolc("All Ticks"), lolc("Last Tick") };
							DComboBox("Show Type##ShowBacktrack", ShowBacktrackType, itemsSBT);
							X1Gui().SameLine();
							DColorEdit("Color##ShowBacktrack", ShowBacktrackColor);
						}
						X1Gui().PushItemWidth(333.f);
						SliderInts("Time (Ms)", Weapons[GetWeap(SelectedWeapon)].BacktrackTimeLimit, 0, 200);
					}
				}
			}
		}
		else if (SubTabAimSelected == 1)
		{

			SliderFloats("RCS X", Weapons[GetWeap(SelectedWeapon)].RcsY, 0, 150);
			SliderFloats("RCS Y", Weapons[GetWeap(SelectedWeapon)].RcsX, 0, 150);

			X1Gui().Spacing();
			X1Gui().Spacing();
			if (false)
				X1Gui().PushItemWidth(260.f);

			SliderFloats("Smooth", Weapons[GetWeap(SelectedWeapon)].SmoothRcs, 0, 100);
			SliderFloats("FOV", Weapons[GetWeap(SelectedWeapon)].FovRcs, 0, 300);
			X1Gui().Spacing();
			X1Gui().Separator();
			X1Gui().Spacing();

			DCheckBox("Standalone RCS", Weapons[GetWeap(SelectedWeapon)].RcsStandelone);

			if (!EntityAim)
			{
				X1Gui().Spacing();
				X1Gui().Separator();
				X1Gui().Spacing();

				DCheckBox("Hitbox after first bullet", Weapons[GetWeap(SelectedWeapon)].HitBoxAfter1B);

				if (Weapons[GetWeap(SelectedWeapon)].HitBoxAfter1B)
				{
					DCheckBox("Nearest RCS", Weapons[GetWeap(SelectedWeapon)].NearestRcs);

					if (!Weapons[GetWeap(SelectedWeapon)].NearestRcs)
					{
						VectorEx<const char*> itemsHB = { lolc("Head"), lolc("Neck"), lolc("Low neck"), lolc("Body"), lolc("Thorax"), lolc("Chest"), lolc("Upper chest") };
						DComboBox("Hitbox", Weapons[GetWeap(SelectedWeapon)].HitBoxRcs, itemsHB);
					}
				}
			}
			X1Gui().PushItemWidth(333.f);
		}
		else if (SubTabAimSelected == 2)
		{
			if (!FaceIt)
			{
				DCheckBox("Silent", Weapons[GetWeap(SelectedWeapon)].Silent);
				SliderInts("% chance", Weapons[GetWeap(SelectedWeapon)].SilentHitchance, 0, 100);

				SliderFloats("FOV", Weapons[GetWeap(SelectedWeapon)].SilentFov, 0, 30,);

				if (!EntityAim)
				{
					X1Gui().Spacing();
					X1Gui().Separator();
					X1Gui().Spacing();

					DCheckBox("Nearest", Weapons[GetWeap(SelectedWeapon)].SilentNearest);

					if (!Weapons[GetWeap(SelectedWeapon)].SilentNearest)
					{
						VectorEx<const char*> itemsHB = { lolc("Head"), lolc("Neck"), lolc("Low neck"), lolc("Body"), lolc("Thorax"), lolc("Chest"), lolc("Upper chest") };
						DComboBox("Hitbox", Weapons[GetWeap(SelectedWeapon)].SilentHitBox, itemsHB);
					}

					X1Gui().Spacing();
					X1Gui().Spacing();
				}
				X1Gui().Spacing();
				X1Gui().Separator();
				X1Gui().Spacing();

				SliderInts("Start bullet", Weapons[GetWeap(SelectedWeapon)].SilentStartBullet, 0, 100);
				SliderInts("End bullet", Weapons[GetWeap(SelectedWeapon)].SilentEndBullet, 0, 100);
			}
		}
		else if (SubTabAimSelected == 3)
		{
			DCheckBox("Target switch delay", Weapons[GetWeap(SelectedWeapon)].TargetSwitchDelayEnable);

			if (Weapons[GetWeap(SelectedWeapon)].TargetSwitchDelayEnable)
				SliderFloats("Delay##tsw", Weapons[GetWeap(SelectedWeapon)].TargetSwitchDelay, 0, 1.f);

			X1Gui().Spacing();
			X1Gui().Separator();
			X1Gui().Spacing();

			DCheckBox("First bullet delay", Weapons[GetWeap(SelectedWeapon)].FirstFireDelayEnable);

			if (Weapons[GetWeap(SelectedWeapon)].FirstFireDelayEnable)
			{
				DCheckBox("One click delay", Weapons[GetWeap(SelectedWeapon)].FirstFireDelayOneClick);

				if (!EntityAim)
				{
					X1Gui().SameLine();
					DCheckBox("Auto", Weapons[GetWeap(SelectedWeapon)].FirstFireDelayAuto);
				}

				if (!FaceIt)
				{
					X1Gui().SameLine();
					DCheckBox("Silent auto delay", Weapons[GetWeap(SelectedWeapon)].FirstFireDelaySilentAuto);
				}

				SliderFloats("Delay##ffdef", Weapons[GetWeap(SelectedWeapon)].FirstFireDelay, 0, 1.f);
			}

			X1Gui().Spacing();
			X1Gui().Separator();
			X1Gui().Spacing();

			DCheckBox("Kill stop", Weapons[GetWeap(SelectedWeapon)].KillStop);
		}
	}
	X1Gui().EndChild();
	X1Gui().Spacing();
	
	if (X1Gui().BeginChild(XorStr("TriggerChild"), Vec2(0, 205), true))
	{
		static int SubtabTrigMiscSelected = 0;

		VectorEx<const char*> AimTrigSettings = { lolc("Basic##trigger"),  lolc("Bind##trigger") };

		TabsLabels(SubtabTrigMiscSelected, AimTrigSettings, Vec2(X1Gui().GetCurWindowSize().x - (X1Gui().GetStyle().wndPadding.x * 2), 0), false);

		X1Gui().Spacing();
		X1Gui().PushItemWidth(240.f);

		if (SubtabTrigMiscSelected == 0)
		{
			DCheckBox("Trigger", TriggerEnable);
			X1Gui().SameLine(163);
			DCheckBox("Aim at teammates", TriggerDeathmatch);

			X1Gui().SameLine(360);
			X1Gui().BeginGroup();
			{
				vector<string> TrigHitboxes =
				{
					lols("Head"), //0
					lols("Chest"), //1
					lols("Stomach"), //2
					lols("Left arm"), //3
					lols("Right arm"), //4
					lols("Left leg"), //5
					lols("Right leg") //6
				};
				if (X1Gui().ListBoxHeader("##TrigHitboxes", Vec2(90, 142)))
				{
					for (int i = 0; i < 7; i++)
					{
						bool selected = ((i == 0) && Weapons[GetWeap(SelectedWeapon)].TRIG_HITGROUP_HEAD) ||
							((i == 1) && Weapons[GetWeap(SelectedWeapon)].TRIG_HITGROUP_CHEST) ||
							((i == 2) && Weapons[GetWeap(SelectedWeapon)].TRIG_HITGROUP_STOMACH) ||
							((i == 3) && Weapons[GetWeap(SelectedWeapon)].TRIG_HITGROUP_LEFTARM) ||
							((i == 4) && Weapons[GetWeap(SelectedWeapon)].TRIG_HITGROUP_RIGHTARM) ||
							((i == 5) && Weapons[GetWeap(SelectedWeapon)].TRIG_HITGROUP_LEFTLEG) ||
							((i == 6) && Weapons[GetWeap(SelectedWeapon)].TRIG_HITGROUP_RIGHTLEG);

						if (X1Gui().SelectLabel(TrigHitboxes.at(i).c_str(), selected))
						{
							switch (i)
							{
							case 0: Weapons[GetWeap(SelectedWeapon)].TRIG_HITGROUP_HEAD = !Weapons[GetWeap(SelectedWeapon)].TRIG_HITGROUP_HEAD; break;
							case 1: Weapons[GetWeap(SelectedWeapon)].TRIG_HITGROUP_CHEST = !Weapons[GetWeap(SelectedWeapon)].TRIG_HITGROUP_CHEST; break;
							case 2: Weapons[GetWeap(SelectedWeapon)].TRIG_HITGROUP_STOMACH = !Weapons[GetWeap(SelectedWeapon)].TRIG_HITGROUP_STOMACH; break;
							case 3: Weapons[GetWeap(SelectedWeapon)].TRIG_HITGROUP_LEFTARM = !Weapons[GetWeap(SelectedWeapon)].TRIG_HITGROUP_LEFTARM; break;
							case 4: Weapons[GetWeap(SelectedWeapon)].TRIG_HITGROUP_RIGHTARM = !Weapons[GetWeap(SelectedWeapon)].TRIG_HITGROUP_RIGHTARM; break;
							case 5: Weapons[GetWeap(SelectedWeapon)].TRIG_HITGROUP_LEFTLEG = !Weapons[GetWeap(SelectedWeapon)].TRIG_HITGROUP_LEFTLEG; break;
							case 6: Weapons[GetWeap(SelectedWeapon)].TRIG_HITGROUP_RIGHTLEG = !Weapons[GetWeap(SelectedWeapon)].TRIG_HITGROUP_RIGHTLEG; break;
							default: break;
							}
						}
					}
				}
				X1Gui().ListBoxFooter();

				DCheckBox("All", Weapons[GetWeap(SelectedWeapon)].TriggerAllHitboxes);
			}
			X1Gui().EndGroup(true);

			DCheckBox("Flash check##Trigger", TriggerFlashCheck);
			X1Gui().SameLine(163);
			DCheckBox("Smoke check##Trigger", TriggerSmokeCheck);
			DCheckBox("Jump check##Trigger", TriggerJumpCheck);
			X1Gui().SameLine(163);
			DCheckBox("Enemy jump check##Trigger", TriggerJumpEnemyCheck);
			if (SelectedWeapon >= 30 || WeaponCustomTypes == 3 || WeaponCustomTypes == 2 || WeaponCustomTypes)
				DCheckBox("Only Zoom##Trigger", TriggerOnlyZoom);

			X1Gui().Spacing();

			SliderInts("RCS X##Trigger", Weapons[GetWeap(SelectedWeapon)].TriggerRcsX, 0, 150);
			SliderInts("RCS Y##Trigger", Weapons[GetWeap(SelectedWeapon)].TriggerRcsY, 0, 150);

			X1Gui().Spacing();

			SliderIntsProc("Hit chance##Trigger", Weapons[GetWeap(SelectedWeapon)].TriggerChanse, 0, 100);
			SliderFloats("Delay##Trigger", Weapons[GetWeap(SelectedWeapon)].TriggerDelay, 0, 1.f);
		}
		else if (SubtabTrigMiscSelected == 1)
		{
			DCheckBox("Bind##triggg", TriggerBind.Enable);
			if (TriggerBind.Enable)
			{
				X1Gui().SameLine();
				DCheckBox("Hold##triggg", TriggerBind.Hold);
				HotsKey("Button##triggg", TriggerBind.Button);
			}
		}
	}
	X1Gui().EndChild();
}

void CLegitAim::SubsectionsMenu()
{
	if (WeaponCustomTypes == 0)
	{
		if (SelectedWeapon == -1)
			SelectedWeapon = 0;

		static int selectedItem = SelectedWeapon;
		if (X1Gui().ListBoxHeader(XorStr("##0"), Vec2(154, 665 - 7)))
		{
			for (int i = 0; i < (sizeof(CGlobal::WeaponNames) / sizeof(*CGlobal::WeaponNames)); i++)
			{
				bool selected = i == SelectedWeapon;
				if (X1Gui().SelectLabel(CGlobal::WeaponNames[i].c_str(), selected, Vec2(144, 0)))
					SelectedWeapon = i;
			}
		}
		X1Gui().ListBoxFooter();
	}
	else if (WeaponCustomTypes == 1)
	{
		static int tabOrderCs[] = { 0 , 1 , 2 , 3 };

		VectorEx<const char*>tabNamesCs = { lolsc("Rifles"), lolsc("Pistols"), lolsc("Shotguns"), lolsc("Snipers") };

		Vec2 Pos = Vec2(0, 0);

		TabsLabels(StandardSubSelected, tabNamesCs, Vec2(X1Gui().GetCurWindowSize().x - (X1Gui().GetStyle().wndPadding.x * 2),
			X1Gui().GetCurWindowSize().y - (X1Gui().GetStyle().wndPadding.y * 2)), true);


		if (StandardSubSelected == 0)
			SelectedWeapon = 34;
		else if (StandardSubSelected == 1)
			SelectedWeapon = 35;
		else if (StandardSubSelected == 2)
			SelectedWeapon = 36;
		else if (StandardSubSelected == 3)
			SelectedWeapon = 37;
	}
	else if (WeaponCustomTypes == 2)
	{
		static char NewSubName[64] = { 't','e','s','t' };

		X1Gui().PushItemWidth(300);

		X1Gui().InputText(XorStr("Name"), NewSubName, 64);

		if (CustomSubs.size() < 33)
		{
			X1Gui().SameLine(365);
			if (X1Gui().Button(XorStr("Add"), Vec2(89, 0)) && string(NewSubName).length() > 0)
			{
				CustomSub  CustomEntry;
				CustomEntry.Idx = Weapons.size();
				CustomEntry.Name = NewSubName;
				CustomEntry.Name += XorStr("##") + to_string(CustomEntry.Idx);

				WeaponSettings WeaponEntry;
				WeaponEntry.WeaponName = CustomEntry.Name;
				WeaponEntry.IsCustomSub = true;

				CustomSubs.push_back(CustomEntry);
				Weapons.push_back(WeaponEntry);

				SelectedSub = CustomSubs.size() - 1;

				strcpy(NewSubName, "");
			}
		}

		if (SelectedSub < (int)CustomSubs.size() && SelectedSub >= 0)
		{
			if (X1Gui().Button(XorStr("Rename")))
			{
				if (string(NewSubName).length() > 0)
				{
					CustomSubs[SelectedSub].Name = NewSubName;
					strcpy(NewSubName, "");
				}
			}

			X1Gui().SameLine();
			if (X1Gui().Button(XorStr("Remove")))
			{
				for (size_t i = 0; i < CustomSubs[SelectedSub].AllocatedWeapon.size(); i++)
					UnallocatedWeapons.push_back(CustomSubs[SelectedSub].AllocatedWeapon[i]);

				for (size_t i = 0; i < Weapons.size(); i++)
					if (i == CustomSubs[SelectedSub].Idx)
					{
						for (size_t j(SelectedSub); j < CustomSubs.size(); j++)
							CustomSubs[j].Idx--;
						Weapons.erase(Weapons.begin() + i);
					}

				CustomSubs.erase(CustomSubs.begin() + SelectedSub);
			}

			X1Gui().Spacing();
			X1Gui().Separator();
			X1Gui().Spacing();

			if ((int)CustomSubs.size() <= SelectedSub)
				SelectedSub = CustomSubs.size() - 1;

			if (CustomSubs.size() > 0 && SelectedSub > -1)
			{
				if (SelectedSubAlloc < (int)CustomSubs[SelectedSub].AllocatedWeapon.size())
				{
					X1Gui().SameLine(155);
					if (X1Gui().Button(XorStr(">>>"), Vec2(148, 0)))
					{
						UnallocatedWeapons.push_back(CustomSubs[SelectedSub].AllocatedWeapon[SelectedSubAlloc]);
						CustomSubs[SelectedSub].AllocatedWeapon.erase(CustomSubs[SelectedSub].AllocatedWeapon.begin() + SelectedSubAlloc);
						if (SelectedSubAlloc > 0)
							SelectedSubAlloc--;
					}
				}

				if ((int)UnallocatedWeapons.size() > 0 && SelectedSubUnAlloc < (int)UnallocatedWeapons.size() && SelectedSubUnAlloc >= 0)
				{
					X1Gui().SameLine(310);
					if (X1Gui().Button(XorStr("<<<"), Vec2(144, 0)))
					{
						CustomSubs[SelectedSub].AllocatedWeapon.push_back(UnallocatedWeapons[SelectedSubUnAlloc]);
						UnallocatedWeapons.erase(UnallocatedWeapons.begin() + SelectedSubUnAlloc);

						if (SelectedSubUnAlloc > 0)
							SelectedSubUnAlloc--;
					}
				}
			}
		}

		if (CustomSubs.size() > 0)
		{
			if (X1Gui().ListBoxHeader(XorStr("##Subsections"), Vec2(149, 583)))
			{
				for (size_t i = 0; i < CustomSubs.size(); i++)
				{
					bool selected = i == SelectedSub;
					if (X1Gui().SelectLabel(CustomSubs[i].Name.c_str(), selected))
						SelectedSub = i;
				}
			}
			X1Gui().ListBoxFooter();

			X1Gui().SameLine();
			if (X1Gui().ListBoxHeader(XorStr("##SubsectionWeapons"), Vec2(149, 583)))
			{
				if (SelectedSub < (int)CustomSubs.size())
				{
					for (size_t i = 0; i < CustomSubs[SelectedSub].AllocatedWeapon.size(); i++)
					{
						bool selected = i == SelectedSubAlloc;
						if (X1Gui().SelectLabel(CustomSubs[SelectedSub].AllocatedWeapon[i].c_str(), selected))
							SelectedSubAlloc = i;
					}
				}
			}
			X1Gui().ListBoxFooter();

			X1Gui().SameLine();

			if (X1Gui().ListBoxHeader(XorStr("UnallocatedWeapons"), Vec2(146, 583)))
			{
				if (SelectedSubUnAlloc < (int)UnallocatedWeapons.size())
				{
					for (size_t i = 0; i < UnallocatedWeapons.size(); i++)
					{
						bool selected = i == SelectedSubUnAlloc;
						if (X1Gui().SelectLabel(UnallocatedWeapons[i].c_str(), selected))
							SelectedSubUnAlloc = i;
					}
				}
			}
			X1Gui().ListBoxFooter();

			if (SelectedSub < (int)CustomSubs.size())
				if (CustomSubs[SelectedSub].Idx < (int)Weapons.size())
					SelectedWeapon = CustomSubs[SelectedSub].Idx;
				else
					SelectedWeapon = 0;
			else
				SelectedWeapon = 0;
		}
	}
}

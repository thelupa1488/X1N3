#include "Misc.h"
#include  "../Setup.h"
#include "../../GUI/Gui.h"
#include "../../Engine/SDK/protomessages.h"
#include "../../Engine/SDK/bfReader.hpp"

#define KEY_DOWN(VK_NNM) ((FastCall::G().t_GetAsyncKeyState(VK_NNM) & 0x8000) ? 1:0)

using namespace HookTables;

void CMisc::Draw()
{
	if (Enable)
	{
		CBaseEntity* plocal = (CBaseEntity*)I::EntityList()->GetClientEntity(I::Engine()->GetLocalPlayer());

		if (plocal)
		{
			CBaseWeapon* pWeapon = plocal->GetBaseWeapon();

			if (pWeapon)
			{
				if (Crosshair)
				{
					if (CGlobal::GWeaponType != WEAPON_TYPE_SNIPER)
					{
						float punch_x = !CrosshairRecoil ? (CGlobal::iScreenWidth / 2.f) : 
							((CGlobal::iScreenWidth / 2) - (int)((CGlobal::iScreenWidth / CGlobal::GFovView) * (plocal->GetAimPunchAngle().y * 0.9)));
						float punch_y = !CrosshairRecoil ? (CGlobal::iScreenHeight / 2.f) :
							((CGlobal::iScreenHeight / 2) + (int)((CGlobal::iScreenHeight / CGlobal::GFovView) * (plocal->GetAimPunchAngle().x * 0.9)));

						switch (CrosshairStyle)
						{
						case 0:
						{
							GP_Render->DrawFilledBox(punch_x - CrosshairSize / 2, punch_y - CrosshairSize / 2, CrosshairSize, CrosshairSize, CrosshairColor);
							if (CrosshairOutline)
								GP_Render->DrawBox((punch_x - CrosshairSize / 2) - 1, (punch_y - CrosshairSize / 2) - 1, CrosshairSize + 1, CrosshairSize + 1, 1, Color::Black());
							break;
						}
						case 1:
						{
							GP_Render->DrawLine(punch_x - CrosshairSize, punch_y, punch_x + CrosshairSize + 1, punch_y, CrosshairColor);
							GP_Render->DrawLine(punch_x, punch_y - CrosshairSize, punch_x, punch_y + CrosshairSize + 1, CrosshairColor);

							if (CrosshairOutline)
							{
								GP_Render->DrawLine(punch_x - CrosshairSize - 1, punch_y - 1, punch_x, punch_y - 1, Color::Black());
								GP_Render->DrawLine(punch_x + 1, punch_y - 1, punch_x + CrosshairSize + 1, punch_y - 1, Color::Black());

								GP_Render->DrawLine(punch_x - CrosshairSize - 1, punch_y + 1, punch_x, punch_y + 1, Color::Black());
								GP_Render->DrawLine(punch_x + 1, punch_y + 1, punch_x + CrosshairSize + 1, punch_y + 1, Color::Black());

								GP_Render->DrawLine(punch_x - CrosshairSize - 1, punch_y - 1, punch_x - CrosshairSize - 1, punch_y + 1, Color::Black());
								GP_Render->DrawLine(punch_x + CrosshairSize + 1, punch_y - 1, punch_x + CrosshairSize + 1, punch_y + 2, Color::Black());


								GP_Render->DrawLine(punch_x - 1, punch_y - CrosshairSize - 1, punch_x - 1, punch_y - 1, Color::Black());
								GP_Render->DrawLine(punch_x + 1, punch_y - CrosshairSize - 1, punch_x + 1, punch_y - 1, Color::Black());

								GP_Render->DrawLine(punch_x - 1, punch_y + CrosshairSize + 1, punch_x - 1, punch_y + 1, Color::Black());
								GP_Render->DrawLine(punch_x + 1, punch_y + CrosshairSize + 1, punch_x + 1, punch_y + 1, Color::Black());

								GP_Render->DrawLine(punch_x - 1, punch_y + CrosshairSize + 1, punch_x + 1, punch_y + CrosshairSize + 1, Color::Black());
								GP_Render->DrawLine(punch_x - 1, punch_y - CrosshairSize - 1, punch_x + 1, punch_y - CrosshairSize - 1, Color::Black());

							}
							break;
						}
						case 2:
						{
							auto lineSize = CrosshairSize;
							int screenCenterX = punch_x;
							int screenCenterY = punch_y;
							GP_Render->DrawLine(screenCenterX - lineSize, screenCenterY - lineSize, screenCenterX - (lineSize / 4), screenCenterY - (lineSize / 4), CrosshairColor);
							GP_Render->DrawLine(screenCenterX - lineSize, screenCenterY + lineSize, screenCenterX - (lineSize / 4), screenCenterY + (lineSize / 4), CrosshairColor);
							GP_Render->DrawLine(screenCenterX + lineSize, screenCenterY + lineSize, screenCenterX + (lineSize / 4), screenCenterY + (lineSize / 4), CrosshairColor);
							GP_Render->DrawLine(screenCenterX + lineSize, screenCenterY - lineSize, screenCenterX + (lineSize / 4), screenCenterY - (lineSize / 4), CrosshairColor);
							break;
						}
						default:
							break;
						}
					}
				}

				if (SnipCrosshair)
				{
					if (CGlobal::GWeaponType == WEAPON_TYPE_SNIPER && CGlobal::GWeaponID != WEAPON_AUG && CGlobal::GWeaponID != WEAPON_SG553)
					{
						CBaseWeapon* Wep = plocal->GetBaseWeapon();
						if (Wep)
						{
							if (Wep->GetZoomLevel() != 1 && Wep->GetZoomLevel() != 2)
							{
								float punch_x = !SnipCrosshairRecoil ? (CGlobal::iScreenWidth / 2.f) :
									((CGlobal::iScreenWidth / 2) - (int)((CGlobal::iScreenWidth / CGlobal::GFovView) * (plocal->GetAimPunchAngle().y * 0.9)));
								float punch_y = !SnipCrosshairRecoil ? (CGlobal::iScreenHeight / 2.f) :
									((CGlobal::iScreenHeight / 2) + (int)((CGlobal::iScreenHeight / CGlobal::GFovView) * (plocal->GetAimPunchAngle().x * 0.9)));

								switch (SnipCrosshairStyle)
								{
								case 0:
								{
									GP_Render->DrawFilledBox(punch_x - CrosshairSize / 2, punch_y - CrosshairSize / 2, CrosshairSize, CrosshairSize, SnipCrosshairColor);
									if (SnipCrosshairOutline)
										GP_Render->DrawBox((punch_x - CrosshairSize / 2) - 1, (punch_y - CrosshairSize / 2) - 1, CrosshairSize + 1, CrosshairSize + 1, 1, Color::Black());
									break;
								}
								case 1:
								{
									GP_Render->DrawLine(punch_x - CrosshairSize, punch_y, punch_x + CrosshairSize + 1, punch_y, SnipCrosshairColor);
									GP_Render->DrawLine(punch_x, punch_y - CrosshairSize, punch_x, punch_y + CrosshairSize + 1, SnipCrosshairColor);

									if (SnipCrosshairOutline)
									{
										GP_Render->DrawLine(punch_x - CrosshairSize - 1, punch_y - 1, punch_x, punch_y - 1, Color::Black());
										GP_Render->DrawLine(punch_x + 1, punch_y - 1, punch_x + CrosshairSize + 1, punch_y - 1, Color::Black());

										GP_Render->DrawLine(punch_x - CrosshairSize - 1, punch_y + 1, punch_x, punch_y + 1, Color::Black());
										GP_Render->DrawLine(punch_x + 1, punch_y + 1, punch_x + CrosshairSize + 1, punch_y + 1, Color::Black());

										GP_Render->DrawLine(punch_x - CrosshairSize - 1, punch_y - 1, punch_x - CrosshairSize - 1, punch_y + 1, Color::Black());
										GP_Render->DrawLine(punch_x + CrosshairSize + 1, punch_y - 1, punch_x + CrosshairSize + 1, punch_y + 2, Color::Black());


										GP_Render->DrawLine(punch_x - 1, punch_y - CrosshairSize - 1, punch_x - 1, punch_y - 1, Color::Black());
										GP_Render->DrawLine(punch_x + 1, punch_y - CrosshairSize - 1, punch_x + 1, punch_y - 1, Color::Black());

										GP_Render->DrawLine(punch_x - 1, punch_y + CrosshairSize + 1, punch_x - 1, punch_y + 1, Color::Black());
										GP_Render->DrawLine(punch_x + 1, punch_y + CrosshairSize + 1, punch_x + 1, punch_y + 1, Color::Black());

										GP_Render->DrawLine(punch_x - 1, punch_y + CrosshairSize + 1, punch_x + 1, punch_y + CrosshairSize + 1, Color::Black());
										GP_Render->DrawLine(punch_x - 1, punch_y - CrosshairSize - 1, punch_x + 1, punch_y - CrosshairSize - 1, Color::Black());
									}
									break;
								}
								case 2:
								{
									auto lineSize = SnipCrosshairSize;
									int screenCenterX = punch_x;
									int screenCenterY = punch_y;
									GP_Render->DrawLine(screenCenterX - lineSize, screenCenterY - lineSize, screenCenterX - (lineSize / 4), screenCenterY - (lineSize / 4), SnipCrosshairColor);
									GP_Render->DrawLine(screenCenterX - lineSize, screenCenterY + lineSize, screenCenterX - (lineSize / 4), screenCenterY + (lineSize / 4), SnipCrosshairColor);
									GP_Render->DrawLine(screenCenterX + lineSize, screenCenterY + lineSize, screenCenterX + (lineSize / 4), screenCenterY + (lineSize / 4), SnipCrosshairColor);
									GP_Render->DrawLine(screenCenterX + lineSize, screenCenterY - lineSize, screenCenterX + (lineSize / 4), screenCenterY - (lineSize / 4), SnipCrosshairColor);
									break;
								}
								default:
									break;
								}
							}
						}
					}
				}

				if (SpreadCircel)
				{
					WEAPON_TYPE WeapType = CGlobal::GWeaponType;

					if (!plocal->IsDead() &&
						WeapType != WEAPON_TYPE_GRENADE &&
						WeapType != WEAPON_TYPE_KNIFE &&
						WeapType != WEAPON_TYPE_C4 &&
						WeapType != WEAPON_TYPE_UNKNOWN)
					{
						GP_Render->DrawRing(
							(CGlobal::iScreenWidth / 2) - (int)((CGlobal::iScreenWidth / CGlobal::GFovView) * (plocal->GetAimPunchAngle().y * 0.9)),
							(CGlobal::iScreenHeight / 2) + (int)((CGlobal::iScreenHeight / CGlobal::GFovView) * (plocal->GetAimPunchAngle().x * 0.9)),
							pWeapon->GetInaccuracy() * 550.f, 42, SpreadColor);
					}
				}

				//if (LegitAA)
				//{
				//	int w_b = 5;
				//	int h_b = 40;

				//	float desync = side - (plocal->GetTickBase() * I::GlobalVars()->interval_per_tick);

				//	GP_Render->DrawString(25, Vec2(w_b + 4, CGlobal::iScreenHeight / 2 + h_b / 2 + 40), Color::Green(), true, false, XorStr("Desync: "), desync);
				//}

				Night();
				CustomWalls();
			}
		}

		HitWorker.Draw();
	}
}

void CMisc::SetNewClan(string New, string Name)
{
	static auto pSetClanTag = reinterpret_cast<void(__fastcall*)(const char*, const char*)>(((DWORD)CSX::Memory::FindPatternV2(XorStr("engine.dll"), XorStr("53 56 57 8B DA 8B F9 FF 15"))));

	if (pSetClanTag)
		pSetClanTag(New.c_str(), Name.c_str());
}

void CMisc::CreateMove(bool& bSendPacket, float flInputSampleTime, CUserCmd* pCmd)
{
	CBaseEntity* plocal = (CBaseEntity*)I::EntityList()->GetClientEntity(I::Engine()->GetLocalPlayer());
	ConVar* cl_righthand = I::GetConVar()->FindVar(XorStr("cl_righthand"));

	if (plocal && CGlobal::IsGameReady)
	{
		if (plocal->GetBaseWeapon())
		{
			CGlobal::GWeaponType = CGlobal::GetWeaponType(plocal->GetBaseWeapon());
			if (plocal->GetBaseWeapon()->GeteAttributableItem())
				CGlobal::GWeaponID = (WEAPON_ID)*plocal->GetBaseWeapon()->GeteAttributableItem()->GetItemDefinitionIndex();
		}
	}
	if (Enable && CGlobal::IsGameReady && !CGlobal::FullUpdateCheck)
	{
		if (plocal)
		{
			if (BHop)
			{
				if (!plocal->IsDead())
				{
					if (pCmd->buttons & IN_JUMP && !(plocal->GetFlags() & FL_ONGROUND))
					{
						static bool bLastJumped = false;
						static bool bShouldFake = false;

						if (!bLastJumped && bShouldFake)
						{
							bShouldFake = false;
							pCmd->buttons |= IN_JUMP;
						}
						else if (pCmd->buttons & IN_JUMP)
						{
							if (plocal->GetFlags() & FL_ONGROUND)
							{
								bLastJumped = true;
								bShouldFake = true;
							}
							else
							{
								pCmd->buttons &= ~IN_JUMP;
								bLastJumped = false;
							}
						}
						else
						{
							bLastJumped = false;
							bShouldFake = false;
						}
					}

					if (AutoStrafe && !(plocal->GetFlags() & FL_ONGROUND))
					{
						if (pCmd->mousedx < 0)
							pCmd->sidemove = -450.0f;
						else if (pCmd->mousedx > 0)
							pCmd->sidemove = 450.0f;
					}
				}
			}

			/*if (EdgeJump && EdgeJumpBind.Check())
			{
				if (plocal->IsDead())
					return;

				const auto mt = plocal->GetMoveType();

				if (mt == MOVETYPE_LADDER || mt == MOVETYPE_NOCLIP)
					return;

				const auto start = plocal->GetOrigin();
				auto end = start;
				end.z -= 32;

				CTraceFilter filter;

				filter.pSkip = plocal;

				trace_t trace;
				Ray_t ray;

				ray.Init(start, end);
				I::EngineTrace()->TraceRay(ray, MASK_VISIBLE, &filter, &trace);

				if (trace.fraction == 1.0f)
					pCmd->buttons |= IN_JUMP;
			}*/

			if (LeftHandKnife)
			{
				if (plocal && CGlobal::GWeaponType == WEAPON_TYPE_KNIFE)
				{
					cl_righthand->SetValue(0);
				}
				else
				{
					cl_righthand->SetValue(1);
				}
			}
			else
			{
				cl_righthand->SetValue(1);
			}

			if (InfiniteDuck)
			{
				if (!plocal->IsDead())
				{
					pCmd->buttons |= IN_BULLRUSH;
				}
			}

			static bool NoFlashReset = false;

			if (AntiFlash)
			{
				float* maxAlpha = plocal->GetFlashMaxAlpha();
				if (maxAlpha)
					*maxAlpha = (float)AntiFlashAlpha;

				NoFlashReset = true;
			}
			if (!AntiFlash && NoFlashReset)
			{
				float* maxAlpha = plocal->GetFlashMaxAlpha();
				if (maxAlpha)
					*maxAlpha = 255.f;
				NoFlashReset = false;
			}

			std::vector<const char*> smoke_materials =
			{
				"particle/vistasmokev1/vistasmokev1_smokegrenade",
				"particle/vistasmokev1/vistasmokev1_emods",
				"particle/vistasmokev1/vistasmokev1_emods_impactdust",
				"particle/vistasmokev1/vistasmokev1_fire",
			};

			static auto smoke_count = *reinterpret_cast<uint32_t**>(CSX::Memory::FindSignature(XorStr("client_panorama.dll"), XorStr("A3 ? ? ? ? 57 8B CB")) + 1);
			static bool NoSmokeReset = false;
			if (NoSmoke)
			{
				for (auto mat : smoke_materials)
				{
					auto material = I::MaterialSystem()->FindMaterial(mat, TEXTURE_GROUP_CLIENT_EFFECTS);
					material->SetMaterialVarFlag(MATERIAL_VAR_WIREFRAME, true);
					if (NoSmoke)
						*(int*)smoke_count = 0;
				}
				NoSmokeReset = true;
			}
			if (!NoSmoke && NoSmokeReset)
			{
				for (auto mat : smoke_materials)
				{
					auto material = I::MaterialSystem()->FindMaterial(mat, TEXTURE_GROUP_CLIENT_EFFECTS);
					material->SetMaterialVarFlag(MATERIAL_VAR_WIREFRAME, false);
					if (!NoSmoke && NoSmokeReset)
						*(int*)smoke_count = 1;
				}
				NoSmokeReset = false;
			}

			static bool ClanTagReset = false;
			if (ClanTagChanger)
			{
				static string OldClan = "";
				string NewClan = ClanTagChangerText;

				switch (ClanTagChangerStyle)
				{
				case 0: NewClan = XorStr("X1N3 > All"); break;
				case 1: NewClan = XorStr("[VALV\xE1\xB4\xB1]"); break;
				case 2:
				{
					switch (int((float)plocal->GetTickBase() * I::GlobalVars()->interval_per_tick) % 10)
					{
					case 0: NewClan = XorStr("-----"); break;
					case 1: NewClan = XorStr("----X"); break;
					case 2: NewClan = XorStr("---X1"); break;
					case 3: NewClan = XorStr("--X1N"); break;
					case 4: NewClan = XorStr("-X1N3"); break;
					case 5: NewClan = XorStr("X1N3-"); break;
					case 6: NewClan = XorStr("1N3--"); break;
					case 7: NewClan = XorStr("N3---"); break;
					case 8: NewClan = XorStr("3----"); break;
					case 9: NewClan = XorStr("-----"); break;
					}
					break;
				}
				case 3:
				{
					switch (int((float)plocal->GetTickBase() * I::GlobalVars()->interval_per_tick) % 15)
					{
					case 0: NewClan = XorStr("-------"); break;
					case 1: NewClan = XorStr("------T"); break;
					case 2: NewClan = XorStr("-----TH"); break;
					case 3: NewClan = XorStr("----THE"); break;
					case 4: NewClan = XorStr("---THEL"); break;
					case 5: NewClan = XorStr("--THELU"); break;
					case 6: NewClan = XorStr("-THELUP"); break;
					case 7: NewClan = XorStr("THELUPA"); break;
					case 8: NewClan = XorStr("HELUPA-"); break;
					case 9: NewClan = XorStr("ELUPA--"); break;
					case 10: NewClan = XorStr("LUPA---"); break;
					case 11: NewClan = XorStr("UPA----"); break;
					case 12: NewClan = XorStr("PA-----"); break;
					case 13: NewClan = XorStr("A------"); break;
					case 14: NewClan = XorStr("-------"); break;
					}
					break;
				}
				default: break;
				}

				if (OldClan != NewClan)
					SetNewClan(NewClan, NewClan);

				OldClan = NewClan;
				ClanTagReset = true;
			}
			if (!ClanTagChanger && ClanTagReset)
			{
				SetNewClan("", "");
				ClanTagReset = false;
			}

			if (ChatSpam && ChatSpamStart)
			{
				std::vector<std::string> chatspam;

				switch (ChatSpamStyle)
				{
				case 0: chatspam = { XorStr("X1N3") }; break;
				case 1: chatspam = { ChatSpamText }; break;
				default:break;
				}

				static DWORD lastspammed = 0;
				if (FastCall::G().t_GetTickCount64() - lastspammed > 800)
				{
					lastspammed = (DWORD)FastCall::G().t_GetTickCount64();
					auto say = XorStr("say ");
					std::string msg = say + chatspam[rand() % chatspam.size()];
					I::Engine()->ExecuteClientCmd(msg.c_str());
				}
			}

			if (RadioSpam && RadioSpamStart)
			{
				std::vector<std::string> RadioSpam = { "coverme" , "takepoint" , "holdpos", "regroup", "followme",
					"takingfire", "go", "fallback", "sticktog",
					"report", "roger", "enemyspot", "needbackup",
					"sectorclear", "inposition", "reportingin",
					"getout", "negative", "enemydown" };

				static DWORD lastspammed = 0;
				if (FastCall::G().t_GetTickCount64() - lastspammed > 800)
				{
					lastspammed = GetTickCount();
					std::string msg = RadioSpam[rand() % RadioSpam.size()];
					I::Engine()->ExecuteClientCmd(msg.c_str());
				}
			}
			static int ticks = 0;

			if (FakeLag && FakeLagBind.Check())
			{
				if (!plocal->IsDead() && bSendPacket && abs(pCmd->sidemove) > 30 &&
					abs(pCmd->forwardmove) > 30)
				{
					if (ticks >= 20)
					{
						bSendPacket = true;
						ticks = 0;
					}
					else
						bSendPacket = ticks < 20 - FakeLagFactor;
					ticks++;
				}
			}

			if (KnifeBot && KnifeBotBind.Check())
			{
				if (CGlobal::GWeaponType == WEAPON_TYPE_KNIFE)
				{
					CBaseWeapon* pLocalWeapon = plocal->GetBaseWeapon();
					if (pLocalWeapon)
					{
						for (int EntIndex = 0; EntIndex < MAX_ENTITY_PLAYERS; EntIndex++)
						{
							CEntityPlayer* Entity = &GP_EntPlayers->EntityPlayer[EntIndex];

							if (!Entity->IsUpdated)
								continue;

							if (Entity->IsLocal)
								continue;

							if (!Entity->IsPlayer)
								continue;

							if (Entity->IsDead)
								continue;

							float Distance = Entity->Distance * 33;

							if (Distance > KnifeBotDistance)
								continue;

							if (KnifeBotFilter == 1)
							{
								if ((int)Entity->Team != plocal->GetTeam())
									continue;
							}
							else if (KnifeBotFilter == 2)
							{
								if ((int)Entity->Team == plocal->GetTeam())
									continue;
							}

							Vector OrignWorld = Entity->RenderOrigin;
							Vector OrignScreen;

							if (!CGlobal::WorldToScreen(OrignWorld, OrignScreen))
								continue;

							switch (KnifeBotMode)
							{
							case 0:
							{
								static int cur_attack = 0;

								if (Distance > 60.f)
									pCmd->buttons |= IN_ATTACK;
								else
								{
									if ((plocal->GetTickBase() * I::GlobalVars()->interval_per_tick) - pLocalWeapon->GetNextPrimaryAttack() > 0)
									{
										if (Entity->Armor > 0)
										{
											if (Entity->Health - 21 <= 0)
												pCmd->buttons |= IN_ATTACK;
											else
												pCmd->buttons |= IN_ATTACK2;
										}
										else
										{
											if (Entity->Health - 34 <= 0)
												pCmd->buttons |= IN_ATTACK;
											else
												pCmd->buttons |= IN_ATTACK2;
										}
									}

								}
								break;
							}
							case 1:
							{
								static int cur_attack = 0;

								if (Distance > 60.f)
								{
									pCmd->buttons |= IN_ATTACK;
									cur_attack = 1;
								}
								else
								{
									float TimeSinceFire = (plocal->GetTickBase() * I::GlobalVars()->interval_per_tick) - pLocalWeapon->GetNextPrimaryAttack();

									if (cur_attack > 0 && TimeSinceFire > 0)
									{
										pCmd->buttons |= IN_ATTACK2;
										TimeSinceFire = -1;
										cur_attack = 0;
									}

									if (cur_attack == 0 && TimeSinceFire > 0)
									{
										pCmd->buttons |= IN_ATTACK;
										cur_attack++;
									}
								}
								break;
							}
							case 2: pCmd->buttons |= IN_ATTACK2; break;
							case 3: pCmd->buttons |= IN_ATTACK; break;
							default: break;
							}
						}
					}
				}
			}
		}
	}
}

void CMisc::Thirdperson()
{

}

void CMisc::Anti_Kick(int type, unsigned int a3, unsigned int length, const void* msg_data)
{
	if (AntiKick)
	{
		if (type == CS_UM_VoteStart)
		{
			if (!AntiKick) 
				return;

			bf_Read read = bf_Read(reinterpret_cast<uintptr_t>(msg_data));
			read.SetOffset(6);
			read.Skip(29); //30 ?
			std::string message = read.ReadString();

//			Message::Get().Start("ANTIKICK", Utils::Format("Detected message: '%s'", std::string(message)));

			PlayerInfo local_info;
			if (!I::Engine()->GetPlayerInfo(I::Engine()->GetLocalPlayer(), &local_info))
				return;

			if (message.find(local_info.m_szPlayerName) != std::string::npos)
			{
				switch (AntiKickMethod)
				{
				case 0:
					AntiKickMethod = 1;
					I::Engine()->ExecuteClientCmd("callvote swapteams");
					Message::Get().Start("Anti-Kicking...\n Method[callvote swapteams]"
					/*"ANTIKICK", Utils::Format("Detected '%s' in message, trying swapteams method.", local_info.m_szPlayerName)*/);
					break;
				case 1:
					AntiKickMethod = 0;
					I::Engine()->ExecuteClientCmd("callvote scrambleteams");
					Message::Get().Start("Anti-Kicking...\n Method[callvote scrambleteams]"
					/*"ANTIKICK", Utils::Format("Detected '%s' in message, trying scrambleteams method.", local_info.m_szPlayerName)*/);
					break;
				}
			}
		}
	}
}

void CMisc::Desync(CUserCmd* pCmd, bool& bSendPacket)
{
	CBaseEntity* pLocalPlayer = (CBaseEntity*)I::EntityList()->GetClientEntity(I::Engine()->GetLocalPlayer());
	QAngle OldAngles = pCmd->viewangles;

	if (LegitAA)
	{
		if (pCmd->buttons & (IN_ATTACK | IN_ATTACK2 | IN_USE) ||
			pLocalPlayer->GetMoveType() == MOVETYPE_LADDER || pLocalPlayer->GetMoveType() == MOVETYPE_NOCLIP
			|| pLocalPlayer->IsDead())
			return;

		auto weapon = pLocalPlayer->GetBaseWeapon();
		if (!weapon)
			return;

		auto weapon_index = weapon->GetModelIndex();
		if ((weapon_index == WEAPON_GLOCK || weapon_index == WEAPON_FAMAS) && weapon->GetNextPrimaryAttack() >= I::GlobalVars()->curtime)
			return;

		auto weapon_data = weapon->GetWeaponInfo();

		if (weapon_data->m_WeaponType == WEAPON_TYPE_GRENADE) {
			if (!weapon->GetPinPulled()) {
				float throwTime = weapon->GetThrowTime();
				if (throwTime > 0.f)
					return;
			}

			if ((pCmd->buttons & IN_ATTACK) || (pCmd->buttons & IN_ATTACK2)) {
				if (weapon->GetThrowTime() > 0.f)
					return;
			}
		}

		static bool broke_lby = false;

		if (LegitAABind.Check()) 
		{
			side = -side;
		}
		if (LegitAAType == 1) 
		{
			float minimal_move = 2.0f;
			if (pLocalPlayer->GetFlags() & FL_DUCKING)
				minimal_move *= 3.f;

			if (pCmd->buttons & IN_WALK)
				minimal_move *= 3.f;

			bool should_move = pLocalPlayer->GetVelocity().Length2D() <= 0.0f
				|| std::fabsf(pLocalPlayer->GetVelocity().z) <= 100.0f;

			if ((pCmd->command_number % 2) == 1) {
				pCmd->viewangles.y += 120.0f * side;
				if (should_move)
					pCmd->sidemove -= minimal_move;
				bSendPacket = false;
			}
			else if (should_move) {
				pCmd->sidemove += minimal_move;
			}
		}
		else 
		{
			if (next_lby >= I::GlobalVars()->curtime) 
			{
				if (!broke_lby && bSendPacket && I::ClientState()->chokedcommands > 0)
					return;

				broke_lby = false;
				bSendPacket = false;
				pCmd->viewangles.y += 120.0f * side;
			}
			else 
			{
				broke_lby = true;
				bSendPacket = false;
				pCmd->viewangles.y += 120.0f * -side;
			}
		}

		FixAngles(pCmd->viewangles);
		MovementFix(pCmd, OldAngles, pCmd->viewangles);
	}
}

void CMisc::OverrideView(CViewSetup* pSetup)
{
	if (Enable && CGlobal::IsGameReady && !CGlobal::FullUpdateCheck)
	{
		if (!pSetup)
			return;

		CBaseEntity* plocal = (CBaseEntity*)I::EntityList()->GetClientEntity(I::Engine()->GetLocalPlayer());

		if (plocal)
		{
			CGlobal::GFovViewExt = pSetup->fov;
			if (FovChanger)
			{
				if (plocal->IsDead())
				{
					if (plocal->GetObserverMode() == ObserverMode_t::OBS_MODE_IN_EYE && plocal->GetObserverTarget())
						plocal = (CBaseEntity*)I::EntityList()->GetClientEntityFromHandle(plocal->GetObserverTarget());

					if (!plocal)
						return;
				}
				bool ChangeFov = true;
				CBaseWeapon* Wep = plocal->GetBaseWeapon();
				if (Wep)
				{
					if (((WEAPON_ID)*Wep->GeteAttributableItem()->GetItemDefinitionIndex() == WEAPON_AWP ||
						(WEAPON_ID)*Wep->GeteAttributableItem()->GetItemDefinitionIndex() == WEAPON_SSG08) &&
						(CGlobal::GFovViewExt == 90 || CGlobal::GFovViewExt == FovView) && !plocal->IsDead())
					{
						ChangeFov = true;
					}
					else
					{
						WEAPON_TYPE WeapType = CGlobal::GWeaponType;
						if ((WeapType != WEAPON_TYPE_GRENADE &&
							WeapType != WEAPON_TYPE_KNIFE) &&
							(Wep->GetZoomLevel() == 1 ||
								Wep->GetZoomLevel() == 2))
						{
							ChangeFov = false;
						}
					}
				}

				if (ChangeFov)
					pSetup->fov = (float)FovView;
			}

			if (NoVisualRecoil)
			{
				pSetup->angles.x -= ((plocal->GetViewPunchAngle().x * 2.f) * 0.45f);
				pSetup->angles.y -= ((plocal->GetViewPunchAngle().y * 2.f) * 0.45f);
			}

			if (FreeCam)
			{
				static Vector newOrigin;

				float freecamspeed = FreeCamSpeed;

				if (!FreeCamBind.Check())
				{
					newOrigin = pSetup->origin;
				}
				else
				{
					float fSpeed = freecamspeed; //5.f;
					if (KEY_DOWN(VK_CONTROL))
						fSpeed = fSpeed * 0.45f;
					if (KEY_DOWN(VK_SHIFT))
						fSpeed = fSpeed * 1.65f;
					if (KEY_DOWN(0x57)) // W		
						newOrigin += pSetup->angles.Forward() * fSpeed;
					if (KEY_DOWN(0x41)) // A		
						newOrigin += pSetup->angles.Right() * fSpeed;
					if (KEY_DOWN(0x44)) // D		
						newOrigin -= pSetup->angles.Right() * fSpeed;
					if (KEY_DOWN(0x53)) // S		
						newOrigin -= pSetup->angles.Forward() * fSpeed;
					if (KEY_DOWN(VK_SPACE)) // Space		
						newOrigin += pSetup->angles.Up() * fSpeed;
					pSetup->origin = newOrigin;
				}
			}
		}
	}

	CBaseEntity* plocal = (CBaseEntity*)I::EntityList()->GetClientEntity(I::Engine()->GetLocalPlayer());

	if (plocal && !CGlobal::FullUpdateCheck)
	{
		if (GP_LegitAim)
			if (GP_LegitAim->CanRCSStandelone && GP_LegitAim->CanRCS)
			{
				pSetup->angles.x -= ((plocal->GetViewPunchAngle().x * 2.f) * 0.2f);
				pSetup->angles.y -= ((plocal->GetViewPunchAngle().y * 2.f) * 0.2f);
			}
	}
	
	CGlobal::GFovView = pSetup->fov;
}

void CMisc::GetViewModelFOV(float &Fov)
{

	if (Enable && CGlobal::IsGameReady && !CGlobal::FullUpdateCheck)
	{
		CBaseEntity* plocal = (CBaseEntity*)I::EntityList()->GetClientEntity(I::Engine()->GetLocalPlayer());

		if (plocal)
		{
			if (FovModelChanger)
			{
				if (plocal->IsDead())
				{
					if (plocal->GetObserverMode() == ObserverMode_t::OBS_MODE_IN_EYE && plocal->GetObserverTarget())
						plocal = (CBaseEntity*)I::EntityList()->GetClientEntityFromHandle(plocal->GetObserverTarget());

					if (!plocal)
						return;
				}

				bool ChangeFov = true;
				CBaseWeapon* Wep = plocal->GetBaseWeapon();
				if (Wep)
				{
					if (((WEAPON_ID)*Wep->GeteAttributableItem()->GetItemDefinitionIndex() == WEAPON_AWP ||
						(WEAPON_ID)*Wep->GeteAttributableItem()->GetItemDefinitionIndex() == WEAPON_SSG08) &&
						(CGlobal::GFovViewExt == 90 || CGlobal::GFovViewExt == FovView) && !plocal->IsDead())
					{
						ChangeFov = true;
					}
					else
					{
						WEAPON_TYPE WeapType = CGlobal::GWeaponType;
						if ((WeapType != WEAPON_TYPE_GRENADE &&
							WeapType != WEAPON_TYPE_KNIFE) &&
							(Wep->GetZoomLevel() == 1 ||
								Wep->GetZoomLevel() == 2))
						{
							ChangeFov = false;
						}
					}

				}

				if (ChangeFov)
					Fov = (float)FovModel;
			}
		}
	}
}

//void SetLocalPlayerReady()
//{
//	static auto SetLocalPlayerReadyFn = reinterpret_cast<bool(__stdcall*)(const char*)>
//		(CSX::Memory::FindPatternV2(XorStr("client_panorama.dll"),
//			XorStr("55 8B EC 83 E4 F8 8B 4D 08 BA ? ? ? ? E8 ? ? ? ? 85 C0 75 12")));
//
//	if (SetLocalPlayerReadyFn)
//		SetLocalPlayerReadyFn("");
//}

//void accept()
//{
//	typedef void(__cdecl* accept_t)(void);
//	static accept_t accept = (accept_t)CSX::Memory::FindPatternV2(XorStr("client_panorama.dll"),
//		XorStr("55 8B EC 51 56 8B 35 ? ? ? ? 57 83 BE"));
//
//	if (accept && **(unsigned long**)((unsigned long)accept + 0x7))
//	{
//		SetLocalPlayerReady();
//	}
//}

void CMisc::AutoAcceptEmit()
{
	if (AutoAccept && !CGlobal::FullUpdateCheck)
	{
		static auto fnAccept = reinterpret_cast<bool(__stdcall*)(const char*)>
			(CSX::Memory::FindPatternV2(XorStr("client_panorama.dll"),
				XorStr("55 8B EC 83 E4 F8 8B 4D 08 BA ? ? ? ? E8 ? ? ? ? 85 C0 75 12")));

		if (fnAccept)
		{
			fnAccept("");
			HWND window = FastCall::G().t_FindWindowA("Valve001", 0);
			FLASHWINFO flash{ sizeof(FLASHWINFO), window, FLASHW_TRAY | FLASHW_TIMERNOFG, 0, 0 };
			FlashWindowEx(&flash);
			ShowWindow(window, SW_RESTORE);
		}

		//typedef void(__cdecl* accept_t)(void);
		//static accept_t accept = (accept_t)CSX::Memory::FindPatternV2(XorStr("client_panorama.dll"),
		//	XorStr("55 8B EC 51 56 8B 35 ? ? ? ? 57 83 BE"));

		//static auto SetLocalPlayerReadyFn = reinterpret_cast<bool(__stdcall*)(const char*)>
		//	(CSX::Memory::FindPatternV2(XorStr("client_panorama.dll"),
		//		XorStr("55 8B EC 83 E4 F8 8B 4D 08 BA ? ? ? ? E8 ? ? ? ? 85 C0 75 12")));

		//auto match_session = I::MatchFramework()->get_match_session();
		//if (match_session) 
		//{
		//	auto session_settings = match_session->get_session_settings();
		//	if (session_settings) 
		//	{
		//		std::string search_state = session_settings->GetString("game/mmqueue", "");

		//		if (search_state == "reserved") 
		//		{
		//			FLASHWINFO fi;
		//			fi.cbSize = sizeof(FLASHWINFO);
		//			fi.hwnd = FastCall::G().t_FindWindowA(NULL, XorStr("Counter-Strike: Global Offensive"));
		//			fi.dwFlags = FLASHW_ALL | FLASHW_TIMERNOFG;
		//			fi.uCount = 0;
		//			fi.dwTimeout = 0;
		//			FlashWindowEx(&fi);
		//			ShowWindow(fi.hwnd, SW_RESTORE);
		//			Sleep(500);
		//			if (accept && **(unsigned long**)((unsigned long)accept + 0x7)) 
		//			{
		//				if (SetLocalPlayerReadyFn)
		//					SetLocalPlayerReadyFn("");
		//			}
		//		}
		//	}
		//}
	}
}

//void CMisc::PlaySound(const char* pszSoundName)
//{
//}

void CMisc::DrawModelExecute(void* thisptr, IMatRenderContext* ctx, const DrawModelState_t &state, const ModelRenderInfo_t &pInfo, matrix3x4_t *pCustomBoneToWorld)
{
	if (Enable && !CGlobal::FullUpdateCheck)
	{
		static IMaterial* VisTex = nullptr;
		static IMaterial* VisFlat = nullptr;
		static IMaterial* VisFrame = nullptr;
		static IMaterial* VisMetallic = nullptr;

		if (!VisTex)
			VisTex = CGlobal::CreateMaterialBasic(false, true, false);

		if (!VisFlat)
			VisFlat = CGlobal::CreateMaterialBasic(false, false, false);

		if (!VisFrame)
			VisFrame = CGlobal::CreateMaterialBasic(false, true, true);

		if (!VisMetallic)
			VisMetallic = CGlobal::CreateMaterialMetallic(false, true);

		if (VisTex && VisFlat && VisFrame)
		{
			if (HandChams)
			{
				float HandColor[3] = { HandChamsColor.G1R(), HandChamsColor.G1G(), HandChamsColor.G1B() };
				const char* ModelName = I::ModelInfo()->GetModelName((model_t*)pInfo.pModel);

				if (strstr(ModelName, XorStr("arms")))
				{
					I::RenderView()->SetColorModulation(HandColor);
					I::RenderView()->SetBlend(HandChamsColor.G1A());

					if (HandChamsStyle == 0)
						I::ModelRender()->ForcedMaterialOverride(VisTex);
					else if (HandChamsStyle == 1)
						I::ModelRender()->ForcedMaterialOverride(VisFlat);
					else if (HandChamsStyle == 2)
						I::ModelRender()->ForcedMaterialOverride(VisFrame);
					else if (HandChamsStyle == 3)
						I::ModelRender()->ForcedMaterialOverride(VisMetallic);
					else if (HandChamsStyle == 5)
					{
						I::RenderView()->SetBlend(0.0f);
						I::ModelRender()->ForcedMaterialOverride(VisFlat);
					}
					HookTables::pDrawModelExecute->GetTrampoline()(thisptr, ctx, state, pInfo, pCustomBoneToWorld);
				}
			}
		}
	}
}

void CMisc::ShowSpectatorList()
{
	if (CGlobal::FullUpdateCheck)
		return;

	string spect = "";
	string mode = "";

	bool op = true;

	int LocalPlayerIdx = I::Engine()->GetLocalPlayer();
	vector<int> observs = GetObservervators(LocalPlayerIdx);

	if (observs.empty() && SpectatorListAutoHide && !CGlobal::IsGuiVisble)
		return;

	static bool Hovered = false;

	GuiStyle& style = X1Gui().GetStyle();
	Vec2 OldPadding = style.wndPadding;
	style.wndPadding = Vec2(3, 3);

	color_t old_color = style.clrBackground;
	style.clrBackground = Color(MainSettings().BackgroundColor.r(),
		MainSettings().BackgroundColor.g(),
		MainSettings().BackgroundColor.b(), SpectatorListAlpha);

	X1Gui().SetNextWindowPos(Vec2(SpectatorListPosX, SpectatorListPosY));

	static Vec2 old_cursor_pos = Vec2(200, 100);

	if (X1Gui().Begin(XorStr("Spectators"), GWF_Window, old_cursor_pos, Vec2(0, 0)))
	{
		X1Gui().Text(XorStr("Name"));
		X1Gui().SameLine(93);
		X1Gui().Text(XorStr("Mode"));
		X1Gui().Separator();

		bool Kastil = false;

		for (int playerId : observs)
		{
			if (playerId == LocalPlayerIdx)
				continue;

			CBaseEntity* pPlayer = (CBaseEntity*)I::EntityList()->GetClientEntity(playerId);
			if (!pPlayer)
				continue;

			PlayerInfo Pinfo;
			if (!I::Engine()->GetPlayerInfo(playerId, &Pinfo))
				continue;

			if (Pinfo.m_bIsFakePlayer)
				continue;

			spect = Pinfo.m_szPlayerName;

			if (spect != "")
			{
				switch (pPlayer->GetObserverMode())
				{
				case ObserverMode_t::OBS_MODE_IN_EYE:
					mode = XorStr("1st person");
					break;
				case ObserverMode_t::OBS_MODE_CHASE:
					mode = XorStr("3rd person");
					break;
				case ObserverMode_t::OBS_MODE_ROAMING:
					mode = XorStr("Free look");
					break;
				case ObserverMode_t::OBS_MODE_DEATHCAM:
					mode = XorStr("Deathcam");
					break;
				case ObserverMode_t::OBS_MODE_FREEZECAM:
					mode = XorStr("Freezecam");
					break;
				case ObserverMode_t::OBS_MODE_FIXED:
					mode = XorStr("Fixed");
					break;
				default:
					break;
				}

				X1Gui().Text((spect + "    ").c_str());
				X1Gui().SameLine(93);
				X1Gui().Text(mode.c_str());
			}
			Kastil = true;
		}
		X1Gui().VerticalSeparator(90);

		if (!Kastil)
		{
			X1Gui().Text("                ");
			X1Gui().SameLine(93);
			X1Gui().Text("                ");
		}

		X1Gui().SameLine();

		old_cursor_pos = Vec2(X1Gui().GetCursorPosEx().x + 10, X1Gui().GetCursorPosEx().y + 10 + 15);
	}
	X1Gui().End();

	style.clrBackground = old_color;
	style.wndPadding = OldPadding;
}

void CMisc::Reset()
{
	if (!HitWorker.DamageVector.empty())
		HitWorker.DamageVector.clear();

	if (!GP_Misc->HitImpacts.empty())
		GP_Misc->HitImpacts.clear();

	HitWorker.HitMarkerEndTime = 0;
}

vector<int> CMisc::GetObservervators(int playerId)
{
	vector<int> SpectatorList;

	CBaseEntity* pPlayer = (CBaseEntity*)I::EntityList()->GetClientEntity(playerId);

	if (!pPlayer)
		return SpectatorList;

	if (pPlayer->IsDead())
	{
		CBaseEntity* pObserverTarget = (CBaseEntity*)I::EntityList()->GetClientEntityFromHandle(pPlayer->GetObserverTarget());

		if (!pObserverTarget)
			return SpectatorList;

		pPlayer = pObserverTarget;
	}

	for (int PlayerIndex = 0; PlayerIndex < I::EntityList()->GetHighestEntityIndex(); PlayerIndex++)
	{
		CBaseEntity* pCheckPlayer = (CBaseEntity*)I::EntityList()->GetClientEntity(PlayerIndex);

		if (!pCheckPlayer)
			continue;

		if (!pCheckPlayer->IsPlayer())
			continue;

		if (pCheckPlayer->IsDormant() || !pCheckPlayer->IsDead())
			continue;

		CBaseEntity* pObserverTarget = (CBaseEntity*)I::EntityList()->GetClientEntityFromHandle(pCheckPlayer->GetObserverTarget());

		if (!pObserverTarget)
			continue;

		if (pPlayer != pObserverTarget)
			continue;

		SpectatorList.push_back(PlayerIndex);
	}

	return SpectatorList;
}

void CMisc::Night()
{
	static bool nightz = false;

	if (NightMode && CGlobal::IsGameReady)
	{
		if (!nightz)
		{
			static auto sv_skyname = I::GetConVar()->FindVar(XorStr("sv_skyname"));
			static auto r_DrawSpecificStaticProp = I::GetConVar()->FindVar(XorStr("r_DrawSpecificStaticProp"));
			r_DrawSpecificStaticProp->SetValue(1);
			sv_skyname->SetValue(XorStr("sky_csgo_night02"));

			for (MaterialHandle_t i = I::MaterialSystem()->FirstMaterial(); i != I::MaterialSystem()->InvalidMaterial(); i = I::MaterialSystem()->NextMaterial(i))
			{
				IMaterial *pMaterial = I::MaterialSystem()->GetMaterial(i);

				if (!pMaterial)
					continue;

				const char* group = pMaterial->GetTextureGroupName();
				const char* name = pMaterial->GetName();

				if (strstr(group, XorStr("World textures")))
				{
					pMaterial->ColorModulate(0.10, 0.10, 0.10);
				}
				if (strstr(group, XorStr("StaticProp")))
				{
					pMaterial->ColorModulate(0.30, 0.30, 0.30);
				}
				if (strstr(name, XorStr("models/props/de_dust/palace_bigdome")))
				{
					pMaterial->SetMaterialVarFlag(MATERIAL_VAR_NO_DRAW, true);
				}
				if (strstr(name, XorStr("models/props/de_dust/palace_pillars")))
				{
					pMaterial->ColorModulate(0.30, 0.30, 0.30);
				}
				if (strstr(group, XorStr("Particle textures")))
				{
					pMaterial->SetMaterialVarFlag(MATERIAL_VAR_NO_DRAW, true);
				}
				nightz = true;
			}
		}
	}
	else
	{
		if (nightz)
		{
			for (MaterialHandle_t i = I::MaterialSystem()->FirstMaterial(); i != I::MaterialSystem()->InvalidMaterial(); i = I::MaterialSystem()->NextMaterial(i))
			{
				IMaterial *pMaterial = I::MaterialSystem()->GetMaterial(i);

				if (!pMaterial)
					continue;

				const char* group = pMaterial->GetTextureGroupName();
				const char* name = pMaterial->GetName();

				if (strstr(group, XorStr("World textures")))
				{
					pMaterial->ColorModulate(1, 1, 1);
				}
				if (strstr(group, XorStr("StaticProp")))
				{
					pMaterial->ColorModulate(1, 1, 1);
				}
				if (strstr(name, XorStr("models/props/de_dust/palace_bigdome")))
				{
					pMaterial->SetMaterialVarFlag(MATERIAL_VAR_NO_DRAW, false);
				}
				if (strstr(name, XorStr("models/props/de_dust/palace_pillars")))
				{
					pMaterial->ColorModulate(1, 1, 1);
				}
				if (strstr(group, XorStr("Particle textures")))
				{
					pMaterial->SetMaterialVarFlag(MATERIAL_VAR_NO_DRAW, false);
				}
			}

			nightz = false;
		}
	}
}

void CMisc::FrameStageNotify(ClientFrameStage_t Stage)
{
}

void CMisc::CustomWalls()
{
	static bool reset = false;

	static KeyValues* KeyValTex;
	static KeyValues* KeyValFlat;

	if (!KeyValTex)
		KeyValTex = CGlobal::KeyValNew(false);

	if (!KeyValFlat)
		KeyValFlat = CGlobal::KeyValNew(false, false);

	if (ColoredWalls && CGlobal::IsGameReady)
	{
		static float old_r = ColoredWallsColor.G1R();
		static float old_g = ColoredWallsColor.G1G();
		static float old_b = ColoredWallsColor.G1B();
		static float old_a = ColoredWallsColor.G1A();

		static int old_style = ColoredWallsStyle;

		if (!reset || old_style != ColoredWallsStyle ||
			(old_r != ColoredWallsColor.G1R() ||
				old_g != ColoredWallsColor.G1G() ||
				old_b != ColoredWallsColor.G1B() ||
				old_a != ColoredWallsColor.G1A()))
		{

			for (MaterialHandle_t i = I::MaterialSystem()->FirstMaterial(); i != I::MaterialSystem()->InvalidMaterial(); i = I::MaterialSystem()->NextMaterial(i))
			{
				IMaterial *pMaterial = I::MaterialSystem()->GetMaterial(i);

				if (!pMaterial)
					continue;

				if (strstr(pMaterial->GetTextureGroupName(), XorStr("World")) ||
					strstr(pMaterial->GetTextureGroupName(), XorStr("Particle textures")) ||
					strstr(pMaterial->GetTextureGroupName(), XorStr("StaticProp")) ||
					strstr(pMaterial->GetTextureGroupName(), XorStr("SkyBox")))
				{
					/*if (ColoredWallsStyle == 1)
					{
						if (KeyValTex)
							pMaterial->SetShaderAndParams(KeyValTex);
					}
					else if (ColoredWallsStyle == 2)
					{
						if (KeyValFlat)
							pMaterial->SetShaderAndParams(KeyValFlat);
					}*/

					pMaterial->AlphaModulate(ColoredWallsColor.G1A());
					pMaterial->ColorModulate(ColoredWallsColor.G1R(), ColoredWallsColor.G1G(), ColoredWallsColor.G1B());
				}

			}

			reset = true;
		}

		old_r = ColoredWallsColor.G1R();
		old_g = ColoredWallsColor.G1G();
		old_b = ColoredWallsColor.G1B();
		old_a = ColoredWallsColor.G1A();
		old_style = ColoredWallsStyle;
	}
	else
	{
		if (reset && CGlobal::IsGameReady)
		{
			for (MaterialHandle_t i = I::MaterialSystem()->FirstMaterial(); i != I::MaterialSystem()->InvalidMaterial(); i = I::MaterialSystem()->NextMaterial(i))
			{
				IMaterial *pMaterial = I::MaterialSystem()->GetMaterial(i);

				if (!pMaterial)
					continue;

				if (strstr(pMaterial->GetTextureGroupName(), XorStr("World")))
				{
					pMaterial->AlphaModulate(1);
					pMaterial->ColorModulate(1, 1, 1);
				}
			}
			reset = false;
		}
	}
}

void ReadSounds(LPCTSTR lpszFileName)
{
	if (GP_Misc)
		GP_Misc->SoundList.push_back(lpszFileName);
}

void CMisc::UpdateSoundList()
{
	SoundList.clear();
	string SoundsDir = CGlobal::SystemDisk + XorStr("X1N3\\Resources\\Sounds\\*.wav");
	CGlobal::SearchFiles(SoundsDir.c_str(), ReadSounds, FALSE);
}

void CHitListener::RegListener()
{
	I::GameEvent()->AddListener(this, XorStr("player_hurt"), false);
	I::GameEvent()->AddListener(this, XorStr("bullet_impact"), false);
}

void CHitListener::UnRegListener()
{
	I::GameEvent()->RemoveListener(this);
}

#define HIT_TRACE_SHOW_TIME 2.f
void CHitListener::FireGameEvent(IGameEvent *event)
{
	if (GP_Misc)
	{
		if (GP_Misc->Enable)
		{
			CBaseEntity* plocal = (CBaseEntity*)I::EntityList()->GetClientEntity(I::Engine()->GetLocalPlayer());
			if (plocal)
			{
				if (!strcmp(event->GetName(), XorStr("bullet_impact")))
				{
					int PlayerIdx = I::Engine()->GetPlayerForUserID(event->GetInt(XorStr("userid")));

					if (PlayerIdx == I::Engine()->GetLocalPlayer())
					{
						Vector ImpactPos(event->GetFloat(XorStr("x")), event->GetFloat(XorStr("y")), event->GetFloat(XorStr("z")));

						Ray_t ray;
						ray.Init(plocal->GetEyePosition(), ImpactPos);

						CTraceFilter filter;
						filter.pSkip = plocal;

						trace_t tr;
						I::EngineTrace()->TraceRay(ray, MASK_SHOT, &filter, &tr);

						if (tr.m_pEnt && tr.DidHit())
						{
							if (reinterpret_cast<CBaseEntity*>(tr.m_pEnt)->IsPlayer())
							{
								CMisc::HitImpact_t ImpEntry;
								ImpEntry.Pos = ImpactPos;
								ImpEntry.MyHeadPos = plocal->GetEyePosition();
								ImpEntry.EndTime = I::GlobalVars()->curtime + HIT_TRACE_SHOW_TIME;
								ImpEntry.Alpha = 255;
								GP_Misc->HitImpacts.push_back(ImpEntry);
							}
						}
					}
				}

				if (!strcmp(event->GetName(), XorStr("player_hurt")))
				{
					if (I::Engine()->GetPlayerForUserID(event->GetInt(XorStr("attacker"))) == I::Engine()->GetLocalPlayer())
					{

						if (GP_Misc->HitMarker)
						HitMarkerEndTime = I::GlobalVars()->curtime + 0.29f;

						if (GP_Misc->HitSound)
							if (!GP_Misc->SoundList.empty() && GP_Misc->HitSoundStyle >= 0 && GP_Misc->HitSoundStyle < (int)GP_Misc->SoundList.size())
								FastCall::G().t_PlaySoundA((CGlobal::SystemDisk + XorStr("X1N3\\Resources\\Sounds\\") + GP_Misc->SoundList[GP_Misc->HitSoundStyle]).c_str(),
									NULL, SND_FILENAME | SND_ASYNC);

						if (GP_Misc->DamageInfo)
						{
							DamgeInfo_t BufInfo;

							CBaseEntity* pHurtEnt = (CBaseEntity*)I::EntityList()->GetClientEntity(I::Engine()->GetPlayerForUserID(event->GetInt(XorStr("userid"))));
							if (pHurtEnt)
							{
								BufInfo.Pos = pHurtEnt->GetHitboxPosition(0);
								if (!BufInfo.Pos.IsZero())
								{
									if (GP_Misc->DamageInfoStyle == 0)
										BufInfo.Number = event->GetInt(XorStr("dmg_health"));
									else if (GP_Misc->DamageInfoStyle == 1)
										BufInfo.Number = pHurtEnt->GetHealth() - event->GetInt(XorStr("dmg_health"));

									BufInfo.EndTime = I::GlobalVars()->curtime + GP_Misc->DamageInfoShowTime;
									BufInfo.Pos.z += 20;
									BufInfo.Alpha = 255;
									BufInfo.OffsetZ = 1;
									DamageVector.push_back(BufInfo);
								}
							}
						}
					}
				}
			}
		}
	}
}

void HitMark(const int &size, const int &tick, const int& pos_x, const int& pos_y, const Color& color)
{
	GP_Render->DrawLine(pos_x - size, pos_y - size, pos_x - (size / 4), pos_y - (size / 4), color, tick);
	GP_Render->DrawLine(pos_x - size, pos_y + size, pos_x - (size / 4), pos_y + (size / 4), color, tick);
	GP_Render->DrawLine(pos_x + size, pos_y + size, pos_x + (size / 4), pos_y + (size / 4), color, tick);
	GP_Render->DrawLine(pos_x + size, pos_y - size, pos_x + (size / 4), pos_y - (size / 4), color, tick);
}

void CHitListener::Draw()
{
	if (GP_Misc)
	{
		if (GP_Misc->HitMarker)
		{
			if (HitMarkerEndTime > I::GlobalVars()->curtime)
			{
				HitMark(GP_Misc->HitMarkerSize, GP_Misc->HitMarkerTickness,
					CGlobal::iScreenWidth / 2, CGlobal::iScreenHeight / 2, GP_Misc->HitMarkerColor);
			}
		}

		if (GP_Misc->DamageInfo)
		{
			if (!DamageVector.empty())
			{
				if (GP_Misc->DamageInfoPosition == 0)
					GP_Render->DrawString(GP_Misc->TextDamageInfo, Vec2(GP_Misc->DamageInfoPosX, GP_Misc->DamageInfoPosY), GP_Misc->DamageInfoColor,
						to_string(DamageVector.back().Number).c_str());

				int Height = GP_Misc->DamageInfoHeight;
				int Speed = GP_Misc->DamageInfoSpeed;

				for (size_t i(0); i < DamageVector.size(); i++)
				{
					if (GP_Misc->DamageInfoPosition == 1)
					{
						if (DamageVector[i].OffsetZ < Height)
							DamageVector[i].OffsetZ += (Height - DamageVector[i].OffsetZ) * (Speed / 1195.f);

						if (DamageVector[i].OffsetZ > Height - (Height / 5))
							if (DamageVector[i].Alpha > 0)
								DamageVector[i].Alpha -= 10;

						if (DamageVector[i].Alpha < 0)
							DamageVector[i].Alpha = 0;

						Vector ScreenPosition;
						Vector WorldPosition = Vector(DamageVector[i].Pos.x,
							DamageVector[i].Pos.y,
							DamageVector[i].Pos.z + DamageVector[i].OffsetZ);

						Color DamageColor = Color(GP_Misc->DamageInfoColor.r(), GP_Misc->DamageInfoColor.g(), GP_Misc->DamageInfoColor.b(), DamageVector[i].Alpha);

						if (CGlobal::WorldToScreen(WorldPosition, ScreenPosition))
							GP_Render->DrawString(GP_Misc->TextDamageInfo, Vec2(ScreenPosition.x, ScreenPosition.y), DamageColor, false, true,
								to_string(DamageVector.back().Number).c_str());

						if (DamageVector[i].OffsetZ > Height - 1)
							DamageVector.erase(DamageVector.begin() + i);
					}

					if (GP_Misc->DamageInfoPosition == 0)
						if (DamageVector[i].EndTime < I::GlobalVars()->curtime)
							if (CGlobal::IsGameReady)
								DamageVector.erase(DamageVector.begin() + i);
				}
			}
		}
	}

}

int CHitListener::GetEventDebugID(void)
{
	return 0x2A;
}
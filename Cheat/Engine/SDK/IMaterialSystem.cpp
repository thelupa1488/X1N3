#include "IMaterialSystem.h"

namespace SDK
{
	using InitKeyValuesFn = void(__thiscall*)(void* thisptr, const char* Name);
	using LoadFromBufferFn = void(__thiscall*)(void* thisptr, const char* resourceName, const char* pBuffer, void* pFileSystem, const char* pPathID, void* pfnEvaluateSymbolProc);

	InitKeyValuesFn InitKeyValuesEx;
	LoadFromBufferFn LoadFromBufferEx;

	void IMaterialSystem::InitKeyValues(KeyValues* pKeyValues, const char* Name)
	{
		InitKeyValuesEx = (InitKeyValuesFn)offsets["InitKeyValuesEx"];
		InitKeyValuesEx(pKeyValues, Name);
	}

	void IMaterialSystem::LoadFromBuffer(KeyValues* pKeyValues, const char* resourceName, const char* pBuffer, void* pFileSystem, const char* pPathID, void* pfnEvaluateSymbolProc)
	{
		LoadFromBufferEx = (LoadFromBufferFn)offsets["LoadFromBufferEx"];
		LoadFromBufferEx(pKeyValues, resourceName, pBuffer, pFileSystem, pPathID, pfnEvaluateSymbolProc);
	}

	int created = 0;
	IMaterial* IMaterialSystem::CreateMaterial(bool flat, bool ignorez, bool wireframed)
	{
		std::string Type = (flat) ? ("UnlitGeneric") : ("VertexLitGeneric");

		std::string matdata = ("\"") + Type + ("\"\n{\n\t\"$basetexture\" \"vgui/white_additive\"\n\t\"$envmap\"  \"\"\n\t\"$model\" \"1\"\n\t\"$flat\" \"1\"\n\t\"$nocull\"  \"0\"\n\t\"$selfillum\" \"1\"\n\t\"$halflambert\" \"1\"\n\t\"$nofog\"  \"0\"\n\t\"$znearer\" \"0\"\n\t\"$wireframe\" \"") + std::to_string(wireframed) + ("\"\n\t\"$ignorez\" \"") + std::to_string(ignorez) + ("\"\n}\n");

		std::string matname = ("custom_") + std::to_string(created);
		++created;

		KeyValues* pKeyValues = new KeyValues(matname.c_str());
		InitKeyValues(pKeyValues, Type.c_str());
		LoadFromBuffer(pKeyValues, matname.c_str(), matdata.c_str());

		typedef IMaterial* (__thiscall* OriginalFn)(void*, const char* pMaterialName, KeyValues* pVMTKeyValues);
		IMaterial* createdMaterial = GetMethod< OriginalFn >(this, 83)(this, matname.c_str(), pKeyValues);

		createdMaterial->IncrementReferenceCount();

		return createdMaterial;
	}

	IMaterial* IMaterialSystem::FindMaterial(char const* pMaterialName, const char* pTextureGroupName, bool complain, const char* pComplainPrefix)
	{
		typedef IMaterial* (__thiscall* OriginalFn)(void*, char const* pMaterialName, const char* pTextureGroupName, bool complain, const char* pComplainPrefix);
		return GetMethod< OriginalFn >(this, 84)(this, pMaterialName, pTextureGroupName, complain, pComplainPrefix);
	}
}
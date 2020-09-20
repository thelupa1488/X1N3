#pragma once
#include "SDK.h"

namespace SDK
{
    class NetworkStringTable
    {
    public:
        int AddString(bool isServer, const char* value, int length = -1, const void* userdata = nullptr)
        {
            typedef int(__thiscall* oAddString)(void*, bool, const char*, int, const void*);
            return GetMethod<oAddString>(this, 8)(this, isServer, value, length, userdata);
        }
    };

    class NetworkStringTableContainer
    {
    public:
        NetworkStringTable* FindTable(const char* name)
        {
            typedef NetworkStringTable*(__thiscall* oFindTable)(void*, const char*);
            return GetMethod<oFindTable>(this, 3)(this, name);
        }
    };
}
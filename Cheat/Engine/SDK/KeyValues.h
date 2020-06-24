#pragma once
#include "SDK.h"

namespace SDK
{
    class KeyValues 
    {
    public:
        std::uintptr_t keyValuesFromString;
        KeyValues* (__thiscall* keyValuesFindKey)(KeyValues* keyValues, const char* keyName, bool create);
        void(__thiscall* keyValuesSetString)(KeyValues* keyValues, const char* value);
        static KeyValues* FromString(const char* name, const char* value);
        KeyValues* FindKey(const char* keyName, bool create);
        void SetString(const char* keyName, const char* value);
    };
}      
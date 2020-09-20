#include "SDK.h"
#include "../../Main.h"
template <typename T>
const auto relativeToAbsolute(int* address)
{
    return reinterpret_cast<T>(reinterpret_cast<char*>(address + 1) + *address);
}

namespace SDK
{
    KeyValues* KeyValues::FromString(const char* name, const char* value)
    {
        const auto pFromString = relativeToAbsolute<decltype(keyValuesFromString)>(reinterpret_cast<int*>(offsets["FromString"])); //need fix
        KeyValues* keyValues;
        __asm 
        {
            push 0
            mov edx, value
            mov ecx, name
            call pFromString
            add esp, 4
            mov keyValues, eax
        }

        return keyValues;
    }

    KeyValues* KeyValues::FindKey(const char* keyName, bool create)
    {
        //using FindKeyFn = KeyValues*(__thiscall*)(KeyValues*, const char*, bool);
        //static auto pFindKey = (FindKeyFn)offsets["FindKey"];
        auto pFindKey = relativeToAbsolute<decltype(keyValuesFindKey)>(reinterpret_cast<int*>(offsets["FindKey"]));
        return pFindKey(this, keyName, create);
    }

    void KeyValues::SetString(const char* keyName, const char* value)
    {
        //using SetStringFn = void(__thiscall*)(KeyValues*, const char*);
        //static auto pSetSring = (SetStringFn)offsets["FindKey"];
        auto pSetSring = relativeToAbsolute<decltype(keyValuesSetString)>(reinterpret_cast<int*>(offsets["SetString"]));
        if (const auto key = FindKey(keyName, true))
            pSetSring(key, value);
    }
}                                                       
#include "SDK.h"
#include "../../Main.h"
template <typename T>
static constexpr auto relativeToAbsolute(int* address) noexcept
{
    return reinterpret_cast<T>(reinterpret_cast<char*>(address + 1) + *address);
}

namespace SDK
{
    KeyValues* KeyValues::FromString(const char* name, const char* value)
    {
        const auto pFromString = relativeToAbsolute<decltype(keyValuesFromString)>(reinterpret_cast<int*>(Utils::PatternScan(clientFactory, "E8 ? ? ? ? 83 C4 04 89 45 D8") + 1)); //доделать
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
        auto pFindKey = relativeToAbsolute<decltype(keyValuesFindKey)>(reinterpret_cast<int*>(Utils::PatternScan(clientFactory, "E8 ? ? ? ? F7 45") + 1));//доделать
        return pFindKey(this, keyName, create);
    }

    void KeyValues::SetString(const char* keyName, const char* value)
    {
        auto pSetSring = relativeToAbsolute<decltype(keyValuesSetString)>(reinterpret_cast<int*>(Utils::PatternScan(clientFactory, "E8 ? ? ? ? 89 77 38") + 1));//доделать
        if (const auto key = FindKey(keyName, true))
            pSetSring(key, value);
    }
}                                                       
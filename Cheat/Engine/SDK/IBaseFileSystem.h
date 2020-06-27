#pragma once
#include "SDK.h"

namespace SDK
{
    class IBaseFileSystem
    {
    public:
        int read(void* output, int size, void* file) {
            typedef int(__thiscall* tRead)(void*, void*, int, void*);
            return GetMethod<tRead>(this, 0)(this, output, size, file);
        }

        void* open(const char* file_name, const char* options, const char* path_id) {
            typedef void* (__thiscall* tOpen)(void*, const char*, const char*, const char*);
            return GetMethod<tOpen>(this, 2)(this, file_name, options, path_id);
        }

        void close(void* file) {
            typedef void(__thiscall* tClose)(void*, void*);
            return GetMethod<tClose>(this, 3)(this, file);
        }

        unsigned int size(void* file) {
            typedef unsigned int(__thiscall* tSize)(void*, void*);
            return GetMethod<tSize>(this, 7)(this, file);
        }
    };
}

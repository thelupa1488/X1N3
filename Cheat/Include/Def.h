#pragma once
#include "../Engine/XorStr.h"
#include <VMProtectSDK.h>

#define YOUGAMEBIZ
#define ENABLE_XOR_STR
#define ENABLE_VMP

//#define ENABLE_INVENTORY

#define PRESENT_ENABLE

//#define ONLY_DRAW_HOOK
//#define ENABLE_CONSOLE_LOG
//#define ENABLE_DEBUG_FILE

#define MAX_FONT_SIZE 30
#define ENABLE_HOOK_CS_WND_PROC

#define PATH_TO_CHEAT_SETTINGS XorStr("\\X1N3\\")

#define MAX_ENTITY_PLAYERS 64

#define CHEAT_HEAD XorStr("X1N3")

#ifdef ENABLE_CONSOLE_LOG
#define ADD_LOG(m, ...) printf(m, __VA_ARGS__)
#else
#define ADD_LOG(m, ...)
#endif

#ifdef ENABLE_XOR_STR
#define XorStr( s ) (_xor_( s ).c_str())
#else
#define XorStr( s ) s
#endif

#ifdef ENABLE_VMP
#define VMP_VIRTUAL(e) VMProtectBeginVirtualization(e);
#define VMP_MUTATION(e) VMProtectBeginMutation(e);
#define VMP_ULTRA(e) VMProtectBeginUltra(e);
#define VMP_BEGIN(e) VMProtectBegin(e);
#define VMP_END VMProtectEnd();
#define VMP_ProtectStringA(e) VMProtectDecryptStringA(e)
#else
#define VMP_MUTATION(e);
#define VMP_ULTRA(e);
#define VMP_BEGIN(e);
#define VMP_END
#define VMP_ProtectStringA(e) 
#endif

#define DELETE_PTR(name) delete name; name = nullptr

#define EX_ARRAYSIZE(_ARR)      ((int)(sizeof(_ARR)/sizeof(*_ARR)))
#define EX_PI                   3.14159265358979323846f
#define EX_OFFSETOF(_TYPE,_ELM) ((size_t)&(((_TYPE*)0)->_ELM))

//offsets def
#define ptr(x, x1, x2) x((DWORD)x1 + (DWORD)x2)
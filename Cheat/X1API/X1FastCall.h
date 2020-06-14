#pragma once
#include <Windows.h>
#include <map>
#include "../Include/Def.h"
#include "cHide.h"

#define DEREF( name )*(UINT_PTR *)(name)
#define DEREF_64( name )*(DWORD64 *)(name)
#define DEREF_32( name )*(DWORD *)(name)
#define DEREF_16( name )*(WORD *)(name)
#define DEREF_8( name )*(BYTE *)(name)

template<typename T>
class Call
{
protected:
	Call() {}
	~Call() {}

	Call(const Call&) = delete;
	Call& operator=(const Call&) = delete;

	Call(Call&&) = delete;
	Call& operator=(Call&&) = delete;

public:
	static T& G()
	{
		static T inst{};
		return inst;
	}
};

class FastCall : public Call<FastCall>
{
private:

	std::map<std::string, FARPROC> lpAddrList
	{
		{XorStr("CreateThread"), pHideMe._GetProcAddress(pHideMe._GetModuleHandle(pHideMe.UTF8ToWstring("kernel32.dll").c_str()),XorStr("CreateThread"))},
		{XorStr("TerminateThread"), pHideMe._GetProcAddress(pHideMe._GetModuleHandle(pHideMe.UTF8ToWstring("kernel32.dll").c_str()),XorStr("TerminateThread"))},
	    {XorStr("FreeLibraryAndExitThread"), pHideMe._GetProcAddress(pHideMe._GetModuleHandle(pHideMe.UTF8ToWstring("kernel32.dll").c_str()),XorStr("FreeLibraryAndExitThread"))},
		{XorStr("DisableThreadLibraryCalls"), pHideMe._GetProcAddress(pHideMe._GetModuleHandle(pHideMe.UTF8ToWstring("kernel32.dll").c_str()),XorStr("DisableThreadLibraryCalls"))},
		{XorStr("CloseHandle"), pHideMe._GetProcAddress(pHideMe._GetModuleHandle(pHideMe.UTF8ToWstring("kernel32.dll").c_str()),XorStr("CloseHandle"))},
		{XorStr("MessageBoxA"), pHideMe._GetProcAddress(pHideMe._GetModuleHandle(pHideMe.UTF8ToWstring("User32.dll").c_str()),XorStr("MessageBoxA"))},
		{XorStr("FindWindowA"), pHideMe._GetProcAddress(pHideMe._GetModuleHandle(pHideMe.UTF8ToWstring("User32.dll").c_str()),XorStr("FindWindowA"))},
		{XorStr("PlaySoundA"), pHideMe._GetProcAddress(pHideMe._GetModuleHandle(pHideMe.UTF8ToWstring("Winmm.dll").c_str()),XorStr("PlaySoundA"))},
		{XorStr("mouse_event"), pHideMe._GetProcAddress(pHideMe._GetModuleHandle(pHideMe.UTF8ToWstring("User32.dll").c_str()),XorStr("mouse_event"))},
		{XorStr("GetFileAttributesA"), pHideMe._GetProcAddress(pHideMe._GetModuleHandle(pHideMe.UTF8ToWstring("kernel32.dll").c_str()),XorStr("GetFileAttributesA"))},
		{XorStr("GetThreadContext"), pHideMe._GetProcAddress(pHideMe._GetModuleHandle(pHideMe.UTF8ToWstring("kernel32.dll").c_str()),XorStr("GetThreadContext"))},
		{XorStr("GetClientRect"), pHideMe._GetProcAddress(pHideMe._GetModuleHandle(pHideMe.UTF8ToWstring("User32.dll").c_str()),XorStr("GetClientRect"))},
		{XorStr("SetCursor"), pHideMe._GetProcAddress(pHideMe._GetModuleHandle(pHideMe.UTF8ToWstring("User32.dll").c_str()),XorStr("SetCursor"))},
		{XorStr("ImmGetContext"), pHideMe._GetProcAddress(pHideMe._GetModuleHandle(pHideMe.UTF8ToWstring("Imm32.dll").c_str()),XorStr("ImmGetContext"))},
		{XorStr("ImmSetCompositionWindow"), pHideMe._GetProcAddress(pHideMe._GetModuleHandle(pHideMe.UTF8ToWstring("Imm32.dll").c_str()),XorStr("ImmSetCompositionWindow"))},
		{XorStr("WaitForSingleObject"), pHideMe._GetProcAddress(pHideMe._GetModuleHandle(pHideMe.UTF8ToWstring("kernel32.dll").c_str()),XorStr("WaitForSingleObject"))},
		{XorStr("MultiByteToWideChar"), pHideMe._GetProcAddress(pHideMe._GetModuleHandle(pHideMe.UTF8ToWstring("kernel32.dll").c_str()),XorStr("MultiByteToWideChar"))},
		{XorStr("GetTickCount64"), pHideMe._GetProcAddress(pHideMe._GetModuleHandle(pHideMe.UTF8ToWstring("kernel32.dll").c_str()),XorStr("GetTickCount64"))},
		{XorStr("GetLastError"), pHideMe._GetProcAddress(pHideMe._GetModuleHandle(pHideMe.UTF8ToWstring("kernel32.dll").c_str()),XorStr("GetLastError"))},
		{XorStr("CreateEventA"), pHideMe._GetProcAddress(pHideMe._GetModuleHandle(pHideMe.UTF8ToWstring("kernel32.dll").c_str()),XorStr("CreateEventA"))},
		{XorStr("VirtualQuery"), pHideMe._GetProcAddress(pHideMe._GetModuleHandle(pHideMe.UTF8ToWstring("kernel32.dll").c_str()),XorStr("VirtualQuery"))},
		{XorStr("FindFirstFileA"), pHideMe._GetProcAddress(pHideMe._GetModuleHandle(pHideMe.UTF8ToWstring("kernel32.dll").c_str()),XorStr("FindFirstFileA"))},
		{XorStr("FindNextFileA"), pHideMe._GetProcAddress(pHideMe._GetModuleHandle(pHideMe.UTF8ToWstring("kernel32.dll").c_str()),XorStr("FindNextFileA"))},
		{XorStr("GetFullPathNameA"), pHideMe._GetProcAddress(pHideMe._GetModuleHandle(pHideMe.UTF8ToWstring("kernel32.dll").c_str()),XorStr("GetFullPathNameA"))},
		{XorStr("FindClose"), pHideMe._GetProcAddress(pHideMe._GetModuleHandle(pHideMe.UTF8ToWstring("kernel32.dll").c_str()),XorStr("FindClose"))},
		{XorStr("lstrcmpiA"), pHideMe._GetProcAddress(pHideMe._GetModuleHandle(pHideMe.UTF8ToWstring("kernel32.dll").c_str()),XorStr("lstrcmpiA"))},
		{XorStr("Sleep"), pHideMe._GetProcAddress(pHideMe._GetModuleHandle(pHideMe.UTF8ToWstring("kernel32.dll").c_str()),XorStr("Sleep"))},
		{XorStr("GetProcAddress"), pHideMe._GetProcAddress(pHideMe._GetModuleHandle(pHideMe.UTF8ToWstring("kernel32.dll").c_str()),XorStr("GetProcAddress"))},
		{XorStr("IsBadCodePtr"), pHideMe._GetProcAddress(pHideMe._GetModuleHandle(pHideMe.UTF8ToWstring("kernel32.dll").c_str()),XorStr("IsBadCodePtr"))},
		{XorStr("IsBadReadPtr"), pHideMe._GetProcAddress(pHideMe._GetModuleHandle(pHideMe.UTF8ToWstring("kernel32.dll").c_str()),XorStr("IsBadReadPtr"))},
		{XorStr("GetFileAttributesA"), pHideMe._GetProcAddress(pHideMe._GetModuleHandle(pHideMe.UTF8ToWstring("kernel32.dll").c_str()),XorStr("GetFileAttributesA"))},
		{XorStr("DeleteFileA"), pHideMe._GetProcAddress(pHideMe._GetModuleHandle(pHideMe.UTF8ToWstring("kernel32.dll").c_str()),XorStr("DeleteFileA"))},
		{XorStr("GlobalAlloc"), pHideMe._GetProcAddress(pHideMe._GetModuleHandle(pHideMe.UTF8ToWstring("kernel32.dll").c_str()),XorStr("GlobalAlloc"))},
		{XorStr("GetLocalTime"), pHideMe._GetProcAddress(pHideMe._GetModuleHandle(pHideMe.UTF8ToWstring("kernel32.dll").c_str()),XorStr("GetLocalTime"))},
		{XorStr("GlobalLock"), pHideMe._GetProcAddress(pHideMe._GetModuleHandle(pHideMe.UTF8ToWstring("kernel32.dll").c_str()),XorStr("GlobalLock"))},
		{XorStr("WideCharToMultiByte"), pHideMe._GetProcAddress(pHideMe._GetModuleHandle(pHideMe.UTF8ToWstring("kernel32.dll").c_str()),XorStr("WideCharToMultiByte"))},
		{XorStr("CreateDirectoryA"), pHideMe._GetProcAddress(pHideMe._GetModuleHandle(pHideMe.UTF8ToWstring("kernel32.dll").c_str()),XorStr("CreateDirectoryA"))},
		{XorStr("GlobalUnlock"), pHideMe._GetProcAddress(pHideMe._GetModuleHandle(pHideMe.UTF8ToWstring("kernel32.dll").c_str()),XorStr("GlobalUnlock"))},
		{XorStr("AddVectoredExceptionHandler"), pHideMe._GetProcAddress(pHideMe._GetModuleHandle(pHideMe.UTF8ToWstring("kernel32.dll").c_str()),XorStr("AddVectoredExceptionHandler"))},
		{XorStr("Beep"), pHideMe._GetProcAddress(pHideMe._GetModuleHandle(pHideMe.UTF8ToWstring("kernel32.dll").c_str()),XorStr("Beep"))},
		{XorStr("GetCurrentThread"), pHideMe._GetProcAddress(pHideMe._GetModuleHandle(pHideMe.UTF8ToWstring("kernel32.dll").c_str()),XorStr("GetCurrentThread"))},
		{XorStr("GetModuleHandleW"), pHideMe._GetProcAddress(pHideMe._GetModuleHandle(pHideMe.UTF8ToWstring("kernel32.dll").c_str()),XorStr("GetModuleHandleW"))},
		{XorStr("QueryPerformanceFrequency"), pHideMe._GetProcAddress(pHideMe._GetModuleHandle(pHideMe.UTF8ToWstring("kernel32.dll").c_str()),XorStr("QueryPerformanceFrequency"))},
		{XorStr("QueryPerformanceCounter"), pHideMe._GetProcAddress(pHideMe._GetModuleHandle(pHideMe.UTF8ToWstring("kernel32.dll").c_str()),XorStr("QueryPerformanceCounter"))},
		{XorStr("TerminateProcess"), pHideMe._GetProcAddress(pHideMe._GetModuleHandle(pHideMe.UTF8ToWstring("kernel32.dll").c_str()),XorStr("TerminateProcess"))},
		{XorStr("SetEndOfFile"), pHideMe._GetProcAddress(pHideMe._GetModuleHandle(pHideMe.UTF8ToWstring("kernel32.dll").c_str()),XorStr("SetEndOfFile"))},
		{XorStr("WriteConsoleW"), pHideMe._GetProcAddress(pHideMe._GetModuleHandle(pHideMe.UTF8ToWstring("kernel32.dll").c_str()),XorStr("WriteConsoleW"))},
		{XorStr("HeapSize"), pHideMe._GetProcAddress(pHideMe._GetModuleHandle(pHideMe.UTF8ToWstring("kernel32.dll").c_str()),XorStr("HeapSize"))},
		{XorStr("CreateFileW"), pHideMe._GetProcAddress(pHideMe._GetModuleHandle(pHideMe.UTF8ToWstring("kernel32.dll").c_str()),XorStr("CreateFileW"))},
		{XorStr("SetStdHandle"), pHideMe._GetProcAddress(pHideMe._GetModuleHandle(pHideMe.UTF8ToWstring("kernel32.dll").c_str()),XorStr("SetStdHandle"))},
		{XorStr("SetEnvironmentVariableW"), pHideMe._GetProcAddress(pHideMe._GetModuleHandle(pHideMe.UTF8ToWstring("kernel32.dll").c_str()),XorStr("SetEnvironmentVariableW"))},
		{XorStr("GetModuleFileNameA"), pHideMe._GetProcAddress(pHideMe._GetModuleHandle(pHideMe.UTF8ToWstring("kernel32.dll").c_str()),XorStr("GetModuleFileNameA"))},
		{XorStr("GetEnvironmentStringsW"), pHideMe._GetProcAddress(pHideMe._GetModuleHandle(pHideMe.UTF8ToWstring("kernel32.dll").c_str()),XorStr("GetEnvironmentStringsW"))},
		{XorStr("GetCommandLineW"), pHideMe._GetProcAddress(pHideMe._GetModuleHandle(pHideMe.UTF8ToWstring("kernel32.dll").c_str()),XorStr("GetCommandLineW"))},
		{XorStr("GetCommandLineA"), pHideMe._GetProcAddress(pHideMe._GetModuleHandle(pHideMe.UTF8ToWstring("kernel32.dll").c_str()),XorStr("GetCommandLineA"))},
		{XorStr("GetOEMCP"), pHideMe._GetProcAddress(pHideMe._GetModuleHandle(pHideMe.UTF8ToWstring("kernel32.dll").c_str()),XorStr("GetOEMCP"))},
		{XorStr("GetACP"), pHideMe._GetProcAddress(pHideMe._GetModuleHandle(pHideMe.UTF8ToWstring("kernel32.dll").c_str()),XorStr("GetACP"))},
		{XorStr("IsValidCodePage"), pHideMe._GetProcAddress(pHideMe._GetModuleHandle(pHideMe.UTF8ToWstring("kernel32.dll").c_str()),XorStr("IsValidCodePage"))},
		{XorStr("FindNextFileW"), pHideMe._GetProcAddress(pHideMe._GetModuleHandle(pHideMe.UTF8ToWstring("kernel32.dll").c_str()),XorStr("FindNextFileW"))},
		{XorStr("K32GetModuleInformation"), pHideMe._GetProcAddress(pHideMe._GetModuleHandle(pHideMe.UTF8ToWstring("kernel32.dll").c_str()),XorStr("K32GetModuleInformation"))},
		{XorStr("GetModuleHandleA"), pHideMe._GetProcAddress(pHideMe._GetModuleHandle(pHideMe.UTF8ToWstring("kernel32.dll").c_str()),XorStr("GetModuleHandleA"))},
		{XorStr("lstrlenA"), pHideMe._GetProcAddress(pHideMe._GetModuleHandle(pHideMe.UTF8ToWstring("kernel32.dll").c_str()),XorStr("lstrlenA"))},
		{XorStr("GetCurrentProcess"), pHideMe._GetProcAddress(pHideMe._GetModuleHandle(pHideMe.UTF8ToWstring("kernel32.dll").c_str()),XorStr("GetCurrentProcess"))},
		{XorStr("GetProcessHeap"), pHideMe._GetProcAddress(pHideMe._GetModuleHandle(pHideMe.UTF8ToWstring("kernel32.dll").c_str()),XorStr("GetProcessHeap"))},
		{XorStr("HeapAlloc"), pHideMe._GetProcAddress(pHideMe._GetModuleHandle(pHideMe.UTF8ToWstring("kernel32.dll").c_str()),XorStr("HeapAlloc"))},
		{XorStr("FindFirstFileExW"), pHideMe._GetProcAddress(pHideMe._GetModuleHandle(pHideMe.UTF8ToWstring("kernel32.dll").c_str()),XorStr("FindFirstFileExW"))},
		{XorStr("HeapReAlloc"), pHideMe._GetProcAddress(pHideMe._GetModuleHandle(pHideMe.UTF8ToWstring("kernel32.dll").c_str()),XorStr("HeapReAlloc"))},
		{XorStr("SetFilePointerEx"), pHideMe._GetProcAddress(pHideMe._GetModuleHandle(pHideMe.UTF8ToWstring("kernel32.dll").c_str()),XorStr("SetFilePointerEx"))},
		{XorStr("FlushFileBuffers"), pHideMe._GetProcAddress(pHideMe._GetModuleHandle(pHideMe.UTF8ToWstring("kernel32.dll").c_str()),XorStr("FlushFileBuffers"))},
		{XorStr("EnumSystemLocalesW"), pHideMe._GetProcAddress(pHideMe._GetModuleHandle(pHideMe.UTF8ToWstring("kernel32.dll").c_str()),XorStr("EnumSystemLocalesW"))},
		{XorStr("GetUserDefaultLCID"), pHideMe._GetProcAddress(pHideMe._GetModuleHandle(pHideMe.UTF8ToWstring("kernel32.dll").c_str()),XorStr("GetUserDefaultLCID"))},
		{XorStr("IsValidLocale"), pHideMe._GetProcAddress(pHideMe._GetModuleHandle(pHideMe.UTF8ToWstring("kernel32.dll").c_str()),XorStr("IsValidLocale"))},
		{XorStr("GetFileType"), pHideMe._GetProcAddress(pHideMe._GetModuleHandle(pHideMe.UTF8ToWstring("kernel32.dll").c_str()),XorStr("GetFileType"))},
		{XorStr("GetStdHandle"), pHideMe._GetProcAddress(pHideMe._GetModuleHandle(pHideMe.UTF8ToWstring("kernel32.dll").c_str()),XorStr("GetStdHandle"))},
		{XorStr("HeapFree"), pHideMe._GetProcAddress(pHideMe._GetModuleHandle(pHideMe.UTF8ToWstring("kernel32.dll").c_str()),XorStr("HeapFree"))},
		{XorStr("GetConsoleCP"), pHideMe._GetProcAddress(pHideMe._GetModuleHandle(pHideMe.UTF8ToWstring("kernel32.dll").c_str()),XorStr("GetConsoleCP"))},
		{XorStr("WriteFile"), pHideMe._GetProcAddress(pHideMe._GetModuleHandle(pHideMe.UTF8ToWstring("kernel32.dll").c_str()),XorStr("WriteFile"))},
		{XorStr("ReadConsoleW"), pHideMe._GetProcAddress(pHideMe._GetModuleHandle(pHideMe.UTF8ToWstring("kernel32.dll").c_str()),XorStr("ReadConsoleW"))},
		{XorStr("GetConsoleMode"), pHideMe._GetProcAddress(pHideMe._GetModuleHandle(pHideMe.UTF8ToWstring("kernel32.dll").c_str()),XorStr("GetConsoleMode"))},
		{XorStr("GetModuleFileNameW"), pHideMe._GetProcAddress(pHideMe._GetModuleHandle(pHideMe.UTF8ToWstring("kernel32.dll").c_str()),XorStr("GetModuleFileNameW"))},
		{XorStr("GetModuleHandleExW"), pHideMe._GetProcAddress(pHideMe._GetModuleHandle(pHideMe.UTF8ToWstring("kernel32.dll").c_str()),XorStr("GetModuleHandleExW"))},
		{XorStr("ExitProcess"), pHideMe._GetProcAddress(pHideMe._GetModuleHandle(pHideMe.UTF8ToWstring("kernel32.dll").c_str()),XorStr("ExitProcess"))},
		{XorStr("ReadFile"), pHideMe._GetProcAddress(pHideMe._GetModuleHandle(pHideMe.UTF8ToWstring("kernel32.dll").c_str()),XorStr("ReadFile"))},
		{XorStr("LoadLibraryExW"), pHideMe._GetProcAddress(pHideMe._GetModuleHandle(pHideMe.UTF8ToWstring("kernel32.dll").c_str()),XorStr("LoadLibraryExW"))},
		{XorStr("FreeLibrary"), pHideMe._GetProcAddress(pHideMe._GetModuleHandle(pHideMe.UTF8ToWstring("kernel32.dll").c_str()),XorStr("FreeLibrary"))},
		{XorStr("InterlockedFlushSList"), pHideMe._GetProcAddress(pHideMe._GetModuleHandle(pHideMe.UTF8ToWstring("kernel32.dll").c_str()),XorStr("InterlockedFlushSList"))},
		{XorStr("RaiseException"), pHideMe._GetProcAddress(pHideMe._GetModuleHandle(pHideMe.UTF8ToWstring("kernel32.dll").c_str()),XorStr("RaiseException"))},
		{XorStr("RtlUnwind"), pHideMe._GetProcAddress(pHideMe._GetModuleHandle(pHideMe.UTF8ToWstring("kernel32.dll").c_str()),XorStr("RtlUnwind"))},
		{XorStr("InitializeSListHead"), pHideMe._GetProcAddress(pHideMe._GetModuleHandle(pHideMe.UTF8ToWstring("kernel32.dll").c_str()),XorStr("InitializeSListHead"))},
		{XorStr("GetCurrentThreadId"), pHideMe._GetProcAddress(pHideMe._GetModuleHandle(pHideMe.UTF8ToWstring("kernel32.dll").c_str()),XorStr("GetCurrentThreadId"))},
		{XorStr("FreeEnvironmentStringsW"), pHideMe._GetProcAddress(pHideMe._GetModuleHandle(pHideMe.UTF8ToWstring("kernel32.dll").c_str()),XorStr("FreeEnvironmentStringsW"))},
		{XorStr("EnterCriticalSection"), pHideMe._GetProcAddress(pHideMe._GetModuleHandle(pHideMe.UTF8ToWstring("kernel32.dll").c_str()),XorStr("EnterCriticalSection"))},
		{XorStr("LeaveCriticalSection"), pHideMe._GetProcAddress(pHideMe._GetModuleHandle(pHideMe.UTF8ToWstring("kernel32.dll").c_str()),XorStr("LeaveCriticalSection"))},
		{XorStr("DeleteCriticalSection"), pHideMe._GetProcAddress(pHideMe._GetModuleHandle(pHideMe.UTF8ToWstring("kernel32.dll").c_str()),XorStr("DeleteCriticalSection"))},
		{XorStr("SetLastError"), pHideMe._GetProcAddress(pHideMe._GetModuleHandle(pHideMe.UTF8ToWstring("kernel32.dll").c_str()),XorStr("SetLastError"))},
		{XorStr("InitializeCriticalSectionAndSpinCount"), pHideMe._GetProcAddress(pHideMe._GetModuleHandle(pHideMe.UTF8ToWstring("kernel32.dll").c_str()),XorStr("InitializeCriticalSectionAndSpinCount"))},
		{XorStr("CreateEventW"), pHideMe._GetProcAddress(pHideMe._GetModuleHandle(pHideMe.UTF8ToWstring("kernel32.dll").c_str()),XorStr("CreateEventW"))},
		{XorStr("SwitchToThread"), pHideMe._GetProcAddress(pHideMe._GetModuleHandle(pHideMe.UTF8ToWstring("kernel32.dll").c_str()),XorStr("SwitchToThread"))},
		{XorStr("TlsAlloc"), pHideMe._GetProcAddress(pHideMe._GetModuleHandle(pHideMe.UTF8ToWstring("kernel32.dll").c_str()),XorStr("TlsAlloc"))},
		{XorStr("TlsGetValue"), pHideMe._GetProcAddress(pHideMe._GetModuleHandle(pHideMe.UTF8ToWstring("kernel32.dll").c_str()),XorStr("TlsGetValue"))},
		{XorStr("TlsSetValue"), pHideMe._GetProcAddress(pHideMe._GetModuleHandle(pHideMe.UTF8ToWstring("kernel32.dll").c_str()),XorStr("TlsSetValue"))},
		{XorStr("TlsFree"), pHideMe._GetProcAddress(pHideMe._GetModuleHandle(pHideMe.UTF8ToWstring("kernel32.dll").c_str()),XorStr("TlsFree"))},
		{XorStr("GetSystemTimeAsFileTime"), pHideMe._GetProcAddress(pHideMe._GetModuleHandle(pHideMe.UTF8ToWstring("kernel32.dll").c_str()),XorStr("GetSystemTimeAsFileTime"))},
		{XorStr("EncodePointer"), pHideMe._GetProcAddress(pHideMe._GetModuleHandle(pHideMe.UTF8ToWstring("kernel32.dll").c_str()),XorStr("EncodePointer"))},
		{XorStr("DecodePointer"), pHideMe._GetProcAddress(pHideMe._GetModuleHandle(pHideMe.UTF8ToWstring("kernel32.dll").c_str()),XorStr("DecodePointer"))},
		{XorStr("GetStringTypeW"), pHideMe._GetProcAddress(pHideMe._GetModuleHandle(pHideMe.UTF8ToWstring("kernel32.dll").c_str()),XorStr("GetStringTypeW"))},
		{XorStr("CompareStringW"), pHideMe._GetProcAddress(pHideMe._GetModuleHandle(pHideMe.UTF8ToWstring("kernel32.dll").c_str()),XorStr("CompareStringW"))},
		{XorStr("LCMapStringW"), pHideMe._GetProcAddress(pHideMe._GetModuleHandle(pHideMe.UTF8ToWstring("kernel32.dll").c_str()),XorStr("LCMapStringW"))},
		{XorStr("GetLocaleInfoW"), pHideMe._GetProcAddress(pHideMe._GetModuleHandle(pHideMe.UTF8ToWstring("kernel32.dll").c_str()),XorStr("GetLocaleInfoW"))},
		{XorStr("GetCPInfo"), pHideMe._GetProcAddress(pHideMe._GetModuleHandle(pHideMe.UTF8ToWstring("kernel32.dll").c_str()),XorStr("GetCPInfo"))},
		{XorStr("InitializeCriticalSection"), pHideMe._GetProcAddress(pHideMe._GetModuleHandle(pHideMe.UTF8ToWstring("kernel32.dll").c_str()),XorStr("InitializeCriticalSection"))},
		{XorStr("SetEvent"), pHideMe._GetProcAddress(pHideMe._GetModuleHandle(pHideMe.UTF8ToWstring("kernel32.dll").c_str()),XorStr("SetEvent"))},
		{XorStr("ResetEvent"), pHideMe._GetProcAddress(pHideMe._GetModuleHandle(pHideMe.UTF8ToWstring("kernel32.dll").c_str()),XorStr("ResetEvent"))},
		{XorStr("WaitForSingleObjectEx"), pHideMe._GetProcAddress(pHideMe._GetModuleHandle(pHideMe.UTF8ToWstring("kernel32.dll").c_str()),XorStr("WaitForSingleObjectEx"))},
		{XorStr("UnhandledExceptionFilter"), pHideMe._GetProcAddress(pHideMe._GetModuleHandle(pHideMe.UTF8ToWstring("kernel32.dll").c_str()),XorStr("UnhandledExceptionFilter"))},
		{XorStr("SetUnhandledExceptionFilter"), pHideMe._GetProcAddress(pHideMe._GetModuleHandle(pHideMe.UTF8ToWstring("kernel32.dll").c_str()),XorStr("SetUnhandledExceptionFilter"))},
		{XorStr("IsProcessorFeaturePresent"), pHideMe._GetProcAddress(pHideMe._GetModuleHandle(pHideMe.UTF8ToWstring("kernel32.dll").c_str()),XorStr("IsProcessorFeaturePresent"))},
		{XorStr("IsDebuggerPresent"), pHideMe._GetProcAddress(pHideMe._GetModuleHandle(pHideMe.UTF8ToWstring("kernel32.dll").c_str()),XorStr("IsDebuggerPresent"))},
		{XorStr("GetStartupInfoW"), pHideMe._GetProcAddress(pHideMe._GetModuleHandle(pHideMe.UTF8ToWstring("kernel32.dll").c_str()),XorStr("GetStartupInfoW"))},
		{XorStr("GetCurrentProcessId"), pHideMe._GetProcAddress(pHideMe._GetModuleHandle(pHideMe.UTF8ToWstring("kernel32.dll").c_str()),XorStr("GetCurrentProcessId"))},
		{XorStr("SetWindowLongA"), pHideMe._GetProcAddress(pHideMe._GetModuleHandle(pHideMe.UTF8ToWstring("User32.dll").c_str()),XorStr("SetWindowLongA"))},
		{XorStr("GetKeyState"), pHideMe._GetProcAddress(pHideMe._GetModuleHandle(pHideMe.UTF8ToWstring("User32.dll").c_str()),XorStr("GetKeyState"))},
		{XorStr("GetClipboardData"), pHideMe._GetProcAddress(pHideMe._GetModuleHandle(pHideMe.UTF8ToWstring("User32.dll").c_str()),XorStr("GetClipboardData"))},
		{XorStr("OpenClipboard"), pHideMe._GetProcAddress(pHideMe._GetModuleHandle(pHideMe.UTF8ToWstring("User32.dll").c_str()),XorStr("OpenClipboard"))},
		{XorStr("CloseClipboard"), pHideMe._GetProcAddress(pHideMe._GetModuleHandle(pHideMe.UTF8ToWstring("User32.dll").c_str()),XorStr("CloseClipboard"))},
		{XorStr("GetAsyncKeyState"), pHideMe._GetProcAddress(pHideMe._GetModuleHandle(pHideMe.UTF8ToWstring("User32.dll").c_str()),XorStr("GetAsyncKeyState"))},
		{XorStr("GetCursorPos"), pHideMe._GetProcAddress(pHideMe._GetModuleHandle(pHideMe.UTF8ToWstring("User32.dll").c_str()),XorStr("GetCursorPos"))},
		{XorStr("SetClipboardData"), pHideMe._GetProcAddress(pHideMe._GetModuleHandle(pHideMe.UTF8ToWstring("User32.dll").c_str()),XorStr("SetClipboardData"))},
		{XorStr("EmptyClipboard"), pHideMe._GetProcAddress(pHideMe._GetModuleHandle(pHideMe.UTF8ToWstring("User32.dll").c_str()),XorStr("EmptyClipboard"))},
		{XorStr("CallWindowProcA"), pHideMe._GetProcAddress(pHideMe._GetModuleHandle(pHideMe.UTF8ToWstring("User32.dll").c_str()),XorStr("CallWindowProcA"))},
		//{XorStr("VMProtectBeginVirtualization"), pHideMe._GetProcAddress(pHideMe._GetModuleHandle(pHideMe.UTF8ToWstring("VMProtectSDK32.dll").c_str()),XorStr("VMProtectBeginVirtualization"))},
		//{XorStr("VMProtectBeginMutation"), pHideMe._GetProcAddress(pHideMe._GetModuleHandle(pHideMe.UTF8ToWstring("VMProtectSDK32.dll").c_str()),XorStr("VMProtectBeginMutation"))},
		//{XorStr("VMProtectBeginUltra"), pHideMe._GetProcAddress(pHideMe._GetModuleHandle(pHideMe.UTF8ToWstring("VMProtectSDK32.dll").c_str()),XorStr("VMProtectBeginUltra"))},
		//{XorStr("VMProtectBegin"), pHideMe._GetProcAddress(pHideMe._GetModuleHandle(pHideMe.UTF8ToWstring("VMProtectSDK32.dll").c_str()),XorStr("VMProtectBegin"))},
		//{XorStr("VMProtectEnd"), pHideMe._GetProcAddress(pHideMe._GetModuleHandle(pHideMe.UTF8ToWstring("VMProtectSDK32.dll").c_str()),XorStr("VMProtectEnd"))},
		{XorStr("WinHttpOpenRequest"), pHideMe._GetProcAddress(pHideMe._GetModuleHandle(pHideMe.UTF8ToWstring("Winhttp.dll").c_str()),XorStr("WinHttpOpenRequest"))},
		{XorStr("WinHttpConnect"), pHideMe._GetProcAddress(pHideMe._GetModuleHandle(pHideMe.UTF8ToWstring("Winhttp.dll").c_str()),XorStr("WinHttpConnect"))},
		{XorStr("WinHttpOpen"), pHideMe._GetProcAddress(pHideMe._GetModuleHandle(pHideMe.UTF8ToWstring("Winhttp.dll").c_str()),XorStr("WinHttpOpen"))},
		{XorStr("WinHttpReadData"), pHideMe._GetProcAddress(pHideMe._GetModuleHandle(pHideMe.UTF8ToWstring("Winhttp.dll").c_str()),XorStr("WinHttpReadData"))},
		{XorStr("WinHttpQueryHeaders"), pHideMe._GetProcAddress(pHideMe._GetModuleHandle(pHideMe.UTF8ToWstring("Winhttp.dll").c_str()),XorStr("WinHttpQueryHeaders"))},
		{XorStr("WinHttpCloseHandle"), pHideMe._GetProcAddress(pHideMe._GetModuleHandle(pHideMe.UTF8ToWstring("Winhttp.dll").c_str()),XorStr("WinHttpCloseHandle"))},
		{XorStr("WinHttpSendRequest"), pHideMe._GetProcAddress(pHideMe._GetModuleHandle(pHideMe.UTF8ToWstring("Winhttp.dll").c_str()),XorStr("WinHttpSendRequest"))},
		{XorStr("WinHttpReceiveResponse"), pHideMe._GetProcAddress(pHideMe._GetModuleHandle(pHideMe.UTF8ToWstring("Winhttp.dll").c_str()),XorStr("WinHttpReceiveResponse"))},
		{XorStr("WinHttpQueryDataAvailable"), pHideMe._GetProcAddress(pHideMe._GetModuleHandle(pHideMe.UTF8ToWstring("Winhttp.dll").c_str()),XorStr("WinHttpQueryDataAvailable"))},
		{XorStr("InternetCloseHandle"), pHideMe._GetProcAddress(pHideMe._GetModuleHandle(pHideMe.UTF8ToWstring("Wininet.dll").c_str()),XorStr("InternetCloseHandle"))},
		{XorStr("InternetReadFile"), pHideMe._GetProcAddress(pHideMe._GetModuleHandle(pHideMe.UTF8ToWstring("Wininet.dll").c_str()),XorStr("InternetReadFile"))},
		{XorStr("HttpOpenRequestA"), pHideMe._GetProcAddress(pHideMe._GetModuleHandle(pHideMe.UTF8ToWstring("Wininet.dll").c_str()),XorStr("HttpOpenRequestA"))},
		{XorStr("InternetConnectA"), pHideMe._GetProcAddress(pHideMe._GetModuleHandle(pHideMe.UTF8ToWstring("Wininet.dll").c_str()),XorStr("InternetConnectA"))},
		{XorStr("InternetOpenA"), pHideMe._GetProcAddress(pHideMe._GetModuleHandle(pHideMe.UTF8ToWstring("Wininet.dll").c_str()),XorStr("InternetOpenA"))},
		{XorStr("HttpSendRequestA"), pHideMe._GetProcAddress(pHideMe._GetModuleHandle(pHideMe.UTF8ToWstring("Wininet.dll").c_str()),XorStr("HttpSendRequestA"))},
		{XorStr("InternetOpenUrlA"), pHideMe._GetProcAddress(pHideMe._GetModuleHandle(pHideMe.UTF8ToWstring("Wininet.dll").c_str()),XorStr("InternetOpenUrlA"))},
		{XorStr("D3DXCreateTextureFromFileInMemoryEx"), pHideMe._GetProcAddress(pHideMe._GetModuleHandle(pHideMe.UTF8ToWstring("d3dx9_43.dll").c_str()),XorStr("D3DXCreateTextureFromFileInMemoryEx"))},
		{XorStr("D3DXCreateTextureFromFileExA"), pHideMe._GetProcAddress(pHideMe._GetModuleHandle(pHideMe.UTF8ToWstring("d3dx9_43.dll").c_str()),XorStr("D3DXCreateTextureFromFileExA"))},
		{XorStr("CreateDXGIFactory1"), pHideMe._GetProcAddress(pHideMe._GetModuleHandle(pHideMe.UTF8ToWstring("dxgi.dll").c_str()),XorStr("CreateDXGIFactory1"))},
		{XorStr("DestroyWindow"), pHideMe._GetProcAddress(pHideMe._GetModuleHandle(pHideMe.UTF8ToWstring("User32.dll").c_str()),XorStr("DestroyWindow"))},
	};
public:

	void Start()
	{
		for (auto it = lpAddrList.begin(); it != lpAddrList.end(); ++it)
		{
			printf(XorStr(": %s "), it->first.c_str());
			printf(XorStr("add: %X\n"),DWORD(it->second));
			//it->second
		}
	}

#define ALL_A(...) __VA_ARGS__

#define CREATE_CALL(type, agrm, name, name_str, args1, args2, args3) type agrm t##name(args1){ \
	using t_##name = type(agrm*)(args2); \
	return reinterpret_cast<t_##name>(lpAddrList[name_str])(args3); \
	}

	CREATE_CALL(ALL_A(_Ret_maybenull_ HANDLE), WINAPI, _CreateThread, XorStr("CreateThread"),
		ALL_A(_In_opt_ LPSECURITY_ATTRIBUTES lpThreadAttributes,
			_In_ SIZE_T dwStackSize,
			_In_ LPTHREAD_START_ROUTINE lpStartAddress,
			_In_opt_ __drv_aliasesMem LPVOID lpParameter,
			_In_ DWORD dwCreationFlags,
			_Out_opt_ LPDWORD lpThreadId
		),
		ALL_A(_In_opt_ LPSECURITY_ATTRIBUTES,
			_In_ SIZE_T,
			_In_ LPTHREAD_START_ROUTINE,
			_In_opt_ __drv_aliasesMem LPVOID,
			_In_ DWORD,
			_Out_opt_ LPDWORD
		),
		ALL_A(_In_opt_ lpThreadAttributes,
			_In_ dwStackSize,
			_In_ lpStartAddress,
			_In_opt_ __drv_aliasesMem lpParameter,
			_In_ dwCreationFlags,
			_Out_opt_ lpThreadId
		));

	CREATE_CALL(BOOL, WINAPI, _TerminateThread, XorStr("TerminateThread"),
		ALL_A(_In_opt_ HANDLE hThread,
			_In_ DWORD  dwExitCode
		),
		ALL_A(_In_opt_ HANDLE,
			_In_     DWORD
		),
		ALL_A(_In_opt_ hThread,
			_In_     dwExitCode
		));

	CREATE_CALL(VOID, WINAPI, _FreeLibraryAndExitThread, XorStr("FreeLibraryAndExitThread"),
		ALL_A(_In_opt_ HMODULE hLibModule,
			_In_     DWORD   dwExitCode
		),
		ALL_A(_In_opt_ HMODULE,
			_In_     DWORD
		),
		ALL_A(_In_opt_ hLibModule,
			_In_     dwExitCode
		));

	CREATE_CALL(BOOL, WINAPI, _DisableThreadLibraryCalls, XorStr("DisableThreadLibraryCalls"),
		ALL_A(_In_opt_ HMODULE hLibModule
		),
		ALL_A(_In_opt_ HMODULE
		),
		ALL_A(_In_opt_ hLibModule
		));

	CREATE_CALL(VOID, WINAPI, _mouse_event, XorStr("mouse_event"),
		ALL_A(_In_ DWORD dwFlags,
			_In_ DWORD dx,
			_In_ DWORD dy,
			_In_ DWORD dwData,
			_In_ ULONG_PTR dwExtraInfo
		),
		ALL_A(_In_ DWORD,
			_In_ DWORD,
			_In_ DWORD,
			_In_ DWORD,
			_In_ ULONG_PTR
		),
		ALL_A(_In_ dwFlags,
			_In_ dx,
			_In_ dy,
			_In_ dwData,
			_In_ dwExtraInfo
		));

	CREATE_CALL(BOOL, WINAPI, _CloseHandle, XorStr("CloseHandle"),
		ALL_A(_In_ HANDLE hObject
		),
		ALL_A(_In_ HANDLE
		),
		ALL_A(_In_ hObject
		));

	CREATE_CALL(INT, WINAPI, _MessageBoxA, XorStr("MessageBoxA"),
		ALL_A(_In_opt_ HWND hWnd,
			_In_opt_ LPCSTR lpText,
			_In_opt_ LPCSTR lpCaption,
			_In_ UINT uType
		),
		ALL_A(_In_opt_ HWND,
			_In_opt_ LPCSTR,
			_In_opt_ LPCSTR,
			_In_ UINT
		),
		ALL_A(_In_opt_ hWnd,
			_In_opt_ lpText,
			_In_opt_ lpCaption,
			_In_ uType
		));

	CREATE_CALL(HWND, WINAPI, _FindWindowA, XorStr("FindWindowA"),
		ALL_A(_In_opt_ LPCSTR lpClassName,
			_In_opt_ LPCSTR lpWindowName
		),
		ALL_A(_In_opt_ LPCSTR,
			_In_opt_ LPCSTR
		),
		ALL_A(_In_opt_ lpClassName,
			_In_opt_ lpWindowName
		));

	CREATE_CALL(BOOL, WINAPI, _PlaySoundA, XorStr("PlaySoundA"),
		ALL_A(_In_opt_ LPCSTR pszSound,
			_In_opt_ HMODULE hmod,
			_In_ DWORD fdwSound
		),
		ALL_A(_In_opt_ LPCSTR,
			_In_opt_ HMODULE,
			_In_ DWORD
		),
		ALL_A(_In_opt_ pszSound,
			_In_opt_ hmod,
			_In_ fdwSound
		));

	CREATE_CALL(DWORD, WINAPI, _GetFileAttributesA, XorStr("GetFileAttributesA"),
		ALL_A(_In_ LPCSTR lpFileName
		),
		ALL_A(_In_ LPCSTR
		),
		ALL_A(_In_ lpFileName
		));

	CREATE_CALL(BOOL, WINAPI, _GetThreadContext, XorStr("GetThreadContext"),
		ALL_A(_In_ HANDLE hThread,
			_Inout_ LPCONTEXT lpContext
		),
		ALL_A(_In_ HANDLE,
			_Inout_ LPCONTEXT
		),
		ALL_A(_In_ hThread,
			_Inout_ lpContext
		));

	CREATE_CALL(BOOL, WINAPI, _GetClientRect, XorStr("GetClientRect"),
		ALL_A(_In_ HWND hWnd,
			_Out_ LPRECT lpRect
		),
		ALL_A(_In_ HWND,
			_Out_ LPRECT
		),
		ALL_A(_In_ hWnd,
			_Out_ lpRect
		));

	CREATE_CALL(HCURSOR, WINAPI, _SetCursor, XorStr("SetCursor"),
		ALL_A(_In_opt_ HCURSOR hCursor
		),
		ALL_A(_In_opt_ HCURSOR
		),
		ALL_A(_In_opt_ hCursor
		));

	CREATE_CALL(BOOL, WINAPI, _ImmSetCompositionWindow, XorStr("ImmSetCompositionWindow"),
		ALL_A(IN HIMC hm, _In_ LPCOMPOSITIONFORM lpCompForm
		),
		ALL_A(IN HIMC, _In_ LPCOMPOSITIONFORM
		),
		ALL_A(IN hm, _In_ lpCompForm
		));

	CREATE_CALL(HIMC, WINAPI, _ImmGetContext, XorStr("ImmGetContext"),
		ALL_A(IN HWND hw
		),
		ALL_A(IN HWND
		),
		ALL_A(IN hw
		));

	CREATE_CALL(HIMC, WINAPI, _WaitForSingleObject, XorStr("WaitForSingleObject"),
		ALL_A(_In_ HANDLE hHandle,
			_In_ DWORD dwMilliseconds
		),
		ALL_A(_In_ HANDLE,
			_In_ DWORD
		),
		ALL_A(_In_ hHandle,
			_In_ dwMilliseconds
		));

	CREATE_CALL(INT, WINAPI, _MultiByteToWideChar, XorStr("MultiByteToWideChar"),
		ALL_A(_In_ UINT CodePage,
			_In_ DWORD dwFlags,
			_In_NLS_string_(cbMultiByte) LPCCH lpMultiByteStr,
			_In_ int cbMultiByte,
			_Out_writes_to_opt_(cchWideChar, return) LPWSTR lpWideCharStr,
			_In_ int cchWideChar
		),
		ALL_A(_In_ UINT,
			_In_ DWORD,
			_In_NLS_string_(cbMultiByte) LPCCH,
			_In_ int cbMultiByte,
			_Out_writes_to_opt_(cchWideChar, return) LPWSTR,
			_In_ int
		),
		ALL_A(_In_ CodePage,
			_In_ dwFlags,
			_In_NLS_string_(cbMultiByte) lpMultiByteStr,
			_In_ cbMultiByte,
			_Out_writes_to_opt_(cchWideChar, return) lpWideCharStr,
			_In_ cchWideChar
		));

	CREATE_CALL(ULONGLONG, WINAPI, _GetTickCount64, XorStr("GetTickCount64"),
		ALL_A(
		),
		ALL_A(
		),
		ALL_A(
		));

	CREATE_CALL(DWORD, WINAPI, _GetLastError, XorStr("GetLastError"),
		ALL_A(
		),
		ALL_A(
		),
		ALL_A(
		));

	_Ret_maybenull_
		CREATE_CALL(HANDLE, WINAPI, _CreateEventA, XorStr("CreateEventA"),
			ALL_A(_In_opt_ LPSECURITY_ATTRIBUTES lpEventAttributes,
				_In_ BOOL bManualReset,
				_In_ BOOL bInitialState,
				_In_opt_ LPCSTR lpName
			),
			ALL_A(
				_In_opt_ LPSECURITY_ATTRIBUTES,
				_In_ BOOL,
				_In_ BOOL,
				_In_opt_ LPCSTR
			),
			ALL_A(_In_opt_ lpEventAttributes,
				_In_ bManualReset,
				_In_ bInitialState,
				_In_opt_ lpName
			));

	CREATE_CALL(SIZE_T, WINAPI, _VirtualQuery, XorStr("VirtualQuery"),
		ALL_A(_In_opt_ LPCVOID lpAddress,
			_Out_writes_bytes_to_(dwLength, return) PMEMORY_BASIC_INFORMATION lpBuffer,
			_In_ SIZE_T dwLength
		),
		ALL_A(_In_opt_ LPCVOID,
			_Out_writes_bytes_to_(dwLength, return) PMEMORY_BASIC_INFORMATION,
			_In_ SIZE_T
		),
		ALL_A(_In_opt_ lpAddress,
			_Out_writes_bytes_to_(dwLength, return) lpBuffer,
			_In_ dwLength
		));

	CREATE_CALL(HANDLE, WINAPI, _FindFirstFileA, XorStr("FindFirstFileA"),
		ALL_A(_In_ LPCSTR lpFileName,
			_Out_ LPWIN32_FIND_DATAA lpFindFileData
		),
		ALL_A(_In_ LPCSTR lpFileName,
			_Out_ LPWIN32_FIND_DATAA
		),
		ALL_A(_In_ lpFileName,
			_Out_ lpFindFileData
		));

	CREATE_CALL(BOOL, WINAPI, _FindNextFileA, XorStr("FindNextFileA"),
		ALL_A(_In_ HANDLE hFindFile,
			_Out_ LPWIN32_FIND_DATAA lpFindFileData
		),
		ALL_A(_In_ HANDLE,
			_Out_ LPWIN32_FIND_DATAA
		),
		ALL_A(_In_ hFindFile,
			_Out_ lpFindFileData
		));



	CREATE_CALL(VOID, WINAPI, _GetLocalTime, XorStr("GetLocalTime"),
		ALL_A(_Out_ LPSYSTEMTIME lpSystemTime
		),
		ALL_A(_Out_ LPSYSTEMTIME
		),
		ALL_A(_Out_ lpSystemTime
		));

	CREATE_CALL(VOID, WINAPI, _GetSystemTimeAsFileTime, XorStr("GetSystemTimeAsFileTime"),
		ALL_A(_Out_ LPFILETIME lpSystemTimeAsFileTime
		),
		ALL_A(_Out_ LPFILETIME
		),
		ALL_A(_Out_ lpSystemTimeAsFileTime
		));

	//=========================

	CREATE_CALL(DWORD, WINAPI, _GetFullPathNameA, XorStr("GetFullPathNameA"),
		ALL_A(_In_ LPCSTR lpFileName,
			_In_ DWORD nBufferLength,
			_Out_writes_to_opt_(nBufferLength, return +1) LPSTR lpBuffer,
			_Outptr_opt_ LPSTR* lpFilePart
		),
		ALL_A(_In_ LPCSTR,
			_In_ DWORD,
			_Out_writes_to_opt_(nBufferLength, return +1) LPSTR,
			_Outptr_opt_ LPSTR*
		),
		ALL_A(_In_ lpFileName,
			_In_ nBufferLength,
			_Out_writes_to_opt_(nBufferLength, return +1) lpBuffer,
			_Outptr_opt_ lpFilePart
		));

	CREATE_CALL(BOOL, WINAPI, _FindClose, XorStr("FindClose"),
		ALL_A(_Inout_ HANDLE hFindFile
		),
		ALL_A(_Inout_ HANDLE
		),
		ALL_A(_Inout_ hFindFile
		));


	CREATE_CALL(BOOL, WINAPI, _DeleteFileA, XorStr("DeleteFileA"),
		ALL_A(_In_ LPCSTR lpFileName
		),
		ALL_A(_In_ LPCSTR
		),
		ALL_A(_In_ lpFileName
		));

	CREATE_CALL(BOOL, WINAPI, _CreateDirectoryA, XorStr("CreateDirectoryA"),
		ALL_A(_In_ LPCSTR lpPathName,
			_In_opt_ LPSECURITY_ATTRIBUTES lpSecurityAttributes
		),
		ALL_A(_In_ LPCSTR,
			_In_opt_ LPSECURITY_ATTRIBUTES
		),
		ALL_A(_In_ lpPathName,
			_In_opt_ lpSecurityAttributes
		));

	CREATE_CALL(BOOL, WINAPI, _SetEndOfFile, XorStr("SetEndOfFile"),
		ALL_A(_In_ HANDLE hFile
		),
		ALL_A(_In_ HANDLE
		),
		ALL_A(_In_ hFile
		));

	CREATE_CALL(HANDLE, WINAPI, _CreateFileW, XorStr("CreateFileW"),
		ALL_A(_In_ LPCWSTR lpFileName,
			_In_ DWORD dwDesiredAccess,
			_In_ DWORD dwShareMode,
			_In_opt_ LPSECURITY_ATTRIBUTES lpSecurityAttributes,
			_In_ DWORD dwCreationDisposition,
			_In_ DWORD dwFlagsAndAttributes,
			_In_opt_ HANDLE hTemplateFile
		),
		ALL_A(_In_ LPCWSTR,
			_In_ DWORD,
			_In_ DWORD,
			_In_opt_ LPSECURITY_ATTRIBUTES,
			_In_ DWORD,
			_In_ DWORD,
			_In_opt_ HANDLE
		),
		ALL_A(_In_ lpFileName,
			_In_ dwDesiredAccess,
			_In_ dwShareMode,
			_In_opt_ lpSecurityAttributes,
			_In_ dwCreationDisposition,
			_In_ dwFlagsAndAttributes,
			_In_opt_ hTemplateFile
		));

	CREATE_CALL(BOOL, WINAPI, _FindNextFileW, XorStr("FindNextFileW"),
		ALL_A(_In_ HANDLE hFindFile,
			_Out_ LPWIN32_FIND_DATAW lpFindFileData
		),
		ALL_A(_In_ HANDLE,
			_Out_ LPWIN32_FIND_DATAW
		),
		ALL_A(_In_ hFindFile,
			_Out_ lpFindFileData
		));

	CREATE_CALL(HANDLE, WINAPI, _FindFirstFileExW, XorStr("FindFirstFileExW"),
		ALL_A(_In_ LPCWSTR lpFileName,
			_In_ FINDEX_INFO_LEVELS fInfoLevelId,
			_Out_writes_bytes_(sizeof(WIN32_FIND_DATAW)) LPVOID lpFindFileData,
			_In_ FINDEX_SEARCH_OPS fSearchOp,
			_Reserved_ LPVOID lpSearchFilter,
			_In_ DWORD dwAdditionalFlags
		),
		ALL_A(_In_ LPCWSTR,
			_In_ FINDEX_INFO_LEVELS,
			_Out_writes_bytes_(sizeof(WIN32_FIND_DATAW)) LPVOID,
			_In_ FINDEX_SEARCH_OPS,
			_Reserved_ LPVOID,
			_In_ DWORD
		),
		ALL_A(_In_ lpFileName,
			_In_ fInfoLevelId,
			_Out_writes_bytes_(sizeof(WIN32_FIND_DATAW)) lpFindFileData,
			_In_ fSearchOp,
			_Reserved_ lpSearchFilter,
			_In_ dwAdditionalFlags
		));

	CREATE_CALL(BOOL, WINAPI, _SetFilePointerEx, XorStr("SetFilePointerEx"),
		ALL_A(_In_ HANDLE hFile,
			_In_ LARGE_INTEGER liDistanceToMove,
			_Out_opt_ PLARGE_INTEGER lpNewFilePointer,
			_In_ DWORD dwMoveMethod
		),
		ALL_A(_In_ HANDLE,
			_In_ LARGE_INTEGER,
			_Out_opt_ PLARGE_INTEGER,
			_In_ DWORD
		),
		ALL_A(_In_ hFile,
			_In_ liDistanceToMove,
			_Out_opt_ lpNewFilePointer,
			_In_ dwMoveMethod
		));

	CREATE_CALL(BOOL, WINAPI, _FlushFileBuffers, XorStr("FlushFileBuffers"),
		ALL_A(_In_ HANDLE hFile
		),
		ALL_A(_In_ HANDLE
		),
		ALL_A(_In_ hFile
		));

	CREATE_CALL(DWORD, WINAPI, _GetFileType, XorStr("GetFileType"),
		ALL_A(_In_ HANDLE hFile
		),
		ALL_A(_In_ HANDLE
		),
		ALL_A(_In_ hFile
		));

	CREATE_CALL(BOOL, WINAPI, _WriteFile, XorStr("WriteFile"),
		ALL_A(_In_ HANDLE hFile,
			_In_reads_bytes_opt_(nNumberOfBytesToWrite) LPCVOID lpBuffer,
			_In_ DWORD nNumberOfBytesToWrite,
			_Out_opt_ LPDWORD lpNumberOfBytesWritten,
			_Inout_opt_ LPOVERLAPPED lpOverlapped
		),
		ALL_A(_In_ HANDLE,
			_In_reads_bytes_opt_(nNumberOfBytesToWrite) LPCVOID,
			_In_ DWORD,
			_Out_opt_ LPDWORD,
			_Inout_opt_ LPOVERLAPPED
		),
		ALL_A(_In_ hFile,
			_In_reads_bytes_opt_(nNumberOfBytesToWrite) lpBuffer,
			_In_ nNumberOfBytesToWrite,
			_Out_opt_ lpNumberOfBytesWritten,
			_Inout_opt_ lpOverlapped
		));

	CREATE_CALL(BOOL, WINAPI, _ReadFile, XorStr("ReadFile"),
		ALL_A(_In_ HANDLE hFile,
			_Out_writes_bytes_to_opt_(nNumberOfBytesToRead, *lpNumberOfBytesRead) __out_data_source(FILE) LPVOID lpBuffer,
			_In_ DWORD nNumberOfBytesToRead,
			_Out_opt_ LPDWORD lpNumberOfBytesRead,
			_Inout_opt_ LPOVERLAPPED lpOverlapped
		),
		ALL_A(_In_ HANDLE,
			_Out_writes_bytes_to_opt_(nNumberOfBytesToRead, *lpNumberOfBytesRead) __out_data_source(FILE) LPVOID,
			_In_ DWORD,
			_Out_opt_ LPDWORD,
			_Inout_opt_ LPOVERLAPPED
		),
		ALL_A(_In_ hFile,
			_Out_writes_bytes_to_opt_(nNumberOfBytesToRead, *lpNumberOfBytesRead) __out_data_source(FILE) lpBuffer,
			_In_ nNumberOfBytesToRead,
			_Out_opt_ lpNumberOfBytesRead,
			_Inout_opt_ lpOverlapped
		));

	CREATE_CALL(INT, WINAPI, _lstrcmpiA, XorStr("lstrcmpiA"),
		ALL_A(_In_ LPCSTR lpString1,
			_In_ LPCSTR lpString2
		),
		ALL_A(_In_ LPCSTR,
			_In_ LPCSTR
		),
		ALL_A(_In_ lpString1,
			_In_ lpString2
		));

	//===========================================

	void test2()
	{
		//InitializeCriticalSection
		//InitializeCriticalSectionAndSpinCount
		//EnterCriticalSection
		//SetEvent

	}

	CREATE_CALL(VOID, WINAPI, _Sleep, XorStr("Sleep"),
		ALL_A(_In_ DWORD dwMilliseconds
		),
		ALL_A(_In_ DWORD
		),
		ALL_A(_In_ dwMilliseconds
		));

	CREATE_CALL(VOID, WINAPI, _EnterCriticalSection, XorStr("EnterCriticalSection"),
		ALL_A(_Inout_ LPCRITICAL_SECTION lpCriticalSection
		),
		ALL_A(_Inout_ LPCRITICAL_SECTION
		),
		ALL_A(_Inout_ lpCriticalSection
		));

	CREATE_CALL(VOID, WINAPI, _LeaveCriticalSection, XorStr("LeaveCriticalSection"),
		ALL_A(_Inout_ LPCRITICAL_SECTION lpCriticalSection
		),
		ALL_A(_Inout_ LPCRITICAL_SECTION
		),
		ALL_A(_Inout_ lpCriticalSection
		));

	CREATE_CALL(VOID, WINAPI, _DeleteCriticalSection, XorStr("DeleteCriticalSection"),
		ALL_A(_Inout_ LPCRITICAL_SECTION lpCriticalSection
		),
		ALL_A(_Inout_ LPCRITICAL_SECTION
		),
		ALL_A(_Inout_ lpCriticalSection
		));

	CREATE_CALL(BOOL, WINAPI, _InitializeCriticalSectionAndSpinCount, XorStr("InitializeCriticalSectionAndSpinCount"),
		ALL_A(_Out_ LPCRITICAL_SECTION lpCriticalSection,
			_In_ DWORD dwSpinCount
		),
		ALL_A(_Out_ LPCRITICAL_SECTION,
			_In_ DWORD
		),
		ALL_A(_Out_ lpCriticalSection,
			_In_ dwSpinCount
		));

	CREATE_CALL(HANDLE, WINAPI, _CreateEventW, XorStr("CreateEventW"),
		ALL_A(_In_opt_ LPSECURITY_ATTRIBUTES lpEventAttributes,
			_In_ BOOL bManualReset,
			_In_ BOOL bInitialState,
			_In_opt_ LPCWSTR lpName
		),
		ALL_A(_In_opt_ LPSECURITY_ATTRIBUTES,
			_In_ BOOL,
			_In_ BOOL,
			_In_opt_ LPCWSTR
		),
		ALL_A(_In_opt_ lpEventAttributes,
			_In_ bManualReset,
			_In_ bInitialState,
			_In_opt_ lpName
		));

	CREATE_CALL(VOID, WINAPI, _InitializeCriticalSection, XorStr("InitializeCriticalSection"),
		ALL_A(_Out_ LPCRITICAL_SECTION lpCriticalSection
		),
		ALL_A(_Out_ LPCRITICAL_SECTION
		),
		ALL_A(_Out_ lpCriticalSection
		));

	CREATE_CALL(BOOL, WINAPI, _SetEvent, XorStr("SetEvent"),
		ALL_A(_In_ HANDLE hEvent
		),
		ALL_A(_In_ HANDLE
		),
		ALL_A(_In_ hEvent
		));

	CREATE_CALL(BOOL, WINAPI, _ResetEvent, XorStr("ResetEvent"),
		ALL_A(_In_ HANDLE hEvent
		),
		ALL_A(_In_ HANDLE
		),
		ALL_A(_In_ hEvent
		));

	CREATE_CALL(DWORD, WINAPI, _WaitForSingleObjectEx, XorStr("WaitForSingleObjectEx"),
		ALL_A(_In_ HANDLE hHandle,
			_In_ DWORD dwMilliseconds,
			_In_ BOOL bAlertable
		),
		ALL_A(_In_ HANDLE,
			_In_ DWORD,
			_In_ BOOL
		),
		ALL_A(_In_ hHandle,
			_In_ dwMilliseconds,
			_In_ bAlertable
		));



	//===========================================

	CREATE_CALL(FARPROC, WINAPI, _GetProcAddress, XorStr("GetProcAddress"),
		ALL_A(_In_ HMODULE hModule,
			_In_ LPCSTR lpProcName
		),
		ALL_A(_In_ HMODULE,
			_In_ LPCSTR
		),
		ALL_A(_In_ hModule,
			_In_ lpProcName
		));

	CREATE_CALL(HMODULE, WINAPI, _GetModuleHandleW, XorStr("GetModuleHandleW"),
		ALL_A(_In_opt_ LPCWSTR lpModuleName
		),
		ALL_A(_In_opt_ LPCWSTR
		),
		ALL_A(_In_opt_ lpModuleName
		));

	CREATE_CALL(DWORD, WINAPI, _GetModuleFileNameA, XorStr("GetModuleFileNameA"),
		ALL_A(_In_opt_ HMODULE hModule,
			_Out_writes_to_(nSize, ((return < nSize) ? (return +1) : nSize)) LPSTR lpFilename,
			_In_ DWORD nSize
		),
		ALL_A(_In_opt_ HMODULE,
			_Out_writes_to_(nSize, ((return < nSize) ? (return +1) : nSize)) LPSTR,
			_In_ DWORD
		),
		ALL_A(_In_opt_ hModule,
			_Out_writes_to_(nSize, ((return < nSize) ? (return +1) : nSize)) lpFilename,
			_In_ nSize
		));

	CREATE_CALL(HMODULE, WINAPI, _GetModuleHandleA, XorStr("GetModuleHandleA"),
		ALL_A(_In_opt_ LPCSTR lpModuleName
		),
		ALL_A(_In_opt_ LPCSTR
		),
		ALL_A(_In_opt_ lpModuleName
		));

	CREATE_CALL(DWORD, WINAPI, _GetModuleFileNameW, XorStr("GetModuleFileNameW"),
		ALL_A(_In_opt_ HMODULE hModule,
			_Out_writes_to_(nSize, ((return < nSize) ? (return +1) : nSize)) LPWSTR lpFilename,
			_In_ DWORD nSize
		),
		ALL_A(_In_opt_ HMODULE,
			_Out_writes_to_(nSize, ((return < nSize) ? (return +1) : nSize)) LPWSTR,
			_In_ DWORD
		),
		ALL_A(_In_opt_ hModule,
			_Out_writes_to_(nSize, ((return < nSize) ? (return +1) : nSize)) lpFilename,
			_In_ nSize
		));

	CREATE_CALL(BOOL, WINAPI, _GetModuleHandleExW, XorStr("GetModuleHandleExW"),
		ALL_A(_In_ DWORD dwFlags,
			_In_opt_ LPCWSTR lpModuleName,
			_Out_ HMODULE* phModule
		),
		ALL_A(_In_ DWORD,
			_In_opt_ LPCWSTR,
			_Out_ HMODULE*
		),
		ALL_A(_In_ dwFlags,
			_In_opt_ lpModuleName,
			_Out_ phModule
		));

	CREATE_CALL(HMODULE, WINAPI, _LoadLibraryExW, XorStr("LoadLibraryExW"),
		ALL_A(_In_ LPCWSTR lpLibFileName,
			_Reserved_ HANDLE hFile,
			_In_ DWORD dwFlags
		),
		ALL_A(_In_ LPCWSTR,
			_Reserved_ HANDLE,
			_In_ DWORD
		),
		ALL_A(_In_ lpLibFileName,
			_Reserved_ hFile,
			_In_ dwFlags
		));

	CREATE_CALL(BOOL, WINAPI, _FreeLibrary, XorStr("FreeLibrary"),
		ALL_A(_In_ HMODULE hLibModule
		),
		ALL_A(_In_ HMODULE
		),
		ALL_A(_In_ hLibModule
		));

	CREATE_CALL(BOOL, WINAPI, _IsBadCodePtr, XorStr("IsBadCodePtr"),
		ALL_A(_In_opt_ FARPROC lpfn
		),
		ALL_A(_In_opt_ FARPROC
		),
		ALL_A(_In_opt_ lpfn
		));

	//CREATE_CALL(BOOL, WINAPI, _IsBadReadPtr, XorStr("IsBadReadPtr"),
	//    ALL_A(_In_opt_ CONST VOID *lp,
	//	    _In_ UINT_PTR ucb
	//    ),
	//    ALL_A(_In_opt_ CONST VOID,
	//	    _In_ UINT_PTR
	//    ),
	//    ALL_A(_In_opt_ CONST VOID lp,
	//	    _In_ ucb
	//    ));

	CREATE_CALL(HGLOBAL, WINAPI, _GlobalAlloc, XorStr("GlobalAlloc"),
		ALL_A(_In_ UINT uFlags,
			_In_ SIZE_T dwBytes
		),
		ALL_A(_In_ UINT,
			_In_ SIZE_T
		),
		ALL_A(_In_ uFlags,
			_In_ dwBytes
		));

	CREATE_CALL(LPVOID, WINAPI, _GlobalLock, XorStr("GlobalLock"),
		ALL_A(_In_ HGLOBAL hMem
		),
		ALL_A(_In_ HGLOBAL
		),
		ALL_A(_In_ hMem
		));

	CREATE_CALL(BOOL, WINAPI, _GlobalUnlock, XorStr("GlobalUnlock"),
		ALL_A(_In_ HGLOBAL hMem
		),
		ALL_A(_In_ HGLOBAL
		),
		ALL_A(_In_ hMem
		));

	CREATE_CALL(INT, WINAPI, _lstrlenA, XorStr("lstrlenA"),
		ALL_A(_In_ LPCSTR lpString
		),
		ALL_A(_In_ LPCSTR
		),
		ALL_A(_In_ lpString
		));

	CREATE_CALL(INT, WINAPI, _WideCharToMultiByte, XorStr("WideCharToMultiByte"),
		ALL_A(_In_ UINT CodePage,
			_In_ DWORD dwFlags,
			_In_NLS_string_(cchWideChar) LPCWCH lpWideCharStr,
			_In_ int cchWideChar,
			_Out_writes_bytes_to_opt_(cbMultiByte, return) LPSTR lpMultiByteStr,
			_In_ int cbMultiByte,
			_In_opt_ LPCCH lpDefaultChar,
			_Out_opt_ LPBOOL lpUsedDefaultChar
		),
		ALL_A(_In_ UINT,
			_In_ DWORD,
			_In_NLS_string_(cchWideChar) LPCWCH,
			_In_ int,
			_Out_writes_bytes_to_opt_(cbMultiByte, return) LPSTR,
			_In_ int,
			_In_opt_ LPCCH,
			_Out_opt_ LPBOOL
		),
		ALL_A(_In_ CodePage,
			_In_ dwFlags,
			_In_NLS_string_(cchWideChar) lpWideCharStr,
			_In_ cchWideChar,
			_Out_writes_bytes_to_opt_(cbMultiByte, return) lpMultiByteStr,
			_In_ cbMultiByte,
			_In_opt_ lpDefaultChar,
			_Out_opt_ lpUsedDefaultChar
		));

	CREATE_CALL(BOOL, WINAPI, _GetStringTypeW, XorStr("GetStringTypeW"),
		ALL_A(_In_ DWORD dwInfoType,
			_In_NLS_string_(cchSrc) LPCWCH lpSrcStr,
			_In_ int cchSrc,
			_Out_ LPWORD lpCharType
		),
		ALL_A(_In_ DWORD,
			_In_NLS_string_(cchSrc) LPCWCH,
			_In_ int,
			_Out_ LPWORD
		),
		ALL_A(_In_ dwInfoType,
			_In_NLS_string_(cchSrc) lpSrcStr,
			_In_ cchSrc,
			_Out_ lpCharType
		));

	CREATE_CALL(INT, WINAPI, _CompareStringW, XorStr("CompareStringW"),
		ALL_A(_In_ LCID Locale,
			_In_ DWORD dwCmpFlags,
			_In_NLS_string_(cchCount1) PCNZWCH lpString1,
			_In_ int cchCount1,
			_In_NLS_string_(cchCount2) PCNZWCH lpString2,
			_In_ int cchCount2
		),
		ALL_A(_In_ LCID,
			_In_ DWORD,
			_In_NLS_string_(cchCount1) PCNZWCH,
			_In_ int,
			_In_NLS_string_(cchCount2) PCNZWCH,
			_In_ int
		),
		ALL_A(_In_ Locale,
			_In_ dwCmpFlags,
			_In_NLS_string_(cchCount1) lpString1,
			_In_ cchCount1,
			_In_NLS_string_(cchCount2) lpString2,
			_In_ cchCount2
		));


	CREATE_CALL(PVOID, WINAPI, _AddVectoredExceptionHandler, XorStr("AddVectoredExceptionHandler"),
		ALL_A(_In_ ULONG First,
			_In_ PVECTORED_EXCEPTION_HANDLER Handler
		),
		ALL_A(_In_ ULONG,
			_In_ PVECTORED_EXCEPTION_HANDLER
		),
		ALL_A(_In_ First,
			_In_ Handler
		));

	/*CREATE_CALL(VOID, WINAPI, _RaiseException, XorStr("RaiseException"),
		ALL_A(_In_ DWORD dwExceptionCode,
			_In_ DWORD dwExceptionFlags,
			_In_ DWORD nNumberOfArguments,
			_In_reads_opt_(nNumberOfArguments) CONST ULONG_PTR* lpArguments
		),
		ALL_A(_In_ DWORD,
			_In_ DWORD,
			_In_ DWORD,
			_In_reads_opt_(nNumberOfArguments) CONST ULONG_PTR*
		),
		ALL_A(_In_ dwExceptionCode,
			_In_ dwExceptionFlags,
			_In_ nNumberOfArguments,
			_In_reads_opt_(nNumberOfArguments) CONST lpArguments
		));*/

	CREATE_CALL(VOID, WINAPI, _SetLastError, XorStr("SetLastError"),
		ALL_A(_In_ DWORD dwErrCode
		),
		ALL_A(_In_ DWORD
		),
		ALL_A(_In_ dwErrCode
		));

	//CREATE_CALL(LONG, WINAPI, _UnhandledExceptionFilter, XorStr("UnhandledExceptionFilter"),
	//	ALL_A(_In_ struct _EXCEPTION_POINTERS* ExceptionInfo
	//	),
	//	ALL_A(_In_ struct _EXCEPTION_POINTERS*
	//	),
	//	ALL_A(_In_ struct ExceptionInfo
	//	));

	//CREATE_CALL(RETLIF_NOITP, WINAPI, _SetUnhandledExceptionFilter, XorStr("SetUnhandledExceptionFilter"),
	//	ALL_A(_In_opt_ LPTOP_LEVEL_EXCEPTION_FILTER lpTopLevelExceptionFilter
	//	),
	//	ALL_A(_In_opt_ LPTOP_LEVEL_EXCEPTION_FILTER
	//	),
	//	ALL_A(_In_opt_ lpTopLevelExceptionFilter
	//	));

	CREATE_CALL(BOOL, WINAPI, _Beep, XorStr("Beep"),
		ALL_A(_In_ DWORD dwFreq,
			_In_ DWORD dwDuration
		),
		ALL_A(_In_ DWORD,
			_In_ DWORD
		),
		ALL_A(_In_ dwFreq,
			_In_ dwDuration
		));

	CREATE_CALL(PVOID, WINAPI, _EncodePointer, XorStr("EncodePointer"),
		ALL_A(_In_opt_ PVOID Ptr
		),
		ALL_A(_In_opt_ PVOID
		),
		ALL_A(_In_opt_ Ptr
		));

	CREATE_CALL(PVOID, WINAPI, _DecodePointer, XorStr("DecodePointer"),
		ALL_A(_In_opt_ PVOID Ptr
		),
		ALL_A(_In_opt_ PVOID
		),
		ALL_A(_In_opt_ Ptr
		));


	CREATE_CALL(HANDLE, WINAPI, _GetCurrentThread, XorStr("GetCurrentThread"),
		ALL_A(
		),
		ALL_A(
		),
		ALL_A(
		));

	CREATE_CALL(BOOL, WINAPI, _TerminateProcess, XorStr("TerminateProcess"),
		ALL_A(_In_ HANDLE hProcess,
			_In_ UINT uExitCode
		),
		ALL_A(_In_ HANDLE,
			_In_ UINT
		),
		ALL_A(_In_ hProcess,
			_In_ uExitCode
		));

	CREATE_CALL(HANDLE, WINAPI, _GetCurrentProcess, XorStr("GetCurrentProcess"),
		ALL_A(
		),
		ALL_A(
		),
		ALL_A(
		));

	CREATE_CALL(VOID, WINAPI, _ExitProcess, XorStr("ExitProcess"),
		ALL_A(_In_ UINT uExitCode
		),
		ALL_A(_In_ UINT
		),
		ALL_A(_In_ uExitCode
		));

	CREATE_CALL(DWORD, WINAPI, _GetCurrentThreadId, XorStr("GetCurrentThreadId"),
		ALL_A(
		),
		ALL_A(
		),
		ALL_A(
		));

	CREATE_CALL(BOOL, WINAPI, _SwitchToThread, XorStr("SwitchToThread"),
		ALL_A(
		),
		ALL_A(
		),
		ALL_A(
		));

	CREATE_CALL(DWORD, WINAPI, _TlsAlloc, XorStr("TlsAlloc"),
		ALL_A(
		),
		ALL_A(
		),
		ALL_A(
		));

	CREATE_CALL(LPVOID, WINAPI, _TlsGetValue, XorStr("TlsGetValue"),
		ALL_A(_In_ DWORD dwTlsIndex
		),
		ALL_A(_In_ DWORD
		),
		ALL_A(_In_ dwTlsIndex
		));

	CREATE_CALL(BOOL, WINAPI, _TlsSetValue, XorStr("TlsSetValue"),
		ALL_A(_In_ DWORD dwTlsIndex,
			_In_opt_ LPVOID lpTlsValue
		),
		ALL_A(_In_ DWORD,
			_In_opt_ LPVOID
		),
		ALL_A(_In_ dwTlsIndex,
			_In_opt_ lpTlsValue
		));

	CREATE_CALL(BOOL, WINAPI, _TlsFree, XorStr("TlsFree"),
		ALL_A(_In_ DWORD dwTlsIndex
		),
		ALL_A(_In_ DWORD
		),
		ALL_A(_In_ dwTlsIndex
		));

	CREATE_CALL(BOOL, WINAPI, _IsProcessorFeaturePresent, XorStr("IsProcessorFeaturePresent"),
		ALL_A(_In_ DWORD ProcessorFeature
		),
		ALL_A(_In_ DWORD
		),
		ALL_A(_In_ ProcessorFeature
		));

	CREATE_CALL(VOID, WINAPI, _GetStartupInfoW, XorStr("GetStartupInfoW"),
		ALL_A(_Out_ LPSTARTUPINFOW lpStartupInfo
		),
		ALL_A(_Out_ LPSTARTUPINFOW
		),
		ALL_A(_Out_ lpStartupInfo
		));

	CREATE_CALL(DWORD, WINAPI, _GetCurrentProcessId, XorStr("GetCurrentProcessId"),
		ALL_A(
		),
		ALL_A(
		),
		ALL_A(
		));


	CREATE_CALL(BOOL, WINAPI, _QueryPerformanceFrequency, XorStr("QueryPerformanceFrequency"),
		ALL_A(_Out_ LARGE_INTEGER* lpFrequency
		),
		ALL_A(_Out_ LARGE_INTEGER*
		),
		ALL_A(_Out_ lpFrequency
		));

	CREATE_CALL(BOOL, WINAPI, _QueryPerformanceCounter, XorStr("QueryPerformanceCounter"),
		ALL_A(_Out_ LARGE_INTEGER* lpPerformanceCount
		),
		ALL_A(_Out_ LARGE_INTEGER*
		),
		ALL_A(_Out_ lpPerformanceCount
		));


	CREATE_CALL(SIZE_T, WINAPI, _HeapSize, XorStr("HeapSize"),
		ALL_A(_In_ HANDLE hHeap,
			_In_ DWORD dwFlags,
			_In_ LPCVOID lpMem
		),
		ALL_A(_In_ HANDLE,
			_In_ DWORD,
			_In_ LPCVOID
		),
		ALL_A(_In_ hHeap,
			_In_ dwFlags,
			_In_ lpMem
		));

	CREATE_CALL(HANDLE, WINAPI, _GetProcessHeap, XorStr("GetProcessHeap"),
		ALL_A(
		),
		ALL_A(
		),
		ALL_A(
		));

	CREATE_CALL(LPVOID, WINAPI, _HeapAlloc, XorStr("HeapAlloc"),
		ALL_A(_In_ HANDLE hHeap,
			_In_ DWORD dwFlags,
			_In_ SIZE_T dwBytes
		),
		ALL_A(_In_ HANDLE,
			_In_ DWORD,
			_In_ SIZE_T
		),
		ALL_A(_In_ hHeap,
			_In_ dwFlags,
			_In_ dwBytes
		));

	CREATE_CALL(LPVOID, WINAPI, _HeapReAlloc, XorStr("HeapReAlloc"),
		ALL_A(_Inout_ HANDLE hHeap,
			_In_ DWORD dwFlags,
			_Frees_ptr_opt_ LPVOID lpMem,
			_In_ SIZE_T dwBytes
		),
		ALL_A(_Inout_ HANDLE,
			_In_ DWORD,
			_Frees_ptr_opt_ LPVOID,
			_In_ SIZE_T
		),
		ALL_A(_Inout_ hHeap,
			_In_ dwFlags,
			_Frees_ptr_opt_ lpMem,
			_In_ dwBytes
		));

	CREATE_CALL(BOOL, WINAPI, _HeapFree, XorStr("HeapFree"),
		ALL_A(_Inout_ HANDLE hHeap,
			_In_ DWORD dwFlags,
			__drv_freesMem(Mem) _Frees_ptr_opt_ LPVOID lpMem
		),
		ALL_A(_Inout_ HANDLE,
			_In_ DWORD,
			__drv_freesMem(Mem) _Frees_ptr_opt_ LPVOID
		),
		ALL_A(_Inout_ hHeap,
			_In_ dwFlags,
			__drv_freesMem(Mem) _Frees_ptr_opt_ lpMem
		));


	CREATE_CALL(LONG, WINAPI, _SetWindowLongA, XorStr("SetWindowLongA"),
		ALL_A(_In_ HWND hWnd,
			_In_ int nIndex,
			_In_ LONG dwNewLong
		),
		ALL_A(_In_ HWND,
			_In_ int,
			_In_ LONG
		),
		ALL_A(_In_ hWnd,
			_In_ nIndex,
			_In_ dwNewLong
		));

	CREATE_CALL(SHORT, WINAPI, _GetKeyState, XorStr("GetKeyState"),
		ALL_A(_In_ int nVirtKey
		),
		ALL_A(_In_ int
		),
		ALL_A(_In_ nVirtKey
		));

	CREATE_CALL(HANDLE, WINAPI, _GetClipboardData, XorStr("GetClipboardData"),
		ALL_A(_In_ UINT uFormat
		),
		ALL_A(_In_ UINT
		),
		ALL_A(_In_ uFormat
		));

	CREATE_CALL(BOOL, WINAPI, _OpenClipboard, XorStr("OpenClipboard"),
		ALL_A(_In_opt_ HWND hWndNewOwner
		),
		ALL_A(_In_opt_ HWND
		),
		ALL_A(_In_opt_ hWndNewOwner
		));

	CREATE_CALL(BOOL, WINAPI, _CloseClipboard, XorStr("CloseClipboard"),
		ALL_A(
		),
		ALL_A(
		),
		ALL_A(
		));

	CREATE_CALL(SHORT, WINAPI, _GetAsyncKeyState, XorStr("GetAsyncKeyState"),
		ALL_A(_In_ int vKey
		),
		ALL_A(_In_ int
		),
		ALL_A(_In_ vKey
		));

	CREATE_CALL(BOOL, WINAPI, _GetCursorPos, XorStr("GetCursorPos"),
		ALL_A(_Out_ LPPOINT lpPoint
		),
		ALL_A(_Out_ LPPOINT
		),
		ALL_A(_Out_ lpPoint
		));

	CREATE_CALL(HANDLE, WINAPI, _SetClipboardData, XorStr("SetClipboardData"),
		ALL_A(_In_ UINT uFormat,
			_In_opt_ HANDLE hMem
		),
		ALL_A(_In_ UINT,
			_In_opt_ HANDLE
		),
		ALL_A(_In_ uFormat,
			_In_opt_ hMem
		));

	CREATE_CALL(BOOL, WINAPI, _EmptyClipboard, XorStr("EmptyClipboard"),
		ALL_A(
		),
		ALL_A(
		),
		ALL_A(
		));

	CREATE_CALL(LRESULT, WINAPI, _CallWindowProcA, XorStr("CallWindowProcA"),
		ALL_A(_In_ WNDPROC lpPrevWndFunc,
			_In_ HWND hWnd,
			_In_ UINT Msg,
			_In_ WPARAM wParam,
			_In_ LPARAM lParam
		),
		ALL_A(_In_ WNDPROC,
			_In_ HWND,
			_In_ UINT,
			_In_ WPARAM,
			_In_ LPARAM
		),
		ALL_A(_In_ lpPrevWndFunc,
			_In_ hWnd,
			_In_ Msg,
			_In_ wParam,
			_In_ lParam
		));

	CREATE_CALL(BOOL, WINAPI, _DestroyWindow, XorStr("DestroyWindow"),
		ALL_A(_In_ HWND hWnd
		),
		ALL_A(_In_ HWND 
		),
		ALL_A(_In_ hWnd
		));
};
